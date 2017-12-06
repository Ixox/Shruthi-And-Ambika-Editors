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
#ifdef AMBIKA
#include "../SliderPfm2.h"
//[/Headers]

#include "PanelMulti.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const char* seqBmpComboItems[] = { "Internal",  "Ext Synced", nullptr };
const char* seqGrooveItems[] = { "swing",    "shuffle",    "push",    "lag",    "human",    "monkey",    nullptr };
const char* seqMultiLabeItems[] = { "Bpm", "Groove", "Amount", "Latch"};
//[/MiscUserDefs]

//==============================================================================
PanelMulti::PanelMulti ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (voicesGroup = new GroupComponent ("Voices Group",
                                                         TRANS("Voices")));

    addAndMakeVisible (tempoGroup = new GroupComponent ("Tempo Group",
                                                        TRANS("Tempo")));

    addAndMakeVisible (buttonsGroup = new GroupComponent ("Buttons Group",
                                                          TRANS("Buttons")));

    addAndMakeVisible (useMultiButton = new ToggleButton ("Use Multi"));

    addAndMakeVisible (useMultiLabel = new Label ("Use Multi Label",
                                                  TRANS("Click this checkbox if you want this tab \n"
                                                  "to be part of your preset.")));
    useMultiLabel->setTooltip (TRANS("If you use several plugin instances, this must be checked only once."));
    useMultiLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    useMultiLabel->setJustificationType (Justification::centred);
    useMultiLabel->setEditable (false, false, false);
    useMultiLabel->setColour (TextEditor::textColourId, Colours::black);
    useMultiLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (pushMultiButton = new TextButton ("Push Multi Button"));
    pushMultiButton->setButtonText (TRANS("Push multi settings"));


    //[UserPreSize]
    pushMultiButton->addListener(this);
    useMultiButton->addListener(this);


    for (int l = 0; l < 4; l++) {
        addAndMakeVisible(seqAllLabels[l] = new Label("seq" + String(seqMultiLabeItems[l]) + " label", seqMultiLabeItems[l]));
        seqAllLabels[l]->setJustificationType(Justification::centred);
    }

    //ScopedPointer<ComboAndSlider> seqBpm;
    addAndMakeVisible(tempoBpm = new ComboAndSlider("Seq Bpm"));
    tempoBpm->setComboParams(seqBmpComboItems, 38);
    tempoBpm->setSliderParams(40.0f, 240.0f, 0);
    tempoBpm->addListener(this);

    //ScopedPointer<ComboBox> seqGoove;
    addAndMakeVisible(tempoGroove = new ComboBox("Seq Groove"));
    tempoGroove->setEditableText(false);
    tempoGroove->setJustificationType(Justification::centred);
    tempoGroove->setColour(ComboBox::buttonColourId, Colours::blue);
    for (int i = 0; seqGrooveItems[i] != nullptr; i++) {
        tempoGroove->addItem(seqGrooveItems[i], i + 1);
    }
    tempoGroove->setSelectedId(1);
    tempoGroove->setScrollWheelEnabled(true);
    tempoGroove->addListener(this);

    //ScopedPointer<Slider> seqAmount;
    addAndMakeVisible(tempoAmount = new SliderPfm2("Seq Amount"));
    tempoAmount->setRange(0, 127, 1);
    tempoAmount->setSliderStyle(Slider::RotaryVerticalDrag);
    tempoAmount->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    tempoAmount->setDoubleClickReturnValue(true, 0.0f);
    tempoAmount->addListener(this);

    addAndMakeVisible(tempoLatch = new SliderPfm2("Seq tempo latch"));
    tempoLatch->setRange(0, 8, 1);
    tempoLatch->setSliderStyle(Slider::RotaryVerticalDrag);
    tempoLatch->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
    tempoLatch->setDoubleClickReturnValue(true, 0.0f);
    tempoLatch->addListener(this);

    // PARTS
    String partItemLabelText[] = { "Midi", "Low Note", "High Note", "Voice 1", "Voice 2", "Voice 3", "Voice 4", "Voice 5", "Voice 6" };
    for (int l = 0; l < 9; l++) {
        DBG("PART " << l);
        addAndMakeVisible(partItemLabel[l] = new Label("PART ITEM LABEL "+ String(l), partItemLabelText[l]));
        partItemLabel[l]->setJustificationType(Justification::centred);
    }
    String noteStrings[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A" , "A#", "B" };
    for (int l = 0; l < NUMBER_OF_PARTS; l++) {
        DBG("PART " << l);
        addAndMakeVisible(partLabel[l] = new Label("PART LABEL" + String(l), "Part " + String(l + 1)));
        partLabel[l]->setJustificationType(Justification::centred);

        DBG("PART VOICE" << l);
        for (int v = 0; v < NUMBER_OF_PARTS; v++) {
            DBG("VOICE " << v);
            addAndMakeVisible(partVoicesLink[l][v] = new ToggleButton("Part " + String(l + 1) + " Voice " + String(v + 1)));
            partVoicesLink[l][v]->setButtonText("");
            partVoicesLink[l][v]->setRadioGroupId(1721 + v);
            partVoicesLink[l][v]->addListener(this);
        }

        DBG("PART CHANNEL" << l);
        addAndMakeVisible(partChannelLink[l] = new ComboBox("Part Channel " + String(l + 1)));
        partChannelLink[l]->setEditableText(false);
        partChannelLink[l]->setJustificationType(Justification::centred);
        partChannelLink[l]->setColour(ComboBox::buttonColourId, Colours::blue);
        for (int i = 0; i < 16; i++) {
            partChannelLink[l]->addItem(String(i + 1), i + 1);
        }
        partChannelLink[l]->setSelectedId(1);
        partChannelLink[l]->setScrollWheelEnabled(true);
        partChannelLink[l]->addListener(this);

        DBG("PART NoteStart" << l);

        addAndMakeVisible(partNoteStart[l] = new ComboBox("Par NoteStart " + String(l + 1)));
        partNoteStart[l]->setEditableText(false);
        partNoteStart[l]->setJustificationType(Justification::centred);
        for (int o = -1; o <= 9; o++) {
            for (int n = 0; n < 12; n++) {
                int index = (o + 1) * 12 + n;
                if (index <= 127) {
                    partNoteStart[l]->addItem(noteStrings[n] + String(o), index + 1);
                }
            }
        }
        DBG("PART NoteSend" << l);
        partNoteStart[l]->setSelectedId(1);
        partNoteStart[l]->setScrollWheelEnabled(true);
        partNoteStart[l]->addListener(this);

        addAndMakeVisible(partNoteEnd[l] = new ComboBox("Par NoteEnd " + String(l + 1)));
        partNoteEnd[l]->setEditableText(false);
        partNoteEnd[l]->setJustificationType(Justification::centred);
        for (int o = -1; o <= 9; o++) {
            for (int n = 0; n < 12; n++) {
                int index = (o + 1) * 12 + n;
                if (index <= 127) {
                    partNoteEnd[l]->addItem(noteStrings[n] + String(o), index + 1);
                }
            }
        }
        partNoteEnd[l]->setSelectedId(1);
        partNoteEnd[l]->setScrollWheelEnabled(true);
        partNoteEnd[l]->addListener(this);

    }




    // KNOBS

    struct KnobParam knobAssignStructs[] = {
        // 0
        { "Osc 1 Wave", 0, 0},
        { "Osc 1 Parameter", 1, 0},
        { "Osc 1 Range", 2, 0},
        { "Osc 1 Detune", 3, 0},
        { "Osc 2 Wave", 4, 0},
        { "Osc 2 Parameter", 5, 0},
        { "Osc 2 Range", 6, 0},
        { "Osc 2 Detune", 7, 0},
        // 8
        { "Mixer Osc Mix", 8, 0},
        { "Mixer Cross Mode", 9, 0},
        { "Mixer Amount", 10, 0},
        { "Mixer Sub Shape", 11, 0},
        { "Mixer Sub Level", 12, 0},
        { "Mixer Noise", 13, 0},
        { "Mixer Fuzz", 14, 0},
        { "Mixer Crush", 15, 0},
        // 16
        { "Filter Cutoff", 16, 0},
        { "Filter Res", 17, 0},
        { "Filter Mode", 18, 0},
        { "Filter2 Cutoff", 19, 0},
        { "Filter2 Res", 20, 0},
        { "Filter2 Mode", 21, 0},
        { "Filter env", 22, 0},
        { "Filter lfo", 23, 0},
        // 25 Env
        { "Env 1 Attack", 25, 0},
        { "Env 2 Attack", 25, 1},
        { "Env 3 Attack", 25, 2},
        { "Env 1 Decay", 26, 0},
        { "Env 2 Decay", 26, 1},
        { "Env 3 Decay", 26, 2},
        { "Env 1 Sustain", 27, 0},
        { "Env 2 Sustain", 27, 1},
        { "Env 3 Sustain", 27, 2},
        { "Env 1 Release", 28, 0},
        { "Env 2 Release", 28, 1},
        { "Env 3 Release", 28, 2},
        // LFO
        { "Lfo 1 Trigger", 29, 0},
        { "Lfo 1 Trigger", 29, 1},
        { "Lfo 1 Trigger", 29, 2},
        { "Lfo 1 Rate", 30, 0},
        { "Lfo 2 Rate", 30, 1},
        { "Lfo 3 Rate", 30, 2},
        { "Lfo 1 waveform", 31, 0},
        { "Lfo 2 waveform", 31, 1},
        { "Lfo 3 waveform", 31, 2},
        { "Voice lfo rate", 32, 0},
        { "Voice lfo waveform", 33, 0},
        // Modulations
        { "Mtx 1 Source", 35, 0},
        { "Mtx 2 Source", 35, 1},
        { "Mtx 3 Source", 35, 2},
        { "Mtx 4 Source", 35, 3},
        { "Mtx 5 Source", 35, 4},
        { "Mtx 6 Source", 35, 5},
        { "Mtx 7 Source", 35, 6},
        { "Mtx 8 Source", 35, 7},
        { "Mtx 9 Source", 35, 8},
        { "Mtx 10 Source", 35, 9},
        { "Mtx 11 Source", 35, 10},
        { "Mtx 12 Source", 35, 11},
        { "Mtx 13 Source", 35, 12},
        { "Mtx 14 Source", 35, 13},
        { "Mtx 1 Destination", 36, 0},
        { "Mtx 2 Destination", 36, 1},
        { "Mtx 3 Destination", 36, 2},
        { "Mtx 4 Destination", 36, 3},
        { "Mtx 5 Destination", 36, 4},
        { "Mtx 6 Destination", 36, 5},
        { "Mtx 7 Destination", 36, 6},
        { "Mtx 8 Destination", 36, 7},
        { "Mtx 9 Destination", 36, 8},
        { "Mtx 10 Destination", 36, 9},
        { "Mtx 11 Destination", 36, 10},
        { "Mtx 12 Destination", 36, 11},
        { "Mtx 13 Destination", 36, 12},
        { "Mtx 14 Destination", 36, 13},
        { "Mtx 1 Amount", 37, 0},
        { "Mtx 2 Amount", 37, 1},
        { "Mtx 3 Amount", 37, 2},
        { "Mtx 4 Amount", 37, 3},
        { "Mtx 5 Amount", 37, 4},
        { "Mtx 6 Amount", 37, 5},
        { "Mtx 7 Amount", 37, 6},
        { "Mtx 8 Amount", 37, 7},
        { "Mtx 9 Amount", 37, 8},
        { "Mtx 10 Amount", 37, 9},
        { "Mtx 11 Amount", 37, 10},
        { "Mtx 12 Amount", 37, 11},
        { "Mtx 13 Amount", 37, 12},
        { "Mtx 14 Amount", 37, 13},
        // Midifier
        { "Mod 1 In1", 39, 0},
        { "Mod 2 In1", 39, 1},
        { "Mod 3 In1", 39, 2},
        { "Mod 4 In1", 39, 3},
        { "Mod 1 In2", 40, 0},
        { "Mod 2 In2", 40, 1},
        { "Mod 3 In2", 40, 2},
        { "Mod 4 In2", 40, 3},
        { "Mod 1 Operator", 41, 0},
        { "Mod 2 Operator", 41, 1},
        { "Mod 3 Operator", 41, 2},
        { "Mod 4 Operator", 41, 3},
        // Part
        { "Part Volume", 42, 0},
        { "Part Octave", 43, 0},
        { "Part Tune", 44, 0},
        { "Part Spread", 45, 0},
        { "Part Rage", 46, 0},
        { "Part Legato", 47, 0},
        { "Part Portamento", 48, 0},
        { "Part Arp/seq", 49, 0},
        { "Arp Direction", 50, 0},
        { "Arp Range", 51, 0},
        { "Arp Pattern", 52, 0},
        { "Arp Grid", 53, 0},
        { "Seq1 Length", 54, 0},
        { "Seq2 Length", 55, 0},
        { "Pattern Length", 56, 0},
        { "Part Mode", 57, 0 },
        { "", 0, 0}
    };

    for (int k = 0; k < NUMBER_OF_KNOBS; k++) {
        addAndMakeVisible(knobLabel[k] = new Label("KNOB LABEL" + String(k), "Knob " + String(k + 1)));
        knobLabel[k]->setJustificationType(Justification::centred);

        addAndMakeVisible(knobPart[k] = new ComboBox("Knob Part " + String(k + 1)));
        knobPart[k]->setEditableText(false);
        knobPart[k]->setJustificationType(Justification::centred);
        knobPart[k]->setColour(ComboBox::buttonColourId, Colours::blue);
        for (int i = 0; i < 6; i++) {
            knobPart[k]->addItem(String(i + 1), i + 1);
        }
        knobPart[k]->setSelectedId(1);
        knobPart[k]->setScrollWheelEnabled(true);
        knobPart[k]->addListener(this);

        // knobAssignTexts
        addAndMakeVisible(knobTarget[k] = new ComboBox("Knob Target " + String(k + 1)));
        knobTarget[k]->setEditableText(false);
        knobTarget[k]->setJustificationType(Justification::centred);
        knobTarget[k]->setColour(ComboBox::buttonColourId, Colours::blue);
        for (int i = 0; knobAssignStructs[i].name.length() > 0; i++) {
            DBG("i " << i << " name '" << knobAssignStructs[i].name << "' comboId : " << knobAssignStructs[i].getComboBoxId());
            knobTarget[k]->addItem(knobAssignStructs[i].name, knobAssignStructs[i].getComboBoxId());
        }
        knobTarget[k]->setSelectedId(1);
        knobTarget[k]->setScrollWheelEnabled(true);
        knobTarget[k]->addListener(this);

    }


    //[/UserPreSize]

    setSize (1000, 400);


    //[Constructor] You can add your own custom stuff here..
    if (settingsListener && useMultiButton->getToggleState()) {
        settingsListener->sendMultiDataToAmbika(getMultiData());
    }
    settingsListener = nullptr;
    //[/Constructor]
}

