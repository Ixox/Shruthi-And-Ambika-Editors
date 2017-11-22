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
#include "../PluginProcessor.h"

//[/Headers]

#include "PanelEngine.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const char *supportedFilters[] = { "SMR4", "SVF", "4PM", "Polivoks", nullptr };

const char* oscShapes[] = {
 "none", "Sawtooth", "Square", "Triangle", "zSaw", "zResonant", "zTriangle", "zPulse", "zSync", "Pad", "FM", "Waves", "Tampur", "Digitl", "Metall", "Bowed", "Slap", "Organ",
 "Male", "User", "8bits", "Crush", "Pwm", "Noise", "Vowel", "Belish", "Polatd", "Cello", "clpswp", "female", "fmtvoc", "frmnt2", "res3hp", "electp", "vibes", nullptr
};
const char* oscSubClicks[] = {
    "sq1 (Sub)", "tr1 (Sub)", "pl1 (Sub)", "sq2 (Sub)", "tr2 (Sub)", "pl2 (Sub)", "click (Click)", "glitch (Click)", "blow (Click)", "metal (Click)", "pop (Click)", nullptr
};

const char* modulationOperators[] = {
    "Sum", "Sync", "Ring", "xor", "Fuzz", ">> 4", ">> 8", "Fold", "Bits", "Duo", "2 Steps", "4 Steps", "8 Steps", "Seqmix", nullptr
};

