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
#include "../SliderPfm2.h"
#include "../../Utils/MidifiedFloatParameter.h"
//[/Headers]

#include "PanelModulationAmbika.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
// 28
const char* matrixSourceNames[] = {
"Envelope 1", "Envelope 2", "Envelope 3", "Lfo 1", "Lfo 2", "Lfo 3", "Voice Lfo", "Modifier 1", "Modifier 2",
"Modifier 3",  "Modifier 4", "Step Seq 1", "Step Seq 2",  "Arpeggiator", "Velocity", "Aftertouch",  
"Pitch-bend", "Mod Wheel",
"Mod Wheel2", "Exp Pedal", "Note number", "Keyb Gate", "Noise", "Note Rand", "= 256",  nullptr 
};

const char* modiferSourceAdditionalNames[] = { "= 128", "= 64", "= 32", "= 16", "= 8", "= 4", nullptr };

// 27
const char* matrixDestNames[] = {
"Osc1 Param","Osc2 PAram", "Osc1 Pitc", "Osc2 Pitch","Osc1&2 Pitch","Fine pitch", "Mix balance",
"Cross mod","Noise","Sub Osc", "Fuzz","Crush", "Filter Cutoff","Filter Res", "Attack", 
"Devay","Release", "Voice Lfo","VCA Gain", nullptr
};


const char* lfoShapes[] = { 
 "Triangle", "Suare", "Sample&Hold", "Ramp", "Sine", "Hrm2", "Hrm3", "Hrm5", "Grg1", "Grg2", "Bat1",
 "Bat2", "Spike 1", "Spike 2", "lSaw", "lsqr", "rSaw", "rSquare", "Stp1", "Stp2",  nullptr };

const char* lfoEnvTriggerText[] = { "Free" , "Env->lfo", "Lfo->Env", nullptr };


const char* operatorOutNames[] = {
 "Off", "Add", "Product", "Product bipolar", "Max", "Min", "Xor", "Greater or equal", "Less or equal", "Quantized", "Low Pass", nullptr
};

const char* lfoRateSyncedText[] = {
    "Internal", 
    "1 / 1",    "3 / 4",    "2 / 3",    "1 / 2",    "3 / 8",    "1 / 3",    "1 / 4",    "1 / 6",
    "1 / 8",    "1 / 12",    "1 / 16",    "1 / 24",    "1 / 32",    "1 / 48",    "1 / 96",
    nullptr
};

//[/MiscUserDefs]

