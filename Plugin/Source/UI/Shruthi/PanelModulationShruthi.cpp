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
#include "../Utils/MidifiedFloatParameter.h"
//[/Headers]

#include "PanelModulation.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
// 28
const char* matrixSourceNames[] = {
"Lfo 1","Lfo 2","Sequencer","Seq 1","Seq 2","Arpegiator","M Wheel","Aftertouch","Bender",
"Offset","cv1","cv2","cv3","cv4","ccA (16)","ccB (17)","Bre (18)","Ped (19)","Noise",
"Envelope 1","Envelope 2","Velocity","Random","Note","Gate","Audio","Operator 1","Operator 2", nullptr
};

// 27
const char* matrixDestNames[] = {
    "Pwm1","Pwm2","Osc 1","Osc 2","Osc 1+2","Osc 1+2 fine","Mix","Noise","Sub Osc","Cutoff","Resonnance",
    "Vca","Cv1", "Cv2",
    "Env1 trigger","Env1 Attk","Env1 Dec","Env1 Sust","Env1 Rel","Env2 trigger","Env2 Attk",
    "Env2 Dec","Env2 Sust", "Env2 Rel","Env1+2 Attk","Lfo1 Rate","Lfo2 Rate",
    nullptr
};

const int matrixDestValue[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 11, 1, 12, 13, 17, 19, 20, 21, 22, 18, 23, 24, 25, 26, 14, 15, 16};
const char* lfoShapes[] = { "Triangle", "Square", "S&hold", "Ramp", "Step", "~1", "~2", "~3", "~4", "~5", "~6", "~7", "~8", "~9", "~10", "~11", "~12", "~13", "~14", "~15", "~16", nullptr };

const char* lfoModes[] = { "Free" , "Slave", "Master", "First Shot", nullptr };

const char* operatorSourceNames[] = {
 "Lfo 1", "Lfo 2", "Sequencer", "Seq 1", "Seq 2", "Arpegiator", "M Wheel", "Aftertouch", "Bender",
 "Offset",
 "cv1","cv2","cv3","cv4","ccA (16)","ccB (17)","Bre (18)","Ped (19)","Noise",
 "Envelope 1","Envelope 2","Velocity","Random","Note","Gate","Audio","Operator 1","Operator 2",
 "= 4", "= 8", "= 16", "= 32", nullptr
};

const char* operatorOutNames[] = {
 "off", "Add", "Product", "Max", "Min", "xor", ">=", "<=", "Quantized", "lag", nullptr
};

const char* lfoRateSyncedText[] = {
    "Internal", "x1", "x2","x3","x4","x5","x6","x7","x8","x9","x10","x11","x12","x13","x14","x15","x16", nullptr
};

//[/MiscUserDefs]

