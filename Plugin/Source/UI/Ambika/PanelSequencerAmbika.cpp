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
//[/Headers]

#include "PanelSequencerAmbika.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "../AudioProcessorCommon.h"

const char* seqAllLabeItems[] = { "Mode" , "Bpm", "Groove", "Amount", "Direction", "Range", "Pattern", "Division", "Length 1/2/3"};

const char* seqModeItems[] = { "Step", "Arpeggiator", "Sequencer", nullptr };
const char* seqDivisionItems[] = {
    "1 / 1", "3 / 4","2 / 3","1 / 2","3 / 8","1 / 3","1 / 4","1 / 6","1 / 8","1 / 12","1 / 16","1 / 24","1 / 32","1 / 48","1 / 96", nullptr };
const char* seqDirectionItems[] = { "Up", "Down", "Up and Down", "Random", "As played", nullptr };
const char* seqPatternItems[] = {
 "o-o- o-o- o-o- o-o-",
 "o-o- oooo o-o- oooo",
 "o-o- oo-o o-o- oo-o",
 "o-o- o-oo o-o- o-oo",
 "o-o- o-o- oo-o -o-o",
 "o-o- o-o- o--o o-o-",
 "o-o- o--o o-o- o--o",

 "o--o ---- o--o ----",
 "o--o --o- -o-- o--o",
 "o--o --o- -o-- o-o-",
 "o--o --o- o--o --o-",
 "o--o o--- o-o- o-oo",

 "oo-o -oo- oo-o -oo-",
 "oo-o o-o- oo-o o-o-",

 "ooo- ooo- ooo- ooo-",
 "ooo- oo-o o-oo -oo-",
 "ooo- o-o- ooo- o-o-",

 "oooo -oo- oooo -oo-",
 "oooo o-oo -oo- ooo-",

 "o--- o--- o--o -o-o",
 "o--- --oo oooo -oo-",
 "o--- ---- o--- o-oo",  nullptr };

const char* seqRhythmicItems[] = { "O", "~", " ", nullptr };

//[/MiscUserDefs]

