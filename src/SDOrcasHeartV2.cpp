#include "plugin.hpp"

#include <math.h>
#include <string>

// #include "SDSharedComponents.hpp"

#define SCALELEN 12
#define SCALECOUNT 2
#define SCALEPRESETCOUNT 16
#define NOTECOUNT 8
#define NOTECOUNT_LEGACY 4
#define HISTORYCOUNT 8
#define MODCOUNT 4
#define TRACKCOUNT 8
#define TRACKCOUNT_LEGACY 4
#define GATEPRESETCOUNT 16

struct SDOrcasHeartV2 : Module {

    int gatePresets[GATEPRESETCOUNT][NOTECOUNT] = {
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

    int scalePresets[SCALEPRESETCOUNT][SCALELEN] = {
    //   0  1  2  3    4  5  6  7    8  9  10 11
        {1, 0, 1, 0,   1, 1, 0, 1,   0, 1, 0, 1}, // major
        {1, 0, 1, 0,   1, 1, 0, 1,   1, 0, 0, 1}, // harmonic major
        {1, 0, 1, 0,   1, 1, 1, 0,   1, 0, 1, 0}, // major locrian
        {1, 0, 1, 0,   1, 0, 0, 1,   0, 1, 0, 0}, // major pentatonic

        {1, 0, 1, 1,   0, 1, 0, 1,   1, 0, 1, 0}, // minor
        {1, 0, 1, 1,   0, 1, 0, 1,   1, 0, 0, 1}, // harmonic minor
        {1, 0, 1, 0,   1, 0, 1, 1,   0, 1, 1, 0}, // lydian dominant
        {0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0},

        {0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0},
        {0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0},
        {0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0},
        {0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0},

        {0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0},
        {0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0},
        {0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0},
        {0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0}
    };

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
        // SCALE_A_LIGHT,
        // SCALE_B_LIGHT,
        NUM_LIGHTS
    };

    SDOrcasHeartV2() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

        // configLight(SCALE_A_LIGHT, "Scale A Selected");
        // configLight(SCALE_B_LIGHT, "Scale B Selected");
        configButton(SCALE_PARAM, "Toggle Scales A/B/both");
        configInput(SCALE_INPUT, "Toggle Scales A/B");
        configSwitch(SCALE_A_OCT_PARAM, 0, 1, 0, "Octave A", { "Down", "Up" });
        configSwitch(SCALE_B_OCT_PARAM, 0, 1, 0, "Octave B", { "Down", "Up" });
        configInput(SCALE_A_OCT_INPUT, "+ Octave A");
        configInput(SCALE_B_OCT_INPUT, "+ Octave B");
        configSwitch(SCALE_A_LOCK_PARAM, 0, 1, 1, "Enable Scale Presets A", { "Disabled", "Enabled" });
        configSwitch(SCALE_B_LOCK_PARAM, 0, 1, 1, "Enable Scale Presets B", { "Disabled", "Enabled" });
        configParam(SCALE_A_PARAM, 1.f, SCALEPRESETCOUNT, 1.f, "Scale Preset A");
        getParamQuantity(SCALE_A_PARAM)->snapEnabled = true;
        configParam(SCALE_B_PARAM, 1.f, SCALEPRESETCOUNT, 1.f, "Scale Preset B");
        getParamQuantity(SCALE_B_PARAM)->snapEnabled = true;
        configInput(SCALE_A_INPUT, "Scale Preset A");
        configInput(SCALE_B_INPUT, "Scale Preset B");

        int scaleOffset;
        for (int i = 0; i < SCALECOUNT; i++) {
            scaleOffset = SCALE_1_PARAM + i * SCALELEN;

            configSwitch(scaleOffset + 0, 0, 1, i == 0, "C", { "Off", "On" });
            configSwitch(scaleOffset + 1, 0, 1, 0, "C#", { "Off", "On" });
            configSwitch(scaleOffset + 2, 0, 1, i == 0, "D", { "Off", "On" });
            configSwitch(scaleOffset + 3, 0, 1, 0, "D#", { "Off", "On" });

            configSwitch(scaleOffset + 4, 0, 1, i == 0, "E", { "Off", "On" });
            configSwitch(scaleOffset + 5, 0, 1, 0, "F", { "Off", "On" });
            configSwitch(scaleOffset + 6, 0, 1, 0, "F#", { "Off", "On" });
            configSwitch(scaleOffset + 7, 0, 1, 0, "G", { "Off", "On" });

            configSwitch(scaleOffset + 8, 0, 1, 0, "G#", { "Off", "On" });
            configSwitch(scaleOffset + 9, 0, 1, 0, "A", { "Off", "On" });
            configSwitch(scaleOffset + 10, 0, 1, 0, "A#", { "Off", "On" });
            configSwitch(scaleOffset + 11, 0, 1, 0, "B", { "Off", "On" });
        }