//==============================================================================
PanelModulation::PanelModulation ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (lfo1Group = new GroupComponent ("lfo1Group",
                                                       TRANS("Lfo 1")));

    addAndMakeVisible (env1Group = new GroupComponent ("env1Group",
                                                       TRANS("Env 1")));

    addAndMakeVisible (matrixGroup = new GroupComponent ("matrixGroup",
                                                         TRANS("Modulation")));

    addAndMakeVisible (env2Group = new GroupComponent ("env2Group",
                                                       TRANS("Env 2")));

    addAndMakeVisible (operatorsGroup = new GroupComponent ("operatorsGroup",
                                                            TRANS("Operators")));

    addAndMakeVisible (lfo2Group = new GroupComponent ("lfo2Group",
                                                       TRANS("Lfo 2")));


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
			matrixDestination[r]->addItem(matrixDestNames[i], matrixDestValue[i] + 1);
		}
		matrixDestination[r]->setScrollWheelEnabled(true);
		matrixDestination[r]->addListener(this);
	}

	addAndMakeVisible(enveloppe1 = new Enveloppe());
    enveloppe1->setName("Env1");

	addAndMakeVisible(enveloppe2 = new Enveloppe());
    enveloppe2->setName("Env2");


    addAndMakeVisible(matrixSourceLabel = new Label("Mtx Source Label", "Source"));
    matrixSourceLabel->setJustificationType(Justification::centred);
    addAndMakeVisible(matrixMultiplierLabel = new Label("Mtx Multipler Label", "Multiplier"));
    matrixMultiplierLabel->setJustificationType(Justification::centred);
    addAndMakeVisible(matrixDestinationLabel = new Label("Mtx Destination Label", "Destination"));
    matrixDestinationLabel->setJustificationType(Justification::centred);


    for (int l = 0; l < NUMBER_OF_LFO; l++) {
        // LFO 1 waveform 0-20 24 112
        addAndMakeVisible(lfoShapeLabel[l] = new Label("Lfo" + String(l + 1) + " Shape label", "Shape"));
        lfoShapeLabel[l]->setJustificationType(Justification::centred);

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
        addAndMakeVisible(lfoRateLabel[l] = new Label("Lfo" + String(l + 1) + " Rate label", "Rate"));
        lfoRateLabel[l]->setJustificationType(Justification::centred);

        addAndMakeVisible(lfoRate[l] = new ComboAndSlider("Lfo" + String(l + 1) + " Rate"));
        lfoRate[l]->setComboParams(lfoRateSyncedText, 0);
        lfoRate[l]->setSliderParams(0.0f, 127.0f, 16.0);
        lfoRate[l]->addListener(this);

        // LFO 1 rise time 0 - 127 26 114
        addAndMakeVisible(lfoAttackLabel[l] = new Label("Lfo" + String(l + 1) + " Attack label", "Attack"));
        lfoAttackLabel[l]->setJustificationType(Justification::centred);

        addAndMakeVisible(lfoAttack[l] = new SliderPfm2("Lfo" + String(l + 1) + " Attack"));
        lfoAttack[l]->setRange(0.0f, 127.0f, 1.00f);
        lfoAttack[l]->setSliderStyle(Slider::RotaryVerticalDrag);
        lfoAttack[l]->setTextBoxStyle(Slider::TextBoxLeft, false, 35, 16);
        lfoAttack[l]->setDoubleClickReturnValue(true, 0.0f);
        lfoAttack[l]->setValue(0.0f, dontSendNotification);
        lfoAttack[l]->addListener(this);

        // LFO 1 master / slave 0 - 3 27 115
        addAndMakeVisible(lfoModeLabel[l] = new Label("Lfo" + String(l + 1) + " Mode label", "Mode"));
        lfoModeLabel[l]->setJustificationType(Justification::centred);

        addAndMakeVisible(lfoMode[l] = new ComboBox("Lfo" + String(l + 1) + " Mode"));
        lfoMode[l]->setEditableText(false);
        lfoMode[l]->setJustificationType(Justification::centred);
        lfoMode[l]->setColour(ComboBox::buttonColourId, Colours::blue);
        for (int i = 0; lfoModes[i] != nullptr; i++) {
            lfoMode[l]->addItem(lfoModes[i], i + 1);
        }
        lfoMode[l]->setSelectedId(1);
        lfoMode[l]->setScrollWheelEnabled(true);
        lfoMode[l]->addListener(this);
    }


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
        operatorSource1[r]->setColour(ComboBox::buttonColourId, Colours::blue);
        for (int i = 0; operatorSourceNames[i] != nullptr; i++) {
            operatorSource1[r]->addItem(operatorSourceNames[i], i + 1);
        }
        operatorSource1[r]->setSelectedId(1);
        operatorSource1[r]->setScrollWheelEnabled(true);
        operatorSource1[r]->addListener(this);

        addAndMakeVisible(operatorSource2[r] = new ComboBox("Op" + String(r + 1) + " Source2"));
        operatorSource2[r]->setEditableText(false);
        operatorSource2[r]->setJustificationType(Justification::centred);
        operatorSource2[r]->setColour(ComboBox::buttonColourId, Colours::blue);
        for (int i = 0; operatorSourceNames[i] != nullptr; i++) {
            operatorSource2[r]->addItem(operatorSourceNames[i], i + 1);
        }
        operatorSource2[r]->setSelectedId(1);
        operatorSource2[r]->setScrollWheelEnabled(true);
        operatorSource2[r]->addListener(this);

        addAndMakeVisible(operatorOut[r] = new ComboBox("Op" + String(r + 1) + " Out"));
        operatorOut[r]->setEditableText(false);
        operatorOut[r]->setJustificationType(Justification::centred);
        operatorOut[r]->setColour(ComboBox::buttonColourId, Colours::blue);
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
    //[/Constructor]
}