//==============================================================================
PanelSequencer::PanelSequencer ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (arpGroup = new GroupComponent ("Arpeggiator Group",
                                                      TRANS("Arpeggiator")));

    addAndMakeVisible (seqGroup = new GroupComponent ("Sequencer Group",
                                                      TRANS("Sequencer")));


    //[UserPreSize]


    for (int l = 0; l < 9; l++) {
        addAndMakeVisible(seqAllLabels[l] = new Label("seq" + String(seqAllLabeItems[l]) + " label", seqAllLabeItems[l]));
        seqAllLabels[l]->setJustificationType(Justification::centred);
    }

    //ScopedPointer<ComboBox> seqMode;
    addAndMakeVisible(seqMode = new ComboBox("Seq Mode"));
    seqMode->setEditableText(false);
    seqMode->setJustificationType(Justification::centred);
    seqMode->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; seqModeItems[i] != nullptr; i++) {
        seqMode->addItem(seqModeItems[i], i + 1);
    }
    seqMode->setScrollWheelEnabled(true);
    seqMode->addListener(this);

    // seqNumberOfStep
    for (int s = 0; s < 3; s++) {
        addAndMakeVisible(seqNumberOfStep[s] = new ComboBox("Seq Length"+ String(s+1)));
        seqNumberOfStep[s]->setEditableText(false);
        seqNumberOfStep[s]->setJustificationType(Justification::centred);
        seqNumberOfStep[s]->setColour(ComboBox::buttonColourId, Colours::blue);
        for (int i = 16; i >= 1; i--) {
            seqNumberOfStep[s]->addItem(String(i), i + 1);
        }
        seqNumberOfStep[s]->setTextWhenNoChoicesAvailable("--");
        seqNumberOfStep[s]->setScrollWheelEnabled(true);
        seqNumberOfStep[s]->addListener(this);
    }


    //ScopedPointer<ComboBox> seqDirection;
    addAndMakeVisible(seqDirection = new ComboBox("Seq Direction"));
    seqDirection->setEditableText(false);
    seqDirection->setJustificationType(Justification::centred);
    seqDirection->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; seqDirectionItems[i] != nullptr; i++) {
        seqDirection->addItem(seqDirectionItems[i], i + 1);
    }
    seqDirection->setSelectedId(1);
    seqDirection->setScrollWheelEnabled(true);
    seqDirection->addListener(this);

    //ScopedPointer<Slider> seqRange;
    addAndMakeVisible(seqRange = new SliderPfm2("Seq Range"));
    seqRange->setRange(1, 4, 1);
    seqRange->setSliderStyle(Slider::RotaryVerticalDrag);
    seqRange->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    seqRange->setDoubleClickReturnValue(true, 0.0f);
    seqRange->addListener(this);


    //ScopedPointer<ComboBox> seqPattern;
    addAndMakeVisible(seqPattern = new ComboBox("Seq Pattern"));
    seqPattern->setEditableText(false);
    seqPattern->setJustificationType(Justification::centred);
    seqPattern->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; seqPatternItems[i] != nullptr; i++) {
        seqPattern->addItem(seqPatternItems[i], i + 1);
    }
    seqPattern->setSelectedId(1);
    seqPattern->setScrollWheelEnabled(true);
    seqPattern->addListener(this);



    //ScopedPointer<ComboBox> seqDivision;
    addAndMakeVisible(seqDivision = new ComboBox("Seq Division"));
    seqDivision->setEditableText(false);
    seqDivision->setJustificationType(Justification::centred);
    seqDivision->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; seqDivisionItems[i] != nullptr; i++) {
        seqDivision->addItem(seqDivisionItems[i], i + 1);
    }
    seqDivision->setSelectedId(1);
    seqDivision->setScrollWheelEnabled(true);
    seqDivision->addListener(this);

    addAndMakeVisible(seqPullButton = new TextButton("pull button"));
    seqPullButton->setTooltip("Pull all Sequencer parameters from plugin to Ambika");
    seqPullButton->setButtonText("PULL from Ambika");
    seqPullButton->addListener(this);

    addAndMakeVisible(seqRandomizeButton = new TextButton("Randomize Sequencer"));
    seqRandomizeButton->setButtonText("Seq Randomizer");
    seqRandomizeButton->addListener(this);


    for (int s = 0; s < NUMBER_OF_STEPS; s++) {
        String namePreffix = "SeqStep" + String(s + 1);

        //ScopedPointer<Label> seqLabel[NUMBER_OF_STEPS];
        addAndMakeVisible(seqStepLabel[s] = new Label(namePreffix + " step label", String(s)));
        if ((s % 4) == 0) {
            seqStepLabel[s]->setColour(Label::textColourId, Colours::whitesmoke);
        }
        else {
            seqStepLabel[s]->setColour(Label::textColourId, Colours::grey);
        }
        seqStepLabel[s]->setJustificationType(Justification::centred);

        //ScopedPointer<Slider> seqNote[NUMBER_OF_STEPS];
        addAndMakeVisible(seqNoteOctave[s] = new ComboBox(namePreffix + " Octave"));
        seqNoteOctave[s]->setEditableText(false);
        seqNoteOctave[s]->setJustificationType(Justification::centred);
        for (int i = 1; i <= 6; i++) {
            seqNoteOctave[s]->addItem(String(i), i);
        }
        seqNoteOctave[s]->setSelectedId(3);
        seqNoteOctave[s]->setScrollWheelEnabled(true);
        seqNoteOctave[s]->addListener(this);

        //ScopedPointer<Slider> seqVelocity[NUMBER_OF_STEPS];
        addAndMakeVisible(seqVelocity[s] = new SliderPfm2(namePreffix + " velocity"));
        seqVelocity[s]->setRange(0.0f, 127.0f, 1.00f);
        seqVelocity[s]->setSliderStyle(Slider::LinearVertical);
        seqVelocity[s]->setTextBoxStyle(Slider::TextBoxBelow, true, 35, 16);
        seqVelocity[s]->setTextBoxIsEditable(false);
        seqVelocity[s]->setDoubleClickReturnValue(true, 100.0);
        seqVelocity[s]->addListener(this);

        //ScopedPointer<Slider> seqRhythmic[NUMBER_OF_STEPS];
        addAndMakeVisible(seqRhythmic[s] = new RotatingComboBox(namePreffix + "Rhythmic"));
        seqRhythmic[s]->setEditableText(false);
        seqRhythmic[s]->setJustificationType(Justification::centred);
        for (int i = 0; seqRhythmicItems[i] != nullptr; i++) {
            seqRhythmic[s]->addItem(String(CharPointer_UTF8(seqRhythmicItems[i])), i + 1);
        }
        seqRhythmic[s]->setFirstLast(1, 3);
        seqRhythmic[s]->setSelectedId(1);
        seqRhythmic[s]->setScrollWheelEnabled(true);
        seqRhythmic[s]->addListener(this);


        //newParam = new MidifiedFloatParameter("Seq1 Step" + String(s + 1), nrpmParam, 1, 0, 255, 128);
        //newParam = new MidifiedFloatParameter("Seq2 Step" + String(s + 1), nrpmParam, 1, 0, 255, 128);

        addAndMakeVisible(seq1Steps[s] = new SliderPfm2("Seq1 Step" + String(s + 1)));
        seq1Steps[s]->setRange(0.0f, 255.0f, 1.00f);
        seq1Steps[s]->setSliderStyle(Slider::LinearVertical);
        seq1Steps[s]->setTextBoxStyle(Slider::TextBoxBelow, true, 35, 16);
        seq1Steps[s]->setTextBoxIsEditable(false);
        seq1Steps[s]->setDoubleClickReturnValue(true, 128.0f);
        seq1Steps[s]->setValue(0.0f, dontSendNotification);
        seq1Steps[s]->addListener(this);

        addAndMakeVisible(seq2Steps[s] = new SliderPfm2("Seq2 Step" + String(s + 1)));
        seq2Steps[s]->setRange(0.0f, 255.0f, 1.00f);
        seq2Steps[s]->setSliderStyle(Slider::LinearVertical);
        seq2Steps[s]->setTextBoxStyle(Slider::TextBoxBelow, true, 35, 16);
        seq2Steps[s]->setTextBoxIsEditable(false);
        seq2Steps[s]->setDoubleClickReturnValue(true, 128.0f);
        seq2Steps[s]->setValue(0.0f, dontSendNotification);
        seq2Steps[s]->addListener(this);

    }
    addAndMakeVisible(seqScore = new SequencerScore("seqScore"));
    seqScore->addListener(this);

    //[/UserPreSize]

    setSize (1000, 710);


    //[Constructor] You can add your own custom stuff here..
    canSendSequencer= nullptr;
    for (int s = 0; s < NUMBER_OF_STEPS; s++) {
        int note = s * 2 + 36;
        seqNoteOctave[s]->setSelectedId((int)(note / 12) - 2);
        sequencer.seqNotes[s].data1  = 0x80 + 38 + s * 2;
        sequencer.seqNotes[s].data2 = s * 10 + 50;
    }

    //[/Constructor]
}

