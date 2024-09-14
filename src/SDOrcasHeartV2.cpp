#include "plugin.hpp"

#include <math.h>
#include <string>

#if !__has_include("VCV_adaptor/widget_convert/eightfold.hh")
#include "SDSharedComponents.hpp"
#endif

#define SCALELEN 12
#define SCALECOUNT 2
#define SCALEPRESETCOUNT 16
#define NOTECOUNT 8
#define NOTECOUNT_LEGACY 4
#define HISTORYCOUNT 8
#define MODCOUNT 8
#define MODOUTPUTCOUNT 4
#define TRACKCOUNT 8
#define TRACKCOUNT_LEGACY 4
#define GATEPRESETCOUNT 16

struct SDOrcasHeartV2 : Module {

    const int gatePresets[GATEPRESETCOUNT][NOTECOUNT] = {
        {0b0001, 0b0010, 0b0100, 0b1000, 0b0000, 0b0001, 0b0101, 0b1010},
        {0b0011, 0b0010, 0b0101, 0b1000, 0b0001, 0b0010, 0b0100, 0b0100},
        {0b0011, 0b0110, 0b1101, 0b1000, 0b0010, 0b0100, 0b0100, 0b0001},
        {0b0111, 0b0110, 0b1101, 0b1001, 0b0100, 0b1000, 0b0010, 0b0001},

        {0b0111, 0b0101, 0b1101, 0b1010, 0b1001, 0b0101, 0b0010, 0b1001},
        {0b1111, 0b0101, 0b1110, 0b1010, 0b0110, 0b1010, 0b0011, 0b1001},
        {0b1101, 0b1101, 0b1010, 0b1011, 0b1010, 0b0110, 0b0011, 0b1100},
        {0b1101, 0b1000, 0b0110, 0b1101, 0b1100, 0b0011, 0b0010, 0b0100},

        {0b1001, 0b1100, 0b1110, 0b0111, 0b1000, 0b0001, 0b0100, 0b0010},
        {0b1100, 0b0101, 0b0110, 0b0111, 0b0100, 0b1000, 0b1010, 0b0110},
        {0b1100, 0b0110, 0b0110, 0b1100, 0b0010, 0b0100, 0b1001, 0b1110},
        {0b0101, 0b1010, 0b0110, 0b1101, 0b0001, 0b0010, 0b0110, 0b1001},

        {0b0101, 0b1001, 0b0110, 0b0101, 0b1101, 0b1011, 0b0010, 0b0001},
        {0b0110, 0b0101, 0b0110, 0b1101, 0b1100, 0b0011, 0b0001, 0b0010},
        {0b1100, 0b0011, 0b0110, 0b1100, 0b0110, 0b0110, 0b1000, 0b0010},
        {0b1001, 0b0010, 0b0101, 0b1000, 0b0010, 0b0100, 0b1010, 0b0001}
    };

    const int scalePresets[SCALEPRESETCOUNT][SCALELEN] = {
        {1, 0, 1, 0,   1, 0, 0, 1,   0, 1, 0, 0},
        {1, 0, 1, 0,   0, 1, 0, 1,   0, 1, 0, 0},
        {1, 0, 1, 0,   0, 1, 0, 1,   0, 0, 1, 0},
        {1, 0, 1, 0,   1, 0, 1, 0,   0, 1, 0, 0},
        
        {0, 0, 1, 0,   1, 0, 0, 1,   0, 1, 0, 1},
        {1, 0, 0, 1,   0, 1, 0, 0,   1, 0, 1, 0},
        {1, 0, 1, 0,   1, 0, 0, 1,   0, 0, 0, 1},
        {1, 0, 0, 1,   0, 1, 0, 1,   0, 0, 1, 0},

        {0, 0, 1, 0,   0, 1, 0, 1,   0, 1, 0, 1},
        {0, 1, 0, 1,   0, 1, 0, 1,   0, 0, 1, 0},
        {1, 0, 1, 0,   1, 0, 0, 1,   0, 0, 1, 0},
        {1, 0, 0, 0,   1, 0, 1, 1,   0, 1, 0, 0},

        {0, 0, 1, 1,   0, 1, 0, 0,   1, 0, 1, 0},
        {1, 0, 0, 1,   0, 1, 1, 0,   0, 0, 1, 0},
        {1, 0, 0, 1,   0, 1, 0, 1,   0, 0, 0, 1},
        {1, 0, 0, 1,   0, 1, 1, 0,   0, 1, 0, 0}
    };
    
    const int weights[TRACKCOUNT] = { 1, 2, 4, 7, 5, 3, 11, 13 };
    
    enum ParamIds {
        SCALE_PARAM,
        SCALE_A_OCT_PARAM,
        SCALE_B_OCT_PARAM,
        SCALE_A_LOCK_PARAM,
        SCALE_B_LOCK_PARAM,
        SCALE_A_PARAM,
        SCALE_B_PARAM,
        
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
        
        // SCALE_ outputs must be arranged consecutively 
        SCALE_1_PARAM,
        SCALE_2_PARAM,
        SCALE_3_PARAM,
        SCALE_4_PARAM,
        SCALE_5_PARAM,
        SCALE_6_PARAM,
        SCALE_7_PARAM,
        SCALE_8_PARAM,
        SCALE_9_PARAM,
        SCALE_10_PARAM,
        SCALE_11_PARAM,
        SCALE_12_PARAM,
        SCALE_13_PARAM,
        SCALE_14_PARAM,
        SCALE_15_PARAM,
        SCALE_16_PARAM,
        SCALE_17_PARAM,
        SCALE_18_PARAM,
        SCALE_19_PARAM,
        SCALE_20_PARAM,
        SCALE_21_PARAM,
        SCALE_22_PARAM,
        SCALE_23_PARAM,
        SCALE_24_PARAM,
        NUM_PARAMS
    };