PanelMulti::~PanelMulti()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    voicesGroup = nullptr;
    tempoGroup = nullptr;
    buttonsGroup = nullptr;
    useMultiButton = nullptr;
    useMultiLabel = nullptr;
    pushMultiButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PanelMulti::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PanelMulti::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    if (false) {
    //[/UserPreResize]

    voicesGroup->setBounds (proportionOfWidth (0.0283f), proportionOfHeight (0.6013f), proportionOfWidth (0.9059f), proportionOfHeight (0.3486f));
    tempoGroup->setBounds (proportionOfWidth (0.3340f), proportionOfHeight (0.0174f), proportionOfWidth (0.5888f), proportionOfHeight (0.2092f));
    buttonsGroup->setBounds (proportionOfWidth (0.0170f), proportionOfHeight (0.2527f), proportionOfWidth (0.9002f), proportionOfHeight (0.3224f));
    useMultiButton->setBounds (288, 56, 150, 24);
    useMultiLabel->setBounds (96, 32, 174, 72);
    pushMultiButton->setBounds (176, 152, 152, 40);
    //[UserResized] Add your own custom resize handling here..
    }

    // Tempo group
    Rectangle<int> totalBounds = getLocalBounds().reduced(10,10);

    // TOP (MULTI + TEMPO)
    Rectangle<int> topBounds = totalBounds.removeFromTop(totalBounds.getHeight() / 5);

    // Use MULTI

    Rectangle<int> useThisPanel = topBounds.removeFromLeft(topBounds.getWidth() / 3).reduced(10,0);

    Rectangle<int> pushMultiButtonBounds = useThisPanel.removeFromBottom(useThisPanel.getHeight() / 3);
    pushMultiButton->setBounds(pushMultiButtonBounds.reduced(pushMultiButtonBounds.getWidth() / 2 - 60, pushMultiButtonBounds.getHeight() / 2 - 12));

    useMultiLabel->setBounds(useThisPanel.removeFromTop(useThisPanel.getHeight() / 2));
    useMultiButton->setBounds(useThisPanel.reduced(pushMultiButtonBounds.getWidth() / 2 - 40, 0));



    // TEMPO
    Rectangle<int> tempoBounds = topBounds.reduced(10,0);

    tempoGroup->setBounds(tempoBounds);
    tempoBounds.removeFromTop(15);

    int numberOfItems = 4;

    Rectangle<int> cBounds = tempoBounds.removeFromLeft(tempoBounds.getWidth() / numberOfItems--);
    seqAllLabels[0]->setBounds(cBounds.removeFromTop(20));
    int reducedHeightForCombo = cBounds.getHeight() / 2 - 10;
    tempoBpm->setBounds(cBounds.reduced(10, 0));

    cBounds = tempoBounds.removeFromLeft(tempoBounds.getWidth() / numberOfItems--);
    seqAllLabels[1]->setBounds(cBounds.removeFromTop(20));
    tempoGroove->setBounds(cBounds.reduced(10, reducedHeightForCombo));

    cBounds = tempoBounds.removeFromLeft(tempoBounds.getWidth() / numberOfItems--);
    seqAllLabels[2]->setBounds(cBounds.removeFromTop(20));
    tempoAmount->setBounds(cBounds.reduced(10, 10));

    cBounds = tempoBounds.removeFromLeft(tempoBounds.getWidth() / numberOfItems--);
    seqAllLabels[3]->setBounds(cBounds.removeFromTop(20));
    tempoLatch->setBounds(cBounds.reduced(10, 10));

    // VOICES
    Rectangle<int> partsBounds = totalBounds.removeFromTop(totalBounds.getHeight() * .6f);
    partsBounds.reduce(10, 10);
    voicesGroup->setBounds(partsBounds);
    partsBounds.removeFromTop(5);
    partsBounds.reduce(10, 10);


    int columnWidth = partsBounds.getWidth() / 10;
    Rectangle<int> labelBounds = partsBounds.removeFromTop(partsBounds.getHeight() / 7);

    // No label in fron of Part labels
    labelBounds.removeFromLeft(columnWidth);
    int toRemovePerLine = jmax(0, (labelBounds.getHeight() - 20) / 2);
    for (int l = 0; l < 9; l++) {
        partItemLabel[l]->setBounds(labelBounds.removeFromLeft(columnWidth).reduced(0, toRemovePerLine));
    }
    int toRemoveFromComboWidth = jmax(0, (columnWidth - 24) / 2);
    for (int p = 0; p < NUMBER_OF_PARTS; p++) {
        Rectangle<int> partBounds = partsBounds.removeFromTop(partsBounds.getHeight() / (NUMBER_OF_PARTS - p));
        toRemovePerLine = jmax(0, (partBounds.getHeight() - 20) / 2);
        partLabel[p]->setBounds(partBounds.removeFromLeft(columnWidth).reduced(10, toRemovePerLine));
        partChannelLink[p]->setBounds(partBounds.removeFromLeft(columnWidth).reduced(10, toRemovePerLine));
        partNoteStart[p]->setBounds(partBounds.removeFromLeft(columnWidth).reduced(10, toRemovePerLine));
        partNoteEnd[p]->setBounds(partBounds.removeFromLeft(columnWidth).reduced(10, toRemovePerLine));
        for (int v = 0; v < NUMBER_OF_PARTS; v++) {
            partVoicesLink[p][v]->setBounds(partBounds.removeFromLeft(columnWidth).reduced(toRemoveFromComboWidth, toRemovePerLine));
        }

    }


    // KNOBS
    Rectangle<int> knobsBounds = totalBounds.reduced(10, 0);

    buttonsGroup->setBounds(knobsBounds);
    knobsBounds.removeFromTop(5);
    knobsBounds.reduce(10, 10);

    for (int r = 0; r < 2; r++) {
        Rectangle<int> buttonRow = knobsBounds.removeFromTop(knobsBounds.getHeight() / (2 - r)).reduced(10, 10);
        for (int kn = 0; kn < 4; kn++) {
            int k = r * 4 + kn;
            Rectangle<int> buttonCell = buttonRow.removeFromLeft(buttonRow.getWidth() / (4 - kn));
            knobLabel[k]->setBounds(buttonCell.removeFromTop(20));
            int height = buttonCell.getHeight() / 2;
            int heightToRemoveFromCombo = jmax(0, (height / 2) - 10);
            knobPart[k]->setBounds(buttonCell.removeFromTop(height).reduced(buttonCell.getWidth() / 2 - 25, heightToRemoveFromCombo));
            knobTarget[k]->setBounds(buttonCell.removeFromTop(height).reduced(5, heightToRemoveFromCombo));
        }
    }




    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void PanelMulti::sliderValueChanged(Slider* sliderThatWasMoved) {
}