PanelSequencer::~PanelSequencer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    updateSequencerSteps();
    canSendSequencer->sendSequencerToSynth((uint8*)&sequencer);
    //[/Destructor_pre]

    arpGroup = nullptr;
    seqGroup = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PanelSequencer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    Rectangle<int> seqBounds = seqGroup->getBounds();
    // Top Space:10 + topArea: 30
    seqBounds.removeFromTop(40);
    seqBounds.removeFromBottom(10);
    seqBounds.reduce(10, 5);

    Rectangle<int> notesBounds = seqBounds;
    // Label
    int labelSize = notesBounds.getWidth() / 17;
    if (seqGroup->isEnabled()) {
        g.setColour(Colours::whitesmoke);
    }
    else {
        g.setColour(Colours::grey);
    }
    g.drawFittedText("Step#", notesBounds.removeFromTop(20).removeFromLeft(labelSize), Justification::centredTop, 1);
    //space
    notesBounds.removeFromTop(10);
    // Step
    g.drawFittedText("Event", notesBounds.removeFromTop(20).removeFromLeft(labelSize), Justification::centredTop, 1);
    // Space
    notesBounds.removeFromTop(10);
    // Octave
    g.drawFittedText("Octave", notesBounds.removeFromTop(20).removeFromLeft(labelSize), Justification::centredTop, 1);
    // Space
    notesBounds.removeFromTop(10);
    notesBounds.removeFromTop(notesBounds.getHeight() * .4f);
    g.drawFittedText("Velocity", notesBounds.removeFromTop(notesBounds.getHeight() / 4).removeFromLeft(labelSize), Justification::centred, 1);
    g.drawFittedText("Seq1", notesBounds.removeFromTop(notesBounds.getHeight() / 2).removeFromLeft(labelSize) , Justification::centred, 1);
    g.drawFittedText("Seq2", notesBounds.removeFromLeft(labelSize), Justification::centred, 1);


    // Draw Lines
    g.setColour(Colours::whitesmoke);
    seqBounds.removeFromLeft(seqBounds.getWidth() / 17);
    g.drawRoundedRectangle(seqBounds.getX(), seqBounds.getY(), seqBounds.getWidth(), seqBounds.getHeight(), 5, 1);

    int lineX[NUMBER_OF_STEPS + 1];
    lineX[0] = seqBounds.getX();
    lineX[NUMBER_OF_STEPS] = seqBounds.getX() + seqBounds.getWidth();
    for (int s = 1; s < NUMBER_OF_STEPS; s++) {
        if ((s % 4) == 0) {
            g.setColour(Colours::whitesmoke);
        }
        else {
            g.setColour(Colours::grey);
        }
        int posX = seqBounds.getX() + s * seqBounds.getWidth() / (NUMBER_OF_STEPS);
        lineX[s] = posX;
        g.drawVerticalLine(posX, seqBounds.getY(), seqBounds.getY() + seqBounds.getHeight());
    }



    //[/UserPaint]
}