    enum InputIds {
        SCALE_INPUT,
        SCALE_A_OCT_INPUT,
        SCALE_B_OCT_INPUT,
        SCALE_A_INPUT,
        SCALE_B_INPUT,
        
        SPEED_INPUT,
        LENGTH_INPUT,
        TRANSPOSE_INPUT,
        GATE_LEN_INPUT,
        VOICES_INPUT,
        SPREAD_INPUT,

        ALGO_X_INPUT,
        ALGO_Y_INPUT,
        SHIFT_INPUT,
        SPACE_INPUT,
        ROTATE_INPUT,
        XMOD_INPUT,

        CLOCK_INPUT,
        RESET_INPUT,
        NUM_INPUTS
    };

    enum OutputIds {
        CLOCK_OUTPUT,
        RESET_OUTPUT,
        
        // CV_ and GATE_ outputs must be arranged consecutively 
        CV_1_OUTPUT,
        CV_2_OUTPUT,
        CV_3_OUTPUT,
        CV_4_OUTPUT,
        CV_5_OUTPUT,
        CV_6_OUTPUT,
        CV_7_OUTPUT,
        CV_8_OUTPUT,
        GATE_1_OUTPUT,
        GATE_2_OUTPUT,
        GATE_3_OUTPUT,
        GATE_4_OUTPUT,
        GATE_5_OUTPUT,
        GATE_6_OUTPUT,
        GATE_7_OUTPUT,
        GATE_8_OUTPUT,
        
        MOD_CV_1_OUTPUT,
        MOD_CV_2_OUTPUT,
        MOD_CV_3_OUTPUT,
        MOD_CV_4_OUTPUT,
        MOD_GATE_1_OUTPUT,
        MOD_GATE_2_OUTPUT,
        MOD_GATE_3_OUTPUT,
        MOD_GATE_4_OUTPUT,
        NUM_OUTPUTS
    };
    
    enum LightIds {
        SCALE_A_LIGHT,
        SCALE_B_LIGHT,
        NUM_LIGHTS
    };

    SDOrcasHeartV2() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

        configLight(SCALE_A_LIGHT, "Scale A Selected");
        configLight(SCALE_B_LIGHT, "Scale B Selected");
        configButton(SCALE_PARAM, "Toggle Scales A/B/both");
        configInput(SCALE_INPUT, "Toggle Scales A/B");
        configSwitch(SCALE_A_OCT_PARAM, 0, 1, 0, "Octave A", { "Down", "Up" });
        configSwitch(SCALE_B_OCT_PARAM, 0, 1, 0, "Octave B", { "Down", "Up" });
        configInput(SCALE_A_OCT_INPUT, "+ Octave A");
        configInput(SCALE_B_OCT_INPUT, "+ Octave B");
        configSwitch(SCALE_A_LOCK_PARAM, 0, 1, 0, "Enable Scale Presets A", { "Disabled", "Enabled" });
        configSwitch(SCALE_B_LOCK_PARAM, 0, 1, 0, "Enable Scale Presets B", { "Disabled", "Enabled" });
        getParamQuantity(SCALE_A_LOCK_PARAM)->randomizeEnabled = false;
        getParamQuantity(SCALE_B_LOCK_PARAM)->randomizeEnabled = false;
        configParam(SCALE_A_PARAM, 1.f, SCALEPRESETCOUNT, 1.f, "Scale Preset A");
        getParamQuantity(SCALE_A_PARAM)->snapEnabled = true;
        configParam(SCALE_B_PARAM, 1.f, SCALEPRESETCOUNT, 1.f, "Scale Preset B");
        getParamQuantity(SCALE_B_PARAM)->snapEnabled = true;
        configInput(SCALE_A_INPUT, "Scale Preset A");
        configInput(SCALE_B_INPUT, "Scale Preset B");

        int scaleOffset;
        for (int i = 0; i < SCALECOUNT; i++) {
            scaleOffset = SCALE_1_PARAM + i * SCALELEN;

            configSwitch(scaleOffset + 0, 0, 1, 1, "C", { "Off", "On" });
            configSwitch(scaleOffset + 1, 0, 1, 0, "C#", { "Off", "On" });
            configSwitch(scaleOffset + 2, 0, 1, 1, "D", { "Off", "On" });
            configSwitch(scaleOffset + 3, 0, 1, 0, "D#", { "Off", "On" });

            configSwitch(scaleOffset + 4, 0, 1, 1, "E", { "Off", "On" });
            configSwitch(scaleOffset + 5, 0, 1, 0, "F", { "Off", "On" });
            configSwitch(scaleOffset + 6, 0, 1, 0, "F#", { "Off", "On" });
            configSwitch(scaleOffset + 7, 0, 1, 1, "G", { "Off", "On" });

            configSwitch(scaleOffset + 8, 0, 1, 0, "G#", { "Off", "On" });
            configSwitch(scaleOffset + 9, 0, 1, 1, "A", { "Off", "On" });
            configSwitch(scaleOffset + 10, 0, 1, 0, "A#", { "Off", "On" });
            configSwitch(scaleOffset + 11, 0, 1, 0, "B", { "Off", "On" });
        }

        configInput(CLOCK_INPUT, "Clock");
        configInput(RESET_INPUT, "Reset");

        speedParamQuantity = configParam(SPEED_PARAM, 0.f, 3.f, 1.f, "Speed", " BPM", 4.0f, 32.f, 0.f);
        getParamQuantity(SPEED_PARAM)->randomizeEnabled = false;
        configInput(SPEED_INPUT, "Speed");