void PanelMulti::comboBoxChanged(ComboBox* comboBoxThatHasChanged) {
}

void PanelMulti::comboOrSliderValueChanged(ComboAndSlider* slider) {
}

void PanelMulti::buttonClicked(Button *buttonThatWasClicked) {
    if (buttonThatWasClicked == pushMultiButton) {
        settingsListener->sendMultiDataToAmbika(getMultiData());
    }
    if (buttonThatWasClicked == useMultiButton) {
        bool state = useMultiButton->getToggleState();
        pushMultiButton->setEnabled(state);
        tempoBpm->setEnabled(state);
        tempoGroove->setEnabled(state);
        tempoAmount->setEnabled(state);
        tempoLatch->setEnabled(state);

        for (int p = 0; p < NUMBER_OF_PARTS; p++) {
            for (int v = 0; v < NUMBER_OF_PARTS; v++) {
                partVoicesLink[p][v]->setEnabled(state);
            }
            partChannelLink[p]->setEnabled(state);
            partNoteStart[p]->setEnabled(state);
            partNoteEnd[p]->setEnabled(state);
        }

        for (int p = 0; p < NUMBER_OF_KNOBS; p++) {
            knobLabel[p]->setEnabled(state);
            knobPart[p]->setEnabled(state);
            knobTarget[p]->setEnabled(state);
        }

        if (settingsListener != nullptr) {
            settingsListener->setMultiDataUsed(state);
            if (state) {
                settingsListener->requestMultiDataTransfer();
            }
        }
    }
}


