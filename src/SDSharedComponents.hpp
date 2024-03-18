#pragma once
#include <rack.hpp>

struct SDMonoInPort : app::SvgPort {
    SDMonoInPort() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDMonoPort.svg")));
    }
};

struct SDMonoOutPort : app::SvgPort {
    SDMonoOutPort() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDMonoPort.svg")));
    }
};

struct SDPolyInPort : app::SvgPort {
    SDPolyInPort() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDPolyPort.svg")));
    }
};

struct SDPolyOutPort : app::SvgPort {
    SDPolyOutPort() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDPolyPort.svg")));
    }
};

struct SDScalePort : app::SvgPort {
    SDScalePort() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDScalePort.svg")));
    }
};

struct SDSmallestKnob : app::SvgKnob {
    SDSmallestKnob() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDSmallestKnob.svg")));
    }
};

struct SDSmallKnob : app::SvgKnob {
    SDSmallKnob() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDSmallKnob.svg")));
    }
};

struct SDMediumKnob : app::SvgKnob {
    SDMediumKnob() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDMediumKnob.svg")));
    }
};

struct SDScaleKnob : app::SvgKnob {
    SDScaleKnob() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDScaleKnob.svg")));
    }
};

struct SDSmallScaleButton : app::SvgSwitch {
    SDSmallScaleButton() {
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDSmallScaleButton_off.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDSmallScaleButton_on.svg")));
    }
};

struct SDScaleButton : app::SvgSwitch {
    SDScaleButton() {
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDScaleButton_off.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDScaleButton_on.svg")));
    }
};

struct SDMomentaryScaleButton : app::SvgSwitch {
    SDMomentaryScaleButton() {
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDScaleButton_off.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDScaleButton_on.svg")));
        momentary = true;
    }
};

struct SDWhiteLight : GrayModuleLightWidget {
	SDWhiteLight() {
		addBaseColor(nvgRGB(0xef, 0xef, 0xef));
	}
};

struct SDTwoSwitch : app::SvgSwitch {
	SDTwoSwitch() {
		shadow->opacity = 0.0;
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDTwoSwitch1.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDTwoSwitch2.svg")));
	}
};

struct SDThreeSwitch : app::SvgSwitch {
	SDThreeSwitch() {
		shadow->opacity = 0.0;
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDThreeSwitch1.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDThreeSwitch2.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/shared/SDThreeSwitch3.svg")));
	}
};
