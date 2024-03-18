#include "plugin.hpp"


struct SDFormation : Module {
    enum ParamId {
        GAIN_PARAM,
        OFFSET_PARAM,
        SPREAD_PARAM,
        DIRECTION_PARAM,
        TILT_PARAM,
        RANDOM_PARAM,
        SPREADCV_PARAM,
        TILTCV_PARAM,
        RANDOMCV_PARAM,
        PARAMS_LEN
    };
    enum InputId {
        TRIGGER_INPUT,
        SPREADCV_INPUT,
        TILTCV_INPUT,
        RANDOMCV_INPUT,
        INPUT_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUTPUT_OUTPUT,
        REVERSE_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    SDFormation() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configParam(GAIN_PARAM, 0.f, 1.f, 0.f, "");
        configParam(OFFSET_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SPREAD_PARAM, 0.f, 1.f, 0.f, "");
        configParam(DIRECTION_PARAM, 0.f, 1.f, 0.f, "");
        configParam(TILT_PARAM, 0.f, 1.f, 0.f, "");
        configParam(RANDOM_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SPREADCV_PARAM, 0.f, 1.f, 0.f, "");
        configParam(TILTCV_PARAM, 0.f, 1.f, 0.f, "");
        configParam(RANDOMCV_PARAM, 0.f, 1.f, 0.f, "");
        configInput(TRIGGER_INPUT, "");
        configInput(SPREADCV_INPUT, "");
        configInput(TILTCV_INPUT, "");
        configInput(RANDOMCV_INPUT, "");
        configInput(INPUT_INPUT, "");
        configOutput(OUTPUT_OUTPUT, "");
        configOutput(REVERSE_OUTPUT, "");
    }

    void process(const ProcessArgs& args) override {
    }
};


struct SDFormationWidget : ModuleWidget {
    SDFormationWidget(SDFormation* module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/SDFormation.svg")));

        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(9.85, 16.411)), module, SDFormation::GAIN_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(25.71, 16.411)), module, SDFormation::OFFSET_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(17.78, 36.021)), module, SDFormation::SPREAD_PARAM));
        addParam(createParam<SDThreeSwitch>(mm2px(Vec(4.074, 41.902)), module, SDFormation::DIRECTION_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(17.78, 55.631)), module, SDFormation::TILT_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(25.71, 76.215)), module, SDFormation::RANDOM_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(6.597, 93.373)), module, SDFormation::SPREADCV_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(17.78, 93.373)), module, SDFormation::TILTCV_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(28.963, 93.373)), module, SDFormation::RANDOMCV_PARAM));

        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(9.85, 77.203)), module, SDFormation::TRIGGER_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(6.597, 104.61)), module, SDFormation::SPREADCV_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(17.78, 104.61)), module, SDFormation::TILTCV_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(28.963, 104.61)), module, SDFormation::RANDOMCV_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(6.597, 119.319)), module, SDFormation::INPUT_INPUT));

        addOutput(createOutputCentered<SDPolyOutPort>(mm2px(Vec(17.78, 119.318)), module, SDFormation::OUTPUT_OUTPUT));
        addOutput(createOutputCentered<SDPolyOutPort>(mm2px(Vec(28.963, 119.319)), module, SDFormation::REVERSE_OUTPUT));
    }
};


Model* modelSDFormation = createModel<SDFormation, SDFormationWidget>("SDFormation");