MultiData* PanelMulti::getMultiData() {
    for (int p = 0; p < NUMBER_OF_PARTS; p++) {
        panelMultiData.part_mapping_[p].midi_channel = partChannelLink[p]->getSelectedId();
        panelMultiData.part_mapping_[p].keyrange_low = partNoteStart[p]->getSelectedId() -1 ;
        panelMultiData.part_mapping_[p].keyrange_high = partNoteEnd[p]->getSelectedId() - 1;
        int voiceBits = 0;
        for (int v = 0; v < NUMBER_OF_PARTS; v++) {
            voiceBits |= (partVoicesLink[p][v]->getToggleState() ? (1 << v) : 0);
        }
        panelMultiData.part_mapping_[p].voice_allocation = voiceBits;
    }

    struct KnobParam kp;
    for (int p = 0; p < NUMBER_OF_KNOBS; p++) {
        panelMultiData.knob_assignment[p].part = knobPart[p]->getSelectedId() -1 ;
        kp.setComboValue(knobTarget[p]->getSelectedId());
        panelMultiData.knob_assignment[p].instance  = kp.instance;
        panelMultiData.knob_assignment[p].parameter = kp.parameter;
    }

    panelMultiData.clock_bpm = tempoBpm->getValue();
    panelMultiData.clock_groove_template = tempoGroove->getSelectedId() - 1;
    panelMultiData.clock_groove_amount = tempoAmount->getValue();
    panelMultiData.clock_release = tempoLatch->getValue();

    return &panelMultiData;
}

