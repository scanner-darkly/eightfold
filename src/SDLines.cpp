#include <tuple>
#include "plugin.hpp"
#include "SDSharedComponents.hpp"

struct SDLines : Module {
    enum ParamIds {
        NUM_PARAMS
    };
    enum InputIds {
        IN_INPUT,
        NUM_INPUTS
    };
    enum OutputIds {
        NUM_OUTPUTS
    };
    enum LightIds {
        NUM_LIGHTS
    };

    int range = 0;
    float min[4] = {0, -10, 0, -5};
    float max[4] = {10, 10, 5, 5};
    bool bipolar[4] = {false, true, false, true};
    
    int mode = 0;
    
    SDLines() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        configInput(IN_INPUT, "Input");
    }

    json_t* dataToJson() override {
        json_t* rootJ = json_object();
        json_object_set_new(rootJ, "range", json_integer(range));
        json_object_set_new(rootJ, "mode", json_integer(mode));
        return rootJ;
    }

    void dataFromJson(json_t* rootJ) override {
        json_t* rangeJ = json_object_get(rootJ, "range");
        if (rangeJ) range = json_integer_value(rangeJ);
        
        json_t* modeJ = json_object_get(rootJ, "mode");
        if (modeJ) mode = json_integer_value(modeJ);
    }
};

struct SDLinesDisplay : TransparentWidget {
    const int MAX_CHANNELS = 16;
    const float stroke = 1.f;
    const float halfstroke = 0.5f;
    
    SDLines *module;

    NVGcolor pos = nvgRGB(255, 255, 255);
    NVGcolor neg = nvgRGB(255, 0, 0);
    NVGcolor zero = nvgRGB(120, 120, 120);
    NVGcolor out = nvgRGB(0, 0, 0);

    float x, y, w, h, deltaX, centerX, centerY, startY;
    
    SDLinesDisplay(Vec pos, Vec size) : TransparentWidget() {
        box.pos = pos;
        box.size = size;
        
        x = box.pos.x + 1.f;
        y = box.pos.y;
        w = box.size.x - 2.f;
        h = box.size.y - 0.5f;

        /*
        x = box.pos.x;
        y = box.pos.y;
        w = box.size.x;
        h = box.size.y;
        */
        
        deltaX = 0; // determined dynamically
        centerX = x + w / 2.f + halfstroke;
        centerY = y + h / 2.f + halfstroke;
        startY = y + h + halfstroke;
    }

    void drawLine(const DrawArgs &args, float x1, float y1, float x2, float y2, NVGcolor color) {
        nvgStrokeWidth(args.vg, stroke);
        nvgStrokeColor(args.vg, color);
        nvgBeginPath(args.vg);
        nvgMoveTo(args.vg, x1, y1);
        nvgLineTo(args.vg, x2, y2);
        nvgStroke(args.vg);
    }
    
    std::tuple<float, NVGcolor> getScaledVoltage(int i) {
        float min = module->min[module->range];
        float max = module->max[module->range];
        float range = max - min;
        if (range == 0) {
            range = 10.f;
            min = 0.f;
            max = 10.f;
        }
        
        float voltage = module->inputs[SDLines::IN_INPUT].getVoltage(i);
        // uncomment for screenshots voltage = (i + 1) * 1.2f - 5.f;
        
        NVGcolor color;
        if (voltage < min) {
            voltage = min;
            color = out;
        } else if (voltage > max) {
            voltage = max;
            color = out;
        } else {
            color = voltage == 0 ? zero : (voltage >= 0 ? pos : neg);
        }

        voltage /= range;
        
        return std::make_tuple(voltage, color);
    }
    
    void drawHorizontalVoltage(const DrawArgs &args, int i) {
        float voltage;
        NVGcolor color;
        std::tie(voltage, color) = getScaledVoltage(i);
        
        float v = (module->bipolar[module->range] ? centerY : startY) - h * voltage - halfstroke;
        drawLine(args, x + halfstroke, v, x + w - halfstroke, v, color);
    }
    
    void drawVerticalVoltage(const DrawArgs &args, int i, int channels) {
        float voltage;
        NVGcolor color;
        std::tie(voltage, color) = getScaledVoltage(i);
        
        float Y = module->bipolar[module->range] ? centerY : startY;
        float v = Y - h * voltage - halfstroke;
        float X = channels == 1 ? centerX : x + 1.f + deltaX * i + halfstroke;
        drawLine(args, X, Y, X, v, color);
    }

    void drawLayer(const DrawArgs &args, int layer) override {
        if (layer == 1) {

            if (module) {
                int channels = std::min(MAX_CHANNELS, module->inputs[SDLines::IN_INPUT].getChannels());
                // uncomment for screenshots channels = 8;
                
                deltaX = channels > 1 ? (w - 2.f - stroke * channels) / (channels - 1) + stroke : stroke;
                
                /*
                NVGcolor frame = nvgRGB(80, 80, 80);
                drawLine(args, x, y, x + w, y, frame);
                drawLine(args, x + w, y, x + w, y + h, frame);
                drawLine(args, x + w, y + h, x, y + h, frame);
                drawLine(args, x, y + h, x, y, frame);
                */

                if (module->mode == 0) {
                    for (int i = 0; i < channels; i++) drawHorizontalVoltage(args, i);
                } else {
                    for (int i = 0; i < channels; i++) drawVerticalVoltage(args, i, channels);
                }
            }
        }
        
        Widget::drawLayer(args, layer);
    }
};

struct SDLinesWidget : ModuleWidget {
    SDLinesWidget(SDLines* module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/SDLines.svg")));

        addInput(createInputCentered<SDPolyInPort>(mm2px(Vec(5.08, 119.319)), module, SDLines::IN_INPUT));

        auto display = new SDLinesDisplay(mm2px(Vec(0.0, 5.709 / 2.f)), mm2px(Vec(10.16, 104.845)));
        display->module = module;
        addChild(display);
    }
    
    void appendContextMenu(Menu* menu) override {
        SDLines* module = getModule<SDLines>();
        menu->addChild(new MenuSeparator);
        menu->addChild(createIndexPtrSubmenuItem("Mode", {"Horizontal", "Vertical"}, &module->mode));
        menu->addChild(createIndexPtrSubmenuItem("Range", {"0 .. +10", "-10 .. +10", "0 .. +5", "-5 .. +5"}, &module->range));
    }
};

Model *modelSDLines = createModel<SDLines, SDLinesWidget>("SDLines");