const char* svgMode1[] = { "Low pass", "Band pass", "High pass", "Low pass <", "Band pass <", "High pass <", nullptr };
const char* svgMode2[] = { "+ Low pass", "+ Band pass", "+ High pass", "> Low pass", "> Band pass", "> High pass", nullptr };

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

    addAndMakeVisible (filterTypeGroup = new GroupComponent ("Filter type group",
                                                             TRANS("Shruthi filter type")));
    filterTypeGroup->setTextLabelPosition (Justification::centredLeft);

    addAndMakeVisible (infoButton = new ImageButton ("Info Button"));
    infoButton->setTooltip (TRANS("Some Info"));
    infoButton->setButtonText (String());

    infoButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::iconInfo_png, BinaryData::iconInfo_pngSize), 0.858f, Colour (0x50000000),
                           Image(), 1.000f, Colour (0x50000000),
                           Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (tuningGroup = new GroupComponent ("Tuning Group",
                                                         TRANS("Tuning")));

    addAndMakeVisible (infoGroup = new GroupComponent ("Info Group",
                                                       TRANS("Info")));


    //[UserPreSize]

    infoButton->addListener(this);

    // don't make visible yet the filter goups
    addChildComponent(filterSVFGroup = new GroupComponent("SVF Filter Group", "Filter2 (SVF)"));


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

    //newParam = new MidifiedFloatParameter(String("Osc1 Operator"), nrpmParam, 1, 0, 13, 0);
    addAndMakeVisible(osc1SubClickLabel = new Label("Osc1 SubClick label", "Sub or Click"));
    osc1SubClickLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(osc1SubClick = new ComboBox("Osc1 SubClick"));
    osc1SubClick->setEditableText(false);
    osc1SubClick->setJustificationType(Justification::left);
    osc1SubClick->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; oscSubClicks[i] != nullptr; i++) {
        osc1SubClick->addItem(oscSubClicks[i], i + 1);
    }
    osc1SubClick->setScrollWheelEnabled(true);
    osc1SubClick->setSelectedId(1);
    osc1SubClick->addListener(this);


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
    osc2Detune->setRange(0, 127, 1);
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

    //  newParam = new MidifiedFloatParameter(String("Modulation Operator"), nrpmParam, 1, 0, 13, 0);
    addAndMakeVisible(mixerOpLabel = new Label("Modulation Operator label", "Operator"));
    mixerOpLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(mixerOp = new ComboBox("Modulation Operator"));
    mixerOp->setEditableText(false);
    mixerOp->setJustificationType(Justification::left);
    mixerOp->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; modulationOperators[i] != nullptr; i++) {
        mixerOp->addItem(modulationOperators[i], i + 1);
    }
    mixerOp->setScrollWheelEnabled(true);
    mixerOp->setSelectedId(2);
    mixerOp->addListener(this);


    //newParam = new MidifiedFloatParameter(String("Oscillator balance"), nrpmParam, 1, 0, 63, 32);
    addAndMakeVisible(mixerMixLabel = new Label("Oscillator balance label", "Osc1/Osc2"));
    mixerMixLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(mixerMix = new SliderPfm2("Oscillator balance"));
    mixerMix->setRange(0, 63, 1);
    mixerMix->setSliderStyle(Slider::RotaryVerticalDrag);
    mixerMix->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    mixerMix->setDoubleClickReturnValue(true, 32.0f);
    mixerMix->addListener(this);


    //newParam = new MidifiedFloatParameter(String("Sub oscillator volume"), nrpmParam, 1, 0, 63, 32);
    addAndMakeVisible(mixerSubLabel = new Label("Sub oscillator volume label", "Sub volume"));
    mixerSubLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(mixerSub = new SliderPfm2("Sub oscillator volume"));
    mixerSub->setRange(0, 63, 1);
    mixerSub->setSliderStyle(Slider::RotaryVerticalDrag);
    mixerSub->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    mixerSub->setDoubleClickReturnValue(true, 0.0f);
    mixerSub->addListener(this);

    //newParam = new MidifiedFloatParameter(String("Noise volume"), nrpmParam, 1, 0, 63, 0);
    addAndMakeVisible(mixerNoiseLabel = new Label("Noise volume label", "Noise volume"));
    mixerNoiseLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(mixerNoise = new SliderPfm2("Noise volume"));
    mixerNoise->setRange(0, 63, 1);
    mixerNoise->setSliderStyle(Slider::RotaryVerticalDrag);
    mixerNoise->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    mixerNoise->setDoubleClickReturnValue(true, 0.0f);
    mixerNoise->addListener(this);

    for (int b = 0; b < NUMBER_SUPPORTED_FILTERS; b++) {
        addAndMakeVisible(shruthiFilterButtons[b] = new TextButton(supportedFilters[b]));
        shruthiFilterButtons[b]->setTooltip("Filter "+ String(b+1));
        shruthiFilterButtons[b]->setButtonText(supportedFilters[b]);
        shruthiFilterButtons[b]->setRadioGroupId(54654);
        shruthiFilterButtons[b]->setClickingTogglesState(true);
        shruthiFilterButtons[b]->addListener(this);
    }



    // ========================== SVF FILTER
    addAndMakeVisible(filterSVFCutoffLabel = new Label("Filter SVF Cutoff label", "Cutoff"));
    filterSVFCutoffLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(filterSVFCutoff = new SliderPfm2("FilterSVF Cutoff"));
    filterSVFCutoff->setRange(0, 127, 1);
    filterSVFCutoff->setSliderStyle(Slider::RotaryVerticalDrag);
    filterSVFCutoff->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    filterSVFCutoff->setDoubleClickReturnValue(true, 63.0f);
    filterSVFCutoff->addListener(this);

    //newParam = new MidifiedFloatParameter(String("Filter Resonnance"), nrpmParam, 1, 0, 63, 0);

    addAndMakeVisible(filterSVFResonnanceLabel = new Label("FilterSVF Resonnance label", "Resonnance"));
    filterSVFResonnanceLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(filterSVFResonnance = new SliderPfm2("FilterSVF Resonnance"));
    filterSVFResonnance->setRange(0, 63, 1);
    filterSVFResonnance->setSliderStyle(Slider::RotaryVerticalDrag);
    filterSVFResonnance->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    filterSVFResonnance->setDoubleClickReturnValue(true, 0.0f);
    filterSVFResonnance->addListener(this);

    addAndMakeVisible(filterSVFMode1Label = new Label("FilterSVF Mode1", "Filter1 Mode"));
    filterSVFMode1Label->setJustificationType(Justification::centred);

    addAndMakeVisible(filterSVFMode1 = new ComboBox("FilterSVF Mode1"));
    filterSVFMode1->setEditableText(false);
    filterSVFMode1->setJustificationType(Justification::left);
    filterSVFMode1->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; svgMode1[i] != nullptr; i++) {
        filterSVFMode1->addItem(svgMode1[i], i + 1);
    }
    filterSVFMode1->setScrollWheelEnabled(true);
    filterSVFMode1->setSelectedId(1);
    filterSVFMode1->addListener(this);

    addAndMakeVisible(filterSVFMode2Label = new Label("FilterSVF Mode2", "Filter2 Mode"));
    filterSVFMode2Label->setJustificationType(Justification::centred);

    addAndMakeVisible(filterSVFMode2 = new ComboBox("FilterSVF Mode2"));
    filterSVFMode2->setEditableText(false);
    filterSVFMode2->setJustificationType(Justification::left);
    filterSVFMode2->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; svgMode2[i] != nullptr; i++) {
        filterSVFMode2->addItem(svgMode2[i], i + 1);
    }
    filterSVFMode2->setScrollWheelEnabled(true);
    filterSVFMode2->setSelectedId(1);
    filterSVFMode2->addListener(this);



    // Legato 0 - 1 : 68
    // newParam = new MidifiedFloatParameter("Tuning Legato", nrpmParam, 1, 0, 1, 0);
    addAndMakeVisible(tuneLegato = new TextButton("Tuning Legato"));
    tuneLegato->setClickingTogglesState(true);
    tuneLegato->setButtonText("Legato");
    tuneLegato->addListener(this);

    addAndMakeVisible(tunePortamentoLabel = new Label("Tuning Portamento Label", "Portamento"));
    tunePortamentoLabel->setJustificationType(Justification::centred);

    // Portamento 0 - 63 : 84
    // newParam = new MidifiedFloatParameter("Tuning Portamento", nrpmParam, 1, 0, 63, 0);
    addAndMakeVisible(tunePortamento = new SliderPfm2("Tuning Portamento"));
    tunePortamento->setRange(0, 63, 1);
    tunePortamento->setSliderStyle(Slider::RotaryVerticalDrag);
    tunePortamento->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    tunePortamento->setDoubleClickReturnValue(true, 0.0f);
    tunePortamento->addListener(this);


    //[/UserPreSize]

    setSize (1000, 710);


    //[Constructor] You can add your own custom stuff here..
    shruthiFilterButtons[0]->setToggleState(true, sendNotification);
    currentFilterType = 0;

    // only SMR4 and SVF for the moment
    shruthiFilterButtons[2]->setEnabled(false);
    shruthiFilterButtons[3]->setEnabled(false);
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
    filterTypeGroup = nullptr;
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

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PanelEngine::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    if (false) {
    //[/UserPreResize]

    osc1Group->setBounds (proportionOfWidth (0.0336f), proportionOfHeight (0.0948f), proportionOfWidth (0.4503f), proportionOfHeight (0.2505f));
    osc2Group->setBounds (proportionOfWidth (0.5161f), proportionOfHeight (0.0948f), proportionOfWidth (0.4503f), proportionOfHeight (0.2505f));
    mixerGroup->setBounds (proportionOfWidth (0.2858f), proportionOfHeight (0.3922f), proportionOfWidth (0.4010f), proportionOfHeight (0.2266f));
    filterGroup->setBounds (proportionOfWidth (0.1645f), proportionOfHeight (0.6623f), proportionOfWidth (0.6689f), proportionOfHeight (0.2604f));
    filterTypeGroup->setBounds (proportionOfWidth (0.2522f), proportionOfHeight (0.0000f), proportionOfWidth (0.4709f), proportionOfHeight (0.0708f));
    infoButton->setBounds (proportionOfWidth (0.0932f), proportionOfHeight (0.4444f), proportionOfWidth (0.0713f), proportionOfHeight (0.1133f));
    tuningGroup->setBounds (proportionOfWidth (0.0219f), proportionOfHeight (0.3922f), proportionOfWidth (0.2522f), proportionOfHeight (0.2266f));
    infoGroup->setBounds (proportionOfWidth (0.7073f), proportionOfHeight (0.3922f), proportionOfWidth (0.2522f), proportionOfHeight (0.2266f));
    //[UserResized] Add your own custom resize handling here..
    }

    Rectangle<int> mainBounds = getLocalBounds();
    mainBounds.removeFromTop(5);

    Rectangle<int> filterTypesBounds = mainBounds.removeFromTop(45);
    filterTypesBounds.removeFromRight(filterTypesBounds.getWidth() / 4);
    filterTypesBounds.removeFromLeft(filterTypesBounds.getWidth() / 3);
    filterTypeGroup->setBounds(filterTypesBounds);



    Rectangle<int> oscBounds = mainBounds.removeFromTop(mainBounds.getHeight() / 3);
    osc1Group->setBounds(oscBounds.removeFromLeft(oscBounds.getWidth() / 2).reduced(10,5));
    osc2Group->setBounds(oscBounds.reduced(10,5));

    Rectangle<int> mixerBounds = mainBounds.removeFromTop(mainBounds.getHeight() / 2);

    // Info Button
    infoGroup->setBounds(mixerBounds.removeFromRight(mainBounds.getWidth() / 4).reduced(10, 5));
    infoButton->setBounds(infoGroup->getBounds().reduced(infoGroup->getBounds().getWidth() / 3, infoGroup->getBounds().getHeight() / 3));

    mixerGroup->setBounds(mixerBounds.removeFromRight(mixerBounds.getWidth() * 2 / 3).reduced(10 ,5));
    Rectangle<int> tuneGroup = mixerBounds.reduced(10, 5);

    if (currentFilterType == 1) {
        filterGroup->setBounds(mainBounds.removeFromLeft(mainBounds.getWidth() * 5  / 8).reduced(10, 5));
        filterSVFGroup->setBounds(mainBounds.reduced(10, 5));
    }
    else {
        filterGroup->setBounds(mainBounds.reduced(mainBounds.getWidth() / 4, 5).reduced(10, 5));
    }

    //osc1Group->setBounds(proportionOfWidth(0.0329f), proportionOfHeight(0.0959f), proportionOfWidth(0.4503f), proportionOfHeight(0.2505f));
    //osc2Group->setBounds(proportionOfWidth(0.5154f), proportionOfHeight(0.0959f), proportionOfWidth(0.4503f), proportionOfHeight(0.2505f));
    //mixerGroup->setBounds(proportionOfWidth(0.2851f), proportionOfHeight(0.3922f), proportionOfWidth(0.4003f), proportionOfHeight(0.2266f));
    //filterGroup->setBounds(proportionOfWidth(0.1645f), proportionOfHeight(0.6623f), proportionOfWidth(0.6689f), proportionOfHeight(0.2614f));
    //filterTypeGroup->setBounds(proportionOfWidth(0.2522f), proportionOfHeight(0.0000f), proportionOfWidth(0.4716f), proportionOfHeight(0.0697f));

    // Shruthi filters
    int numberInRow = NUMBER_SUPPORTED_FILTERS;
    Rectangle<int> groupBounds = filterTypeGroup->getBounds();



    for (int b = 0; b < NUMBER_SUPPORTED_FILTERS; b++) {
        Rectangle<int> filterTypeBounds = groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, groupBounds.getHeight() / 2 - 10);
        filterTypeBounds.setY(filterTypeBounds.getY() + 3);
        shruthiFilterButtons[b]->setBounds(filterTypeBounds);
    }


    numberInRow = 4;
    groupBounds = osc1Group->getBounds();
    groupBounds.removeFromTop(20);
    Rectangle<int> labelBounds = groupBounds.removeFromTop(18);
    osc1ShapeLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc1ParamLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc1RangeLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc1SubClickLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    numberInRow = 4;
    groupBounds.removeFromTop(10);
    osc1Shape->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, groupBounds.getHeight() / 2 - 10));
    osc1Param->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, 0));
    osc1Range->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, 0));
    osc1SubClick->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, groupBounds.getHeight() / 2 - 10));


    // osc2
    numberInRow = 4;
    groupBounds = osc2Group->getBounds();
    groupBounds.removeFromTop(20);
    labelBounds = groupBounds.removeFromTop(18);
    osc2ShapeLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc2ParamLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc2RangeLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    osc2DetuneLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    groupBounds.removeFromTop(10);
    numberInRow = 4;
    osc2Shape->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, groupBounds.getHeight() / 2 - 10));
    osc2Param->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, 0));
    osc2Range->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, 0));
    osc2Detune->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, 0));




    // mixer
    numberInRow = 4;
    mixerBounds = mixerGroup->getBounds();
    mixerBounds.removeFromTop(20);
    labelBounds = mixerBounds.removeFromTop(18);

    mixerOpLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    mixerMixLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    mixerSubLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    mixerNoiseLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    mixerBounds.removeFromTop(10);
    numberInRow = 4;
    mixerOp->setBounds(mixerBounds.removeFromLeft(mixerBounds.getWidth() / numberInRow--).reduced(10, mixerBounds.getHeight() / 2 - 10));
    mixerMix->setBounds(mixerBounds.removeFromLeft(mixerBounds.getWidth() / numberInRow--).reduced(10, 0));
    mixerSub->setBounds(mixerBounds.removeFromLeft(mixerBounds.getWidth() / numberInRow--).reduced(10, 0));
    mixerNoise->setBounds(mixerBounds.removeFromLeft(mixerBounds.getWidth() / numberInRow--).reduced(10, 0));


    // Sustem Button
    tuningGroup->setBounds(tuneGroup);
    tuneGroup.removeFromTop(20);
    tuneLegato->setBounds(tuneGroup.removeFromTop(20).reduced(tuneGroup.getWidth() / 2 - 40, 0));
    tuneGroup.removeFromTop(20);
    tunePortamentoLabel->setBounds(tuneGroup.removeFromTop(20).reduced(10, 0));
    tunePortamento->setBounds(tuneGroup.reduced(15,15));


    // FILTERS !!

    numberInRow = 4;
    if (currentFilterType == 1) {
        numberInRow = 5;
    }

    groupBounds = filterGroup->getBounds();
    groupBounds.removeFromTop(20);
    labelBounds = groupBounds.removeFromTop(18);

    filterCutoffLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    filterResonnanceLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    filterEnvLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    filterLfoLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    if (currentFilterType == 1) {
        filterSVFMode1Label->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
    }
    groupBounds.removeFromTop(10);
    numberInRow = 4;
    if (currentFilterType == 1) {
        numberInRow = 5;
    }
    filterCutoff->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, 0));
    filterResonnance->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, 0));
    filterEnv->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, 0));
    filterLfo->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, 0));

    if (currentFilterType == 1) {
        filterSVFMode1->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, groupBounds.getHeight() / 2 - 10));
    }


    // SVF Filter
    if (currentFilterType == 1) {

        numberInRow = 3;
        groupBounds = filterSVFGroup->getBounds();
        groupBounds.removeFromTop(20);
        labelBounds = groupBounds.removeFromTop(18);


        filterSVFCutoffLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
        filterSVFResonnanceLabel->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
        filterSVFMode2Label->setBounds(labelBounds.removeFromLeft(labelBounds.getWidth() / numberInRow--));
        numberInRow = 3;
        groupBounds.removeFromTop(10);
        filterSVFCutoff->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, 0));
        filterSVFResonnance->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, 0));
        filterSVFMode2->setBounds(groupBounds.removeFromLeft(groupBounds.getWidth() / numberInRow--).reduced(10, groupBounds.getHeight() / 2 - 10));
    }




    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