void PanelMulti::setMultiData(MultiData *md) {
    for (int p = 0; p < NUMBER_OF_PARTS; p++) {
        partChannelLink[p]->setSelectedId(md->part_mapping_[p].midi_channel);
        partNoteStart[p]->setSelectedId(md->part_mapping_[p].keyrange_low + 1);
        partNoteEnd[p]->setSelectedId(md->part_mapping_[p].keyrange_high + 1);
        int voiceBits = md->part_mapping_[p].voice_allocation;
        for (int v = 0; v < NUMBER_OF_PARTS; v++) {
            partVoicesLink[p][v]->setToggleState(((voiceBits & (1 << v)) > 0), false);
        }
    }

    struct KnobParam kp;
    for (int p = 0; p < NUMBER_OF_KNOBS; p++) {
        DBG("KNOV " << p << " part : " << md->knob_assignment[p].part << "  parameter : " << md->knob_assignment[p].parameter << " instance " << md->knob_assignment[p].instance);
        knobPart[p]->setSelectedId(md->knob_assignment[p].part + 1);
        kp.instance = md->knob_assignment[p].instance;
        kp.parameter= md->knob_assignment[p].parameter;
        knobTarget[p]->setSelectedId(kp.getComboBoxId());
    }

    tempoBpm->setValue(md->clock_bpm);
    tempoGroove->setSelectedId(md->clock_groove_template + 1);
    tempoAmount->setValue(md->clock_groove_amount);
    tempoLatch->setValue(md->clock_release);

}

