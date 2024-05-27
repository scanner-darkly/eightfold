#include "plugin.hpp"
#include "SDSharedComponents.hpp"

#define CHANNEL_COUNT 8

struct SDComparator : Module {
    enum ParamId {
        LEVEL1_PARAM,
        LEVEL2_PARAM,
        LEVEL3_PARAM,
        LEVEL4_PARAM,
        LEVEL5_PARAM,
        LEVEL6_PARAM,
        LEVEL7_PARAM,
        LEVEL8_PARAM,
        DOT_PARAM,
        PARAMS_LEN
    };
    enum InputId {
        LEVELS_INPUT,
        INPUT_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        GATE1_OUTPUT,
        GATE2_OUTPUT,
        GATE3_OUTPUT,
        GATE4_OUTPUT,
        GATE5_OUTPUT,
        GATE6_OUTPUT,
        GATE7_OUTPUT,
        GATE8_OUTPUT,
        OUTPUT_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        GATEON1_LIGHT,
        GATEON2_LIGHT,
        GATEON3_LIGHT,
        GATEON4_LIGHT,
        GATEON5_LIGHT,
        GATEON6_LIGHT,
        GATEON7_LIGHT,
        GATEON8_LIGHT,
        LIGHTS_LEN
    };

    SDComparator() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        
        configParam(LEVEL1_PARAM, -10.f, 10.f, 0.f, "Threshold Level 1");
        configParam(LEVEL2_PARAM, -10.f, 10.f, 0.f, "Threshold Level 2");
        configParam(LEVEL3_PARAM, -10.f, 10.f, 0.f, "Threshold Level 3");
        configParam(LEVEL4_PARAM, -10.f, 10.f, 0.f, "Threshold Level 4");
        configParam(LEVEL5_PARAM, -10.f, 10.f, 0.f, "Threshold Level 5");
        configParam(LEVEL6_PARAM, -10.f, 10.f, 0.f, "Threshold Level 6");
        configParam(LEVEL7_PARAM, -10.f, 10.f, 0.f, "Threshold Level 7");
        configParam(LEVEL8_PARAM, -10.f, 10.f, 0.f, "Threshold Level 8");
        
        configSwitch(DOT_PARAM, 0.0, 1.0, 0.0, "Dot Mode", {"On", "Off"});
        getParamQuantity(DOT_PARAM)->randomizeEnabled = false;
        
        configInput(LEVELS_INPUT, "Threshold Levels");
        configInput(INPUT_INPUT, "Input");
        
        configOutput(GATE1_OUTPUT, "Gate 1");
        configOutput(GATE2_OUTPUT, "Gate 2");
        configOutput(GATE3_OUTPUT, "Gate 3");
        configOutput(GATE4_OUTPUT, "Gate 4");
        configOutput(GATE5_OUTPUT, "Gate 5");
        configOutput(GATE6_OUTPUT, "Gate 6");
        configOutput(GATE7_OUTPUT, "Gate 7");
        configOutput(GATE8_OUTPUT, "Gate 8");
        
        configOutput(OUTPUT_OUTPUT, "Output");

        configLight(GATEON1_LIGHT, "Gate 1");
        configLight(GATEON2_LIGHT, "Gate 2");
        configLight(GATEON3_LIGHT, "Gate 3");
        configLight(GATEON4_LIGHT, "Gate 4");
        configLight(GATEON5_LIGHT, "Gate 5");
        configLight(GATEON6_LIGHT, "Gate 6");
        configLight(GATEON7_LIGHT, "Gate 7");
        configLight(GATEON8_LIGHT, "Gate 8");
    }

    void process(const ProcessArgs& args) override {

        bool gates[CHANNEL_COUNT];
        float level, voltage, highest;
        voltage = inputs[INPUT_INPUT].getVoltage();
        
        highest = -100.f;
        int highest_index = -1;
        bool higher;
        
        int level_count = inputs[LEVELS_INPUT].getChannels();
        
        for (int i = 0; i < CHANNEL_COUNT; i++) {
            level = (i < level_count ? inputs[LEVELS_INPUT].getVoltage(i) : 0.f) + params[LEVEL1_PARAM + i].getValue();
            higher = voltage >= level;
            
            gates[i] = higher;
            if (higher && level > highest) {
                highest_index = i;
                highest = level;
            }
        }
        
        if (params[DOT_PARAM].getValue() == 1) { // dot
            for (int i = 0; i < CHANNEL_COUNT; i++) {
                lights[GATEON1_LIGHT + i].setBrightness(i == highest_index ? 1.f : 0.f);
                outputs[GATE1_OUTPUT + i].setVoltage(i == highest_index ? 10.f : 0.f);
                outputs[OUTPUT_OUTPUT].setVoltage(i == highest_index ? 10.f : 0.f, i);
            }
        } else { // bar
            for (int i = 0; i < CHANNEL_COUNT; i++) {
                lights[GATEON1_LIGHT + i].setBrightness(gates[i] ? 1.f : 0.f);
                outputs[GATE1_OUTPUT + i].setVoltage(gates[i] ? 10.f : 0.f);
                outputs[OUTPUT_OUTPUT].setVoltage(gates[i] ? 10.f : 0.f, i);
            }
        }

        outputs[OUTPUT_OUTPUT].setChannels(CHANNEL_COUNT);
    }
};


struct SDComparatorWidget : ModuleWidget {
    SDComparatorWidget(SDComparator* module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/SDComparator.svg")));

        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(6.271, 13.126)), module, SDComparator::LEVEL1_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(6.271, 24.148)), module, SDComparator::LEVEL2_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(6.271, 35.17)), module, SDComparator::LEVEL3_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(6.271, 46.192)), module, SDComparator::LEVEL4_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(6.271, 57.214)), module, SDComparator::LEVEL5_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(6.271, 68.236)), module, SDComparator::LEVEL6_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(6.271, 79.258)), module, SDComparator::LEVEL7_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(6.271, 90.28)), module, SDComparator::LEVEL8_PARAM));
        addParam(createParam<SDTwoSwitch>(mm2px(Vec(15.541, 101.089)), module, SDComparator::DOT_PARAM));

        addInput(createInputCentered<SDPolyInPort>(mm2px(Vec(6.651, 104.61)), module, SDComparator::LEVELS_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(6.651, 119.319)), module, SDComparator::INPUT_INPUT));

        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(18.749, 13.126)), module, SDComparator::GATE1_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(18.749, 24.148)), module, SDComparator::GATE2_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(18.749, 35.17)), module, SDComparator::GATE3_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(18.749, 46.192)), module, SDComparator::GATE4_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(18.749, 57.214)), module, SDComparator::GATE5_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(18.749, 68.236)), module, SDComparator::GATE6_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(18.749, 79.258)), module, SDComparator::GATE7_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(18.749, 90.28)), module, SDComparator::GATE8_OUTPUT));
        addOutput(createOutputCentered<SDPolyOutPort>(mm2px(Vec(17.836, 119.318)), module, SDComparator::OUTPUT_OUTPUT));

        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 13.126)), module, SDComparator::GATEON1_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 24.148)), module, SDComparator::GATEON2_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 35.17)), module, SDComparator::GATEON3_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 46.192)), module, SDComparator::GATEON4_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 57.214)), module, SDComparator::GATEON5_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 68.236)), module, SDComparator::GATEON6_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 79.258)), module, SDComparator::GATEON7_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 90.28)), module, SDComparator::GATEON8_LIGHT));
    }
};

Model* modelSDComparator = createModel<SDComparator, SDComparatorWidget>("SDComparator");
