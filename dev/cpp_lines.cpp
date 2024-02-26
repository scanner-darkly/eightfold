#include "plugin.hpp"


struct SDLines : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        IN_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    SDLines() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(IN_INPUT, "");
    }

    void process(const ProcessArgs& args) override {
    }
};


struct SDLinesWidget : ModuleWidget {
    SDLinesWidget(SDLines* module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/SDLines.svg")));

        addInput(createInputCentered<SDPolyPort>(mm2px(Vec(5.08, 119.319)), module, SDLines::IN_INPUT));

        auto display = new SDLinesDisplay(mm2px(Vec(0.0, 5.709 / 2.f)), mm2px(Vec(10.16, 104.845)));
        display->module = module;
        addChild(display);
    }
};


Model* modelSDLines = createModel<SDLines, SDLinesWidget>("SDLines");