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
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SequencerScore  : public Component
{
public:
    //==============================================================================
    SequencerScore (String componentName);
    ~SequencerScore();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setNotes(int* newNotes);
    void setEvents(int* newEvents);
    int getNote(int s);
    void setStepMax(int sm);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) override;

    class JUCE_API  Listener
    {
    public:
        //==============================================================================
        /** Destructor. */
        virtual ~Listener() {}
        virtual void noteChanged(SequencerScore* sequencer, int step, int newNote) = 0;
    };
    typedef std::vector<Listener *> SequencerScoreListenerList;
    void addListener(Listener* listener);
    void removeListener(Listener* listener);
    void notifyListeners(int step, int newNote);

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    int notes[16];
    int events[16];
    int stepMax;
    SequencerScoreListenerList listeners;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequencerScore)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
