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

#pragma once

//[Headers]     -- You can add your own extra header files here --

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
#include "../Enveloppe.h"
#include "../PanelOfComponents.h"
#include "../ComboAndSlider.h"

#define NUMBER_OF_STEP_SEQ 2
#define NUMBER_OF_LFO 2

#define NUMBER_OF_MATRIX_ROW 12
#define NUMBER_OF_OPERATORS 2
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
	An auto-generated component, created by the Introjucer.

	Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PanelModulation  : public Component,
                         public Button::Listener,
                         public Slider::Listener,
                         public ComboBox::Listener,
                         public PanelOfComponents,
                         public ComboAndSlider::Listener
{
public:
    //==============================================================================
    PanelModulation ();
    ~PanelModulation();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI);
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged, bool fromPluginUI);
	void updateUIEnveloppe(String paramName);
	void updateUIStepSequencer(String paramName);

    void buildParameters() override;
    void updateSliderFromParameter_hook(Slider* slider) override;
    void updateComboFromParameter_hook(ComboBox* combo) override;
    void buttonClicked(Button* buttonThatWasClicked) override;
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged(Slider* sliderThatWasMoved) override;
    void sliderDragStarted(Slider* slider)	override;
	void sliderDragEnded(Slider* slider) override;
    void comboOrSliderValueChanged(ComboAndSlider* slider) override;
    bool containsThisParameterAsEnveloppe(String name) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

	// LFO
    ScopedPointer<Label> lfoShapeLabel[NUMBER_OF_LFO];
    ScopedPointer<ComboBox> lfoShape[NUMBER_OF_LFO];
    ScopedPointer<Label> lfoRateLabel[NUMBER_OF_LFO];
    ScopedPointer<ComboAndSlider> lfoRate[NUMBER_OF_LFO];
    ScopedPointer<Label> lfoAttackLabel[NUMBER_OF_LFO];
    ScopedPointer<Slider> lfoAttack[NUMBER_OF_LFO];
    ScopedPointer<Label> lfoModeLabel[NUMBER_OF_LFO];
    ScopedPointer<ComboBox> lfoMode[NUMBER_OF_LFO];


	// MATRIX
    ScopedPointer<Label> matrixSourceLabel;
    ScopedPointer<Label> matrixMultiplierLabel;
    ScopedPointer<Label> matrixDestinationLabel;
    ScopedPointer<Label> matrixRowLabel[NUMBER_OF_MATRIX_ROW];
	ScopedPointer<ComboBox> matrixSource[NUMBER_OF_MATRIX_ROW];
	ScopedPointer<Slider> matrixMultipler[NUMBER_OF_MATRIX_ROW];
	ScopedPointer<ComboBox> matrixDestination[NUMBER_OF_MATRIX_ROW];

	// ENVELOPPES
	ScopedPointer<Enveloppe> enveloppe1;
	ScopedPointer<Enveloppe> enveloppe2;


    // OPERATOR
    ScopedPointer<Label> operatorSource1Label;
    ScopedPointer<Label> operatorSource2Label;
    ScopedPointer<Label> operatorOutLabel;
    ScopedPointer<Label> operatorRowLabel[NUMBER_OF_OPERATORS];
    ScopedPointer<ComboBox> operatorSource1[NUMBER_OF_OPERATORS];
    ScopedPointer<ComboBox> operatorSource2[NUMBER_OF_OPERATORS];
    ScopedPointer<ComboBox> operatorOut[NUMBER_OF_OPERATORS];

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> lfo1Group;
    ScopedPointer<GroupComponent> env1Group;
    ScopedPointer<GroupComponent> matrixGroup;
    ScopedPointer<GroupComponent> env2Group;
    ScopedPointer<GroupComponent> operatorsGroup;
    ScopedPointer<GroupComponent> lfo2Group;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelModulation)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