void PanelSequencer::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    if (false) {
    //[/UserPreResize]

    arpGroup->setBounds (480, 24, 240, 160);
    seqGroup->setBounds (312, 296, 896, 488);
    //[UserResized] Add your own custom resize handling here..
    }

    Rectangle<int> totalBounds = getLocalBounds();
    Rectangle<int> topBounds = totalBounds.removeFromTop(totalBounds.getHeight() / 5);

    int topBoundsSpace = topBounds.getWidth() / 8;
    topBounds.removeFromRight(topBoundsSpace);
    topBounds.removeFromLeft(topBoundsSpace / 2);

    // Mode
    Rectangle<int> seqModeBounds = topBounds.removeFromLeft(topBounds.getWidth() / 4);

    seqModeBounds.removeFromTop(10);

    seqAllLabels[0]->setBounds(seqModeBounds.removeFromTop(20));
    seqMode->setBounds(seqModeBounds.reduced(10, seqModeBounds.getHeight() / 2 - 12));

    // Space between mode and arp
    topBounds.removeFromLeft(topBoundsSpace / 2);

    // Arpeggiator group
    arpGroup->setBounds(topBounds);
    topBounds.removeFromTop(15);
    topBounds.reduce(10, 0);

    Rectangle<int> labelsBounds = topBounds.removeFromTop(20);
    for (int l = 0; l < 4; l++) {
        seqAllLabels[l + 4]->setBounds(labelsBounds.removeFromLeft(labelsBounds.getWidth() / (4 - l)));

    }
    int numberOfItems = 4;
    int reducedHeightForCombo = topBounds.getHeight() / 2 - 10;
    seqDirection->setBounds(topBounds.removeFromLeft(topBounds.getWidth() / (numberOfItems--)).reduced(10, reducedHeightForCombo));
    seqRange->setBounds(topBounds.removeFromLeft(topBounds.getWidth() / (numberOfItems --)).reduced(10, 10));
    seqPattern->setBounds(topBounds.removeFromLeft(topBounds.getWidth() / (numberOfItems--)).reduced(10, reducedHeightForCombo));
    seqDivision->setBounds(topBounds.removeFromLeft(topBounds.getWidth() / (numberOfItems --)).reduced(10, reducedHeightForCombo));


    // Sequencer Group
    seqGroup->setBounds(totalBounds);
    totalBounds.reduce(10, 5);
    totalBounds.removeFromTop(10);

    // Add bottom space
    totalBounds.removeFromBottom(10);


    // Top area (number of step and randomizer;
    Rectangle<int> scoreTopArea = totalBounds.removeFromTop(30);
    seqRandomizeButton->setBounds(scoreTopArea.removeFromRight(120).reduced(10, 5));

    scoreTopArea.removeFromLeft(scoreTopArea.getWidth() / 17);
    seqPullButton->setBounds(scoreTopArea.removeFromLeft(120).reduced(10, 5));
    Rectangle<int> numberOfStepLabelBounds = scoreTopArea.removeFromLeft(scoreTopArea.getWidth() / 2);
    seqAllLabels[8]->setBounds(numberOfStepLabelBounds.removeFromRight(100).reduced(0, 5));

    for (int s = 0; s < 3; s++) {
        seqNumberOfStep[s]->setBounds(scoreTopArea.removeFromLeft(60).reduced(5, 5));
    }


    // Save score Area
    // We store scoreArea
    Rectangle<int> scoreArea = totalBounds;
    scoreArea.removeFromTop(90);
    seqScore->setBounds(scoreArea.removeFromTop(scoreArea.getHeight() * .4f));

    Rectangle<int> seqBounds = totalBounds;

    // Label bounds
    Rectangle<int> lablelsBounds = seqBounds.removeFromLeft(seqBounds.getWidth() / 17);

    for (int s = 0; s < 16; s++) {
        int step = s; // +p * 8;
        Rectangle<int> stepBounds = seqBounds.removeFromLeft(seqBounds.getWidth() / (16 - s));
        seqStepLabel[step]->setBounds(stepBounds.removeFromTop(20));
        stepBounds.removeFromTop(10);
        seqRhythmic[step]->setBounds(stepBounds.removeFromTop(20).reduced(5, 0));
        stepBounds.removeFromTop(10);
        seqNoteOctave[step]->setBounds(stepBounds.removeFromTop(20).reduced(5, 0));
        stepBounds.removeFromTop(10);
        stepBounds.removeFromTop(stepBounds.getHeight() * .4f );
        seqVelocity[step]->setBounds(stepBounds.removeFromTop(stepBounds.getHeight() / 4).reduced(0, 3));
        seq1Steps[step]->setBounds(stepBounds.removeFromTop(stepBounds.getHeight() / 2 ).reduced(0, 3));
        seq2Steps[step]->setBounds(stepBounds.removeFromTop(stepBounds.getHeight()).reduced(0, 3));
    }

