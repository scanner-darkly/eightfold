#include "plugin.hpp"


struct SDOrcasHeartV2 : Module {
    enum ParamId {
        SCALE_2_PARAM,
        SCALE_4_PARAM,
        SCALE_7_PARAM,
        SCALE_9_PARAM,
        SCALE_11_PARAM,
        SCALE_A_OCT_PARAM,
        SCALE_A_LOCK_PARAM,
        SCALE_A_PARAM,
        SCALE_1_PARAM,
        SCALE_3_PARAM,
        SCALE_5_PARAM,
        SCALE_6_PARAM,
        SCALE_8_PARAM,
        SCALE_10_PARAM,
        SCALE_12_PARAM,
        SCALE_PARAM,
        SCALE_14_PARAM,
        SCALE_16_PARAM,
        SCALE_19_PARAM,
        SCALE_21_PARAM,
        SCALE_23_PARAM,
        SCALE_B_OCT_PARAM,
        SCALE_B_LOCK_PARAM,
        SCALE_B_PARAM,
        SCALE_13_PARAM,
        SCALE_15_PARAM,
        SCALE_17_PARAM,
        SCALE_18_PARAM,
        SCALE_20_PARAM,
        SCALE_22_PARAM,
        SCALE_24_PARAM,
        SPEED_PARAM,
        LENGTH_PARAM,
        TRANSPOSE_PARAM,
        GATE_LEN_PARAM,
        VOICES_PARAM,
        SPREAD_PARAM,
        ALGO_X_PARAM,
        ALGO_Y_PARAM,
        SHIFT_PARAM,
        SPACE_PARAM,
        ROTATE_PARAM,
        XMOD_PARAM,
        PARAMS_LEN
    };
    enum InputId {
        SCALE_A_OCT_INPUT,
        SCALE_A_INPUT,
        SCALE_INPUT,
        SCALE_B_OCT_INPUT,
        SCALE_B_INPUT,
        CLOCK_INPUT,
        RESET_INPUT,
        SPEED_INPUT,
        ALGO_X_INPUT,
        LENGTH_INPUT,
        ALGO_Y_INPUT,
        TRANSPOSE_INPUT,
        SHIFT_INPUT,
        GATE_LEN_INPUT,
        SPACE_INPUT,
        VOICES_INPUT,
        ROTATE_INPUT,
        SPREAD_INPUT,
        XMOD_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        CLOCK_OUTPUT,
        MOD_CV_1_OUTPUT,
        MOD_CV_2_OUTPUT,
        MOD_CV_3_OUTPUT,
        MOD_CV_4_OUTPUT,
        CV_1_OUTPUT,
        CV_2_OUTPUT,
        CV_3_OUTPUT,
        CV_4_OUTPUT,
        CV_5_OUTPUT,
        CV_6_OUTPUT,
        CV_7_OUTPUT,
        CV_8_OUTPUT,
        RESET_OUTPUT,
        MOD_GATE_1_OUTPUT,
        MOD_GATE_2_OUTPUT,
        MOD_GATE_3_OUTPUT,
        MOD_GATE_4_OUTPUT,
        GATE_1_OUTPUT,
        GATE_2_OUTPUT,
        GATE_3_OUTPUT,
        GATE_4_OUTPUT,
        GATE_5_OUTPUT,
        GATE_6_OUTPUT,
        GATE_7_OUTPUT,
        GATE_8_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        SCALE_A_LIGHT,
        SCALE_B_LIGHT,
        LIGHTS_LEN
    };