PanelModulation::~PanelModulation()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lfo1Group = nullptr;
    env1Group = nullptr;
    matrixGroup = nullptr;
    env2Group = nullptr;
    operatorsGroup = nullptr;
    lfo2Group = nullptr;


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

    lfo1Group->setBounds (proportionOfWidth (0.0048f), proportionOfHeight (0.0087f), proportionOfWidth (0.2577f), proportionOfHeight (0.2353f));
    env1Group->setBounds (proportionOfWidth (0.0048f), proportionOfHeight (0.2440f), proportionOfWidth (0.5422f), proportionOfHeight (0.2527f));
    matrixGroup->setBounds (proportionOfWidth (0.5593f), 0, proportionOfWidth (0.4277f), getHeight() - 0);
    env2Group->setBounds (proportionOfWidth (0.0048f), proportionOfHeight (0.4967f), proportionOfWidth (0.5422f), proportionOfHeight (0.2527f));
    operatorsGroup->setBounds (proportionOfWidth (0.0048f), proportionOfHeight (0.7495f), proportionOfWidth (0.5422f), proportionOfHeight (0.2353f));
    lfo2Group->setBounds (proportionOfWidth (0.2844f), proportionOfHeight (0.0087f), proportionOfWidth (0.2577f), proportionOfHeight (0.2353f));
    //[UserResized] Add your own custom resize handling here..

    }

    Rectangle<int> mainBounds = getLocalBounds();

    matrixGroup->setBounds(mainBounds.removeFromLeft(mainBounds.getWidth() * .4).reduced(3));
    operatorsGroup->setBounds(mainBounds.removeFromBottom(mainBounds.getHeight() / 6).reduced(3));
    env2Group->setBounds(mainBounds.removeFromBottom(mainBounds.getHeight() / 3).reduced(3));
    env1Group->setBounds(mainBounds.removeFromBottom(mainBounds.getHeight() / 2).reduced(3));
    lfo1Group->setBounds(mainBounds.removeFromLeft(mainBounds.getWidth() / 2).reduced(3));
    lfo2Group->setBounds(mainBounds.reduced(3));

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


    Rectangle<int> env1Bounds = env1Group->getBounds();
	enveloppe1->setBounds(env1Bounds);
    Rectangle<int> env2Bounds = env2Group->getBounds();
    enveloppe2->setBounds(env2Bounds);

    GroupComponent* lfoGroups[] = { lfo1Group, lfo2Group };
    for (int l = 0; l < NUMBER_OF_LFO; l++) {
        Rectangle<int> groupBounds = lfoGroups[l]->getBounds();
        // space
        groupBounds.removeFromTop(15);
        Rectangle<int> firstLine = groupBounds.removeFromTop(groupBounds.getHeight() / 3);;
        Rectangle<int> labels = firstLine.removeFromTop(18);

        lfoShapeLabel[l]->setBounds(labels.removeFromLeft(labels.getWidth() / 2));
        lfoModeLabel[l]->setBounds(labels);

        lfoShape[l]->setBounds(firstLine.removeFromLeft(firstLine.getWidth() / 2).reduced(10, firstLine.getHeight() / 2 - 10));
        lfoMode[l]->setBounds(firstLine.reduced(10, firstLine.getHeight() / 2 - 10));

        //  lfoRate[l]->setBounds(firstLine.removeFromLeft(firstLine.getWidth() / 2));

        labels = groupBounds.removeFromTop(18);
        lfoAttackLabel[l]->setBounds(labels.removeFromLeft(labels.getWidth() / 2));
        lfoRateLabel[l]->setBounds(labels);

        Rectangle<int> attackBounds = groupBounds.removeFromLeft(groupBounds.getWidth() / 2);
        attackBounds.reduced(3);
        attackBounds.setX(attackBounds.getX() + 10);
        lfoAttack[l]->setBounds(attackBounds.reduced(10));
        lfoRate[l]->setBounds(groupBounds.reduced(10, 0));
    }

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void PanelModulation::buttonClicked(Button* buttonThatWasClicked) {


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
    for (int l = 0; l < NUMBER_OF_LFO; l++) {
        updateComboFromParameter(lfoShape[l]);
        updateSliderFromParameter(lfoAttack[l]);
        updateComboFromParameter(lfoMode[l]);
        updateComboAndSliderFromParameter(lfoRate[l]);
    }


    for (int k = 0; k < NUMBER_OF_MATRIX_ROW; k++) {
		updateComboFromParameter(matrixSource[k]);
		updateSliderFromParameter(matrixMultipler[k]);
		updateComboFromParameter(matrixDestination[k]);
	}

    // Initialize paramMap for enveloppe
    const char** pointName = enveloppe1->getPointSuffix();
    for (int p = 1; p < enveloppe1->getNumberOfPoints(); p++) {
        checkParamExistence("Env1" + String(pointName[p - 1]));
        checkParamExistence("Env2" + String(pointName[p - 1]));
    }

	// Let listen to enveloppe
	enveloppe1->addListener((EnveloppeListener*)this);
	enveloppe2->addListener((EnveloppeListener*)this);

    for (int r = 0; r < NUMBER_OF_MATRIX_ROW; r++) {
        checkParamExistence(matrixMultipler[r]->getName());
        checkParamExistence(matrixDestination[r]->getName());
        checkParamExistence(matrixSource[r]->getName());
    }
    for (int r = 0; r < NUMBER_OF_OPERATORS; r++) {
        updateComboFromParameter(operatorSource1[r]);
        updateComboFromParameter(operatorSource2[r]);
        updateComboFromParameter(operatorOut[r]);
    }
}


