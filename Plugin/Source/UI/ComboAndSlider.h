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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    Component that share the midi value between a combo and a slider
                                                                    //[/Comments]
*/
class ComboAndSlider  : public Component,
                        public ComboBox::Listener,
                        public Slider::Listener
{
public:
    //==============================================================================
    ComboAndSlider (String name);
    ~ComboAndSlider();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setComboParams(const char* labels[], int comboFirstNrpmParam = 1);
    void setSliderParams(float min, float max, float bias);
    void setValue(int v);
    int getValue();
    void sliderValueChanged(Slider *slider) override;
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;
    class JUCE_API  Listener
    {
    public:
        //==============================================================================
        /** Destructor. */
        virtual ~Listener() {}
        virtual void comboOrSliderValueChanged(ComboAndSlider* comboAndSlider) = 0;
    };
    typedef std::vector<Listener *> ComboAndSliderListenerList;
    void addListener(Listener* listener);
    void removeListener(Listener* listener);
    void notifyListeners();

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ScopedPointer<ComboBox> myCombo;
    ScopedPointer<Slider> mySlider;
    int value;
    ComboAndSliderListenerList listeners;
    int comboLastNrpmParam;
    int comboFirstNrpmParam;
    float sliderBias;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComboAndSlider)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
