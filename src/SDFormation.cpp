#include "plugin.hpp"
#include "SDSharedComponents.hpp"

#define SIZE 8

struct SDFormation : Module {
    enum ParamIds {
        DIRECTION_PARAM,
        SPREAD_PARAM,
        SPREADCV_PARAM,
        TILT_PARAM,
        TILTCV_PARAM,
        RANDOM_PARAM,
        RANDOMCV_PARAM,
        OFFSET_PARAM,
        GAIN_PARAM,
        NUM_PARAMS
    };
    enum InputIds {
        SPREADCV_INPUT,
        TILTCV_INPUT,
        TRIGGER_INPUT,
        RANDOMCV_INPUT,
        INPUT_INPUT,
        NUM_INPUTS
    };
    enum OutputIds {
        OUTPUT_OUTPUT,
        REVERSE_OUTPUT,
        NUM_OUTPUTS
    };
    enum LightIds {
        NUM_LIGHTS
    };

    const float tiltMin = 0.255f;
    
    // the total number of tilt deltas to be added
    // the formula is (N * (N + 2)) / 4, where N is SIZE - 3
    // because there are SIZE - 1 gaps that the tilt deltas should be distributed across
    // and the 1st / last gaps will be set to tiltMin without the tild delta added
    const float tiltCount = round((SIZE - 3) * (SIZE - 3 + 2) / 4.f);
    const float tiltFactor = ((1.f - tiltMin) * (SIZE - 1.f)) / tiltCount;
    
    dsp::SchmittTrigger trigIn;
    float randoms[SIZE] = { 0.f };

    SDFormation() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        
        configParam(GAIN_PARAM, -1.f, 1.f, 1.f, "Input Gain");
        getParamQuantity(GAIN_PARAM)->randomizeEnabled = false;
        configParam(OFFSET_PARAM, -10.f, 10.f, 0.f, "CV Offset");

        configParam(SPREAD_PARAM, -1.4f, 1.4f, 0.f, "Spread");
        configParam(SPREADCV_PARAM, -1.f, 1.f, 0.f, "Spread CV Level");
        getParamQuantity(SPREADCV_PARAM)->randomizeEnabled = false;
        configInput(SPREADCV_INPUT, "Spread CV");
        configSwitch(DIRECTION_PARAM, 0.0, 2.0, 1.0, "Direction", {"Down", "Center", "Up"});
        
        configParam(TILT_PARAM, -1.f, 1.f, 0.f, "Tilt");
        configParam(TILTCV_PARAM, -1.f, 1.f, 0.f, "Tilt CV Level");
        getParamQuantity(TILTCV_PARAM)->randomizeEnabled = false;
        configInput(TILTCV_INPUT, "Tilt CV");
        
        configParam(RANDOM_PARAM, -1.f, 1.f, 0.f, "Random");
        configParam(RANDOMCV_PARAM, -1.f, 1.f, 0.f, "Random CV Level");
        getParamQuantity(RANDOMCV_PARAM)->randomizeEnabled = false;
        configInput(RANDOMCV_INPUT, "Random CV");
        configInput(TRIGGER_INPUT, "Trigger New Random");
        