        configInput(CLOCK_INPUT, "Clock");
        configInput(RESET_INPUT, "Reset");

        configParam(SPEED_PARAM, 20.f, 2000.f, 400.f, "Speed");
        configInput(SPEED_INPUT, "Speed");

        configParam(LENGTH_PARAM, 1.f, 64.f, 8.f, "Length");
        getParamQuantity(LENGTH_PARAM)->snapEnabled = true;
        configInput(LENGTH_INPUT, "Length");

        configParam(TRANSPOSE_PARAM, -3.f, 3.f, 0.f, "Transpose");
        configInput(TRANSPOSE_INPUT, "Transpose");

        configParam(GATE_LEN_PARAM, 0.01f, 4.0f, 0.2f, "Gate Length");
        configInput(GATE_LEN_INPUT, "Gate Length");

        configParam(VOICES_PARAM, 1.f, 8.f, 8.f, "Voice Count");
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

        configParam(SPACE_PARAM, 0.f, 1.f, 0.f, "Space");
        configInput(SPACE_INPUT, "Space");

        configParam(ROTATE_PARAM, -8.f, 8.f, 0.f, "Rotate");
        getParamQuantity(ROTATE_PARAM)->snapEnabled = true;
        configInput(ROTATE_INPUT, "Rotate");

        configParam(XMOD_PARAM, 0.f, 1.f, 0.f, "Cross Modulation");
        configInput(XMOD_INPUT, "Cross Modulation");

        configOutput(CLOCK_OUTPUT, "Clock");
        configOutput(RESET_OUTPUT, "Reset");
        
        configOutput(MOD_CV_1_OUTPUT, "Modulation CV #1");
        configOutput(MOD_CV_2_OUTPUT, "Modulation CV #2");
        configOutput(MOD_CV_3_OUTPUT, "Modulation CV #3");
        configOutput(MOD_CV_4_OUTPUT, "Modulation CV #4");
        configOutput(MOD_GATE_1_OUTPUT, "Modulation Gate #1");
        configOutput(MOD_GATE_2_OUTPUT, "Modulation Gate #2");
        configOutput(MOD_GATE_3_OUTPUT, "Modulation Gate #3");
        configOutput(MOD_GATE_4_OUTPUT, "Modulation Gate #4");

        configOutput(CV_1_OUTPUT, "Note CV #1 1V/Oct");
        configOutput(CV_2_OUTPUT, "Note CV #2 1V/Oct");
        configOutput(CV_3_OUTPUT, "Note CV #3 1V/Oct");
        configOutput(CV_4_OUTPUT, "Note CV #4 1V/Oct");
        configOutput(CV_5_OUTPUT, "Note CV #5 1V/Oct");
        configOutput(CV_6_OUTPUT, "Note CV #6 1V/Oct");
        configOutput(CV_7_OUTPUT, "Note CV #7 1V/Oct");
        configOutput(CV_8_OUTPUT, "Note CV #8 1V/Oct");
        configOutput(GATE_1_OUTPUT, "Note Gate #1");
        configOutput(GATE_2_OUTPUT, "Note Gate #2");
        configOutput(GATE_3_OUTPUT, "Note Gate #3");
        configOutput(GATE_4_OUTPUT, "Note Gate #4");
        configOutput(GATE_5_OUTPUT, "Note Gate #5");
        configOutput(GATE_6_OUTPUT, "Note Gate #6");
        configOutput(GATE_7_OUTPUT, "Note Gate #7");
        configOutput(GATE_8_OUTPUT, "Note Gate #8");
        
        outputs[CV_1_OUTPUT].setChannels(NOTECOUNT);
        outputs[GATE_1_OUTPUT].setChannels(NOTECOUNT);

        updateScales();
        updateScaleLeds();
        scaleAPreset = round(getCombinedValue(SCALE_A_PARAM, SCALE_A_INPUT)) - 1;
        scaleBPreset = round(getCombinedValue(SCALE_B_PARAM, SCALE_B_INPUT)) - 1;
        
