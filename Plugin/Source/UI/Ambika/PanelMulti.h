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
#include "JuceHeader.h"
#include "../ComboAndSlider.h"
#include "AmbikaMultiData.h"
#include "../MISettingsListener.h"

#define NUMBER_OF_PARTS 6
#define NUMBER_OF_KNOBS 8

struct KnobParam {
    String name;
    int parameter;
    int instance;
    int getComboBoxId() {
        return (parameter << 8) + instance + 1;
    }
    void setComboValue(int v) {
        v = v - 1;
        parameter = v >> 8;
        instance = v & 0xff;
    }
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PanelMulti  : public Component,
                    public Button::Listener,
                    public Slider::Listener,
                    public ComboBox::Listener,
                    public ComboAndSlider::Listener,
                    public AmbikaMultiDataUI
{
public:
    //==============================================================================
    PanelMulti ();
    ~PanelMulti();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void sliderValueChanged(Slider* sliderThatWasMoved) override;
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    void comboOrSliderValueChanged(ComboAndSlider* slider) override;
    void buttonClicked(Button *buttonThatWasClicked) override;

    // Ambika MultiData
    MultiData* getMultiData() override;
    void setMultiData(MultiData *md) override;
    void setSettingsListener(MISettingsListener* misl) { settingsListener = misl; }
    bool isMultiDataUsed() override;
    void setMultiDataUsed(bool mdu) override ;
    void requestMultiDataFromAmbika();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ScopedPointer<Label> seqAllLabels[4];

    // Tempo
    ScopedPointer<ComboAndSlider> tempoBpm;
    ScopedPointer<ComboBox> tempoGroove;
    ScopedPointer<Slider> tempoAmount;
    ScopedPointer<Slider> tempoLatch;

    // Parts
    ScopedPointer<Label> partItemLabel[9];
    ScopedPointer<Label> partLabel[NUMBER_OF_PARTS];
    ScopedPointer<ToggleButton > partVoicesLink[NUMBER_OF_PARTS][NUMBER_OF_PARTS];
    ScopedPointer<ComboBox> partChannelLink[NUMBER_OF_PARTS];
    ScopedPointer<ComboBox> partNoteStart[NUMBER_OF_PARTS];
    ScopedPointer<ComboBox> partNoteEnd[NUMBER_OF_PARTS];

    // Buttons
    ScopedPointer<Label> knobLabel[NUMBER_OF_KNOBS];
    ScopedPointer<ComboBox> knobPart[NUMBER_OF_KNOBS];
    ScopedPointer<ComboBox> knobTarget[NUMBER_OF_KNOBS];

    MISettingsListener* settingsListener;
    MultiData panelMultiData;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> voicesGroup;
    ScopedPointer<GroupComponent> tempoGroup;
    ScopedPointer<GroupComponent> buttonsGroup;
    ScopedPointer<ToggleButton> useMultiButton;
    ScopedPointer<Label> useMultiLabel;
    ScopedPointer<TextButton> pushMultiButton;
    ScopedPointer<TextButton> pullMultiButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelMulti)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