//    }

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...



void PanelSequencer::buttonClicked(Button *buttonThatWasClicked) {
    if (buttonThatWasClicked == seqPullButton) {
        canSendSequencer->requestSequencerTransfer();
    }
    else if (buttonThatWasClicked == seqRandomizeButton) {
        srand(time(NULL));
        int notes[NUMBER_OF_STEPS];
        for (int s = 0; s < NUMBER_OF_STEPS; s++) {
            seqNoteOctave[s]->setSelectedId(3 + rand() % 3);
            seqVelocity[s]->setValue(rand() % 128);
            seqRhythmic[s]->setSelectedId(1 +rand() % 3);
            notes[s] = rand() % 12;
            seq1Steps[s]->setValue(rand() % 256);
            seq2Steps[s]->setValue(rand() % 256);
        }
        seqScore->setNotes(notes);
        repaint();
        updateSequencerSteps();
        if (canSendSequencer != nullptr) {
            canSendSequencer->sendSequencerToSynth((uint8*)&sequencer);
        }
    }
}

void PanelSequencer::sliderDragStarted(Slider* slider) {
    AudioProcessorParameter * param = parameterMap[slider->getName()];
    if (param != nullptr) {
        param->beginChangeGesture();
    }
}
void PanelSequencer::sliderDragEnded(Slider* slider) {
    AudioProcessorParameter * param = parameterMap[slider->getName()];
    if (param != nullptr) {
        param->endChangeGesture();
    }
}