//==============================================================================
PanelModulation::PanelModulation ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (lfoGroup = new GroupComponent ("Lfo Group",
                                                      String()));

    addAndMakeVisible (matrixGroup = new GroupComponent ("matrixGroup",
                                                         TRANS("Modulation")));

    addAndMakeVisible (operatorsGroup = new GroupComponent ("operatorsGroup",
                                                            TRANS("Operators")));

    addAndMakeVisible (lfoVoiceGroup = new GroupComponent ("Lfo Voice Group",
                                                           TRANS("Lfo Voice")));

    addAndMakeVisible (envGroup = new GroupComponent ("Env Group",
                                                      String()));


    //[UserPreSize]



	for (int r = 0; r < NUMBER_OF_MATRIX_ROW; r++) {
		addAndMakeVisible(matrixRowLabel[r] = new Label(String("matrix label ") + String(r + 1), String(r + 1)));
		matrixRowLabel[r]->setJustificationType(Justification::centred);

		addAndMakeVisible(matrixMultipler[r] = new SliderPfm2("Mtx" + String(r + 1) + " Multiplier"));
		matrixMultipler[r]->setRange(-63.0f, 63.0f, 1.00f);
		matrixMultipler[r]->setSliderStyle(Slider::RotaryVerticalDrag);
		matrixMultipler[r]->setTextBoxStyle(Slider::TextBoxLeft, false, 35, 16);
		matrixMultipler[r]->setDoubleClickReturnValue(true, 0.0f);
		matrixMultipler[r]->setValue(0.0f, dontSendNotification);
		matrixMultipler[r]->addListener(this);

		addAndMakeVisible(matrixSource[r] = new ComboBox("Mtx" + String(r + 1) + " Source"));
		matrixSource[r]->setEditableText(false);
		matrixSource[r]->setJustificationType(Justification::centred);
		matrixSource[r]->setColour(ComboBox::buttonColourId, Colours::blue);
		for (int i = 0; matrixSourceNames[i] != nullptr; i++) {
			matrixSource[r]->addItem(matrixSourceNames[i], i + 1);
		}
		matrixSource[r]->setSelectedId(1);
		matrixSource[r]->setScrollWheelEnabled(true);
		matrixSource[r]->addListener(this);

		addAndMakeVisible(matrixDestination[r] = new ComboBox("Mtx" + String(r + 1) + " Destination"));
		matrixDestination[r]->setEditableText(false);
		matrixDestination[r]->setJustificationType(Justification::centred);
		matrixDestination[r]->setColour(ComboBox::buttonColourId, Colours::blue);
		for (int i = 0; matrixDestNames[i] != nullptr; i++) {
			matrixDestination[r]->addItem(matrixDestNames[i], i + 1);
		}
        matrixSource[r]->setSelectedId(1);
        matrixDestination[r]->setScrollWheelEnabled(true);
		matrixDestination[r]->addListener(this);
	}



    addAndMakeVisible(matrixSourceLabel = new Label("Mtx Source Label", "Source"));
    matrixSourceLabel->setJustificationType(Justification::centred);
    addAndMakeVisible(matrixMultiplierLabel = new Label("Mtx Multipler Label", "Multiplier"));
    matrixMultiplierLabel->setJustificationType(Justification::centred);
    addAndMakeVisible(matrixDestinationLabel = new Label("Mtx Destination Label", "Destination"));
    matrixDestinationLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(lfoShapeLabel = new Label("Lfo Shape label", "Shape"));
    lfoShapeLabel->setJustificationType(Justification::centred);
    addAndMakeVisible(lfoRateLabel = new Label("Lfo Rate label", "Rate"));
    lfoRateLabel->setJustificationType(Justification::centred);
    addAndMakeVisible(lfoVoiceShapeLabel = new Label("Lfovoice Shape label", "Shape"));
    lfoVoiceShapeLabel->setJustificationType(Justification::centredRight);
    addAndMakeVisible(lfoVoiceRateLabel = new Label("Lfovoice Rate label", "Rate"));
    lfoVoiceRateLabel->setJustificationType(Justification::centredRight);

    for (int l = 0; l < NUMBER_OF_LFO_ENV; l++) {

        addAndMakeVisible(lfoEnvTriggerLabel[l] = new Label("Lfo Trigger label", "Trigger "+ String(l+1)));
        lfoEnvTriggerLabel[l]->setJustificationType(Justification::centred);

        // LFO 1 waveform 0-20 24 112

        addAndMakeVisible(lfoShape[l] = new ComboBox("Lfo" + String(l + 1) + " Shape"));
        lfoShape[l]->setEditableText(false);
        lfoShape[l]->setJustificationType(Justification::centred);
        lfoShape[l]->setColour(ComboBox::buttonColourId, Colours::blue);
        for (int i = 0; lfoShapes[i] != nullptr; i++) {
            lfoShape[l]->addItem(lfoShapes[i], i + 1);
        }
        lfoShape[l]->setSelectedId(1);
        lfoShape[l]->setScrollWheelEnabled(true);
        lfoShape[l]->addListener(this);

        // LFO 1 rate 0 - 143 25 113

        addAndMakeVisible(lfoRate[l] = new ComboAndSlider("Lfo" + String(l + 1) + " Rate"));
        lfoRate[l]->setComboParams(lfoRateSyncedText, 0);
        lfoRate[l]->setSliderParams(0.0f, 127.0f, 15.0);
        lfoRate[l]->addListener(this);

        // Trigger
        addAndMakeVisible(lfoEnvTrigger[l] = new ComboBox("LfoEnv" + String(l + 1) + " Trigger"));
        lfoEnvTrigger[l]->setEditableText(false);
        lfoEnvTrigger[l]->setJustificationType(Justification::centred);
        for (int i = 0; lfoEnvTriggerText[i] != nullptr; i++) {
            lfoEnvTrigger[l]->addItem(lfoEnvTriggerText[i], i + 1);
        }
        lfoEnvTrigger[l]->setSelectedId(1);
        lfoEnvTrigger[l]->setScrollWheelEnabled(true);
        lfoEnvTrigger[l]->addListener(this);

        addAndMakeVisible(enveloppe[l] = new Enveloppe());
        enveloppe[l]->setName("Env" + String(l + 1));
        enveloppe[l]->addListener(this);

        addAndMakeVisible(lfoButton[l] = new TextButton("Text Button Env" + String(l)));
        lfoButton[l]->setButtonText("Lfo " + String(l + 1));
        lfoButton[l]->setRadioGroupId(771);
        lfoButton[l]->setClickingTogglesState(true);
        lfoButton[l]->setConnectedEdges((l > 0 ? Button::ConnectedOnLeft : 0) + (l < 2 ? Button::ConnectedOnRight : 0));
        lfoButton[l]->addListener(this);

        addAndMakeVisible(envButton[l] = new TextButton("Text Button Env" + String(l)));
        envButton[l]->setButtonText("Env " + String(l + 1));
        envButton[l]->setRadioGroupId(772);
        envButton[l]->setClickingTogglesState(true);
        envButton[l]->setConnectedEdges((l > 0 ? Button::ConnectedOnLeft : 0) + (l < 2 ? Button::ConnectedOnRight : 0));
        envButton[l]->addListener(this);

    }

    // Voice LFO
    addAndMakeVisible(lfoVoiceShape = new ComboBox("Lfovoice Shape"));
    lfoVoiceShape->setEditableText(false);
    lfoVoiceShape->setJustificationType(Justification::centred);
    for (int i = 0; lfoShapes[i] != nullptr && i < 4; i++) {
        lfoVoiceShape->addItem(lfoShapes[i], i + 1);
    }
    lfoVoiceShape->setSelectedId(1);
    lfoVoiceShape->setScrollWheelEnabled(true);
    lfoVoiceShape->addListener(this);

    addAndMakeVisible(lfoVoiceRate = new SliderPfm2("Lfovoice Rate"));
    lfoVoiceRate->setRange(0.0f, 127.0f, 1.00f);
    lfoVoiceRate->setSliderStyle(Slider::RotaryVerticalDrag);
    lfoVoiceRate->setTextBoxStyle(Slider::TextBoxLeft, false, 35, 16);
    lfoVoiceRate->setDoubleClickReturnValue(true, 0.0f);
    lfoVoiceRate->setValue(0.0f, dontSendNotification);
    lfoVoiceRate->addListener(this);



    addAndMakeVisible(operatorSource1Label = new Label("Op Source1 Label", "Input 1"));
    operatorSource1Label->setJustificationType(Justification::centred);
    addAndMakeVisible(operatorSource2Label = new Label("Op Source2 Label", "Input 2"));
    operatorSource2Label->setJustificationType(Justification::centred);
    addAndMakeVisible(operatorOutLabel = new Label("Op Out Label", "Operator"));
    operatorOutLabel->setJustificationType(Justification::centred);


    for (int r = 0; r < NUMBER_OF_OPERATORS; r++) {
        addAndMakeVisible(operatorRowLabel[r] = new Label(String("Op label ") + String(r + 1), String(r + 1)));
        operatorRowLabel[r]->setJustificationType(Justification::centred);


        addAndMakeVisible(operatorSource1[r] = new ComboBox("Op" + String(r + 1) + " Source1"));
        operatorSource1[r]->setEditableText(false);
        operatorSource1[r]->setJustificationType(Justification::centred);
        int i;
        for (i = 0; matrixSourceNames[i] != nullptr; i++) {
            operatorSource1[r]->addItem(matrixSourceNames[i], i + 1);
        }
        for (int j = 0; modiferSourceAdditionalNames[j] != nullptr; j++) {
            operatorSource1[r]->addItem(matrixSourceNames[j], j + i + 1);
        }
        operatorSource1[r]->setSelectedId(1);
        operatorSource1[r]->setScrollWheelEnabled(true);
        operatorSource1[r]->addListener(this);

        addAndMakeVisible(operatorSource2[r] = new ComboBox("Op" + String(r + 1) + " Source2"));
        operatorSource2[r]->setEditableText(false);
        operatorSource2[r]->setJustificationType(Justification::centred);
        for (int i = 0; matrixSourceNames[i] != nullptr; i++) {
            operatorSource2[r]->addItem(matrixSourceNames[i], i + 1);
        }
        for (int j = 0; modiferSourceAdditionalNames[j] != nullptr; j++) {
            operatorSource2[r]->addItem(matrixSourceNames[j], j + i + 1);
        }
        operatorSource2[r]->setSelectedId(1);
        operatorSource2[r]->setScrollWheelEnabled(true);
        operatorSource2[r]->addListener(this);

        addAndMakeVisible(operatorOut[r] = new ComboBox("Op" + String(r + 1) + " Out"));
        operatorOut[r]->setEditableText(false);
        operatorOut[r]->setJustificationType(Justification::centred);
        for (int i = 0; operatorOutNames[i] != nullptr; i++) {
            operatorOut[r]->addItem(operatorOutNames[i], i + 1);
        }
        operatorOut[r]->setSelectedId(1);
        operatorOut[r]->setScrollWheelEnabled(true);
        operatorOut[r]->addListener(this);
    }


    //[/UserPreSize]

    setSize (1000, 710);


    //[Constructor] You can add your own custom stuff here..
	eventsToAdd = nullptr;
    lfoButton[0]->setToggleState(true, sendNotification);
    envButton[0]->setToggleState(true, sendNotification);
    //[/Constructor]
}