void PanelEngine::sliderValueChanged(Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    sliderValueChanged(sliderThatWasMoved, true);
    //[/UsersliderValueChanged_Pre]

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PanelEngine::sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI)
{
    // Update the value if the change comes from the UI
    if (fromPluginUI) {
        AudioProcessorParameter* parameterReady = parameterMap[sliderThatWasMoved->getName()];
        if (parameterReady != nullptr) {
            float value = (float)sliderThatWasMoved->getValue();
            ((MidifiedFloatParameter*)parameterReady)->setRealValue(value);
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
            ((MidifiedFloatParameter*)parameterReady)->setRealValue(value - 1.0f);
        }
    }
}


void PanelEngine::buttonClicked(Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    for (int b = 0; b < NUMBER_SUPPORTED_FILTERS; b++) {
        if (buttonThatWasClicked == shruthiFilterButtons[b]) {
            if (currentFilterType != b) {
                DBG("Shruti filter type changed : " << supportedFilters[b]);
                currentFilterType = b;
                filterSVFGroup->setVisible(b == 1);
                filterSVFCutoff->setVisible(b == 1);
                filterSVFCutoffLabel->setVisible(b == 1);
                filterSVFResonnance->setVisible(b == 1);
                filterSVFResonnanceLabel->setVisible(b == 1);
                filterSVFMode1->setVisible(b == 1);
                filterSVFMode1Label->setVisible(b == 1);
                filterSVFMode2->setVisible(b == 1);
                filterSVFMode2Label->setVisible(b == 1);
                resized();
            }
        }
    }

    if (buttonThatWasClicked == infoButton) {

        {
            AlertWindow midiWindow("Ixox Shruthi Editor v" + String(ProjectInfo::versionString),
                "by Xavier Hosxe",
                AlertWindow::InfoIcon);

            midiWindow.addTextBlock("Check your shruthi midi options : \n"
                ". Set midi out to ctrl\n"
                ". Remember the midi channel used\n\n"
                "In the main editor window :\n"
                ". Click on 'Midi' button to select your midi device\n"
                ". Select the midi channel (1-16) of the shruthi                \n"
                "   you want to talk to.");

            const void* str = "If you like and use this Editor, please pay for it (10€), thanks";
            HyperlinkButton paypal(String::createStringFromData(str, 94),
                URL("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=4S6JPKATW2AC4"));
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

    if (buttonThatWasClicked == tuneLegato) {
        AudioProcessorParameter * parameterReady = parameterMap[tuneLegato->getName()];
        int value = tuneLegato->getToggleState() ? 1 : 0;
        ((MidifiedFloatParameter*)parameterReady)->setRealValue(value);
    }
    //[/UserbuttonClicked_Pre]

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



void PanelEngine::buildParameters() {
    updateComboFromParameter(osc1Shape);
    updateSliderFromParameter(osc1Param);
    updateSliderFromParameter(osc1Range);
    updateComboFromParameter(osc1SubClick);
    updateComboFromParameter(osc2Shape);
    updateSliderFromParameter(osc2Param);
    updateSliderFromParameter(osc2Range);
    updateSliderFromParameter(osc2Detune);
    updateSliderFromParameter(filterCutoff);
    updateSliderFromParameter(filterResonnance);
    updateSliderFromParameter(filterEnv);
    updateSliderFromParameter(filterLfo);
    updateSliderFromParameter(mixerMix);
    updateSliderFromParameter(mixerSub);
    updateSliderFromParameter(mixerNoise);
    updateComboFromParameter(mixerOp);
    updateSliderFromParameter(filterSVFCutoff);
    updateSliderFromParameter(filterSVFResonnance);
    updateComboFromParameter(filterSVFMode1);
    updateComboFromParameter(filterSVFMode2);
    updateSliderFromParameter(tunePortamento);
    updateButtonFromParameter(tuneLegato);
}

void PanelEngine::updateUIEnveloppe(String paramName) {
}

bool PanelEngine::containsThisParameterAsEnveloppe(String name) {
    return (name.startsWith("Op") && name.indexOf(" Env") == 3);
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
  <BACKGROUND backgroundColour="173e5a"/>
  <GROUPCOMPONENT name="Osc1 Group" id="f2a0395148710745" memberName="osc1Group"
                  virtualName="" explicitFocusOrder="0" pos="3.358% 9.477% 45.031% 25.054%"
                  title="Oscillator 1"/>
  <GROUPCOMPONENT name="Osc2 Group" id="c95a43b07e06b375" memberName="osc2Group"
                  virtualName="" explicitFocusOrder="0" pos="51.611% 9.477% 45.031% 25.054%"
                  title="Oscillator 2"/>
  <GROUPCOMPONENT name="Mixer Group" id="68ec52c66aafee91" memberName="mixerGroup"
                  virtualName="" explicitFocusOrder="0" pos="28.581% 39.216% 40.096% 22.658%"
                  title="Mixer"/>
  <GROUPCOMPONENT name="Filter Group" id="6e8f214af349f96d" memberName="filterGroup"
                  virtualName="" explicitFocusOrder="0" pos="16.45% 66.231% 66.895% 26.035%"
                  title="Filter"/>
  <GROUPCOMPONENT name="Filter type group" id="a6750fe53a709bc4" memberName="filterTypeGroup"
                  virtualName="" explicitFocusOrder="0" pos="25.223% 0% 47.087% 7.081%"
                  title="Shruthi filter type" textpos="33"/>
  <IMAGEBUTTON name="Info Button" id="bd0f020830de2111" memberName="infoButton"
               virtualName="" explicitFocusOrder="0" pos="9.321% 44.444% 7.128% 11.329%"
               tooltip="Some Info" buttonText="" connectedEdges="0" needsCallback="0"
               radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::iconInfo_png"
               opacityNormal="0.85760861635208129883" colourNormal="50000000"
               resourceOver="" opacityOver="1" colourOver="50000000" resourceDown=""
               opacityDown="1" colourDown="0"/>
  <GROUPCOMPONENT name="Tuning Group" id="26235bda1e7cecac" memberName="tuningGroup"
                  virtualName="" explicitFocusOrder="0" pos="2.193% 39.216% 25.223% 22.658%"
                  title="Tuning"/>
  <GROUPCOMPONENT name="Info Group" id="a34cf8d753760e42" memberName="infoGroup"
                  virtualName="" explicitFocusOrder="0" pos="70.733% 39.216% 25.223% 22.658%"
                  title="Info"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