        configInput(INPUT_INPUT, "Input");
        configOutput(OUTPUT_OUTPUT, "Poly");
        configOutput(REVERSE_OUTPUT, "Reversed Poly");
    }
    
    float getCombinedValue(int param, int cv, int input) {
        float min = paramQuantities[param]->minValue;
        float max = paramQuantities[param]->maxValue;
        float i = inputs[input].getVoltage() * params[cv].getValue() * (max - min) / 10.f + params[param].getValue();

        if (min > max) {
            float t = min;
            min = max;
            max = t;
        }
        if (i < min) i = min; else if (i > max) i = max;

        return i;
    }

    void process(const ProcessArgs &args) override {
        float voltage = inputs[INPUT_INPUT].getVoltage() * params[GAIN_PARAM].getValue() + params[OFFSET_PARAM].getValue();
        
        float spread = getCombinedValue(SPREAD_PARAM, SPREADCV_PARAM, SPREADCV_INPUT);
        float tilt = spread * getCombinedValue(TILT_PARAM, TILTCV_PARAM, TILTCV_INPUT);
        float random = getCombinedValue(RANDOM_PARAM, RANDOMCV_PARAM, RANDOMCV_INPUT);
        
        int trigger = 0;
        if (inputs[TRIGGER_INPUT].active) {
            trigger = trigIn.process(rescale(inputs[TRIGGER_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f));
        }
        if (trigger) {
            for (int i = 0; i < SIZE; i++) randoms[i] = random::get<float>();
        }
        
        float voltage_i;
        
        if (params[DIRECTION_PARAM].getValue() == 2) { // up

            voltage_i = voltage;
            for (int i = 0; i < SIZE; i++) {
                if (i) voltage_i += spread + (SIZE - i * 2.f) / SIZE * tilt;
                
                outputs[OUTPUT_OUTPUT].setVoltage(voltage_i + randoms[i] * random, i);
                outputs[REVERSE_OUTPUT].setVoltage(voltage_i + randoms[i] * random, SIZE - 1 - i);
            }
            
        } else if (params[DIRECTION_PARAM].getValue() == 1) { // center

            voltage_i = voltage - (SIZE - 1) / 2.f * spread;
            float factor;
            for (int i = 0; i < SIZE; i++) {
                factor = (tiltMin + tiltFactor * (SIZE / 2 - 1 - abs(i - SIZE / 2))) - 1;
                if (i) voltage_i += spread + tilt * factor;
                outputs[OUTPUT_OUTPUT].setVoltage(voltage_i + (randoms[i] - 0.5f) * random, i);
                outputs[REVERSE_OUTPUT].setVoltage(voltage_i + (randoms[i] - 0.5f) * random, SIZE - 1 - i);
            }
            
        } else { // down

            voltage_i = voltage;
            for (int i = 0; i < SIZE; i++) {
                if (i) voltage_i -= spread + (SIZE - i * 2.f) / SIZE * tilt;
                outputs[OUTPUT_OUTPUT].setVoltage(voltage_i - randoms[i] * random, i);
                outputs[REVERSE_OUTPUT].setVoltage(voltage_i - randoms[i] * random, SIZE - 1 - i);
            }
        }

        outputs[OUTPUT_OUTPUT].setChannels(SIZE);
        outputs[REVERSE_OUTPUT].setChannels(SIZE);
    }

    json_t* dataToJson() override {
        json_t* randomsJ = json_array();
        for (int i = 0; i < SIZE; i++) json_array_insert_new(randomsJ, i, json_real(randoms[i]));
        
        json_t* rootJ = json_object();
        json_object_set_new(rootJ, "randoms", randomsJ);

        return rootJ;
    }

    void dataFromJson(json_t* rootJ) override {
        json_t* randomsJ = json_object_get(rootJ, "randoms");
        if (randomsJ) {
            for (int i = 0; i < SIZE; i++) {
                json_t* randomJ = json_array_get(randomsJ, i);
                if (randomJ) randoms[i] = json_number_value(randomJ);
            }
        }
    }
};


struct SDFormationWidget : ModuleWidget {
    SDFormationWidget(SDFormation *module) {
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SDFormation.svg")));

        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(9.85, 16.411)), module, SDFormation::GAIN_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(25.71, 16.411)), module, SDFormation::OFFSET_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(17.78, 36.021)), module, SDFormation::SPREAD_PARAM));
        addParam(createParam<SDThreeSwitch>(mm2px(Vec(4.074, 41.902)), module, SDFormation::DIRECTION_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(17.78, 55.631)), module, SDFormation::TILT_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(25.71, 76.215)), module, SDFormation::RANDOM_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(6.597, 93.373)), module, SDFormation::SPREADCV_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(17.78, 93.373)), module, SDFormation::TILTCV_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(28.963, 93.373)), module, SDFormation::RANDOMCV_PARAM));

        addInput(createInputCentered<SDMonoPort>(mm2px(Vec(9.85, 77.203)), module, SDFormation::TRIGGER_INPUT));
        addInput(createInputCentered<SDMonoPort>(mm2px(Vec(6.597, 104.61)), module, SDFormation::SPREADCV_INPUT));
        addInput(createInputCentered<SDMonoPort>(mm2px(Vec(17.78, 104.61)), module, SDFormation::TILTCV_INPUT));
        addInput(createInputCentered<SDMonoPort>(mm2px(Vec(28.963, 104.61)), module, SDFormation::RANDOMCV_INPUT));
        addInput(createInputCentered<SDMonoPort>(mm2px(Vec(6.597, 119.319)), module, SDFormation::INPUT_INPUT));

        addOutput(createOutputCentered<SDPolyPort>(mm2px(Vec(17.78, 119.318)), module, SDFormation::OUTPUT_OUTPUT));
        addOutput(createOutputCentered<SDPolyPort>(mm2px(Vec(28.963, 119.319)), module, SDFormation::REVERSE_OUTPUT));
    }
};

Model *modelSDFormation = createModel<SDFormation, SDFormationWidget>("SDFormation");