PanelModulation::~PanelModulation()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lfoGroup = nullptr;
    matrixGroup = nullptr;
    operatorsGroup = nullptr;
    lfoVoiceGroup = nullptr;
    envGroup = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PanelModulation::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        int x = proportionOfWidth (0.0100f), y = proportionOfHeight (0.3400f), width = proportionOfWidth (0.5000f), height = proportionOfHeight (0.6500f);
        Colour fillColour1 = Colour (0xff19547e), fillColour2 = Colour (0xff173e5a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        fillColour1 = findColour(PopupMenu::backgroundColourId).darker();
        fillColour2 = findColour(PopupMenu::backgroundColourId);
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       static_cast<float> (proportionOfWidth (0.2500f)) - static_cast<float> (proportionOfWidth (0.0100f)) + x,
                                       static_cast<float> (proportionOfHeight (0.6500f)) - static_cast<float> (proportionOfHeight (0.3400f)) + y,
                                       fillColour2,
                                       static_cast<float> (proportionOfWidth (0.2500f)) - static_cast<float> (proportionOfWidth (0.0100f)) + x,
                                       static_cast<float> (proportionOfHeight (0.3600f)) - static_cast<float> (proportionOfHeight (0.3400f)) + y,
                                       true));
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PanelModulation::resized()
{
    //[UserPreResize] Add your own custom resize code here..

    if (false) {

    //[/UserPreResize]

    lfoGroup->setBounds (proportionOfWidth (0.4473f), proportionOfHeight (0.0174f), proportionOfWidth (0.5421f), proportionOfHeight (0.2614f));
    matrixGroup->setBounds (proportionOfWidth (0.0057f), 0, proportionOfWidth (0.4275f), getHeight() - 0);
    operatorsGroup->setBounds (proportionOfWidth (0.4473f), proportionOfHeight (0.7320f), proportionOfWidth (0.5421f), proportionOfHeight (0.2353f));
    lfoVoiceGroup->setBounds (proportionOfWidth (0.4473f), proportionOfHeight (0.5055f), proportionOfWidth (0.5265f), proportionOfHeight (0.1569f));
    envGroup->setBounds (proportionOfWidth (0.4473f), proportionOfHeight (0.3312f), proportionOfWidth (0.5421f), proportionOfHeight (0.1656f));
    //[UserResized] Add your own custom resize handling here..

    }

    Rectangle<int> mainBounds = getLocalBounds();

    matrixGroup->setBounds(mainBounds.removeFromLeft(mainBounds.getWidth() * .4f).reduced(3));
    operatorsGroup->setBounds(mainBounds.removeFromBottom(mainBounds.getHeight() / 4.0f).reduced(3));
    //env2Group->setBounds(mainBounds.removeFromBottom(mainBounds.getHeight() / 3).reduced(3));
    lfoVoiceGroup->setBounds(mainBounds.removeFromBottom(mainBounds.getHeight() / 4).reduced(3));
    envGroup->setBounds(mainBounds.removeFromBottom(mainBounds.getHeight() / 2 - 15).reduced(3));
    lfoGroup->setBounds(mainBounds.removeFromRight(mainBounds.getWidth() * .75).reduced(3));
    Rectangle<int> triggerBounds = mainBounds;

    Rectangle<int> matrixBounds = matrixGroup->getBounds();
    matrixBounds.removeFromTop(12);
    Rectangle<int> matrixLabelsBounds = matrixBounds.removeFromTop(18);
    matrixLabelsBounds.removeFromLeft(matrixLabelsBounds.getWidth() / 15);
    matrixSourceLabel->setBounds(matrixLabelsBounds.removeFromLeft(matrixLabelsBounds.getWidth() / 3));
    matrixMultiplierLabel->setBounds(matrixLabelsBounds.removeFromLeft(matrixLabelsBounds.getWidth() / 2));
    matrixDestinationLabel->setBounds(matrixLabelsBounds);

    for (int r = 0; r < NUMBER_OF_MATRIX_ROW; r++) {
        Rectangle<int> rowBounds = matrixBounds.removeFromTop(matrixBounds.getHeight() / (NUMBER_OF_MATRIX_ROW - r));
		matrixRowLabel[r]->setBounds(rowBounds.removeFromLeft(rowBounds.getWidth() / 15));
		matrixSource[r]->setBounds(rowBounds.removeFromLeft(rowBounds.getWidth() / 3).reduced(10, rowBounds.getHeight() / 2 - 10));
		matrixMultipler[r]->setBounds(rowBounds.removeFromLeft(rowBounds.getWidth() / 2).expanded(0, 4));
		matrixDestination[r]->setBounds(rowBounds.reduced(10, rowBounds.getHeight() / 2 - 10));
	}

    Rectangle<int> operatorBounds = operatorsGroup->getBounds();
    operatorBounds.removeFromTop(12);
    operatorBounds.removeFromBottom(10);;

    Rectangle<int> operatorLabelsBounds = operatorBounds.removeFromTop(18);
    operatorLabelsBounds.removeFromLeft(operatorLabelsBounds.getWidth() / 15);
    operatorSource1Label->setBounds(operatorLabelsBounds.removeFromLeft(operatorLabelsBounds.getWidth() / 3));
    operatorSource2Label->setBounds(operatorLabelsBounds.removeFromLeft(operatorLabelsBounds.getWidth() / 2));
    operatorOutLabel->setBounds(operatorLabelsBounds);

    for (int r = 0; r < NUMBER_OF_OPERATORS; r++) {
        Rectangle<int> rowBounds = operatorBounds.removeFromTop(operatorBounds.getHeight() / (NUMBER_OF_OPERATORS - r));
        operatorRowLabel[r]->setBounds(rowBounds.removeFromLeft(rowBounds.getWidth() / 15));
        operatorSource1[r]->setBounds(rowBounds.removeFromLeft(rowBounds.getWidth() / 3).reduced(10, rowBounds.getHeight() / 2 - 10));
        operatorSource2[r]->setBounds(rowBounds.removeFromLeft(rowBounds.getWidth() / 2).reduced(10, rowBounds.getHeight() / 2 - 10));
        operatorOut[r]->setBounds(rowBounds.reduced(10, rowBounds.getHeight() / 2 - 10));
    }


    Rectangle<int> lfoGroupBounds = lfoGroup->getBounds();
    Rectangle<int> lfoButtonsBounds = lfoGroupBounds.removeFromTop(25);
    lfoButtonsBounds.removeFromLeft(20);
    for (int e = 0; e< NUMBER_OF_LFO_ENV; e++) {
        lfoButton[e]->setBounds(lfoButtonsBounds.removeFromLeft(70));
    }

    triggerBounds.removeFromTop(triggerBounds.getHeight() / 2 - 75);
    for (int l = 0; l < NUMBER_OF_LFO_ENV; l++) {
        lfoEnvTriggerLabel[l]->setBounds(triggerBounds.removeFromTop(20).reduced(10,0));
        lfoEnvTrigger[l]->setBounds(triggerBounds.removeFromTop(20).reduced(10, 0));
        triggerBounds.removeFromTop(10);
    }

    for (int l = 0; l < NUMBER_OF_LFO_ENV; l++) {
        Rectangle<int> thisLfoBounds = lfoGroupBounds;

        Rectangle<int> thisLfoRate = thisLfoBounds.removeFromLeft(thisLfoBounds.getWidth() / 2);
        thisLfoRate.removeFromTop(20);
        lfoShapeLabel->setBounds(thisLfoRate.removeFromTop(20).reduced(thisLfoRate.getWidth() / 2 - 50, 0));
        lfoShape[l]->setBounds(thisLfoRate.removeFromTop(20).reduced(thisLfoRate.getWidth() / 2 - 50, 0));

        thisLfoRate = thisLfoBounds;
        lfoRateLabel->setBounds(thisLfoRate.removeFromTop(20).reduced(thisLfoRate.getWidth() / 2 - 50, 0));
        lfoRate[l]->setBounds(thisLfoRate.reduced(15));

    }

    Rectangle<int> envGroupBounds = envGroup->getBounds();
    Rectangle<int> envButtonsBounds = envGroupBounds.removeFromTop(25);
    envButtonsBounds.removeFromLeft(20);
    for (int e = 0; e< NUMBER_OF_LFO_ENV; e++) {
        envButton[e]->setBounds(envButtonsBounds.removeFromLeft(100));
    }

    for (int l = 0; l < NUMBER_OF_LFO_ENV; l++) {
        enveloppe[l]->setBounds(envGroupBounds);
    }


    Rectangle<int> lfoVoiceBounds = lfoVoiceGroup->getBounds();
    lfoVoiceBounds.removeFromTop(20);
    int lfoVoiceToCut = lfoVoiceBounds.getWidth() / 8;
    lfoVoiceBounds.removeFromRight(lfoVoiceToCut);
    lfoVoiceShapeLabel->setBounds(lfoVoiceBounds.removeFromLeft(lfoVoiceBounds.getWidth() / 4).reduced(10, 10));
    lfoVoiceShape->setBounds(lfoVoiceBounds.removeFromLeft(lfoVoiceBounds.getWidth() / 3).reduced(10, lfoVoiceBounds.getHeight() / 2 - 10));
    lfoVoiceRateLabel->setBounds(lfoVoiceBounds.removeFromLeft(lfoVoiceBounds.getWidth() / 2).reduced(10, 10));
    lfoVoiceRate->setBounds(lfoVoiceBounds.removeFromLeft(lfoVoiceBounds.getWidth() / 1).reduced(0, 0));


    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void PanelModulation::buttonClicked(Button* buttonThatWasClicked) {
    int envIndex = -1;
    int lfoIndex = -1;
    for (int e = 0; e < NUMBER_OF_LFO_ENV; e++) {
        if (buttonThatWasClicked == lfoButton[e]) {
            lfoIndex = e;
            break;
        }
        if (buttonThatWasClicked == envButton[e]) {
            envIndex = e;
            break;
        }
    }
    if (envIndex != -1) {
        for (int e = 0; e < NUMBER_OF_LFO_ENV; e++) {
            DBG("Enveloppe " << e << " visible : " << ((e == envIndex) ? "true" : "false"));
            enveloppe[e]->setVisible(e == envIndex);
        }
    }
    if (lfoIndex != -1) {
        for (int e = 0; e < NUMBER_OF_LFO_ENV; e++) {
            lfoShape[e]->setVisible(e == lfoIndex);
            lfoRate[e]->setVisible(e == lfoIndex);
        }
    }
}

void PanelModulation::sliderValueChanged(Slider* sliderThatWasMoved) {
	sliderValueChanged(sliderThatWasMoved, true);
}

void PanelModulation::sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI)
{
	// Update the value if the change comes from the UI
	if (fromPluginUI) {
		AudioProcessorParameter * parameterReady = parameterMap[sliderThatWasMoved->getName()];
		if (parameterReady != nullptr) {
			float value = (float)sliderThatWasMoved->getValue();
			((MidifiedFloatParameter*)parameterReady)->setValueFromUI(value);
		}
	}

}