void PanelSequencer::buildParameters() {
    updateComboFromParameter(seqMode);


    updateComboFromParameter(seqDirection);
    updateSliderFromParameter(seqRange);
    updateComboFromParameter(seqPattern);
    updateComboFromParameter(seqDivision);

    for (int s = 0; s < 3; s++) {
        updateComboFromParameter(seqNumberOfStep[s]);
        if (seqNumberOfStep[s]->getSelectedId() < 2 || seqNumberOfStep[s]->getSelectedId() > 17) {
            seqNumberOfStep[s]->setSelectedId(17);
        }
    }

}


// Copy own sequencer value so that PluginProcessor can store it
uint8* PanelSequencer::getSequencerData() {
    updateSequencerSteps();
    return (uint8*)&sequencer;
}

void PanelSequencer::updateSequencerSteps() {
    for (int s = 0; s < 16; s++) {
        sequencer.seqNotes[s].data1 = seqScore->getNote(s) + (seqNoteOctave[s]->getSelectedId() + 1) * 12;
        if (seqRhythmic[s]->getSelectedId() <= 2) {
            sequencer.seqNotes[s].data1 |= 0x80;
        }
        sequencer.seqNotes[s].data2 = (int)seqVelocity[s]->getValue();
        if (seqRhythmic[s]->getSelectedId() == 2) {
            sequencer.seqNotes[s].data2 |= 0x80;
        }
    }
}


void PanelSequencer::setSequencerData(uint8* seqData) {
    DBG("PanelEngine::setSequencerData() !!!!!!!!!!!!!! ");

    uint8* buffer = (uint8*)&sequencer;
    for (int b = 0; b < 64; b++) {
        buffer[b] = seqData[b];
    }

    int newNotes[16];
    int newEvents[16];

    for (int s = 0; s < 16; s++) {
        seq1Steps[s]->setValue(sequencer.seqController1[s], dontSendNotification);
        seq2Steps[s]->setValue(sequencer.seqController2[s], dontSendNotification);
    }
    for (int b = 0; b < 16; b++) {
        // DBG("STEP " << b << " note " << sequencerSettings.steps[b].note() << " gate " << (sequencerSettings.steps[b].gate() ? 1 : 0));
        // seqNoteOctave[b]->setValue(sequencerSettings.steps[b].note());
        // DBG("STEP " << b << " note " << sequencer.seqNotes[b].getNote() << " gate " << (sequencer.seqNotes[b].isGate() ? 1 : 0) << " velocity " << sequencer.seqNotes[b].getVelocity());
        seqVelocity[b]->setValue(sequencer.seqNotes[b].getVelocity());
        seqNoteOctave[b]->setSelectedId(((sequencer.seqNotes[b].getNote()) / 12) - 1);
        if (sequencer.seqNotes[b].isGate()) {
            if (sequencer.seqNotes[b].isLegato()) {
                seqRhythmic[b]->setSelectedId(2);
            }
            else {
                seqRhythmic[b]->setSelectedId(1);
            }
        }
        else {
            seqRhythmic[b]->setSelectedId(3);
        }
        newNotes[b] = sequencer.seqNotes[b].getNote() % 12;
        newEvents[b] = seqRhythmic[b]->getSelectedId();
    }
    seqScore->setNotes(newNotes);
    seqScore->setEvents(newEvents);
    repaint();
}


void PanelSequencer::setCanSendSequencerClass(CanSendSequencerClass* css) {
    canSendSequencer = css;
}

void PanelSequencer::comboOrSliderValueChanged(ComboAndSlider* comboAndSlider) {
    DBG("PanelSequencer comboOrSliderValueChanged : " << comboAndSlider->getValue());
    AudioProcessorParameter * parameterReady = parameterMap[comboAndSlider->getName()];
    if (parameterReady != nullptr) {
        float value = (float)comboAndSlider->getValue();
        ((MidifiedFloatParameter*)parameterReady)->setValueFromUI(value);
    }
}

void PanelSequencer::sliderValueChanged(Slider* sliderThatWasMoved) {
    sliderValueChanged(sliderThatWasMoved, true);
}