    SDOrcasHeartV2() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configParam(SCALE_2_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_4_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_7_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_9_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_11_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_A_OCT_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_A_LOCK_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_A_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_1_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_3_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_5_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_6_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_8_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_10_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_12_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_14_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_16_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_19_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_21_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_23_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_B_OCT_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_B_LOCK_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_B_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_13_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_15_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_17_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_18_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_20_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_22_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_24_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SPEED_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LENGTH_PARAM, 0.f, 1.f, 0.f, "");
        configParam(TRANSPOSE_PARAM, 0.f, 1.f, 0.f, "");
        configParam(GATE_LEN_PARAM, 0.f, 1.f, 0.f, "");
        configParam(VOICES_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SPREAD_PARAM, 0.f, 1.f, 0.f, "");
        configParam(ALGO_X_PARAM, 0.f, 1.f, 0.f, "");
        configParam(ALGO_Y_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SHIFT_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SPACE_PARAM, 0.f, 1.f, 0.f, "");
        configParam(ROTATE_PARAM, 0.f, 1.f, 0.f, "");
        configParam(XMOD_PARAM, 0.f, 1.f, 0.f, "");
        configInput(SCALE_A_OCT_INPUT, "");
        configInput(SCALE_A_INPUT, "");
        configInput(SCALE_INPUT, "");
        configInput(SCALE_B_OCT_INPUT, "");
        configInput(SCALE_B_INPUT, "");
        configInput(CLOCK_INPUT, "");
        configInput(RESET_INPUT, "");
        configInput(SPEED_INPUT, "");
        configInput(ALGO_X_INPUT, "");
        configInput(LENGTH_INPUT, "");
        configInput(ALGO_Y_INPUT, "");
        configInput(TRANSPOSE_INPUT, "");
        configInput(SHIFT_INPUT, "");
        configInput(GATE_LEN_INPUT, "");
        configInput(SPACE_INPUT, "");
        configInput(VOICES_INPUT, "");
        configInput(ROTATE_INPUT, "");
        configInput(SPREAD_INPUT, "");
        configInput(XMOD_INPUT, "");
        configOutput(CLOCK_OUTPUT, "");
        configOutput(MOD_CV_1_OUTPUT, "");
        configOutput(MOD_CV_2_OUTPUT, "");
        configOutput(MOD_CV_3_OUTPUT, "");
        configOutput(MOD_CV_4_OUTPUT, "");
        configOutput(CV_1_OUTPUT, "");
        configOutput(CV_2_OUTPUT, "");
        configOutput(CV_3_OUTPUT, "");
        configOutput(CV_4_OUTPUT, "");
        configOutput(CV_5_OUTPUT, "");
        configOutput(CV_6_OUTPUT, "");
        configOutput(CV_7_OUTPUT, "");
        configOutput(CV_8_OUTPUT, "");
        configOutput(RESET_OUTPUT, "");
        configOutput(MOD_GATE_1_OUTPUT, "");
        configOutput(MOD_GATE_2_OUTPUT, "");
        configOutput(MOD_GATE_3_OUTPUT, "");
        configOutput(MOD_GATE_4_OUTPUT, "");
        configOutput(GATE_1_OUTPUT, "");
        configOutput(GATE_2_OUTPUT, "");
        configOutput(GATE_3_OUTPUT, "");
        configOutput(GATE_4_OUTPUT, "");
        configOutput(GATE_5_OUTPUT, "");
        configOutput(GATE_6_OUTPUT, "");
        configOutput(GATE_7_OUTPUT, "");
        configOutput(GATE_8_OUTPUT, "");
    }

    void process(const ProcessArgs& args) override {
    }
};