void PanelModulation::comboBoxChanged(ComboBox* comboBoxThatHasChanged) {
	comboBoxChanged(comboBoxThatHasChanged, true);
}

void PanelModulation::comboBoxChanged(ComboBox* comboBoxThatHasChanged, bool fromPluginUI) {
	// Update the value if the change comes from the UI
	if (fromPluginUI) {
		AudioProcessorParameter * parameterReady = parameterMap[comboBoxThatHasChanged->getName()];
		if (parameterReady != nullptr) {
			float value = (float)comboBoxThatHasChanged->getSelectedId();
			((MidifiedFloatParameter*)parameterReady)->setValueFromUI(value - 1.0f);
		}
	}
}


void PanelModulation::buildParameters() {
    for (int l = 0; l < NUMBER_OF_LFO_ENV; l++) {
        updateComboFromParameter(lfoShape[l]);
        updateComboAndSliderFromParameter(lfoRate[l]);
        updateComboFromParameter(lfoEnvTrigger[l]);
    }
    updateComboFromParameter(lfoVoiceShape);
    updateSliderFromParameter(lfoVoiceRate);


    // Initialize paramMap for enveloppe
    const char** pointName = enveloppe[0]->getPointSuffix();
    for (int p = 1; p < enveloppe[0]->getNumberOfPoints(); p++) {
        checkParamExistence("Env1" + String(pointName[p - 1]));
        checkParamExistence("Env2" + String(pointName[p - 1]));
        checkParamExistence("Env3" + String(pointName[p - 1]));
    }

	// Let listen to enveloppe
    for (int e = 0; e < 3; e++) {
    	enveloppe[e]->addListener((EnveloppeListener*)this);
    }

    for (int r = 0; r < NUMBER_OF_MATRIX_ROW; r++) {
        updateSliderFromParameter(matrixMultipler[r]);
        updateComboFromParameter(matrixDestination[r]);
        updateComboFromParameter(matrixSource[r]);
    }
    for (int r = 0; r < NUMBER_OF_OPERATORS; r++) {
        updateComboFromParameter(operatorSource1[r]);
        updateComboFromParameter(operatorSource2[r]);
        updateComboFromParameter(operatorOut[r]);
    }
}