        configParam(LENGTH_PARAM, 1.f, 64.f, 8.f, "Length", " steps");
        getParamQuantity(LENGTH_PARAM)->snapEnabled = true;
        configInput(LENGTH_INPUT, "Length");

        configParam(TRANSPOSE_PARAM, -3.f, 3.f, 0.f, "Transpose", " V/Oct");
        getParamQuantity(TRANSPOSE_PARAM)->randomizeEnabled = false;
        configInput(TRANSPOSE_INPUT, "Transpose");

        configParam(GATE_LEN_PARAM, 0.01f, 2.0f, 0.2f, "Gate Length", " sec");
        configInput(GATE_LEN_INPUT, "Gate Length");

        configParam(VOICES_PARAM, 1.f, 8.f, 8.f, "Voice Count", " voice(s)");
        getParamQuantity(VOICES_PARAM)->snapEnabled = true;
        configInput(VOICES_INPUT, "Voice Count");

        configParam(SPREAD_PARAM, 0.f, 1.f, 0.f, "Spread");
        configInput(SPREAD_INPUT, "Spread");
       
        configParam(ALGO_X_PARAM, 0.f, 127.f, 1.f, "Algo X");
        getParamQuantity(ALGO_X_PARAM)->snapEnabled = true;
        configInput(ALGO_X_INPUT, "Algo X");

        configParam(ALGO_Y_PARAM, 0.f, 127.f, 1.f, "Algo Y");
        getParamQuantity(ALGO_Y_PARAM)->snapEnabled = true;
        configInput(ALGO_Y_INPUT, "Algo Y");

        configParam(SHIFT_PARAM, 0.f, 12.f, 0.f, "Shift");
        getParamQuantity(SHIFT_PARAM)->snapEnabled = true;
        configInput(SHIFT_INPUT, "Shift");

        configParam(SPACE_PARAM, 0.f, 16.f, 0.f, "Space");
        getParamQuantity(SPACE_PARAM)->snapEnabled = true;
        configInput(SPACE_INPUT, "Space");

        configParam(ROTATE_PARAM, -8.f, 8.f, 0.f, "Rotate");
        getParamQuantity(ROTATE_PARAM)->snapEnabled = true;
        configInput(ROTATE_INPUT, "Rotate");

        configParam(XMOD_PARAM, 0.f, 127.f, 0.f, "Cross Modulation");
        getParamQuantity(XMOD_PARAM)->snapEnabled = true;
        configInput(XMOD_INPUT, "Cross Modulation");

        configOutput(CLOCK_OUTPUT, "Clock");
        configOutput(RESET_OUTPUT, "Reset");
        
        configOutput(MOD_CV_1_OUTPUT, "Modulation CV 1 / Poly");
        configOutput(MOD_CV_2_OUTPUT, "Modulation CV 2");
        configOutput(MOD_CV_3_OUTPUT, "Modulation CV 3");
        configOutput(MOD_CV_4_OUTPUT, "Modulation CV 4");
        configOutput(MOD_GATE_1_OUTPUT, "Modulation Gate 1 / Poly");
        configOutput(MOD_GATE_2_OUTPUT, "Modulation Gate 2");
        configOutput(MOD_GATE_3_OUTPUT, "Modulation Gate 3");
        configOutput(MOD_GATE_4_OUTPUT, "Modulation Gate 4");

        configOutput(CV_1_OUTPUT, "Note CV 1 / Poly");
        configOutput(CV_2_OUTPUT, "Note CV 2");
        configOutput(CV_3_OUTPUT, "Note CV 3");
        configOutput(CV_4_OUTPUT, "Note CV 4");
        configOutput(CV_5_OUTPUT, "Note CV 5");
        configOutput(CV_6_OUTPUT, "Note CV 6");
        configOutput(CV_7_OUTPUT, "Note CV 7");
        configOutput(CV_8_OUTPUT, "Note CV 8");
        configOutput(GATE_1_OUTPUT, "Note Gate 1 / Poly");
        configOutput(GATE_2_OUTPUT, "Note Gate 2");
        configOutput(GATE_3_OUTPUT, "Note Gate 3");
        configOutput(GATE_4_OUTPUT, "Note Gate 4");
        configOutput(GATE_5_OUTPUT, "Note Gate 5");
        configOutput(GATE_6_OUTPUT, "Note Gate 6");
        configOutput(GATE_7_OUTPUT, "Note Gate 7");
        configOutput(GATE_8_OUTPUT, "Note Gate 8");
        
        outputs[CV_1_OUTPUT].setChannels(NOTECOUNT);
        outputs[GATE_1_OUTPUT].setChannels(NOTECOUNT);

        updateScales();
        updateScaleLeds();
        scaleAPreset = round(getCombinedValue(SCALE_A_PARAM, SCALE_A_INPUT)) - 1;
        scaleBPreset = round(getCombinedValue(SCALE_B_PARAM, SCALE_B_INPUT)) - 1;
        