void PanelSequencer::sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI)
{
    // Update the value if the change comes from the UI
    if (fromPluginUI) {
        AudioProcessorParameter * parameterReady = parameterMap[sliderThatWasMoved->getName()];
        if (parameterReady != nullptr) {
            float value = (float)sliderThatWasMoved->getValue();
            ((MidifiedFloatParameter*)parameterReady)->setValueFromUI(value);
        }
    }

    for (int s = 0; s < 16; s++) {
        if (sliderThatWasMoved == seqVelocity[s]) {
            int vel = seqVelocity[s]->getValue();
            if (seqRhythmic[s]->getSelectedId() == 2) {
                vel |= 0x80;
            }
            canSendSequencer->setRealTimeUpdate(32 + s * 2 + 1, vel);
            break;
        }
        if (sliderThatWasMoved == seq1Steps[s]) {
            canSendSequencer->setRealTimeUpdate(s, seq1Steps[s]->getValue());
            break;
        }
        if (sliderThatWasMoved == seq2Steps[s]) {
            canSendSequencer->setRealTimeUpdate(s+ 16, seq1Steps[s]->getValue());
            break;
        }
    }

}

void PanelSequencer::comboBoxChanged(ComboBox* comboBoxThatHasChanged) {
    comboBoxChanged(comboBoxThatHasChanged, true);
}

void PanelSequencer::comboBoxChanged(ComboBox* comboBoxThatHasChanged, bool fromPluginUI) {
    // Update the value if the change comes from the UI
    if (fromPluginUI) {
        AudioProcessorParameter * parameterReady = parameterMap[comboBoxThatHasChanged->getName()];
        if (parameterReady != nullptr) {
            float value = (float)comboBoxThatHasChanged->getSelectedId();
            ((MidifiedFloatParameter*)parameterReady)->setValueFromUI(value - 1.0f);
        }
        bool mustRedrawSequencer = false;
        int newEvents[16];

        for (int s = 0; s < 16; s++) {
            if (comboBoxThatHasChanged == seqRhythmic[s]) {
                mustRedrawSequencer = true;
                newEvents[s] = seqRhythmic[s]->getSelectedId();
                uint8 data1 = seqScore->getNote(s) + (seqNoteOctave[s]->getSelectedId() + 1) * 12;
                if (seqRhythmic[s]->getSelectedId() <= 2) {
                    data1 |= 0x80;
                }
                uint8 data2 = (int)seqVelocity[s]->getValue();
                if (seqRhythmic[s]->getSelectedId() == 2) {
                    data2 |= 0x80;
                }

                canSendSequencer->setRealTimeUpdate(32 + s * 2, data1);
                canSendSequencer->setRealTimeUpdate(32 + s * 2 + 1, data2);
                break;
            }
            if (comboBoxThatHasChanged == seqNoteOctave[s]) {
                uint8 data1 = seqScore->getNote(s) + (seqNoteOctave[s]->getSelectedId() + 1) * 12;
                if (seqRhythmic[s]->getSelectedId() <= 2) {
                    data1 |= 0x80;
                }
                canSendSequencer->setRealTimeUpdate(32 + s * 2, data1);
            }
        }
        if (mustRedrawSequencer) {
            seqScore->setEvents(newEvents);
            seqScore->repaint();
        }
    }


    if (comboBoxThatHasChanged == seqNumberOfStep[0]) {
        int stepMax = seqNumberOfStep[0]->getSelectedId() - 1;
        if (stepMax == -1) {
            stepMax = 16;
            seqNumberOfStep[0]->setSelectedId(17);
        }
        if (stepMax >= 1 && stepMax <= 16) {
            for (int s = 1; s <= stepMax; s++) {
                seqNoteOctave[s - 1]->setEnabled(true);
                seqRhythmic[s - 1]->setEnabled(true);
                seqVelocity[s - 1]->setEnabled(true);
            }
            if (stepMax < 16) {
                for (int s = stepMax + 1; s <= 16; s++) {
                    seqNoteOctave[s - 1]->setEnabled(false);
                    seqRhythmic[s - 1]->setEnabled(false);
                    seqVelocity[s - 1]->setEnabled(false);
                }
            }
            seqScore->setStepMax(stepMax);
        }
    }
    if (comboBoxThatHasChanged == seqNumberOfStep[1]) {
        int stepMax = seqNumberOfStep[1]->getSelectedId() - 1;
        if (stepMax == -1) {
            stepMax = 16;
            seqNumberOfStep[1]->setSelectedId(17);
        }
        if (stepMax >= 1 && stepMax <= 16) {
            for (int s = 1; s <= stepMax; s++) {
                seq1Steps[s - 1]->setEnabled(true);
            }
            if (stepMax < 16) {
                for (int s = stepMax + 1; s <= 16; s++) {
                    seq1Steps[s - 1]->setEnabled(false);
                }
            }
        }
    }
    if (comboBoxThatHasChanged == seqNumberOfStep[2]) {
        int stepMax = seqNumberOfStep[2]->getSelectedId() - 1;
        if (stepMax == -1) {
            stepMax = 16;
            seqNumberOfStep[2]->setSelectedId(17);
        }
        if (stepMax >= 1 && stepMax <= 16) {
            for (int s = 1; s <= stepMax; s++) {
                seq2Steps[s - 1]->setEnabled(true);
            }
            if (stepMax < 16) {
                for (int s = stepMax + 1; s <= 16; s++) {
                    seq2Steps[s - 1]->setEnabled(false);
                }
            }
        }
    }

    // Not a goo idea !
    //if (comboBoxThatHasChanged == seqMode) {
    //    bool arpEnabled = seqMode->getSelectedId() == 2;
    //    bool seqEnabled = seqMode->getSelectedId() == 3;

    //    for (int l = 4; l <= 7; l++) {
    //        seqAllLabels[l]->setEnabled(arpEnabled);
    //    }
    //    arpGroup->setEnabled(arpEnabled);
    //    seqDirection->setEnabled(arpEnabled);
    //    seqRange->setEnabled(arpEnabled);
    //    seqPattern->setEnabled(arpEnabled);
    //    seqDivision->setEnabled(arpEnabled);

    //    for (int s = 0; s < NUMBER_OF_STEPS; s++) {
    //        seqStepLabel[s]->setEnabled(seqEnabled);
    //        seqRhythmic[s]->setEnabled(seqEnabled);
    //        seqNoteOctave[s]->setEnabled(seqEnabled);
    //        seqVelocity[s]->setEnabled(seqEnabled);
    //    }
    //    seqGroup->setEnabled(seqEnabled);
    //    seqPullButton->setEnabled(seqEnabled);
    //    seqPushButton->setEnabled(seqEnabled);
    //    seqRandomizeButton->setEnabled(seqEnabled);
    //    seqAllLabels[8]->setEnabled(seqEnabled);
    //    seqNumberOfStep->setEnabled(seqEnabled);
    //    seqScore->setEnabled(seqEnabled);
    //    seqScore->repaint();
    //}
}