void PanelModulation::updateUIEnveloppe(String paramName) {
	const char** pointName = enveloppe[0]->getPointSuffix();
    Enveloppe* env;
    if (paramName.startsWith("Env1")) {
        env = enveloppe[0];
    }
    else if (paramName.startsWith("Env2")) {
        env = enveloppe[1];
    }
    else if (paramName.startsWith("Env3")) {
        env = enveloppe[2];
    }
    else {
        return;
    }

    String pString = env->getName();
    for (int p = 1; p < env->getNumberOfPoints(); p++) {
		String name = pString + String(pointName[p - 1]);

		MidifiedFloatParameter* param = checkParamExistence(name);

		if (paramName.length() > 0 && (param == nullptr || name != String(paramName))) {
			continue;
		}

		// And let's update the value and update the UI Without sending modification !!!
		// No modification : we dont want sliderValueChanged to be called in the different panels

		if (p == 3) {
			if (param->getValue() != env->getY(p)) {
				env->setY(p, param->getRealValue());
				env->repaint();
			}
		}
		else {
			if (param->getValue() != env->getX(p)) {
				env->setX(p, param->getRealValue());
				env->repaint();
			}
		}
	}
}

void PanelModulation::updateUIStepSequencer(String paramName) {
	if (paramName.startsWith("Step Seq 1")) {
//		updateStepSeqParameter(stepSequencer[0]);
	}
	else {
//		updateStepSeqParameter(stepSequencer[1]);
	}
}