bool PanelMulti::isMultiDataUsed() {
    return useMultiButton->getToggleState();
}

void PanelMulti::setMultiDataUsed(bool mdu) {
    useMultiButton->setToggleState(mdu, true);
}


#endif
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PanelMulti" componentName=""
                 parentClasses="public Component, public Button::Listener, public Slider::Listener, public ComboBox::Listener, public ComboAndSlider::Listener, public AmbikaMultiData"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="1000"
                 initialHeight="400">
  <BACKGROUND backgroundColour="323e44"/>
  <GROUPCOMPONENT name="Voices Group" id="3032bf1acb4fa126" memberName="voicesGroup"
                  virtualName="" explicitFocusOrder="0" pos="2.831% 60.131% 90.587% 34.858%"
                  title="Voices"/>
  <GROUPCOMPONENT name="Tempo Group" id="46a8a583740739cc" memberName="tempoGroup"
                  virtualName="" explicitFocusOrder="0" pos="33.404% 1.743% 58.882% 20.915%"
                  title="Tempo"/>
  <GROUPCOMPONENT name="Buttons Group" id="eeecc8e1d69508ae" memberName="buttonsGroup"
                  virtualName="" explicitFocusOrder="0" pos="1.699% 25.272% 90.021% 32.244%"
                  title="Buttons"/>
  <TOGGLEBUTTON name="Use Multi" id="fd9ce31d2ea1df76" memberName="useMultiButton"
                virtualName="" explicitFocusOrder="0" pos="288 56 150 24" buttonText="Use Multi"
                connectedEdges="0" needsCallback="0" radioGroupId="0" state="0"/>
  <LABEL name="Use Multi Label" id="c3adf3505dcc603e" memberName="useMultiLabel"
         virtualName="" explicitFocusOrder="0" pos="96 32 174 72" tooltip="If you use several plugin instances, this must be checked only once."
         edTextCol="ff000000" edBkgCol="0" labelText="Click this checkbox if you want this tab &#10;to be part of your preset."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
         justification="36"/>
  <TEXTBUTTON name="Push Multi Button" id="2228958e47087a4f" memberName="pushMultiButton"
              virtualName="" explicitFocusOrder="0" pos="176 152 152 40" buttonText="Push multi settings"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