void PanelSequencer::updateSliderFromParameter_hook(Slider* slider) {
    sliderValueChanged(slider, false);
}

void PanelSequencer::updateComboFromParameter_hook(ComboBox* combo) {
    comboBoxChanged(combo, false);
}

void PanelSequencer::noteChanged(SequencerScore* sequencer, int step, int newNote) {
    uint8 data1 = newNote + (seqNoteOctave[step]->getSelectedId() + 1) * 12;
    if (seqRhythmic[step]->getSelectedId() <= 2) {
        data1 |= 0x80;
    }
    canSendSequencer->setRealTimeUpdate(32 + step * 2, data1);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PanelSequencer" componentName=""
                 parentClasses="public Component, public Button::Listener, public Slider::Listener, public ComboBox::Listener, public PanelOfComponents, public MISequencer, public ComboAndSlider::Listener, public SequencerScore::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="1000"
                 initialHeight="710">
  <BACKGROUND backgroundColour="173e5a"/>
  <GROUPCOMPONENT name="Arpeggiator Group" id="b4a755ef60332f60" memberName="arpGroup"
                  virtualName="" explicitFocusOrder="0" pos="480 24 240 160" title="Arpeggiator"/>
  <GROUPCOMPONENT name="Sequencer Group" id="c28124fe342ca7bb" memberName="seqGroup"
                  virtualName="" explicitFocusOrder="0" pos="312 296 896 488" title="Sequencer"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
