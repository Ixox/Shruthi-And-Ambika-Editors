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
#include "../../AudioProcessorCommon.h"
#include "../PanelOfComponents.h"
#include "../SliderPfm2.h"
#include "../SequencerScore.h"
#include "../ShruthiSequencer.h"
#include "../sequencer_settings.h"

#define NUMBER_OF_STEPS 16

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PanelSequencer  : public Component,
                        public Button::Listener,
                        public Slider::Listener,
                        public ComboBox::Listener,
                        public PanelOfComponents,
                        public MISequencer,
                        public ComboAndSlider::Listener
{
public:
    //==============================================================================
    PanelSequencer ();
    ~PanelSequencer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void buttonClicked(Button *buttonThatWasClicked) override;
    void sliderValueChanged(Slider* sliderThatWasMoved) override;
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI);
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged, bool fromPluginUI);
    void sliderDragStarted(Slider* slider)	override;
    void sliderDragEnded(Slider* slider) override;
    void buildParameters() override;
    void comboOrSliderValueChanged(ComboAndSlider* slider) override;
    void updateSliderFromParameter_hook(Slider* slider) override;
    void updateComboFromParameter_hook(ComboBox* combo) override;


    // Sysex aware
    void setCanSendSequencerClass(CanSendSequencerClass* css);
    void updateSequencerSteps();

    // ShruthiSequencer
    uint8* getSequencerSteps();
    void setSequencerSteps(uint8 steps[32]);

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
//    ScopedPointer<>
    ScopedPointer<Label> seqAllLabels[9];
    ScopedPointer<ComboBox> seqMode;
    ScopedPointer<ComboBox> seqNumberOfStep;
    ScopedPointer<ComboAndSlider> tempoBpm;
    ScopedPointer<ComboBox> tempoGroove;
    ScopedPointer<Slider> tempoAmount;

    ScopedPointer<ComboBox> seqDirection;
    ScopedPointer<Slider> seqRange;
    ScopedPointer<ComboBox> seqPattern;
    ScopedPointer<ComboBox> seqDivision;


    ScopedPointer<Label> seqLabels[5];
    ScopedPointer<Label> seqStepLabel[NUMBER_OF_STEPS];
    ScopedPointer<ComboBox> seqNoteOctave[NUMBER_OF_STEPS];
    ScopedPointer<RotatingComboBox> seqRhythmic[NUMBER_OF_STEPS];
    ScopedPointer<Slider> seqVelocity[NUMBER_OF_STEPS];
    ScopedPointer<Slider> seq1Steps[NUMBER_OF_STEPS];
    ScopedPointer<SequencerScore> seqScore;
    ScopedPointer<TextButton> seqPushButton;
    ScopedPointer<TextButton> seqPullButton;
    ScopedPointer<TextButton> seqRandomizeButton;
    int stepControl[NUMBER_OF_STEPS];
    CanSendSequencerClass* canSendSequencer;
    struct shruthi::SequencerSettings sequencerSettings;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> tempoGroup;
    ScopedPointer<GroupComponent> arpGroup;
    ScopedPointer<GroupComponent> seqGroup;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelSequencer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
