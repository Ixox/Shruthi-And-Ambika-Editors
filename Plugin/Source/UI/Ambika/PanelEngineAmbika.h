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

#define NUMBER_OF_VOICES 3

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
	An auto-generated component, created by the Introjucer.

	Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PanelEngine  : public Component,
                     public Slider::Listener,
                     public Button::Listener,
                     public ComboBox::Listener,
                     public PanelOfComponents
{
public:
    //==============================================================================
    PanelEngine ();
    ~PanelEngine();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void buttonClicked(Button* buttonThatWasClicked, bool fromPluginUI);
    void buttonClicked(Button* buttonThatWasClicked) override;

	void sliderDragStarted(Slider* slider)	override;
	void sliderDragEnded(Slider* slider) override;
	void sliderValueChanged(Slider* sliderThatWasMoved) override;
	void sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI);
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged, bool fromPluginUI);
	// Panel of parameters
	void buildParameters() override;;
	void updateSliderFromParameter_hook(Slider* slider) override;
    void updateButtonFromParameter_hook(Button* button) override;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.


	ScopedPointer<Label> osc1ShapeLabel;
	ScopedPointer<ComboBox> osc1Shape;
    ScopedPointer<Label> osc1ParamLabel;
    ScopedPointer<Slider> osc1Param;
    ScopedPointer<Label> osc1RangeLabel;
    ScopedPointer<Slider> osc1Range;
    ScopedPointer<Label> osc1DetuneLabel;
    ScopedPointer<Slider> osc1Detune;

    ScopedPointer<Label> osc2ShapeLabel;
    ScopedPointer<ComboBox> osc2Shape;
    ScopedPointer<Label> osc2ParamLabel;
    ScopedPointer<Slider> osc2Param;
    ScopedPointer<Label> osc2RangeLabel;
    ScopedPointer<Slider> osc2Range;
    ScopedPointer<Label> osc2DetuneLabel;
    ScopedPointer<Slider> osc2Detune;


    ScopedPointer<Label> mixLabels[8];
    ScopedPointer<Slider> mixBalance;
    ScopedPointer<ComboBox> mixOp;
    ScopedPointer<Slider> mixParameter;
    ScopedPointer<ComboBox> mixSubOscShape;
    ScopedPointer<Slider> mixSubOsc;
    ScopedPointer<Slider> mixNoise;
    ScopedPointer<Slider> mixFuzz;
    ScopedPointer<Slider> mixCrush;

    ScopedPointer<Label> osc1SubClickLabel;
    ScopedPointer<ComboBox> osc1SubClick;

    ScopedPointer<Label> filterCutoffLabel;
    ScopedPointer<Slider> filterCutoff;
    ScopedPointer<Label> filterResonnanceLabel;
    ScopedPointer<Slider> filterResonnance;
    ScopedPointer<Label> filterEnvLabel;
    ScopedPointer<Slider> filterEnv;
    ScopedPointer<Label> filterLfoLabel;
    ScopedPointer<Slider> filterLfo;
    ScopedPointer<Label> filterModeLabel;
    ScopedPointer<ComboBox> filterMode;

    // Tuning
    ScopedPointer<Label> tuningLabels[8];

    ScopedPointer<Slider> tuningVolume;
    ScopedPointer<Slider> tuningOctave;
    ScopedPointer<Slider> tuningTune;
    ScopedPointer<Slider> tuningSpread;
    ScopedPointer<ComboBox> tuningRaga;
    ScopedPointer<TextButton> tuningLegato;
    ScopedPointer<Slider> tuningPortamento;
    ScopedPointer<ComboBox> tuningPolyphonyMode;



	MidiBuffer* eventsToAdd;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> osc1Group;
    ScopedPointer<GroupComponent> osc2Group;
    ScopedPointer<GroupComponent> mixerGroup;
    ScopedPointer<GroupComponent> filterGroup;
    ScopedPointer<ImageButton> infoButton;
    ScopedPointer<GroupComponent> tuningGroup;
    ScopedPointer<GroupComponent> infoGroup;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelEngine)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
