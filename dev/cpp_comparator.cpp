#include "plugin.hpp"


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
        MODE_PARAM,
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
        configParam(LEVEL1_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LEVEL2_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LEVEL3_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LEVEL4_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LEVEL5_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LEVEL6_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LEVEL7_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LEVEL8_PARAM, 0.f, 1.f, 0.f, "");
        configParam(MODE_PARAM, 0.f, 1.f, 0.f, "");
        configInput(LEVELS_INPUT, "");
        configInput(INPUT_INPUT, "");
        configOutput(GATE1_OUTPUT, "");
        configOutput(GATE2_OUTPUT, "");
        configOutput(GATE3_OUTPUT, "");
        configOutput(GATE4_OUTPUT, "");
        configOutput(GATE5_OUTPUT, "");
        configOutput(GATE6_OUTPUT, "");
        configOutput(GATE7_OUTPUT, "");
        configOutput(GATE8_OUTPUT, "");
        configOutput(OUTPUT_OUTPUT, "");
    }

    void process(const ProcessArgs& args) override {
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
        addParam(createParam<SDTwoSwitch>(mm2px(Vec(15.617, 101.089)), module, SDComparator::MODE_PARAM));

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