struct SDOrcasHeartV2Widget : ModuleWidget {
    SDOrcasHeartV2Widget(SDOrcasHeartV2* module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/SDOrcasHeartV2.svg")));

        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(59.672, 14.503)), module, SDOrcasHeartV2::SCALE_2_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(68.626, 14.503)), module, SDOrcasHeartV2::SCALE_4_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(86.533, 14.503)), module, SDOrcasHeartV2::SCALE_7_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(95.487, 14.503)), module, SDOrcasHeartV2::SCALE_9_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(104.44, 14.503)), module, SDOrcasHeartV2::SCALE_11_PARAM));
        addParam(createParamCentered<SDScaleButton>(mm2px(Vec(42.651, 16.863)), module, SDOrcasHeartV2::SCALE_A_OCT_PARAM));
        addParam(createParamCentered<SDScaleButton>(mm2px(Vec(120.932, 16.863)), module, SDOrcasHeartV2::SCALE_A_LOCK_PARAM));
        addParam(createParamCentered<SDScaleKnob>(mm2px(Vec(132.115, 16.863)), module, SDOrcasHeartV2::SCALE_A_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(55.195, 19.223)), module, SDOrcasHeartV2::SCALE_1_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(64.149, 19.223)), module, SDOrcasHeartV2::SCALE_3_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(73.102, 19.223)), module, SDOrcasHeartV2::SCALE_5_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(82.056, 19.223)), module, SDOrcasHeartV2::SCALE_6_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(91.01, 19.223)), module, SDOrcasHeartV2::SCALE_8_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(99.964, 19.223)), module, SDOrcasHeartV2::SCALE_10_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(108.917, 19.223)), module, SDOrcasHeartV2::SCALE_12_PARAM));
        addParam(createParamCentered<SDMomentaryScaleButton>(mm2px(Vec(20.284, 24.754)), module, SDOrcasHeartV2::SCALE_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(59.143, 30.286)), module, SDOrcasHeartV2::SCALE_14_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(68.096, 30.286)), module, SDOrcasHeartV2::SCALE_16_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(86.004, 30.286)), module, SDOrcasHeartV2::SCALE_19_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(94.958, 30.286)), module, SDOrcasHeartV2::SCALE_21_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(103.911, 30.286)), module, SDOrcasHeartV2::SCALE_23_PARAM));
        addParam(createParamCentered<SDScaleButton>(mm2px(Vec(42.651, 32.646)), module, SDOrcasHeartV2::SCALE_B_OCT_PARAM));
        addParam(createParamCentered<SDScaleButton>(mm2px(Vec(120.932, 32.646)), module, SDOrcasHeartV2::SCALE_B_LOCK_PARAM));
        addParam(createParamCentered<SDScaleKnob>(mm2px(Vec(132.115, 32.646)), module, SDOrcasHeartV2::SCALE_B_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(54.666, 35.006)), module, SDOrcasHeartV2::SCALE_13_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(63.62, 35.006)), module, SDOrcasHeartV2::SCALE_15_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(72.573, 35.006)), module, SDOrcasHeartV2::SCALE_17_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(81.527, 35.006)), module, SDOrcasHeartV2::SCALE_18_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(90.481, 35.006)), module, SDOrcasHeartV2::SCALE_20_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(99.434, 35.006)), module, SDOrcasHeartV2::SCALE_22_PARAM));
        addParam(createParamCentered<SDSmallScaleButton>(mm2px(Vec(108.388, 35.006)), module, SDOrcasHeartV2::SCALE_24_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(20.284, 53.868)), module, SDOrcasHeartV2::SPEED_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(42.651, 53.868)), module, SDOrcasHeartV2::LENGTH_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(65.017, 53.868)), module, SDOrcasHeartV2::TRANSPOSE_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(87.383, 53.868)), module, SDOrcasHeartV2::GATE_LEN_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(109.749, 53.868)), module, SDOrcasHeartV2::VOICES_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(132.115, 53.868)), module, SDOrcasHeartV2::SPREAD_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(31.468, 71.614)), module, SDOrcasHeartV2::ALGO_X_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(53.834, 71.614)), module, SDOrcasHeartV2::ALGO_Y_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(76.2, 71.614)), module, SDOrcasHeartV2::SHIFT_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(98.566, 71.614)), module, SDOrcasHeartV2::SPACE_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(120.932, 71.614)), module, SDOrcasHeartV2::ROTATE_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(143.299, 71.614)), module, SDOrcasHeartV2::XMOD_PARAM));

        addInput(createInputCentered<SDScalePort>(mm2px(Vec(31.468, 16.863)), module, SDOrcasHeartV2::SCALE_A_OCT_INPUT));
        addInput(createInputCentered<SDScalePort>(mm2px(Vec(143.299, 16.863)), module, SDOrcasHeartV2::SCALE_A_INPUT));
        addInput(createInputCentered<SDScalePort>(mm2px(Vec(9.101, 24.754)), module, SDOrcasHeartV2::SCALE_INPUT));
        addInput(createInputCentered<SDScalePort>(mm2px(Vec(31.468, 32.646)), module, SDOrcasHeartV2::SCALE_B_OCT_INPUT));
        addInput(createInputCentered<SDScalePort>(mm2px(Vec(143.299, 32.646)), module, SDOrcasHeartV2::SCALE_B_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(9.101, 69.868)), module, SDOrcasHeartV2::CLOCK_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(9.101, 84.65)), module, SDOrcasHeartV2::RESET_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(20.284, 84.65)), module, SDOrcasHeartV2::SPEED_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(31.468, 84.65)), module, SDOrcasHeartV2::ALGO_X_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(42.651, 84.65)), module, SDOrcasHeartV2::LENGTH_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(53.834, 84.65)), module, SDOrcasHeartV2::ALGO_Y_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(65.017, 84.65)), module, SDOrcasHeartV2::TRANSPOSE_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(76.2, 84.65)), module, SDOrcasHeartV2::SHIFT_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(87.383, 84.65)), module, SDOrcasHeartV2::GATE_LEN_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(98.566, 84.65)), module, SDOrcasHeartV2::SPACE_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(109.749, 84.65)), module, SDOrcasHeartV2::VOICES_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(120.932, 84.65)), module, SDOrcasHeartV2::ROTATE_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(132.115, 84.65)), module, SDOrcasHeartV2::SPREAD_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(143.299, 84.65)), module, SDOrcasHeartV2::XMOD_INPUT));

        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(9.101, 104.537)), module, SDOrcasHeartV2::CLOCK_OUTPUT));
        addOutput(createOutputCentered<SDPolyOutPort>(mm2px(Vec(20.284, 104.536)), module, SDOrcasHeartV2::MOD_CV_1_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(31.468, 104.536)), module, SDOrcasHeartV2::MOD_CV_2_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(42.651, 104.536)), module, SDOrcasHeartV2::MOD_CV_3_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(53.834, 104.536)), module, SDOrcasHeartV2::MOD_CV_4_OUTPUT));
        addOutput(createOutputCentered<SDPolyOutPort>(mm2px(Vec(65.017, 104.536)), module, SDOrcasHeartV2::CV_1_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(76.2, 104.536)), module, SDOrcasHeartV2::CV_2_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(87.383, 104.536)), module, SDOrcasHeartV2::CV_3_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(98.566, 104.536)), module, SDOrcasHeartV2::CV_4_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(109.749, 104.536)), module, SDOrcasHeartV2::CV_5_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(120.932, 104.536)), module, SDOrcasHeartV2::CV_6_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(132.116, 104.536)), module, SDOrcasHeartV2::CV_7_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(143.299, 104.536)), module, SDOrcasHeartV2::CV_8_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(9.101, 119.318)), module, SDOrcasHeartV2::RESET_OUTPUT));
        addOutput(createOutputCentered<SDPolyOutPort>(mm2px(Vec(20.284, 119.318)), module, SDOrcasHeartV2::MOD_GATE_1_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(31.468, 119.318)), module, SDOrcasHeartV2::MOD_GATE_2_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(42.651, 119.318)), module, SDOrcasHeartV2::MOD_GATE_3_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(53.834, 119.318)), module, SDOrcasHeartV2::MOD_GATE_4_OUTPUT));
        addOutput(createOutputCentered<SDPolyOutPort>(mm2px(Vec(65.017, 119.318)), module, SDOrcasHeartV2::GATE_1_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(76.2, 119.318)), module, SDOrcasHeartV2::GATE_2_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(87.383, 119.318)), module, SDOrcasHeartV2::GATE_3_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(98.566, 119.318)), module, SDOrcasHeartV2::GATE_4_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(109.749, 119.318)), module, SDOrcasHeartV2::GATE_5_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(120.932, 119.318)), module, SDOrcasHeartV2::GATE_6_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(132.115, 119.318)), module, SDOrcasHeartV2::GATE_7_OUTPUT));
        addOutput(createOutputCentered<SDMonoOutPort>(mm2px(Vec(143.299, 119.318)), module, SDOrcasHeartV2::GATE_8_OUTPUT));

        addChild(createLightCentered<MediumLight<SDWhiteLight>>(mm2px(Vec(20.284, 16.863)), module, SDOrcasHeartV2::SCALE_A_LIGHT));
        addChild(createLightCentered<MediumLight<SDWhiteLight>>(mm2px(Vec(20.284, 32.646)), module, SDOrcasHeartV2::SCALE_B_LIGHT));
    }
};


Model* modelSDOrcasHeartV2 = createModel<SDOrcasHeartV2, SDOrcasHeartV2Widget>("SDOrcasHeartV2");