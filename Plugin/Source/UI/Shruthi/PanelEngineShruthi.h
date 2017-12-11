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
#include "../MISettingsListener.h"

#define NUMBER_OF_VOICES 3
#define NUMBER_SUPPORTED_FILTERS 4

#define FILTER_SMR4 0
#define FILTER_SVF 1
#define FILTER_4PM 2
#define FILTER_POLIVOKS 3

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
                     public PanelOfComponents,
                     public FilterTypeUI
{
public:
    //==============================================================================
    PanelEngine ();
    ~PanelEngine();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void buttonClicked(Button* buttonThatWasClicked)override;

	void sliderDragStarted(Slider* slider)	override;
	void sliderDragEnded(Slider* slider) override;
	void sliderValueChanged(Slider* sliderThatWasMoved) override;
	void sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI);
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged, bool fromPluginUI);
	// Panel of parameters
	void buildParameters() override;;
	void updateSliderFromParameter_hook(Slider* slider) override;
	void updateUIEnveloppe(String paramName) override;;
	bool containsThisParameterAsEnveloppe(String name) override;;
    void setSettingsListener(MISettingsListener* misl) { settingsListener = misl; }
    void setFitlerType(int ft);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MISettingsListener* settingsListener;


	ScopedPointer<Label> osc1ShapeLabel;
	ScopedPointer<ComboBox> osc1Shape;
    ScopedPointer<Label> osc1ParamLabel;
    ScopedPointer<Slider> osc1Param;
    ScopedPointer<Label> osc1RangeLabel;
    ScopedPointer<Slider> osc1Range;
    ScopedPointer<Label> osc1SubClickLabel;
    ScopedPointer<ComboBox> osc1SubClick;

    ScopedPointer<Label> osc2ShapeLabel;
    ScopedPointer<ComboBox> osc2Shape;
    ScopedPointer<Label> osc2ParamLabel;
    ScopedPointer<Slider> osc2Param;
    ScopedPointer<Label> osc2RangeLabel;
    ScopedPointer<Slider> osc2Range;
    ScopedPointer<Label> osc2DetuneLabel;
    ScopedPointer<Slider> osc2Detune;

    ScopedPointer<Label> mixerOpLabel;
    ScopedPointer<ComboBox> mixerOp;
    ScopedPointer<Label> mixerMixLabel;
    ScopedPointer<Slider> mixerMix;
    ScopedPointer<Label> mixerSubLabel;
    ScopedPointer<Slider> mixerSub;
    ScopedPointer<Label> mixerNoiseLabel;
    ScopedPointer<Slider> mixerNoise;


    ScopedPointer<Label> filterCutoffLabel;
    ScopedPointer<Slider> filterCutoff;
    ScopedPointer<Label> filterResonnanceLabel;
    ScopedPointer<Slider> filterResonnance;
    ScopedPointer<Label> filterEnvLabel;
    ScopedPointer<Slider> filterEnv;
    ScopedPointer<Label> filterLfoLabel;
    ScopedPointer<Slider> filterLfo;

    ScopedPointer<Label> filterSVFCutoffLabel;
    ScopedPointer<Slider> filterSVFCutoff;
    ScopedPointer<Label> filterSVFResonnanceLabel;
    ScopedPointer<Slider> filterSVFResonnance;
    ScopedPointer<Label> filterSVFMode1Label;
    ScopedPointer<ComboBox> filterSVFMode1;
    ScopedPointer<Label> filterSVFMode2Label;
    ScopedPointer<ComboBox> filterSVFMode2;

    ScopedPointer<Label> filter4PMModeLabel;
    ScopedPointer<ComboBox> filter4PMMode;
    ScopedPointer<Label> filter4PMFlavorLabel;
    ScopedPointer<ComboBox> filter4PMFlavor;

    ScopedPointer<GroupComponent> filterSVFGroup;
    ScopedPointer<TextButton> tuneLegato;
    ScopedPointer<Label> tunePortamentoLabel;
    ScopedPointer<Slider> tunePortamento;


    ScopedPointer<TextButton> shruthiFilterButtons[NUMBER_SUPPORTED_FILTERS];
    int currentFilterType;


	MidiBuffer* eventsToAdd;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> osc1Group;
    ScopedPointer<GroupComponent> osc2Group;
    ScopedPointer<GroupComponent> mixerGroup;
    ScopedPointer<GroupComponent> filterGroup;
    ScopedPointer<GroupComponent> filterTypeGroup;
    ScopedPointer<ImageButton> infoButton;
    ScopedPointer<GroupComponent> tuningGroup;
    ScopedPointer<GroupComponent> infoGroup;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelEngine)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