        initHistory();
        clockIntervalCounter = clockInterval = 0;
    }

    dsp::SchmittTrigger clockIn, resetIn, scaleSwitchTrig, scaleInputTrig;
    dsp::PulseGenerator clockOut, resetOut;

    int length, voices, algoX, algoY, shift, rotate;
    float speed, transpose, gateLength, spread, space;
    
    int scales[SCALECOUNT + 1][SCALELEN] = {};
    int scaleCount[SCALECOUNT + 1] = {};
    int scale = 0, scaleAPreset, scaleBPreset;

    float internalClock = 2.f, clockInterval, clockIntervalCounter;
    
    // engine state
    int globalCounter = 0;
    int counter[TRACKCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int divisor[TRACKCOUNT] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    int phase[TRACKCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int weights[TRACKCOUNT] = { 1, 2, 4, 7, 5, 3, 11, 13 };
    int trackOn[TRACKCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int weightOn[TRACKCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int totalWeight = 0;

    int notes[NOTECOUNT][HISTORYCOUNT];
    bool gateOn[NOTECOUNT][HISTORYCOUNT];
    bool gateChanged[NOTECOUNT][HISTORYCOUNT];
    float gateTimer[NOTECOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    bool gateTriggered[NOTECOUNT];
    int shifts[NOTECOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int muted[NOTECOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };

    int modCvs[MODCOUNT];
    bool modGateOn[MODCOUNT] = { 0, 0, 0, 0 };
    bool modGateChanged[MODCOUNT] = { 1, 1, 1, 1 };
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
        /*
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
        */
    }

    void processScaleSwitch() {
        if (scaleSwitchTrig.process(params[SCALE_PARAM].getValue() > 0.f)) {
            scale = (scale + 1) % (SCALECOUNT + 1);
        }
        
        if (scaleInputTrig.process(rescale(inputs[SCALE_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f))) {
            scale = scale ? 0 : 1;
        }
        
        updateScaleLeds();
    }
    
    void processScalePresets() {
        int newScaleAPreset = round(getCombinedValue(SCALE_A_PARAM, SCALE_A_INPUT)) - 1;
        int newScaleBPreset = round(getCombinedValue(SCALE_B_PARAM, SCALE_B_INPUT)) - 1;
        
        if (newScaleAPreset != scaleAPreset) {
            scaleAPreset = newScaleAPreset;
            if (scaleSwitchTrig.process(params[SCALE_A_LOCK_PARAM].getValue() > 0.f)) {
                for (int i = 0; i < SCALELEN; i++)
                    params[SCALE_1_PARAM + i].setValue(scalePresets[scaleAPreset][i]);
            }
        }

        if (newScaleBPreset != scaleBPreset) {
            scaleBPreset = newScaleBPreset;
            if (scaleSwitchTrig.process(params[SCALE_B_LOCK_PARAM].getValue() > 0.f)) {
                for (int i = 0; i < SCALELEN; i++)
                    params[SCALE_1_PARAM + i + SCALELEN].setValue(scalePresets[scaleBPreset][i]);
            }
        }
    }

    void updateScales() {
        scaleCount[SCALECOUNT] = 0;
        for (int s = 0; s < SCALECOUNT; s++) {
            scaleCount[s] = 0;
            
            for (int i = 0; i < SCALELEN; i++) {
                if (params[SCALE_1_PARAM + i + s * SCALELEN].getValue() > 0) {
                    scales[s][scaleCount[s]++] = i;
                    scales[SCALECOUNT][scaleCount[SCALECOUNT]++] = s ? i + 12 : i;
                }
            }
        }
    }

    void updateParameters() {
        int speedBPM = round(getCombinedValue(SPEED_PARAM, SPEED_INPUT));
        speed = 60.f / speedBPM;
        length = round(getCombinedValue(LENGTH_PARAM, LENGTH_INPUT));
        transpose = getCombinedValue(TRANSPOSE_PARAM, TRANSPOSE_INPUT);
        float gateLen = getCombinedValue(GATE_LEN_PARAM, GATE_LEN_INPUT);
        gateLength = speed * gateLen;
        spread = getCombinedValue(SPREAD_PARAM, SPREAD_INPUT);
    }

    void updateSyncedParameters() {
        voices = round(getCombinedValue(VOICES_PARAM, VOICES_INPUT)) - 1;
        algoX = round(getCombinedValue(ALGO_X_PARAM, ALGO_X_INPUT));
        algoY = round(getCombinedValue(ALGO_Y_PARAM, ALGO_Y_INPUT));
        shift = round(getCombinedValue(SHIFT_PARAM, SHIFT_INPUT));
        space = getCombinedValue(SPACE_PARAM, SPACE_INPUT);
        rotate = round(getCombinedValue(ROTATE_PARAM, ROTATE_INPUT));
        float algoXMod = getCombinedValue(XMOD_PARAM, XMOD_INPUT) * outputs[CV_1_OUTPUT].getVoltage() / 12.f * 128.f;
        algoX += round(algoXMod);
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

        for (int i = 0; i < TRACKCOUNT; i++) shifts[i] = getCombinedValue(SHIFT_PARAM, SHIFT_INPUT);
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
        for (int i = 0; i < MODCOUNT; i++) modGateOn[i] = trackOn[i % (i < 4 ? TRACKCOUNT_LEGACY : TRACKCOUNT)];

        modCvs[0] = totalWeight + weightOn[0];
        modCvs[1] = weights[1] * (trackOn[3] + trackOn[2]) + weights[2] * (trackOn[0] + trackOn[2]);
        modCvs[2] = weights[0] * (trackOn[2] + trackOn[1]) + weights[3] * (trackOn[0] + trackOn[3]);
        modCvs[3] = weights[1] * (trackOn[1] + trackOn[2]) + weights[2] * (trackOn[2] + trackOn[3]) + weights[3] * (trackOn[3] + trackOn[2]);

        for (int i = 0; i < MODCOUNT; i++) modCvs[i] %= 10;
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
        // if (inputs[CLOCK_INPUT].active) {
        //    advance = clockIn.process(rescale(inputs[CLOCK_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f));
        //} else {
            internalClock += args.sampleTime;
            if (internalClock >= speed) {
                advance = 1;
                internalClock = 0;
            }
        //}

        updateParameters();
        if (advance) updateSyncedParameters();
        updateTrackParameters();
        processScaleSwitch();
        processScalePresets();
        updateScales();

        if (advance) {
            updateCounters();
            updateMod();
            pushHistory();
            for (int n = 0; n < NOTECOUNT; n++) calculateNextNote(n);
            clockOut.trigger(1e-3);
            clockInterval = clockIntervalCounter;
            clockIntervalCounter = 0;
            for (int i = 0; i < NOTECOUNT; i++) gateTriggered[i] = false;
            
            for (int i = 0; i < NOTECOUNT; i++) {
                if (muted[i]) {
                    muted[i]--;
                } else {
                    float chance = space;
                    //if (space > 0.5f) chance += ((float)i / (float)NOTECOUNT) * 0.1f;
                    muted[i] = rand() / (float)RAND_MAX < chance ? round(length * (1 + space) * (i + 1)): 0;
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

            if (scaleCount[scale] == 0 || (n > voices)) {
                g = 0;
            } else {
                int nindex = notes[n][history] % scaleCount[scale];
                int sindex = scale < SCALECOUNT ? scale : nindex < scaleCount[0] ? 0 : 1;
                
                float trans = transpose;
                if ((sindex == 0 && getCombinedValue(SCALE_A_OCT_PARAM, SCALE_A_OCT_INPUT) > 0) || 
                    (sindex == 1 && getCombinedValue(SCALE_B_OCT_PARAM, SCALE_B_OCT_INPUT) > 0)) trans += 1.f;
                
                cv = scales[scale][nindex] / 12.f + std::min(2, notes[n][history] / 12) + trans;
                
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

            outputs[CV_1_OUTPUT + n].setVoltage(cv);
            outputs[GATE_1_OUTPUT + n].setVoltage(g);
            
            outputs[CV_1_OUTPUT].setVoltage(cv, n);
            outputs[GATE_1_OUTPUT].setVoltage(g, n);
        }

        outputs[CV_1_OUTPUT].setChannels(NOTECOUNT);
        outputs[GATE_1_OUTPUT].setChannels(NOTECOUNT);

        for (int i = 0; i < MODCOUNT; i++) {
            outputs[MOD_GATE_1_OUTPUT + i].setVoltage(modGateOn[i] ? 10.f : 0.f);
            outputs[MOD_CV_1_OUTPUT + i].setVoltage((float)(modCvs[i] % 8) / 7.f * 10.f);
        }

        outputs[CLOCK_OUTPUT].setVoltage(clockOut.process(args.sampleTime) ? 10.f : 0.f);
        outputs[RESET_OUTPUT].setVoltage(resetOut.process(args.sampleTime) ? 10.f : 0.f);
    }

    json_t* dataToJson() override {
        json_t* rootJ = json_object();
        json_object_set_new(rootJ, "selected_scale", json_integer(scale));
        return rootJ;
    }

    void dataFromJson(json_t* rootJ) override {
        json_t* scaleJ = json_object_get(rootJ, "selected_scale");
        if (scaleJ) {
            scale = json_integer_value(scaleJ);
            scaleAPreset = round(getCombinedValue(SCALE_A_PARAM, SCALE_A_INPUT)) - 1;
            scaleBPreset = round(getCombinedValue(SCALE_B_PARAM, SCALE_B_INPUT)) - 1;
            updateScaleLeds();
            updateScales();
        }
    }
};

struct SDOrcasHeartWidget : ModuleWidget {
    SDOrcasHeartWidget(SDOrcasHeartV2* module) {
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SDOrcasHeartV2.svg")));

        addParam(createParamCentered<CKD6>(mm2px(Vec(59.672, 14.503)), module, SDOrcasHeartV2::SCALE_2_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(68.626, 14.503)), module, SDOrcasHeartV2::SCALE_4_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(86.533, 14.503)), module, SDOrcasHeartV2::SCALE_7_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(95.487, 14.503)), module, SDOrcasHeartV2::SCALE_9_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(104.44, 14.503)), module, SDOrcasHeartV2::SCALE_11_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(42.651, 16.863)), module, SDOrcasHeartV2::SCALE_A_OCT_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(120.932, 16.863)), module, SDOrcasHeartV2::SCALE_A_LOCK_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(132.115, 16.863)), module, SDOrcasHeartV2::SCALE_A_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(55.195, 19.223)), module, SDOrcasHeartV2::SCALE_1_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(64.149, 19.223)), module, SDOrcasHeartV2::SCALE_3_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(73.102, 19.223)), module, SDOrcasHeartV2::SCALE_5_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(82.056, 19.223)), module, SDOrcasHeartV2::SCALE_6_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(91.01, 19.223)), module, SDOrcasHeartV2::SCALE_8_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(99.964, 19.223)), module, SDOrcasHeartV2::SCALE_10_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(108.917, 19.223)), module, SDOrcasHeartV2::SCALE_12_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(20.284, 24.754)), module, SDOrcasHeartV2::SCALE_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(59.143, 30.286)), module, SDOrcasHeartV2::SCALE_14_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(68.096, 30.286)), module, SDOrcasHeartV2::SCALE_16_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(86.004, 30.286)), module, SDOrcasHeartV2::SCALE_19_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(94.958, 30.286)), module, SDOrcasHeartV2::SCALE_21_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(103.911, 30.286)), module, SDOrcasHeartV2::SCALE_23_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(42.651, 32.646)), module, SDOrcasHeartV2::SCALE_B_OCT_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(120.932, 32.646)), module, SDOrcasHeartV2::SCALE_B_LOCK_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(132.115, 32.646)), module, SDOrcasHeartV2::SCALE_B_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(54.666, 35.006)), module, SDOrcasHeartV2::SCALE_13_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(63.62, 35.006)), module, SDOrcasHeartV2::SCALE_15_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(72.573, 35.006)), module, SDOrcasHeartV2::SCALE_17_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(81.527, 35.006)), module, SDOrcasHeartV2::SCALE_18_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(90.481, 35.006)), module, SDOrcasHeartV2::SCALE_20_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(99.434, 35.006)), module, SDOrcasHeartV2::SCALE_22_PARAM));
        addParam(createParamCentered<CKD6>(mm2px(Vec(108.388, 35.006)), module, SDOrcasHeartV2::SCALE_24_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(20.284, 53.868)), module, SDOrcasHeartV2::SPEED_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(42.651, 53.868)), module, SDOrcasHeartV2::LENGTH_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(65.017, 53.868)), module, SDOrcasHeartV2::TRANSPOSE_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(87.383, 53.868)), module, SDOrcasHeartV2::GATE_LEN_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(109.749, 53.868)), module, SDOrcasHeartV2::VOICES_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(132.115, 53.868)), module, SDOrcasHeartV2::SPREAD_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(31.468, 71.614)), module, SDOrcasHeartV2::ALGO_X_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(53.834, 71.614)), module, SDOrcasHeartV2::ALGO_Y_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(76.2, 71.614)), module, SDOrcasHeartV2::SHIFT_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(98.566, 71.614)), module, SDOrcasHeartV2::SPACE_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(120.932, 71.614)), module, SDOrcasHeartV2::ROTATE_PARAM));
        addParam(createParamCentered<Rogan2PSGreen>(mm2px(Vec(143.299, 71.614)), module, SDOrcasHeartV2::XMOD_PARAM));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.468, 16.863)), module, SDOrcasHeartV2::SCALE_A_OCT_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(143.299, 16.863)), module, SDOrcasHeartV2::SCALE_A_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.101, 24.754)), module, SDOrcasHeartV2::SCALE_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.468, 32.646)), module, SDOrcasHeartV2::SCALE_B_OCT_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(143.299, 32.646)), module, SDOrcasHeartV2::SCALE_B_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.101, 69.868)), module, SDOrcasHeartV2::CLOCK_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.101, 84.65)), module, SDOrcasHeartV2::RESET_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.284, 84.65)), module, SDOrcasHeartV2::SPEED_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.468, 84.65)), module, SDOrcasHeartV2::ALGO_X_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(42.651, 84.65)), module, SDOrcasHeartV2::LENGTH_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(53.834, 84.65)), module, SDOrcasHeartV2::ALGO_Y_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(65.017, 84.65)), module, SDOrcasHeartV2::TRANSPOSE_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(76.2, 84.65)), module, SDOrcasHeartV2::SHIFT_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(87.383, 84.65)), module, SDOrcasHeartV2::GATE_LEN_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(98.566, 84.65)), module, SDOrcasHeartV2::SPACE_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(109.749, 84.65)), module, SDOrcasHeartV2::VOICES_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(120.932, 84.65)), module, SDOrcasHeartV2::ROTATE_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(132.115, 84.65)), module, SDOrcasHeartV2::SPREAD_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(143.299, 84.65)), module, SDOrcasHeartV2::XMOD_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(9.101, 104.537)), module, SDOrcasHeartV2::CLOCK_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(20.284, 104.536)), module, SDOrcasHeartV2::MOD_CV_1_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(31.468, 104.536)), module, SDOrcasHeartV2::MOD_CV_2_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(42.651, 104.536)), module, SDOrcasHeartV2::MOD_CV_3_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.834, 104.536)), module, SDOrcasHeartV2::MOD_CV_4_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(65.017, 104.536)), module, SDOrcasHeartV2::CV_1_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(76.2, 104.536)), module, SDOrcasHeartV2::CV_2_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(87.383, 104.536)), module, SDOrcasHeartV2::CV_3_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(98.566, 104.536)), module, SDOrcasHeartV2::CV_4_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(109.749, 104.536)), module, SDOrcasHeartV2::CV_5_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(120.932, 104.536)), module, SDOrcasHeartV2::CV_6_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(132.116, 104.536)), module, SDOrcasHeartV2::CV_7_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(143.299, 104.536)), module, SDOrcasHeartV2::CV_8_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(9.101, 119.318)), module, SDOrcasHeartV2::RESET_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(20.284, 119.318)), module, SDOrcasHeartV2::MOD_GATE_1_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(31.468, 119.318)), module, SDOrcasHeartV2::MOD_GATE_2_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(42.651, 119.318)), module, SDOrcasHeartV2::MOD_GATE_3_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.834, 119.318)), module, SDOrcasHeartV2::MOD_GATE_4_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(65.017, 119.318)), module, SDOrcasHeartV2::GATE_1_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(76.2, 119.318)), module, SDOrcasHeartV2::GATE_2_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(87.383, 119.318)), module, SDOrcasHeartV2::GATE_3_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(98.566, 119.318)), module, SDOrcasHeartV2::GATE_4_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(109.749, 119.318)), module, SDOrcasHeartV2::GATE_5_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(120.932, 119.318)), module, SDOrcasHeartV2::GATE_6_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(132.115, 119.318)), module, SDOrcasHeartV2::GATE_7_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(143.299, 119.318)), module, SDOrcasHeartV2::GATE_8_OUTPUT));

        // addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.284, 16.863)), module, SDOrcasHeartV2::SCALE_A_LIGHT));
        // addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.284, 32.646)), module, SDOrcasHeartV2::SCALE_B_LIGHT));
    }
};

Model* modelSDOrcasHeartV2 = createModel<SDOrcasHeartV2, SDOrcasHeartWidget>("SDOrcasHeartV2");