void PanelModulation::updateUIEnveloppe(String paramName) {
	const char** pointName = enveloppe1->getPointSuffix();
    Enveloppe* enveloppe;
    if (paramName.startsWith("Env1")) {
        enveloppe = enveloppe1;
    }
    else if (paramName.startsWith("Env2")) {
        enveloppe = enveloppe2;
    }
    else {
        return;
    }

    String pString = enveloppe->getName();
    for (int p = 1; p < enveloppe->getNumberOfPoints(); p++) {
		String name = pString + String(pointName[p - 1]);

		MidifiedFloatParameter* param = checkParamExistence(name);

		if (paramName.length() > 0 && (param == nullptr || name != String(paramName))) {
			continue;
		}

		// And let's update the value and update the UI Without sending modification !!!
		// No modification : we dont want sliderValueChanged to be called in the different panels

		if (p == 3) {
			if (param->getValue() != enveloppe->getY(p)) {
				enveloppe->setY(p, param->getRealValue());
				enveloppe->repaint();
			}
		}
		else {
			if (param->getValue() != enveloppe->getX(p)) {
				enveloppe->setX(p, param->getRealValue());
				enveloppe->repaint();
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
	return name.startsWith("Env");
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
  <GROUPCOMPONENT name="lfo1Group" id="178ff1e4b1af9a2f" memberName="lfo1Group"
                  virtualName="" explicitFocusOrder="0" pos="0.48% 0.871% 25.771% 23.529%"
                  title="Lfo 1"/>
  <GROUPCOMPONENT name="env1Group" id="3420ca195fbbe4e6" memberName="env1Group"
                  virtualName="" explicitFocusOrder="0" pos="0.48% 24.401% 54.215% 25.272%"
                  title="Env 1"/>
  <GROUPCOMPONENT name="matrixGroup" id="e0162bb0e79330d7" memberName="matrixGroup"
                  virtualName="" explicitFocusOrder="0" pos="55.929% 0 42.769% 0M"
                  title="Modulation"/>
  <GROUPCOMPONENT name="env2Group" id="cf2ae727450c0ea4" memberName="env2Group"
                  virtualName="" explicitFocusOrder="0" pos="0.48% 49.673% 54.215% 25.272%"
                  title="Env 2"/>
  <GROUPCOMPONENT name="operatorsGroup" id="47b2f0c9ab2af6e8" memberName="operatorsGroup"
                  virtualName="" explicitFocusOrder="0" pos="0.48% 74.946% 54.215% 23.529%"
                  title="Operators"/>
  <GROUPCOMPONENT name="lfo2Group" id="e478119d0c82c79f" memberName="lfo2Group"
                  virtualName="" explicitFocusOrder="0" pos="28.444% 0.871% 25.771% 23.529%"
                  title="Lfo 2"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
