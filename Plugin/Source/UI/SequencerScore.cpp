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
//[/Headers]

#include "SequencerScore.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SequencerScore::SequencerScore (String componentName)
    : Component(componentName)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    for (int s = 0; s < 16; s++) {
        notes[s] = (s * 2) % 12;
        events[s] = 1;
    }
    stepMax = 16;
    //[/Constructor]
}

SequencerScore::~SequencerScore()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SequencerScore::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0x50000000));

    //[UserPaint] Add your own custom painting code here..

    if (!isEnabled()) {
        return;
    }
    int noteType[] = { 1, 2 ,1, 2, 1, 1 , 2, 1, 2, 1, 2, 1 };
    String noteStrings[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A" , "A#", "B" };
    Colour whiteTrans = Colour::fromRGBA(255, 255, 255, 50);

    Rectangle<int> scoreBounds = getLocalBounds();
    Rectangle<int>toHide = getLocalBounds();

    int maxY = toHide.getWidth() * (17 - (stepMax + 1)) / 17;

    g.setColour(whiteTrans);
    for (int n = 0; n < 12; n++) {
        Rectangle<int> oneNoteRect = scoreBounds.removeFromBottom(scoreBounds.getHeight() / (12 - n));
        if (noteType[n] == 1) {
            g.setColour(whiteTrans);
            Rectangle<int> withMaxY = oneNoteRect;
            withMaxY.removeFromRight(maxY).reduced(0, 1);
            g.fillRect(withMaxY);
        }
        g.setColour(Colours::whitesmoke);
        Rectangle<int> noteLabel = oneNoteRect.removeFromLeft(oneNoteRect.getWidth() / 17);
        g.drawFittedText(noteStrings[n], noteLabel, Justification::centred, 1);
    }

    // Draw Notes
    scoreBounds = getLocalBounds();
    scoreBounds.removeFromLeft(scoreBounds.getWidth() / 17);
    float stepWidth = (float)scoreBounds.getWidth() / 16;
    float noteHeight = (float)scoreBounds.getHeight() / 12.0f;
    for (int s = 0; s < stepMax; s++) {
        switch (events[s]) {
        case 1: {
            g.setColour(Colours::whitesmoke);
            Rectangle<float> noteRect((float)stepWidth * (s + 1), (float)(scoreBounds.getY() + (11 - notes[s]) * noteHeight), stepWidth, noteHeight);
            g.drawRoundedRectangle(noteRect.reduced(5, 2), 8, 3);
            break;
        }
        case 2: {
            g.setColour(Colours::whitesmoke);
            Rectangle<float> noteRect((float)stepWidth * (s + 1), (float)(scoreBounds.getY() + (11 - notes[s]) * noteHeight), stepWidth, noteHeight);
            Point<float> startPoint;
            Point<float> endPoint;
            float lineShiftX = noteRect.getWidth() / 4;
            float lineShiftY = noteRect.getHeight() / 4;
            if (s == 0 || notes[s - 1] == notes[s]) {
                startPoint = noteRect.getCentre();
                startPoint.addXY(-lineShiftX, 0);
                endPoint = noteRect.getCentre();
                endPoint.addXY(lineShiftX, 0);
            }
            else if (notes[s - 1] > notes[s]) {
                startPoint = noteRect.getCentre();
                startPoint.addXY(-lineShiftX, -lineShiftY);
                endPoint = noteRect.getCentre();
                endPoint.addXY(lineShiftX, lineShiftY);
            }
            else {
                startPoint = noteRect.getCentre();
                startPoint.addXY(-lineShiftX, lineShiftY);
                endPoint = noteRect.getCentre();
                endPoint.addXY(lineShiftX, -lineShiftY);
            }
            g.drawLine(startPoint.getX(), startPoint.getY(), endPoint.getX(), endPoint.getY(), 3);
            break;
        }
        case 3: {
            g.setColour(Colours::grey);
            Rectangle<float> noteRect((float)stepWidth * (s + 1), (float)(scoreBounds.getY() + (11 - notes[s]) * noteHeight), stepWidth, noteHeight);
            g.drawRoundedRectangle(noteRect.reduced(9, 4), 8, 3);
            break;
        }
        }
    }


    //[/UserPaint]
}

void SequencerScore::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SequencerScore::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    int stepSize = getWidth() / 17;
    int noteSize = getHeight() / 12;
    int step = (e.getPosition().getX() - getX()) / stepSize - 1;
    int note = 11 - e.getPosition().getY() / noteSize;
    DBG("In score area !!! step " << step << " note " << note);
    DBG(" mouse Y " << e.getPosition().getY() );
    if (note < 0 || note > 11 || step < 0 || step > (stepMax -1)) {
        return;
    }
    if (note != notes[step]) {
        DBG("NEW NOTE !");
        notes[step] = note;
        repaint();
    }

    //[/UserCode_mouseDown]
}

void SequencerScore::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    mouseDown(e);
    //[/UserCode_mouseDrag]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SequencerScore::setNotes(int* newNotes) {
    for (int s = 0; s < 16; s++) {
        notes[s] = newNotes[s];
    }
}

void SequencerScore::setEvents(int* newEvents) {
    for (int s = 0; s < 16; s++) {
        DBG("NEW EVENT : " << s << " value : " << newEvents[s]);
        if (newEvents[s] >= 1 && newEvents[s] <= 3) {
            events[s] = newEvents[s];
        }
    }
    repaint();
}

int SequencerScore::getNote(int s) {
    return notes[s];
}

void SequencerScore::setStepMax(int sm) {
    stepMax = sm;
    repaint();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SequencerScore" componentName=""
                 parentClasses="public Component" constructorParams="String componentName"
                 variableInitialisers="Component(componentName)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="600" initialHeight="400">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="50000000"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
