#include "plugin.hpp"


struct SDTransgate : Module {
    enum ParamId {
        TRANS1_PARAM,
        TRANS2_PARAM,
        TRANS3_PARAM,
        TRANS4_PARAM,
        TRANS5_PARAM,
        TRANS6_PARAM,
        TRANS7_PARAM,
        TRANS8_PARAM,
        ALL_ON_PARAM,
        PARAMS_LEN
    };
    enum InputId {
        GATE1_INPUT,
        GATE2_INPUT,
        GATE3_INPUT,
        GATE4_INPUT,
        GATE5_INPUT,
        GATE6_INPUT,
        GATE7_INPUT,
        GATE8_INPUT,
        GATES_INPUT,
        INPUT_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
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

    SDTransgate() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configParam(TRANS1_PARAM, 0.f, 1.f, 0.f, "");
        configParam(TRANS2_PARAM, 0.f, 1.f, 0.f, "");
        configParam(TRANS3_PARAM, 0.f, 1.f, 0.f, "");
        configParam(TRANS4_PARAM, 0.f, 1.f, 0.f, "");
        configParam(TRANS5_PARAM, 0.f, 1.f, 0.f, "");
        configParam(TRANS6_PARAM, 0.f, 1.f, 0.f, "");
        configParam(TRANS7_PARAM, 0.f, 1.f, 0.f, "");
        configParam(TRANS8_PARAM, 0.f, 1.f, 0.f, "");
        configParam(ALL_ON_PARAM, 0.f, 1.f, 0.f, "");
        configInput(GATE1_INPUT, "");
        configInput(GATE2_INPUT, "");
        configInput(GATE3_INPUT, "");
        configInput(GATE4_INPUT, "");
        configInput(GATE5_INPUT, "");
        configInput(GATE6_INPUT, "");
        configInput(GATE7_INPUT, "");
        configInput(GATE8_INPUT, "");
        configInput(GATES_INPUT, "");
        configInput(INPUT_INPUT, "");
        configOutput(OUTPUT_OUTPUT, "");
    }

    void process(const ProcessArgs& args) override {
    }
};


struct SDTransgateWidget : ModuleWidget {
    SDTransgateWidget(SDTransgate* module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/SDTransgate.svg")));

        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(19.128, 13.126)), module, SDTransgate::TRANS1_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(19.128, 24.148)), module, SDTransgate::TRANS2_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(19.128, 35.17)), module, SDTransgate::TRANS3_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(19.128, 46.192)), module, SDTransgate::TRANS4_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(19.128, 57.214)), module, SDTransgate::TRANS5_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(19.128, 68.236)), module, SDTransgate::TRANS6_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(19.128, 79.258)), module, SDTransgate::TRANS7_PARAM));
        addParam(createParamCentered<SDSmallestKnob>(mm2px(Vec(19.128, 90.28)), module, SDTransgate::TRANS8_PARAM));
        addParam(createParam<SDTwoSwitch>(mm2px(Vec(15.617, 101.089)), module, SDTransgate::ALL_ON_PARAM));

        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(6.652, 13.126)), module, SDTransgate::GATE1_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(6.652, 24.148)), module, SDTransgate::GATE2_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(6.652, 35.17)), module, SDTransgate::GATE3_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(6.652, 46.192)), module, SDTransgate::GATE4_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(6.652, 57.214)), module, SDTransgate::GATE5_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(6.652, 68.236)), module, SDTransgate::GATE6_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(6.652, 79.258)), module, SDTransgate::GATE7_INPUT));
        addInput(createInputCentered<SDMonoInPort>(mm2px(Vec(6.652, 90.28)), module, SDTransgate::GATE8_INPUT));
        addInput(createInputCentered<SDPolyInPort>(mm2px(Vec(6.652, 104.61)), module, SDTransgate::GATES_INPUT));
        addInput(createInputCentered<SDPolyInPort>(mm2px(Vec(6.652, 119.319)), module, SDTransgate::INPUT_INPUT));

        addOutput(createOutputCentered<SDPolyOutPort>(mm2px(Vec(17.836, 119.318)), module, SDTransgate::OUTPUT_OUTPUT));

        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 13.126)), module, SDTransgate::GATEON1_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 24.148)), module, SDTransgate::GATEON2_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 35.17)), module, SDTransgate::GATEON3_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 46.192)), module, SDTransgate::GATEON4_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 57.214)), module, SDTransgate::GATEON5_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 68.236)), module, SDTransgate::GATEON6_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 79.258)), module, SDTransgate::GATEON7_LIGHT));
        addChild(createLightCentered<SmallLight<SDWhiteLight>>(mm2px(Vec(12.7, 90.28)), module, SDTransgate::GATEON8_LIGHT));
    }
};


Model* modelSDTransgate = createModel<SDTransgate, SDTransgateWidget>("SDTransgate");