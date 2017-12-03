/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

/*
* Copyright 2017 Xavier Hosxe
*
* Author: Xavier Hosxe (xavier <dot> hosxe
*                      (at) g m a i l <dot> com)
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "JuceHeader.h"
#include "SliderPfm2.h"
#include "../AudioProcessorCommon.h"

//[/Headers]

#include "PanelEngineAmbika.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...


// Ambika Strings :
// https://github.com/pichenettes/ambika/blob/49e8a04ad23b6fb40bf3298fc84659065f640b9d/controller/resources/strings.py


const char *tuningPolyphonyModeTexts[] = {
    "mono", "poly","2x unison","cyclic", "chain", nullptr,
};


const char* mixLabelTexts[] = {
    "Osc1/Osc2", "Cross Op", "Op Param", "Sub&Click", "Sub Volume", "Noise", "Fuzz", "Crush",
    nullptr
};

const char* tuningLabelTexts[] = {
    "Volume",  "Polyphony", "Legato", "Portamento", "Octave", "Semi tone", "Spread",  "Raga",
    nullptr
};

const char* oscShapes[] = {
 "None", "Sawtooth", "Square", "Triangle", "Sine", "zSaw", "lp zSaw", "pk zsaw", "bp zSaw",
 "hp zSaw", "lp zPulse", "pk zPulse", "bp zPulse", "hp zPulse", "zTriangle", "Pad", "FM",
 "8 bits", "Pwm", "Noise", "Vowel", "Mmale", "Female", "Choir", "Tampura", "Bowed", "Cello",
 "Vibes", "Slap bass", "E-Piano", "Organ", "Waves", "Digital PPG", "Drone 1", "Drone 2", "Metallic",
 "Bell", "Wavquence", nullptr
};
const char* mixSubOscShapeTexts[] = {
    "Square Sub -1", "Triangle Sub -1", "Pulse Sub -1", "Square Sub -2", "Triangle Sub -2", "Pulse Sub -2", "Click", "Glitch Click", "Blow Click", "Metal Click", "Pop Click", nullptr
};

const char* mixOpTexts[] = {
    "Off",     "Sync",    "Ring",    "Xor",    "Foldback",    "Bits Redu",  nullptr
};

const char* filterModeTexts[] = {
    "Low Pass",     "Band Pass",    "High Pass", nullptr
};

//[/MiscUserDefs]

//==============================================================================
PanelEngine::PanelEngine ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (osc1Group = new GroupComponent ("Osc1 Group",
                                                       TRANS("Oscillator 1")));

    addAndMakeVisible (osc2Group = new GroupComponent ("Osc2 Group",
                                                       TRANS("Oscillator 2")));

    addAndMakeVisible (mixerGroup = new GroupComponent ("Mixer Group",
                                                        TRANS("Mixer")));

    addAndMakeVisible (filterGroup = new GroupComponent ("Filter Group",
                                                         TRANS("Filter")));
    filterGroup->setColour (GroupComponent::outlineColourId, Colour (0xffad7277));
    filterGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (infoButton = new ImageButton ("Info Button"));
    infoButton->setTooltip (TRANS("Some Info"));
    infoButton->setButtonText (String());

    infoButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::iconInfo_png, BinaryData::iconInfo_pngSize), 0.858f, Colour (0x50000000),
                           Image(), 1.000f, Colour (0x50000000),
                           Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (tuningGroup = new GroupComponent ("Tuning Group",
                                                         TRANS("Tuning Part")));

    addAndMakeVisible (infoGroup = new GroupComponent ("Info Group",
                                                       TRANS("Info")));


    //[UserPreSize]

    infoButton->addListener(this);


    //newParam = new MidifiedFloatParameter(String("Osc1 Shape"), nrpmParam, 1, 0, 34, 0);

    addAndMakeVisible(osc1ShapeLabel = new Label("Osc1 Shape label", "Shape"));
    osc1ShapeLabel->setJustificationType(Justification::centred);


    addAndMakeVisible(osc1Shape = new ComboBox("Osc1 Shape"));
    osc1Shape->setEditableText(false);
    osc1Shape->setJustificationType(Justification::left);
    osc1Shape->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; oscShapes[i] != nullptr; i++) {
        osc1Shape->addItem(oscShapes[i], i + 1);
    }
    osc1Shape->setScrollWheelEnabled(true);
    osc1Shape->setSelectedId(1);
    osc1Shape->addListener(this);

    //newParam = new MidifiedFloatParameter(String("Osc1 Parameter"), nrpmParam, 1, 0, 127, 0);


    addAndMakeVisible(osc1ParamLabel = new Label("Osc1 Param label", "Param"));
    osc1ParamLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(osc1Param = new SliderPfm2("Osc1 Param"));
    osc1Param->setRange(0, 127, 1);
    osc1Param->setSliderStyle(Slider::RotaryVerticalDrag);
    osc1Param->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    osc1Param->setDoubleClickReturnValue(true, 0.0f);
    osc1Param->addListener(this);

    //newParam = new MidifiedFloatParameter(String("Osc1 Range"), nrpmParam, 1, -24, 24, 0);
    addAndMakeVisible(osc1RangeLabel = new Label("Osc1 Range label", "Range"));
    osc1RangeLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(osc1Range = new SliderPfm2("Osc1 Range"));
    osc1Range->setRange(-24, 24, 1);
    osc1Range->setSliderStyle(Slider::RotaryVerticalDrag);
    osc1Range->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    osc1Range->setDoubleClickReturnValue(true, 0.0f);
    osc1Range->addListener(this);

    //newParam = new MidifiedFloatParameter(String("Osc1 Detune"), nrpmParam, 1, 0, 127, 0);
    addAndMakeVisible(osc1DetuneLabel = new Label("Osc1 Detune label", "Detune"));
    osc1DetuneLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(osc1Detune = new SliderPfm2("Osc1 Detune"));
    osc1Detune->setRange(-64, 63, 1);
    osc1Detune->setSliderStyle(Slider::RotaryVerticalDrag);
    osc1Detune->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    osc1Detune->setDoubleClickReturnValue(true, 0.0f);
    osc1Detune->addListener(this);




    //newParam = new MidifiedFloatParameter(String("Osc2 Shape"), nrpmParam, 1, 0, 34, 0);

    addAndMakeVisible(osc2ShapeLabel = new Label("Osc2 Shape label", "Shape"));
    osc2ShapeLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(osc2Shape = new ComboBox("Osc2 Shape"));
    osc2Shape->setEditableText(false);
    osc2Shape->setJustificationType(Justification::left);
    osc2Shape->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; oscShapes[i] != nullptr; i++) {
        osc2Shape->addItem(oscShapes[i], i + 1);
    }
    osc2Shape->setScrollWheelEnabled(true);
    osc2Shape->setSelectedId(2);
    osc2Shape->addListener(this);

    //newParam = new MidifiedFloatParameter(String("Osc2 Param"), nrpmParam, 1, 0, 127, 0);
    addAndMakeVisible(osc2ParamLabel = new Label("Osc2 Param label", "Param"));
    osc2ParamLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(osc2Param = new SliderPfm2("Osc2 Param"));
    osc2Param->setRange(0, 127, 1);
    osc2Param->setSliderStyle(Slider::RotaryVerticalDrag);
    osc2Param->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    osc2Param->setDoubleClickReturnValue(true, 0.0f);
    osc2Param->addListener(this);

    //newParam = new MidifiedFloatParameter(String("Osc2 Range"), nrpmParam, 1, -24, 24, 0);
    addAndMakeVisible(osc2RangeLabel = new Label("Osc2 Range label", "Range"));
    osc2RangeLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(osc2Range = new SliderPfm2("Osc2 Range"));
    osc2Range->setRange(-24, 24, 1);
    osc2Range->setSliderStyle(Slider::RotaryVerticalDrag);
    osc2Range->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    osc2Range->setDoubleClickReturnValue(true, 0.0f);
    osc2Range->addListener(this);

    //newParam = new MidifiedFloatParameter(String("Osc2 Detune"), nrpmParam, 1, 0, 127, 0);
    addAndMakeVisible(osc2DetuneLabel = new Label("Osc2 Detune label", "Detune"));
    osc2DetuneLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(osc2Detune = new SliderPfm2("Osc2 Detune"));
    osc2Detune->setRange(-64, 63, 1);
    osc2Detune->setSliderStyle(Slider::RotaryVerticalDrag);
    osc2Detune->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    osc2Detune->setDoubleClickReturnValue(true, 0.0f);
    osc2Detune->addListener(this);

    //Filter cutoff	0 - 127	12	14, 74

    //newParam = new MidifiedFloatParameter(String("Filter Cutoff"), nrpmParam, 1, 0, 127, 0);

    addAndMakeVisible(filterCutoffLabel = new Label("Filter Cutoff label", "Cutoff"));
    filterCutoffLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(filterCutoff = new SliderPfm2("Filter Cutoff"));
    filterCutoff->setRange(0, 127, 1);
    filterCutoff->setSliderStyle(Slider::RotaryVerticalDrag);
    filterCutoff->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    filterCutoff->setDoubleClickReturnValue(true, 63.0f);
    filterCutoff->addListener(this);

    //newParam = new MidifiedFloatParameter(String("Filter Resonnance"), nrpmParam, 1, 0, 63, 0);

    addAndMakeVisible(filterResonnanceLabel = new Label("Filter Resonnance label", "Resonnance"));
    filterResonnanceLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(filterResonnance = new SliderPfm2("Filter Resonnance"));
    filterResonnance->setRange(0, 63, 1);
    filterResonnance->setSliderStyle(Slider::RotaryVerticalDrag);
    filterResonnance->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    filterResonnance->setDoubleClickReturnValue(true, 0.0f);
    filterResonnance->addListener(this);

    addAndMakeVisible(filterModeLabel= new Label("Filter Mode label", "Mode"));
    filterModeLabel->setJustificationType(Justification::centred);

    //newParam = new MidifiedFloatParameter(String("mix_op"), nrpmParam, 1, 0, 5, 0);
    addAndMakeVisible(filterMode = new ComboBox("Filter Mode"));
    filterMode->setEditableText(false);
    filterMode->setJustificationType(Justification::left);
    filterMode->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; filterModeTexts[i] != nullptr; i++) {
        filterMode->addItem(filterModeTexts[i], i + 1);
    }
    filterMode->setScrollWheelEnabled(true);
    filterMode->setSelectedId(1);
    filterMode->addListener(this);


    //newParam = new MidifiedFloatParameter(String("Enveloppe->Cutoff"), nrpmParam, 1, 0, 63, 0);

    addAndMakeVisible(filterEnvLabel = new Label("Filter Env label", "Env1->Cutoff"));
    filterEnvLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(filterEnv = new SliderPfm2("Filter Env"));
    filterEnv->setRange(0, 63, 1);
    filterEnv->setSliderStyle(Slider::RotaryVerticalDrag);
    filterEnv->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    filterEnv->setDoubleClickReturnValue(true, 0.0f);
    filterEnv->addListener(this);

    //newParam = new MidifiedFloatParameter(String("Lfo->Cutoff"), nrpmParam, 1, 0, 63, 0);

    addAndMakeVisible(filterLfoLabel = new Label("Filter Lfo label", "Lfo2->Cutoff"));
    filterLfoLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(filterLfo = new SliderPfm2("Filter Lfo"));
    filterLfo->setRange(0, 63, 1);
    filterLfo->setSliderStyle(Slider::RotaryVerticalDrag);
    filterLfo->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    filterLfo->setDoubleClickReturnValue(true, 0.0f);
    filterLfo->addListener(this);

    //
    // Mixer
    //

    //newParam = new MidifiedFloatParameter(String("Osc1 Operator"), nrpmParam, 1, 0, 13, 0);
    for (int l = 0; l < 8; l++) {
        addAndMakeVisible(mixLabels[l] = new Label("Mix Label"+ String(l), mixLabelTexts[l]));
        mixLabels[l]->setJustificationType(Justification::centred);
    }


    //newParam = new MidifiedFloatParameter(String("mix_balance"), nrpmParam, 1, 0, 63, 32);
    addAndMakeVisible(mixBalance = new SliderPfm2("mix_balance"));
    mixBalance->setRange(0, 63, 1);
    mixBalance->setSliderStyle(Slider::RotaryVerticalDrag);
    mixBalance->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    mixBalance->setDoubleClickReturnValue(true, 32.0f);
    mixBalance->addListener(this);

    //newParam = new MidifiedFloatParameter(String("mix_op"), nrpmParam, 1, 0, 5, 0);
    addAndMakeVisible(mixOp = new ComboBox("mix_op"));
    mixOp->setEditableText(false);
    mixOp->setJustificationType(Justification::left);
    mixOp->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; mixOpTexts[i] != nullptr; i++) {
        mixOp->addItem(mixOpTexts[i], i + 1);
    }
    mixOp->setScrollWheelEnabled(true);
    mixOp->setSelectedId(1);
    mixOp->addListener(this);

    //newParam = new MidifiedFloatParameter(String("mix_parameter"), nrpmParam, 1, 0, 63, 0);
    addAndMakeVisible(mixParameter = new SliderPfm2("mix_parameter"));
    mixParameter->setRange(0, 63, 1);
    mixParameter->setSliderStyle(Slider::RotaryVerticalDrag);
    mixParameter->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    mixParameter->setDoubleClickReturnValue(true, 0.0f);
    mixParameter->addListener(this);

    //newParam = new MidifiedFloatParameter(String("mix_sub_osc_shape"), nrpmParam, 1, 0, 10, 0);
    addAndMakeVisible(mixSubOscShape = new ComboBox("mix_sub_osc_shape"));
    mixSubOscShape->setEditableText(false);
    mixSubOscShape->setJustificationType(Justification::left);
    mixSubOscShape->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; mixSubOscShapeTexts[i] != nullptr; i++) {
        mixSubOscShape->addItem(mixSubOscShapeTexts[i], i + 1);
    }
    mixSubOscShape->setScrollWheelEnabled(true);
    mixOp->setSelectedId(1);
    mixSubOscShape->addListener(this);

    //newParam = new MidifiedFloatParameter(String("mix_sub_osc"), nrpmParam, 1, 0, 63, 32);
    addAndMakeVisible(mixSubOsc = new SliderPfm2("mix_sub_osc"));
    mixSubOsc->setRange(0, 63, 1);
    mixSubOsc->setSliderStyle(Slider::RotaryVerticalDrag);
    mixSubOsc->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    mixSubOsc->setDoubleClickReturnValue(true, 0.0f);
    mixSubOsc->addListener(this);

    //newParam = new MidifiedFloatParameter(String("mix_noise"), nrpmParam, 1, 0, 63, 0);
    addAndMakeVisible(mixNoise = new SliderPfm2("mix_noise"));
    mixNoise->setRange(0, 63, 1);
    mixNoise->setSliderStyle(Slider::RotaryVerticalDrag);
    mixNoise->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    mixNoise->setDoubleClickReturnValue(true, 0.0f);
    mixNoise->addListener(this);

    //newParam = new MidifiedFloatParameter(String("mix_fuzz"), nrpmParam, 1, 0, 63, 0);
    addAndMakeVisible(mixFuzz = new SliderPfm2("mix_fuzz"));
    mixFuzz->setRange(0, 63, 1);
    mixFuzz->setSliderStyle(Slider::RotaryVerticalDrag);
    mixFuzz->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    mixFuzz->setDoubleClickReturnValue(true, 0.0f);
    mixFuzz->addListener(this);

    //newParam = new MidifiedFloatParameter(String("mix_crush"), nrpmParam, 1, 0, 31, 0);
    addAndMakeVisible(mixCrush = new SliderPfm2("mix_crush"));
    mixCrush->setRange(0, 63, 1);
    mixCrush->setSliderStyle(Slider::RotaryVerticalDrag);
    mixCrush->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    mixCrush->setDoubleClickReturnValue(true, 0.0f);
    mixCrush->addListener(this);





    // Tuning

    for (int t = 0; t < 8; t++) {
        addAndMakeVisible(tuningLabels[t] = new Label("Tuning Label" + String(t), tuningLabelTexts[t]));
        tuningLabels[t]->setJustificationType(Justification::centred);
    }


    const char* tunningNames[8] = {
        "volume", "octave", "tuning", "spread", "raga", "legato", "portamento_time", "polyphony_mode"
    };
    const int nrpnOffset[8] = { 0, 1, 2, 3, 4, 5, 6, 13 };
    const int nrpnMin[8] = { 0, -2, -127, 0, 0, 0, 0, 0 };
    const int nrpnMax[8] = { 127, 2, 126, 31, 10, 1, 63, 4 };



    addAndMakeVisible(tuningVolume = new SliderPfm2("Tuning volume"));
    tuningVolume->setRange(0, 127, 1);
    tuningVolume->setSliderStyle(Slider::RotaryVerticalDrag);
    tuningVolume->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    tuningVolume->setDoubleClickReturnValue(true, 127.0f);
    tuningVolume->addListener(this);

    addAndMakeVisible(tuningOctave = new SliderPfm2("Tuning octave"));
    tuningOctave->setRange(-2, 2, 1);
    tuningOctave->setSliderStyle(Slider::RotaryVerticalDrag);
    tuningOctave->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    tuningOctave->setDoubleClickReturnValue(true, 0.0f);
    tuningOctave->addListener(this);

    addAndMakeVisible(tuningTune= new SliderPfm2("Tuning tuning"));
    tuningTune->setRange(-127, 126, 1);
    tuningTune->setSliderStyle(Slider::RotaryVerticalDrag);
    tuningTune->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    tuningTune->setDoubleClickReturnValue(true, 0.0f);
    tuningTune->addListener(this);

    addAndMakeVisible(tuningSpread= new SliderPfm2("Tuning spread"));
    tuningSpread->setRange(0, 40, 1);
    tuningSpread->setSliderStyle(Slider::RotaryVerticalDrag);
    tuningSpread->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    tuningSpread->setDoubleClickReturnValue(true, 0.0f);
    tuningSpread->addListener(this);

    addAndMakeVisible(tuningRaga = new ComboBox("Tuning raga"));
    tuningRaga->setEditableText(false);
    tuningRaga->setJustificationType(Justification::left);
    tuningRaga->setColour(ComboBox::buttonColourId, Colours::blue);
    tuningRaga->addItem("Equal", 1);
    for (int i = 1; i < 32; i++) {
        tuningRaga->addItem("Raga " + String(i), i + 1);
    }
    tuningRaga->setScrollWheelEnabled(true);
    tuningRaga->setSelectedId(1);
    tuningRaga->addListener(this);

    // Legato 
    addAndMakeVisible(tuningLegato = new TextButton("Tuning legato"));
    tuningLegato->setClickingTogglesState(true);
    tuningLegato->setButtonText("Off");
    tuningLegato->addListener(this);

    // portamento_time
    addAndMakeVisible(tuningPortamento = new SliderPfm2("Tuning portamento_time"));
    tuningPortamento->setRange(0, 63, 1);
    tuningPortamento->setSliderStyle(Slider::RotaryVerticalDrag);
    tuningPortamento->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    tuningPortamento->setDoubleClickReturnValue(true, 0.0f);
    tuningPortamento->addListener(this);


    addAndMakeVisible(tuningPolyphonyMode = new ComboBox("Tuning polyphony_mode"));
    tuningPolyphonyMode->setEditableText(false);
    tuningPolyphonyMode->setJustificationType(Justification::left);
    tuningRaga->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; tuningPolyphonyModeTexts[i] != nullptr; i++) {
        tuningPolyphonyMode->addItem(tuningPolyphonyModeTexts[i], i + 1);
    }
    tuningPolyphonyMode->setScrollWheelEnabled(true);
    tuningPolyphonyMode->setSelectedId(1);
    tuningPolyphonyMode->addListener(this);


    //[/UserPreSize]

    setSize (1000, 710);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PanelEngine::~PanelEngine()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    osc1Group = nullptr;
    osc2Group = nullptr;
    mixerGroup = nullptr;
    filterGroup = nullptr;
    infoButton = nullptr;
    tuningGroup = nullptr;
    infoGroup = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PanelEngine::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        int x = 2, y = proportionOfHeight (0.5000f), width = getWidth() - 4, height = proportionOfHeight (0.2000f);
        Colour fillColour1 = Colour (0xff173e5a), fillColour2 = Colour (0xff1f5073);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        fillColour1 = findColour(PopupMenu::backgroundColourId);
        fillColour2 = findColour(PopupMenu::backgroundColourId).darker();
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       static_cast<float> (proportionOfWidth (0.5000f)) - 2.0f + x,
                                       static_cast<float> (proportionOfHeight (0.5000f)) - static_cast<float> (proportionOfHeight (0.5000f)) + y,
                                       fillColour2,
                                       static_cast<float> (proportionOfWidth (0.5000f)) - 2.0f + x,
                                       static_cast<float> (proportionOfHeight (0.7000f)) - static_cast<float> (proportionOfHeight (0.5000f)) + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 2, y = proportionOfHeight (0.6900f), width = getWidth() - 4, height = proportionOfHeight (0.2100f);
        Colour fillColour1 = Colour (0xff1f5073), fillColour2 = Colour (0xff173e5a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        fillColour2 = findColour(PopupMenu::backgroundColourId);
        fillColour1 = findColour(PopupMenu::backgroundColourId).darker();
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       static_cast<float> (proportionOfWidth (0.5000f)) - 2.0f + x,
                                       static_cast<float> (proportionOfHeight (0.7000f)) - static_cast<float> (proportionOfHeight (0.6900f)) + y,
                                       fillColour2,
                                       static_cast<float> (proportionOfWidth (0.5000f)) - 2.0f + x,
                                       static_cast<float> (proportionOfHeight (0.9000f)) - static_cast<float> (proportionOfHeight (0.6900f)) + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PanelEngine::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    if (false) {
    //[/UserPreResize]

    osc1Group->setBounds (proportionOfWidth (0.0333f), proportionOfHeight (0.0163f), proportionOfWidth (0.4536f), proportionOfHeight (0.1580f));
    osc2Group->setBounds (proportionOfWidth (0.5159f), proportionOfHeight (0.0163f), proportionOfWidth (0.4501f), proportionOfHeight (0.1492f));
    mixerGroup->setBounds (proportionOfWidth (0.0679f), proportionOfHeight (0.1917f), proportionOfWidth (0.8719f), proportionOfHeight (0.2266f));
    filterGroup->setBounds (proportionOfWidth (0.1755f), proportionOfHeight (0.4357f), proportionOfWidth (0.6688f), proportionOfHeight (0.2004f));
    infoButton->setBounds (proportionOfWidth (0.8776f), proportionOfHeight (0.4793f), proportionOfWidth (0.0715f), proportionOfHeight (0.1133f));
    tuningGroup->setBounds (proportionOfWidth (0.0170f), proportionOfHeight (0.6623f), proportionOfWidth (0.9625f), proportionOfHeight (0.2266f));
    infoGroup->setBounds (proportionOfWidth (0.8549f), proportionOfHeight (0.4444f), proportionOfWidth (0.1154f), proportionOfHeight (0.1917f));
    //[UserResized] Add your own custom resize handling here..
    }


    Rectangle<int> localBounds = getLocalBounds();
    localBounds.removeFromTop(5);

    // -------------------------------------------
    // Osc bounds --------------------------------
    // -------------------------------------------
    Rectangle<int> oscBounds = localBounds.removeFromTop(localBounds.getHeight() / 4);
    osc1Group->setBounds(oscBounds.removeFromLeft(oscBounds.getWidth() / 2).reduced(10,5));
    osc2Group->setBounds(oscBounds.reduced(10,5));

    int     numberInRow = 4;
    Rectangle<int> osc1Bounds = osc1Group->getBounds();
    osc1Bounds.removeFromTop(20);
    Rectangle<int> labelBounds = osc1Bounds.removeFromTop(20);
    osc1ShapeLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc1ParamLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc1RangeLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc1DetuneLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    numberInRow = 4;
    osc1Bounds.removeFromTop(10);
    osc1Shape->setBounds(osc1Bounds.removeFromLeft(osc1Bounds.getWidth() / numberInRow--).reduced(10, osc1Bounds.getHeight() / 2 - 10));
    osc1Param->setBounds(osc1Bounds.removeFromLeft(osc1Bounds.getWidth() / numberInRow--).reduced(10, 0));
    osc1Range->setBounds(osc1Bounds.removeFromLeft(osc1Bounds.getWidth() / numberInRow--).reduced(10, 0));
    osc1Detune->setBounds(osc1Bounds.removeFromLeft(osc1Bounds.getWidth() / numberInRow--).reduced(10, 0));


    // osc2
    numberInRow = 4;
    Rectangle<int> osc2Bounds = osc2Group->getBounds();
    osc2Bounds = osc2Group->getBounds();
    osc2Bounds.removeFromTop(20);
    labelBounds = osc2Bounds.removeFromTop(20);
    osc2ShapeLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc2ParamLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc2RangeLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc2DetuneLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc2Bounds.removeFromTop(10);
    numberInRow = 4;
    osc2Shape->setBounds(osc2Bounds.removeFromLeft(osc2Bounds.getWidth() / numberInRow--).reduced(10, osc2Bounds.getHeight() / 2 - 10));
    osc2Param->setBounds(osc2Bounds.removeFromLeft(osc2Bounds.getWidth() / numberInRow--).reduced(10, 0));
    osc2Range->setBounds(osc2Bounds.removeFromLeft(osc2Bounds.getWidth() / numberInRow--).reduced(10, 0));
    osc2Detune->setBounds(osc2Bounds.removeFromLeft(osc2Bounds.getWidth() / numberInRow--).reduced(10, 0));




    // -------------------------------------------
    // Mix bounds --------------------------------
    // -------------------------------------------

    Rectangle<int> mixerBounds = localBounds.removeFromTop(localBounds.getHeight() / 3);
    mixerGroup->setBounds(mixerBounds.reduced(10 ,5));


    numberInRow = 8;
    mixerBounds = mixerGroup->getBounds();
    mixerBounds.removeFromTop(20);
    labelBounds = mixerBounds.removeFromTop(20);

    for (int l = 0; l < 8; l++) {
        mixLabels[l]->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / (8 - l)));
    }
    mixerBounds.removeFromTop(10);
    numberInRow = 8;
    mixBalance->setBounds(mixerBounds.removeFromLeft(mixerBounds.getWidth() / numberInRow--).reduced(10, 0));
    mixOp->setBounds(mixerBounds.removeFromLeft(mixerBounds.getWidth() / numberInRow--).reduced(10, mixerBounds.getHeight() / 2 - 10));
    mixParameter->setBounds(mixerBounds.removeFromLeft(mixerBounds.getWidth() / numberInRow--).reduced(10, 0));
    mixSubOscShape->setBounds(mixerBounds.removeFromLeft(mixerBounds.getWidth() / numberInRow--).reduced(2, mixerBounds.getHeight() / 2 - 10));

    mixSubOsc->setBounds(mixerBounds.removeFromLeft(mixerBounds.getWidth() / numberInRow--).reduced(10, 0));
    mixNoise->setBounds(mixerBounds.removeFromLeft(mixerBounds.getWidth() / numberInRow--).reduced(10, 0));
    mixFuzz->setBounds(mixerBounds.removeFromLeft(mixerBounds.getWidth() / numberInRow--).reduced(10, 0));
    mixCrush->setBounds(mixerBounds.removeFromLeft(mixerBounds.getWidth() / numberInRow--).reduced(10, 0));



    // -------------------------------------------
    // Filter bounds --------------------------------
    // -------------------------------------------
    Rectangle<int> filterBounds = localBounds.removeFromTop(localBounds.getHeight() / 2);
    filterGroup->setBounds(filterBounds.reduced(10, 5));

    // Info Button
    int toCut = filterBounds.getWidth() / 5;
    infoGroup->setBounds(filterBounds.removeFromRight(toCut).reduced(10, 5));
    infoButton->setBounds(infoGroup->getBounds().reduced(infoGroup->getBounds().getWidth() / 3, infoGroup->getBounds().getHeight() / 3));
    filterBounds.removeFromLeft(toCut);
    filterGroup->setBounds(filterBounds.reduced(10, 5));


    numberInRow = 5;

    filterBounds = filterGroup->getBounds();
    filterBounds.removeFromTop(20);
    labelBounds = filterBounds.removeFromTop(20);

    filterModeLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    filterCutoffLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    filterResonnanceLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    filterEnvLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    filterLfoLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    filterBounds.removeFromTop(10);
    numberInRow = 5;
    filterMode->setBounds(filterBounds.removeFromLeft(filterBounds.getWidth() / numberInRow--).reduced(10, filterBounds.getHeight() / 2 - 10));
    filterCutoff->setBounds(filterBounds.removeFromLeft(filterBounds.getWidth() / numberInRow--).reduced(10, 0));
    filterResonnance->setBounds(filterBounds.removeFromLeft(filterBounds.getWidth() / numberInRow--).reduced(10, 0));
    filterEnv->setBounds(filterBounds.removeFromLeft(filterBounds.getWidth() / numberInRow--).reduced(10, 0));
    filterLfo->setBounds(filterBounds.removeFromLeft(filterBounds.getWidth() / numberInRow--).reduced(10, 0));


    // -------------------------------------------
    // Tuning bounds --------------------------------
    // -------------------------------------------
    Rectangle<int> tuningBounds = localBounds;
    tuningGroup->setBounds(tuningBounds.reduced(10, 5));

    // Sustem Button
    tuningBounds = tuningGroup->getBounds();
    tuningBounds.removeFromTop(20);

    labelBounds = tuningBounds.removeFromTop(20);
    for (int l = 0; l < 8; l++) {
        tuningLabels[l]->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / (8 - l)));
    }

//    "Volume", "Polyphony", "Legato", "Portamento", "Octave", "Semi tone", "Spread", "Raga",
    numberInRow = 8;
    tuningVolume->setBounds(tuningBounds.removeFromLeft(tuningBounds.getWidth() / numberInRow--).reduced(10, 0));
    tuningPolyphonyMode->setBounds(tuningBounds.removeFromLeft(tuningBounds.getWidth() / numberInRow--).reduced(10, filterBounds.getHeight() / 2 - 10));
    tuningLegato->setBounds(tuningBounds.removeFromLeft(tuningBounds.getWidth() / numberInRow--).reduced(10, filterBounds.getHeight() / 2 - 10));
    tuningPortamento->setBounds(tuningBounds.removeFromLeft(tuningBounds.getWidth() / numberInRow--).reduced(10, 0));

    tuningOctave->setBounds(tuningBounds.removeFromLeft(tuningBounds.getWidth() / numberInRow--).reduced(10, 0));
    tuningTune->setBounds(tuningBounds.removeFromLeft(tuningBounds.getWidth() / numberInRow--).reduced(10, 0));
    tuningSpread->setBounds(tuningBounds.removeFromLeft(tuningBounds.getWidth() / numberInRow--).reduced(10, 0));
    tuningRaga->setBounds(tuningBounds.removeFromLeft(tuningBounds.getWidth() / numberInRow--).reduced(10, filterBounds.getHeight() / 2 - 10));


    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


void PanelEngine::sliderValueChanged(Slider* sliderThatWasMoved) 
{
    sliderValueChanged(sliderThatWasMoved, true);
}

void PanelEngine::sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI)
{
    // Update the value if the change comes from the UI
    if (fromPluginUI) {
        AudioProcessorParameter* parameterReady = parameterMap[sliderThatWasMoved->getName()];
        if (parameterReady != nullptr) {
            float value = (float)sliderThatWasMoved->getValue();
            ((MidifiedFloatParameter*)parameterReady)->setValueFromUI(value);
        }
    }
}

void PanelEngine::comboBoxChanged(ComboBox* comboBoxThatHasChanged) {
    comboBoxChanged(comboBoxThatHasChanged, true);
}

void PanelEngine::comboBoxChanged(ComboBox* comboBoxThatHasChanged, bool fromPluginUI) {
    // Update the value if the change comes from the UI
    if (fromPluginUI) {
        AudioProcessorParameter * parameterReady = parameterMap[comboBoxThatHasChanged->getName()];
        if (parameterReady != nullptr) {
            float value = (float)comboBoxThatHasChanged->getSelectedId();
            // First item on shruthi is 0 (0 is forbidden in Juce so : -1);
            ((MidifiedFloatParameter*)parameterReady)->setValueFromUI(value - 1.0f);
        }
    }
}


void PanelEngine::buttonClicked(Button* buttonThatWasClicked, bool fromPluginUI) {

    // Only From UI
    if (fromPluginUI) {
        AudioProcessorParameter * parameterReady = parameterMap[tuningLegato->getName()];
        int value = tuningLegato->getToggleState() ? 1 : 0;
        ((MidifiedFloatParameter*)parameterReady)->setValueFromUI(value);
    }


    // From UI and MIDI and DAW
    if (buttonThatWasClicked == infoButton) {
        {
            AlertWindow midiWindow("Ixox Ambika Editor v" + String(ProjectInfo::versionString),
                "by Xavier Hosxe",
                AlertWindow::InfoIcon);

            midiWindow.addTextBlock("Check your Ambika midi options : \n"
                ". Set midi out to ctrl\n"
                ". Remember the midi channel used\n\n"
                "In the main editor window :\n"
                ". Click on 'Midi' button to select your midi device\n"
                ". Select the midi channel (1-16) of the Ambika part             \n"
                "   you want to talk to.");

            const void* str = "If you like and use this Editor, please pay for it (10€), thanks";
#ifdef SHRUTHI
            HyperlinkButton paypal(String::createStringFromData(str, 94),
                URL("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=4S6JPKATW2AC4"));
#endif
#ifdef AMBIKA
            HyperlinkButton paypal(String::createStringFromData(str, 94),
                URL("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=6LJNV844H68SY"));
#endif
            paypal.setButtonText("Pay Now");
            paypal.setSize(400, 45);
            midiWindow.addCustomComponent(&paypal);

            //HyperlinkButton lastRelease("Click here to check the latest release: ", URL("https://github.com/Ixox/"));
            //lastRelease.setButtonText("Github repository");
            //lastRelease.setSize(400, 25);
            //midiWindow.addCustomComponent(&lastRelease);

            midiWindow.addButton("I understand", 1);
            midiWindow.runModalLoop();
        }
    }

    if (buttonThatWasClicked == tuningLegato) {
        int value = tuningLegato->getToggleState() ? 1 : 0;
        tuningLegato->setButtonText(String((value == 1) ? "On" : "Off"));
    }

}

void PanelEngine::buttonClicked(Button* buttonThatWasClicked)
{
    buttonClicked(buttonThatWasClicked, true);
}



void PanelEngine::buildParameters() {
    updateComboFromParameter(osc1Shape);
    updateSliderFromParameter(osc1Param);
    updateSliderFromParameter(osc1Range);
    updateSliderFromParameter(osc1Detune);
    updateComboFromParameter(osc2Shape);
    updateSliderFromParameter(osc2Param);
    updateSliderFromParameter(osc2Range);
    updateSliderFromParameter(osc2Detune);
    updateSliderFromParameter(filterCutoff);
    updateSliderFromParameter(filterResonnance);
    updateSliderFromParameter(filterEnv);
    updateSliderFromParameter(filterLfo);
    updateComboFromParameter(filterMode);
    updateSliderFromParameter(mixBalance);
    updateComboFromParameter(mixOp);
    updateSliderFromParameter(mixParameter);
    updateComboFromParameter(mixSubOscShape);
    updateSliderFromParameter(mixSubOsc);
    updateSliderFromParameter(mixNoise);
    updateSliderFromParameter(mixFuzz);
    updateSliderFromParameter(mixCrush);

    updateSliderFromParameter(tuningVolume);
    updateSliderFromParameter(tuningOctave);
    updateSliderFromParameter(tuningTune);
    updateSliderFromParameter(tuningSpread);
    updateComboFromParameter(tuningRaga);
    updateButtonFromParameter(tuningLegato);
    updateSliderFromParameter(tuningPortamento);
    updateComboFromParameter(tuningPolyphonyMode);
    

}


void PanelEngine::updateButtonFromParameter_hook(Button* button) {
    buttonClicked(button, false);
}

void PanelEngine::updateSliderFromParameter_hook(Slider* slider) {
    sliderValueChanged(slider, false);
}

void PanelEngine::sliderDragStarted(Slider* slider) {
    AudioProcessorParameter * param = parameterMap[slider->getName()];
    if (param != nullptr) {
        param->beginChangeGesture();
    }
}
void PanelEngine::sliderDragEnded(Slider* slider) {
    AudioProcessorParameter * param = parameterMap[slider->getName()];
    if (param != nullptr) {
        param->endChangeGesture();
    }
}



//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PanelEngine" componentName=""
                 parentClasses="public Component, public Slider::Listener, public Button::Listener, public ComboBox::Listener, public PanelOfComponents"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="1000"
                 initialHeight="710">
  <BACKGROUND backgroundColour="173e5a">
    <RECT pos="2 50% 4M 20%" fill="linear: 50% 50%, 50% 70%, 0=ff173e5a, 1=ff1f5073"
          hasStroke="0"/>
    <RECT pos="2 69% 4M 21%" fill="linear: 50% 70%, 50% 90%, 0=ff1f5073, 1=ff173e5a"
          hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="Osc1 Group" id="f2a0395148710745" memberName="osc1Group"
                  virtualName="" explicitFocusOrder="0" pos="3.326% 1.634% 45.364% 15.795%"
                  title="Oscillator 1"/>
  <GROUPCOMPONENT name="Osc2 Group" id="c95a43b07e06b375" memberName="osc2Group"
                  virtualName="" explicitFocusOrder="0" pos="51.592% 1.634% 45.011% 14.924%"
                  title="Oscillator 2"/>
  <GROUPCOMPONENT name="Mixer Group" id="68ec52c66aafee91" memberName="mixerGroup"
                  virtualName="" explicitFocusOrder="0" pos="6.794% 19.172% 87.19% 22.658%"
                  title="Mixer"/>
  <GROUPCOMPONENT name="Filter Group" id="6e8f214af349f96d" memberName="filterGroup"
                  virtualName="" explicitFocusOrder="0" pos="17.551% 43.573% 66.879% 20.044%"
                  outlinecol="ffad7277" textcol="ffffffff" title="Filter"/>
  <IMAGEBUTTON name="Info Button" id="bd0f020830de2111" memberName="infoButton"
               virtualName="" explicitFocusOrder="0" pos="87.757% 47.93% 7.148% 11.329%"
               tooltip="Some Info" buttonText="" connectedEdges="0" needsCallback="0"
               radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::iconInfo_png"
               opacityNormal="0.85760861635208129883" colourNormal="50000000"
               resourceOver="" opacityOver="1" colourOver="50000000" resourceDown=""
               opacityDown="1" colourDown="0"/>
  <GROUPCOMPONENT name="Tuning Group" id="26235bda1e7cecac" memberName="tuningGroup"
                  virtualName="" explicitFocusOrder="0" pos="1.699% 66.231% 96.249% 22.658%"
                  title="Tuning Part"/>
  <GROUPCOMPONENT name="Info Group" id="a34cf8d753760e42" memberName="infoGroup"
                  virtualName="" explicitFocusOrder="0" pos="85.492% 44.444% 11.536% 19.172%"
                  title="Info"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