        initHistory();
        clockIntervalCounter = clockInterval = 0;
    }

    int scaleSwitchMode = 0;
    
    dsp::SchmittTrigger clockIn{}, resetIn{}, scaleSwitchTrig{}, scaleInputTrig{};
    dsp::PulseGenerator clockOut, resetOut;
    ParamQuantity* speedParamQuantity;

    float internalClock = 2.f, clockInterval, clockIntervalCounter;
    
    int length{}, voices{}, algoX{}, algoY{}, shift{}, rotate{}, space{};
    double speed{};
    float transpose{}, gateLength{}, spread{};
    
    int scales[SCALECOUNT + 1][SCALELEN] = {};
    int scaleCount[SCALECOUNT + 1] = {};
    int scale = 0, scaleAPreset, scaleBPreset;

    // engine state
    int globalCounter = 0;
    int totalWeight = 0;
    int counter[TRACKCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int divisor[TRACKCOUNT] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    int phase[TRACKCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int trackOn[TRACKCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int weightOn[TRACKCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };

    int notes[NOTECOUNT][HISTORYCOUNT]{};
    bool gateOn[NOTECOUNT][HISTORYCOUNT]{};
    bool gateChanged[NOTECOUNT][HISTORYCOUNT]{};

    float gateTimer[NOTECOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    bool gateTriggered[NOTECOUNT]{};
    int muted[NOTECOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int shifts[NOTECOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };

    float modCvs[MODCOUNT] { 0, 0, 0, 0, 0, 0, 0, 0 };
    bool modGate[MODCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    // engine state

    float getCombinedValue(int param, int input) {
        float min = paramQuantities[param]->minValue;
        float max = paramQuantities[param]->maxValue;
        float i = inputs[input].getVoltage() * (max - min) / 10.f + params[param].getValue();

        if (min > max) {
            float t = min;
            min = max;
            max = t;
        }
        if (i < min) i = min; else if (i > max) i = max;

        return i;
    }

    void updateScaleLeds() {
        if (scale == SCALECOUNT) {
            lights[SCALE_A_LIGHT].setBrightness(1.f);
            lights[SCALE_B_LIGHT].setBrightness(1.f);
        } else if (scale == 1) {
            lights[SCALE_A_LIGHT].setBrightness(0.f);
            lights[SCALE_B_LIGHT].setBrightness(1.f);
        } else {
            lights[SCALE_A_LIGHT].setBrightness(1.f);
            lights[SCALE_B_LIGHT].setBrightness(0.f);
        }
    }

    void processScaleSwitch() {
        if (scaleSwitchTrig.process(params[SCALE_PARAM].getValue() > 0.f)) {
            scale = (scale + 1) % (SCALECOUNT + 1);
        }
        
        if (scaleSwitchMode == 0) { // trigger mode
            if (scaleInputTrig.process(rescale(inputs[SCALE_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f))) {
                scale = scale ? 0 : 1;
            }
        } else { // gate mode
            scale = inputs[SCALE_INPUT].getVoltage() ? 1 : 0;
        }
        
        updateScaleLeds();
    }
    
    void processScalePresets() {
        int newScaleAPreset = round(getCombinedValue(SCALE_A_PARAM, SCALE_A_INPUT)) - 1;
        int newScaleBPreset = round(getCombinedValue(SCALE_B_PARAM, SCALE_B_INPUT)) - 1;
        
        if (newScaleAPreset != scaleAPreset) {
            scaleAPreset = newScaleAPreset;
            if (params[SCALE_A_LOCK_PARAM].getValue() > 0.f) {
                for (int i = 0; i < SCALELEN; i++)
                    params[SCALE_1_PARAM + i].setValue(scalePresets[scaleAPreset][i]);
            }
        }

        if (newScaleBPreset != scaleBPreset) {
            scaleBPreset = newScaleBPreset;
            if (params[SCALE_B_LOCK_PARAM].getValue() > 0.f) {
                for (int i = 0; i < SCALELEN; i++)
                    params[SCALE_1_PARAM + i + SCALELEN].setValue(scalePresets[scaleBPreset][i]);
            }
        }
    }

    void updateScales() {
        scaleCount[SCALECOUNT] = 0;
        
        int count = 0;
        for (int i = 0; i < SCALELEN; i++) {
            if (params[SCALE_1_PARAM + i].getValue() > 0) {
                scales[0][count] = scales[SCALECOUNT][count] = i;
                count++;
            }
        }
        scaleCount[0] = scaleCount[SCALECOUNT] = count;

        count = 0;
        for (int i = 0; i < SCALELEN; i++) {
            if (params[SCALE_1_PARAM + i + SCALELEN].getValue() > 0) {
                scales[1][count] = i;
                scales[SCALECOUNT][count] = i + 12;
                count++;
            }
        }
        scaleCount[1] = count;
        scaleCount[SCALECOUNT] += count;
    }

    void updateParameters() {
        int speedBPM = round(inputs[SPEED_INPUT].getVoltage() * (2048 - 32) / 10.f + speedParamQuantity->getDisplayValue());
        speed = 60.0 / speedBPM;
        length = round(getCombinedValue(LENGTH_PARAM, LENGTH_INPUT));
        transpose = inputs[TRANSPOSE_INPUT].getVoltage() + params[TRANSPOSE_PARAM].getValue();
        float gateLen = getCombinedValue(GATE_LEN_PARAM, GATE_LEN_INPUT);
        gateLength = speed * gateLen;
        spread = getCombinedValue(SPREAD_PARAM, SPREAD_INPUT);
    }

    void updateSyncedParameters() {
        voices = round(getCombinedValue(VOICES_PARAM, VOICES_INPUT)) - 1;
        algoX = round(getCombinedValue(ALGO_X_PARAM, ALGO_X_INPUT));
        algoY = round(getCombinedValue(ALGO_Y_PARAM, ALGO_Y_INPUT));
        shift = round(getCombinedValue(SHIFT_PARAM, SHIFT_INPUT));
        space = round(getCombinedValue(SPACE_PARAM, SPACE_INPUT));
        rotate = round(getCombinedValue(ROTATE_PARAM, ROTATE_INPUT));
        float xmod = getCombinedValue(XMOD_PARAM, XMOD_INPUT) / 127.f;
        algoX += round(xmod * outputs[CV_1_OUTPUT].getVoltage() * 12.8f);
        if (xmod > 0.8) rotate += round((xmod - 0.8) * outputs[CV_5_OUTPUT].getVoltage() * 1.6f);
        else if (xmod > 0.6) shift += round((xmod - 0.4) * outputs[CV_7_OUTPUT].getVoltage() * 1.6f);
        else if (xmod > 0.4) algoY += round((xmod - 0.2) * outputs[CV_8_OUTPUT].getVoltage() * 12.8f);
    }

    void updateTrackParameters() {
        divisor[0] = (algoX & 3) + 1;
        phase[0] = algoX >> 5;

        for (int i = 1; i < TRACKCOUNT; i++) {
            if (algoX & (1 << (i + 2))) divisor[i] = divisor[i - 1] + 1; else divisor[i] = divisor[i - 1] - 1;
            if (divisor[i] < 0) divisor[i] = 1 - divisor[i];
            if (divisor[i] == 0) divisor[i] = i + 2;
            phase[i] = ((algoX & (0b11 << i)) + i) % divisor[i];
        }

        for (int i = 0; i < NOTECOUNT; i++) shifts[i] = getCombinedValue(SHIFT_PARAM, SHIFT_INPUT);
    }

    void updateCounters() {
        if (resetIn.process(rescale(inputs[RESET_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f))) {
            globalCounter = 0;
            for (int i = 0; i < TRACKCOUNT; i++) counter[i] = 0;
            resetOut.trigger(1e-3);
        } else {

            if (++globalCounter >= length) {
                globalCounter = 0;
                for (int i = 0; i < TRACKCOUNT; i++) counter[i] = 0;
                resetOut.trigger(1e-3);
            } else {
                for (int i = 0; i < TRACKCOUNT; i++) counter[i]++;
            }
        }

        totalWeight = 0;
        for (int i = 0; i < TRACKCOUNT; i++) {
            trackOn[i] = ((counter[i] + phase[i]) / divisor[i]) & 1;
            weightOn[i] = trackOn[i] ? weights[i] : 0;
            totalWeight += weightOn[i];
        }

        for (int i = 0; i < NOTECOUNT; i++) {
            shifts[i] = shift;
            if (shift > SCALELEN / 2) shifts[i] += i;
        }
    }

    void updateMod() {
        for (int i = 0; i < TRACKCOUNT; i++) modGate[i] = trackOn[i] ? trackOn[i] : (phase[i] + i) & 1;

        modCvs[0] = totalWeight + weightOn[0];
        modCvs[1] = weights[1] * (modGate[3] + modGate[2]) + weights[2] * (modGate[0] + modGate[2]);
        modCvs[2] = weights[0] * (modGate[2] + modGate[1]) + weights[3] * (modGate[0] + modGate[3]);
        modCvs[3] = weights[1] * (modGate[1] + modGate[2]) + weights[2] * (modGate[2] + modGate[3]) + weights[3] * (modGate[3] + modGate[2]);
        modCvs[4] = totalWeight + weightOn[7];
        modCvs[5] = weights[6] * (modGate[4] + modGate[5]) + weights[5] * (modGate[7] + modGate[5]);
        modCvs[6] = weights[7] * (modGate[5] + modGate[6]) + weights[4] * (modGate[7] + modGate[4]);
        modCvs[7] = weights[6] * (modGate[6] + modGate[5]) + weights[5] * (modGate[5] + modGate[4]) + weights[4] * (modGate[4] + modGate[3]);

        for (int i = 0; i < MODCOUNT; i++) modCvs[i] = (int(modCvs[i]) % 30) / 3.f;
    }

    void initHistory() {
        for (uint8_t n = 0; n < NOTECOUNT; n++)
            for (uint8_t h = 1; h < HISTORYCOUNT; h++) {
                notes[n][h] = 0;
                gateOn[n][h] = 0;
                gateChanged[n][h] = 0;
            }
    }

    void pushHistory() {
        for (uint8_t n = 0; n < NOTECOUNT; n++)
            for (int8_t h = HISTORYCOUNT - 1; h > 0; h--) {
                notes[n][h] = notes[n][h-1];
                gateOn[n][h] = gateOn[n][h-1];
                gateChanged[n][h] = gateChanged[n][h-1];
            }
    }

    void calculateNote(int n) {
        int mask = algoY >> 3;

        notes[n][0] = 0;
        for (int j = 0; j < TRACKCOUNT; j++) {
            if (trackOn[j] && (mask & (1 << j))) notes[n][0] += weightOn[j];
        }

        if (n < 4) {
            if (algoY & 1) notes[n][0] += weightOn[(n + 1) % TRACKCOUNT_LEGACY];
            if (algoY & 2) notes[n][0] += weightOn[(n + 2) % TRACKCOUNT_LEGACY];
            if (algoY & 4) notes[n][0] += weightOn[(n + 3) % TRACKCOUNT_LEGACY];
        } else {
            if (algoY & 1) notes[n][0] += weightOn[(n + 1) % TRACKCOUNT];
            if (algoY & 2) notes[n][0] += weightOn[(n + 2) % TRACKCOUNT];
            if (algoY & 4) notes[n][0] += weightOn[(n + 3) % TRACKCOUNT];
        }

        notes[n][0] += shifts[n];
    }

    void calculateNextNote(int n) {
        int mask = gatePresets[algoY >> 3][n];
        if (mask == 0) mask = 0b0101;
        for (int i = 0; i < n; i++) mask = ((mask & 1) << 3) | (mask >> 1);

        int g = 0;
        for (int j = 0; j < TRACKCOUNT; j++) {
            if (trackOn[j] && (mask & (1 << j))) g = 1;
            // if (mask & (1 << j)) g = 1;
        }

        if (n < 4) {
            if (algoY & 1) g ^= trackOn[n % TRACKCOUNT_LEGACY] << 1;
            if (algoY & 2) g ^= trackOn[(n + 2) % TRACKCOUNT_LEGACY] << 2;
            if (algoY & 4) g ^= trackOn[(n + 3) % TRACKCOUNT_LEGACY] << 3;
        } else {
            if (algoY & 1) g ^= trackOn[n % TRACKCOUNT] << 1;
            if (algoY & 2) g ^= trackOn[(n + 2) % TRACKCOUNT] << 2;
            if (algoY & 4) g ^= trackOn[(n + 3) % TRACKCOUNT] << 3;
        }

        bool previousGatesOn = 1;
        
        if (n < NOTECOUNT_LEGACY) {
            for (int i = 0; i < NOTECOUNT_LEGACY - 1; i++) previousGatesOn &= gateChanged[i][0] & gateOn[i][0];
            if (n == NOTECOUNT_LEGACY - 1 && previousGatesOn) g = 0;
        } else {
            for (int i = 0; i < NOTECOUNT - 1; i++) previousGatesOn &= gateChanged[i][0] & gateOn[i][0];
            if (n == NOTECOUNT - 1 && previousGatesOn) g = 0;
        }

        gateChanged[n][0] = gateOn[n][0] != g;
        gateOn[n][0] = g;
        if (gateChanged[n][0]) calculateNote(n);
    }

    void process(const ProcessArgs& args) override {
        bool advance = 0;
        if (inputs[CLOCK_INPUT].getChannels()) {
            advance = clockIn.process(rescale(inputs[CLOCK_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f));
        } else {
            internalClock += args.sampleTime;
            if (internalClock >= speed) {
                advance = 1;
                internalClock = 0;
            }
        }

        updateParameters();
        if (advance) updateSyncedParameters();
        updateTrackParameters();
        processScaleSwitch();
        processScalePresets();

        if (advance) {
            updateScales();
            updateCounters();
            updateMod();
            pushHistory();
            for (int n = 0; n < NOTECOUNT; n++) calculateNextNote(n);
            clockOut.trigger(1e-3);
            clockInterval = clockIntervalCounter;
            clockIntervalCounter = 0;
            for (int i = 0; i < NOTECOUNT; i++) gateTriggered[i] = false;
            
            for (int i = 0; i < NOTECOUNT; i++) {
                if (muted[i] > 0) {
                    muted[i]--;
                } else {
                    float rnd = random::get<float>() * 15.f + 0.01f;
                    if (rnd < space) muted[i] = space;
                }
            }
        } else {
            clockIntervalCounter += args.sampleTime;
        }

        float cv, g, delta;
        int history;
        cv = scales[0][0];
        
        for (int n = 0; n < NOTECOUNT; n++) {
            delta = (spread * n * clockInterval) / (float)NOTECOUNT;
            
            history = (rotate > 0 ? rotate * n : -rotate * (NOTECOUNT - 1 - n)) / NOTECOUNT;
            if (history >= HISTORYCOUNT) history = HISTORYCOUNT - 1;
            else if (history < 0) history = 0;

            if (scaleCount[scale] == 0) {
                g = 0;
            } else {
                int nindex = notes[n][history] % scaleCount[scale];
                int sindex = scale < SCALECOUNT ? scale : nindex < scaleCount[0] ? 0 : 1;
                
                float trans = transpose;
                if ((sindex == 0 && (inputs[SCALE_A_OCT_INPUT].getVoltage() > 0 || params[SCALE_A_OCT_PARAM].getValue() > 0)) ||
                    (sindex == 1 && (inputs[SCALE_B_OCT_INPUT].getVoltage() > 0 || params[SCALE_B_OCT_PARAM].getValue() > 0))) trans += 1.f;
                
                cv = scales[scale][nindex] / 12.f + std::min(2, notes[n][history] / 12) + trans;
                
                if (n > voices) {
                    g = 0;
                } else {
                    if ((clockIntervalCounter >= delta) && !gateTriggered[n]) {
                        gateTriggered[n] = true;
                        if (gateChanged[n][history] && gateOn[n][history] && !muted[n]) {
                            gateTimer[n] = gateLength;
                        }
                    }

                    if (gateTimer[n] > 0) gateTimer[n] -= args.sampleTime;
                    if (gateTimer[n] < 0) gateTimer[n] = 0;
                    g = gateTimer[n] > 0 ? 10 : 0;
                }
            }
            
            // prevent feedback if a note CV is connected to TRANS
            if (cv > 10.f) cv = 10.f;
            else if (cv < -10.f) cv = -10.f;

            outputs[CV_1_OUTPUT + n].setVoltage(cv);
            outputs[GATE_1_OUTPUT + n].setVoltage(g);
            
            outputs[CV_1_OUTPUT].setVoltage(cv, n);
            outputs[GATE_1_OUTPUT].setVoltage(g, n);
        }

        outputs[CV_1_OUTPUT].setChannels(NOTECOUNT);
        outputs[GATE_1_OUTPUT].setChannels(NOTECOUNT);

        for (int i = 0; i < MODOUTPUTCOUNT; i++) {
            outputs[MOD_GATE_1_OUTPUT + i].setVoltage(modGate[i] ? 10.f : 0.f);
            outputs[MOD_GATE_1_OUTPUT].setVoltage(modGate[i] ? 10.f : 0.f, i);
            
            outputs[MOD_CV_1_OUTPUT + i].setVoltage(modCvs[i]);
            outputs[MOD_CV_1_OUTPUT].setVoltage(modCvs[i], i);
        }
        
        for (int i = MODOUTPUTCOUNT; i < MODCOUNT; i++) {
            outputs[MOD_GATE_1_OUTPUT].setVoltage(modGate[i] ? 10.f : 0.f, i);
            outputs[MOD_CV_1_OUTPUT].setVoltage(modCvs[i], i);
        }
        
        outputs[MOD_GATE_1_OUTPUT].setChannels(MODCOUNT);
        outputs[MOD_CV_1_OUTPUT].setChannels(MODCOUNT);

        outputs[CLOCK_OUTPUT].setVoltage(clockOut.process(args.sampleTime) ? 10.f : 0.f);
        outputs[RESET_OUTPUT].setVoltage(resetOut.process(args.sampleTime) ? 10.f : 0.f);
    }

    json_t* dataToJson() override {
        json_t* rootJ = json_object();
        json_t* arrayJ;
        
        json_object_set_new(rootJ, "scaleSwitchMode", json_integer(scaleSwitchMode));
        json_object_set_new(rootJ, "selectedScale", json_integer(scale));

        json_object_set_new(rootJ, "globalCounter", json_integer(globalCounter));
        json_object_set_new(rootJ, "totalWeight", json_integer(totalWeight));
        
        arrayJ = json_array();
        for (int i = 0; i < TRACKCOUNT; i++) json_array_insert_new(arrayJ, i, json_integer(counter[i]));
        json_object_set_new(rootJ, "counter", arrayJ);
        
        arrayJ = json_array();
        for (int i = 0; i < TRACKCOUNT; i++) json_array_insert_new(arrayJ, i, json_integer(divisor[i]));
        json_object_set_new(rootJ, "divisor", arrayJ);
        
        arrayJ = json_array();
        for (int i = 0; i < TRACKCOUNT; i++) json_array_insert_new(arrayJ, i, json_integer(phase[i]));
        json_object_set_new(rootJ, "phase", arrayJ);
        
        arrayJ = json_array();
        for (int i = 0; i < TRACKCOUNT; i++) json_array_insert_new(arrayJ, i, json_integer(trackOn[i]));
        json_object_set_new(rootJ, "trackOn", arrayJ);
        
        arrayJ = json_array();
        for (int i = 0; i < TRACKCOUNT; i++) json_array_insert_new(arrayJ, i, json_integer(weightOn[i]));
        json_object_set_new(rootJ, "weightOn", arrayJ);
        
        for (int h = 0; h < HISTORYCOUNT; h++) {
            arrayJ = json_array();
            for (int i = 0; i < NOTECOUNT; i++) json_array_insert_new(arrayJ, i, json_integer(notes[i][h]));
            json_object_set_new(rootJ, ("notes" + std::to_string(h)).c_str(), arrayJ);
        }

        for (int h = 0; h < HISTORYCOUNT; h++) {
            arrayJ = json_array();
            for (int i = 0; i < NOTECOUNT; i++) json_array_insert_new(arrayJ, i, json_boolean(gateOn[i][h]));
            json_object_set_new(rootJ, ("gateOn" + std::to_string(h)).c_str(), arrayJ);
        }

        for (int h = 0; h < HISTORYCOUNT; h++) {
            arrayJ = json_array();
            for (int i = 0; i < NOTECOUNT; i++) json_array_insert_new(arrayJ, i, json_boolean(gateChanged[i][h]));
            json_object_set_new(rootJ, ("gateChanged" + std::to_string(h)).c_str(), arrayJ);
        }

        arrayJ = json_array();
        for (int i = 0; i < NOTECOUNT; i++) json_array_insert_new(arrayJ, i, json_real(gateTimer[i]));
        json_object_set_new(rootJ, "gateTimer", arrayJ);
        
        arrayJ = json_array();
        for (int i = 0; i < NOTECOUNT; i++) json_array_insert_new(arrayJ, i, json_boolean(gateTriggered[i]));
        json_object_set_new(rootJ, "gateTriggered", arrayJ);
        
        arrayJ = json_array();
        for (int i = 0; i < NOTECOUNT; i++) json_array_insert_new(arrayJ, i, json_integer(muted[i]));
        json_object_set_new(rootJ, "muted", arrayJ);
        
        arrayJ = json_array();
        for (int i = 0; i < NOTECOUNT; i++) json_array_insert_new(arrayJ, i, json_integer(shifts[i]));
        json_object_set_new(rootJ, "shifts", arrayJ);
        
        arrayJ = json_array();
        for (int i = 0; i < MODCOUNT; i++) json_array_insert_new(arrayJ, i, json_real(modCvs[i]));
        json_object_set_new(rootJ, "modCvs", arrayJ);
        
        arrayJ = json_array();
        for (int i = 0; i < MODCOUNT; i++) json_array_insert_new(arrayJ, i, json_boolean(modGate[i]));
        json_object_set_new(rootJ, "modGate", arrayJ);

        return rootJ;
    }

    void dataFromJson(json_t* rootJ) override {
        json_t* objectJ;
        json_t* arrayJ;
        
        objectJ = json_object_get(rootJ, "scaleSwitchMode");
        if (objectJ) scaleSwitchMode = json_integer_value(objectJ);

        objectJ = json_object_get(rootJ, "selectedScale");
        if (objectJ) {
            scale = json_integer_value(objectJ);
            scaleAPreset = round(getCombinedValue(SCALE_A_PARAM, SCALE_A_INPUT)) - 1;
            scaleBPreset = round(getCombinedValue(SCALE_B_PARAM, SCALE_B_INPUT)) - 1;
            updateScaleLeds();
            updateScales();
        }
        
        objectJ = json_object_get(rootJ, "globalCounter");
        if (objectJ) globalCounter = json_integer_value(objectJ);
        objectJ = json_object_get(rootJ, "totalWeight");
        if (objectJ) totalWeight = json_integer_value(objectJ);
        
        arrayJ = json_object_get(rootJ, "counter");
        if (arrayJ) {
            for (int i = 0; i < TRACKCOUNT; i++) {
                objectJ = json_array_get(arrayJ, i);
                if (objectJ) counter[i] = json_integer_value(objectJ);
            }
        }

        arrayJ = json_object_get(rootJ, "divisor");
        if (arrayJ) {
            for (int i = 0; i < TRACKCOUNT; i++) {
                objectJ = json_array_get(arrayJ, i);
                if (objectJ) divisor[i] = json_integer_value(objectJ);
            }
        }

        arrayJ = json_object_get(rootJ, "phase");
        if (arrayJ) {
            for (int i = 0; i < TRACKCOUNT; i++) {
                objectJ = json_array_get(arrayJ, i);
                if (objectJ) phase[i] = json_integer_value(objectJ);
            }
        }

        arrayJ = json_object_get(rootJ, "trackOn");
        if (arrayJ) {
            for (int i = 0; i < TRACKCOUNT; i++) {
                objectJ = json_array_get(arrayJ, i);
                if (objectJ) trackOn[i] = json_integer_value(objectJ);
            }
        }

        arrayJ = json_object_get(rootJ, "weightOn");
        if (arrayJ) {
            for (int i = 0; i < TRACKCOUNT; i++) {
                objectJ = json_array_get(arrayJ, i);
                if (objectJ) weightOn[i] = json_integer_value(objectJ);
            }
        }

        for (int h = 0; h < HISTORYCOUNT; h++) {
            arrayJ = json_object_get(rootJ, ("notes" + std::to_string(h)).c_str());
            if (arrayJ) {
                for (int i = 0; i < NOTECOUNT; i++) {
                    objectJ = json_array_get(arrayJ, i);
                    if (objectJ) notes[i][h] = json_integer_value(objectJ);
                }
            }
        }

        for (int h = 0; h < HISTORYCOUNT; h++) {
            arrayJ = json_object_get(rootJ, ("gateOn" + std::to_string(h)).c_str());
            if (arrayJ) {
                for (int i = 0; i < NOTECOUNT; i++) {
                    objectJ = json_array_get(arrayJ, i);
                    if (objectJ) gateOn[i][h] = json_boolean_value(objectJ);
                }
            }
        }

        for (int h = 0; h < HISTORYCOUNT; h++) {
            arrayJ = json_object_get(rootJ, ("gateChanged" + std::to_string(h)).c_str());
            if (arrayJ) {
                for (int i = 0; i < NOTECOUNT; i++) {
                    objectJ = json_array_get(arrayJ, i);
                    if (objectJ) gateChanged[i][h] = json_boolean_value(objectJ);
                }
            }
        }

        arrayJ = json_object_get(rootJ, "gateTimer");
        if (arrayJ) {
            for (int i = 0; i < NOTECOUNT; i++) {
                objectJ = json_array_get(arrayJ, i);
                if (objectJ) gateTimer[i] = json_real_value(objectJ);
            }
        }

        arrayJ = json_object_get(rootJ, "gateTriggered");
        if (arrayJ) {
            for (int i = 0; i < NOTECOUNT; i++) {
                objectJ = json_array_get(arrayJ, i);
                if (objectJ) gateTriggered[i] = json_boolean_value(objectJ);
            }
        }

        arrayJ = json_object_get(rootJ, "muted");
        if (arrayJ) {
            for (int i = 0; i < NOTECOUNT; i++) {
                objectJ = json_array_get(arrayJ, i);
                if (objectJ) muted[i] = json_integer_value(objectJ);
            }
        }

        arrayJ = json_object_get(rootJ, "shifts");
        if (arrayJ) {
            for (int i = 0; i < NOTECOUNT; i++) {
                objectJ = json_array_get(arrayJ, i);
                if (objectJ) shifts[i] = json_integer_value(objectJ);
            }
        }

        arrayJ = json_object_get(rootJ, "modCvs");
        if (arrayJ) {
            for (int i = 0; i < MODCOUNT; i++) {
                objectJ = json_array_get(arrayJ, i);
                if (objectJ) modCvs[i] = json_real_value(objectJ);
            }
        }

        arrayJ = json_object_get(rootJ, "modGate");
        if (arrayJ) {
            for (int i = 0; i < MODCOUNT; i++) {
                objectJ = json_array_get(arrayJ, i);
                if (objectJ) modGate[i] = json_boolean_value(objectJ);
            }
        }
    }
};

struct SDOrcasHeartWidget : ModuleWidget {
    SDOrcasHeartWidget(SDOrcasHeartV2* module) {
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SDOrcasHeartV2.svg")));

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

    void appendContextMenu(Menu* menu) override {
        SDOrcasHeartV2* module = getModule<SDOrcasHeartV2>();
        menu->addChild(new MenuSeparator);
        menu->addChild(createIndexPtrSubmenuItem("Scale Switch Mode", {"Trigger", "Gate"}, &module->scaleSwitchMode));
    }
};

Model* modelSDOrcasHeartV2 = createModel<SDOrcasHeartV2, SDOrcasHeartWidget>("SDOrcasHeartV2");