bool PanelModulation::containsThisParameterAsEnveloppe(String name) {
    return (name.startsWith("Env") != -1 && name[3] >= '1' && name[3] <= '3');
}


void PanelModulation::updateSliderFromParameter_hook(Slider* slider) {
	sliderValueChanged(slider, false);
}

void PanelModulation::updateComboFromParameter_hook(ComboBox* combo) {
	comboBoxChanged(combo, false);
}

void PanelModulation::sliderDragStarted(Slider* slider) {
	AudioProcessorParameter * param = parameterMap[slider->getName()];
	if (param != nullptr) {
		param->beginChangeGesture();
	}
}
void PanelModulation::sliderDragEnded(Slider* slider) {
	AudioProcessorParameter * param = parameterMap[slider->getName()];
	if (param != nullptr) {
		param->endChangeGesture();
	}
}

void PanelModulation::comboOrSliderValueChanged(ComboAndSlider* comboAndSlider) {
    DBG("comboOrSliderValueChanged : " << comboAndSlider->getValue());
    AudioProcessorParameter * parameterReady = parameterMap[comboAndSlider->getName()];
    if (parameterReady != nullptr) {
        float value = (float)comboAndSlider->getValue();
        ((MidifiedFloatParameter*)parameterReady)->setValueFromUI(value);
    }
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PanelModulation" componentName=""
                 parentClasses="public Component, public Button::Listener, public Slider::Listener, public ComboBox::Listener, public PanelOfComponents, public ComboAndSlider::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="1000"
                 initialHeight="710">
  <BACKGROUND backgroundColour="173e5a">
    <RECT pos="1% 34% 50% 65%" fill=" radial: 25% 65%, 25% 36%, 0=ff19547e, 1=ff173e5a"
          hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="Lfo Group" id="3420ca195fbbe4e6" memberName="lfoGroup"
                  virtualName="" explicitFocusOrder="0" pos="44.728% 1.743% 54.211% 26.144%"
                  title=""/>
  <GROUPCOMPONENT name="matrixGroup" id="e0162bb0e79330d7" memberName="matrixGroup"
                  virtualName="" explicitFocusOrder="0" pos="0.566% 0 42.746% 0M"
                  title="Modulation"/>
  <GROUPCOMPONENT name="operatorsGroup" id="47b2f0c9ab2af6e8" memberName="operatorsGroup"
                  virtualName="" explicitFocusOrder="0" pos="44.728% 73.203% 54.211% 23.529%"
                  title="Operators"/>
  <GROUPCOMPONENT name="Lfo Voice Group" id="2db8201ad14cec86" memberName="lfoVoiceGroup"
                  virtualName="" explicitFocusOrder="0" pos="44.728% 50.545% 52.654% 15.686%"
                  title="Lfo Voice"/>
  <GROUPCOMPONENT name="Env Group" id="fe52f427d633eb91" memberName="envGroup"
                  virtualName="" explicitFocusOrder="0" pos="44.728% 33.115% 54.211% 16.558%"
                  title=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
