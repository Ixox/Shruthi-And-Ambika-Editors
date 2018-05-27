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


#ifdef AMBIKA

#include "AudioProcessorAmbika.h"

AudioProcessorAmbika::AudioProcessorAmbika()
{
    for (int s = 0; s < 16; s++) {
        sequencer.seqNotes[s].data1 = 200 + s * 2;
        sequencer.seqNotes[s].data2 = 80 + s * 2;
        sequencer.seqController1[s] = (s * 30) % 256 ;
        sequencer.seqController2[s] = (128 + s * 30) % 256;
    }
    canReceiveSysexPartData = false;
}

void AudioProcessorAmbika::initAllParameters() {
    int nrpmParam;
    // ================== OSC1 ===========================================================================
    //Oscillator 1 shape        0 - 34         0    20
    nrpmParam = 0;
    MidifiedFloatParameter* newParam = new MidifiedFloatParameter(String("Osc1 Shape"), nrpmParam, 1, 0, 37, 1);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //Oscillator 1 parameter    0 - 127        1    21
    nrpmParam = 1;
    newParam = new MidifiedFloatParameter(String("Osc1 Param"), nrpmParam, 1, 0, 127, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //Oscillator 1 range        - 24 - 24      2    22
    nrpmParam = 2;
    newParam = new MidifiedFloatParameter(String("Osc1 Range"), nrpmParam, 1, -24, 24, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //Oscillator 1 detune	-64 - 63	7	27
    nrpmParam = 3;
    newParam = new MidifiedFloatParameter(String("Osc1 Detune"), nrpmParam, 1, -64, 63, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;


    // ================== OSC2 ===========================================================================      
    //Oscillator 2 shape0 - 34	4	24
    nrpmParam = 4;
    newParam = new MidifiedFloatParameter(String("Osc2 Shape"), nrpmParam, 1, 0, 37, 2);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;
    //Oscillator 2 parameter	0 - 127	5	25
    nrpmParam = 5;
    newParam = new MidifiedFloatParameter(String("Osc2 Param"), nrpmParam, 1, 0, 127, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //Oscillator 2 range - 24 - 24	6	26
    nrpmParam = 6;
    newParam = new MidifiedFloatParameter(String("Osc2 Range"), nrpmParam, 1, -24, 24, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //Oscillator 2 detune	0 - 127	7	27
    nrpmParam = 7;
    newParam = new MidifiedFloatParameter(String("Osc2 Detune"), nrpmParam, 1, -64, 63, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;


    // ================== MIX ===========================================================================
    //Oscillator balance	
    nrpmParam = 8;
    newParam = new MidifiedFloatParameter(String("mix_balance"), nrpmParam, 1, 0, 63, 32);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //Modulation operator       
    nrpmParam = 9;
    newParam = new MidifiedFloatParameter(String("mix_op"), nrpmParam, 1, 0, 5, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    // mix_parameter
    nrpmParam = 10;
    newParam = new MidifiedFloatParameter(String("mix_parameter"), nrpmParam, 1, 0, 63, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    // mix_parameter
    nrpmParam = 11;
    newParam = new MidifiedFloatParameter(String("mix_sub_osc_shape"), nrpmParam, 1, 0, 10, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;


    //Sub oscillator volume	
    nrpmParam = 12;
    newParam = new MidifiedFloatParameter(String("mix_sub_osc"), nrpmParam, 1, 0, 63, 32);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //Noise volume	
    nrpmParam = 13;
    newParam = new MidifiedFloatParameter(String("mix_noise"), nrpmParam, 1, 0, 63, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    // mix Fuzz 
    nrpmParam = 14;
    newParam = new MidifiedFloatParameter(String("mix_fuzz"), nrpmParam, 1, 0, 63, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    // Crush amount
    nrpmParam = 15;
    newParam = new MidifiedFloatParameter(String("mix_crush"), nrpmParam, 1, 0, 31, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    // ================== FILTER ===========================================================================
    //Filter cutoff	0 - 127	12	14, 74
    nrpmParam = 16;
    newParam = new MidifiedFloatParameter(String("Filter Freq"), nrpmParam, 1, 0, 127, 63);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;
    //Filter resonance	0 - 63	13	15, 71
    nrpmParam = 17;
    newParam = new MidifiedFloatParameter(String("Filter Resonance"), nrpmParam, 1, 0, 63, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;
    //Filter Mod	0 - 63	13	15, 71
    nrpmParam = 18;
    newParam = new MidifiedFloatParameter(String("Filter Mode"), nrpmParam, 1, 0, 2, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;
    //Envelope->cutoff modulation amount	0 - 63	14	102
    nrpmParam = 22;
    newParam = new MidifiedFloatParameter(String("Filter Env"), nrpmParam, 1, 0, 63, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;
    //Lfo->cutoff modulation amount	0 - 63	15	103
    nrpmParam = 23;
    newParam = new MidifiedFloatParameter(String("Filter Lfo"), nrpmParam, 1, 0, 63, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;
    // Filter Velocity
    nrpmParam = 104;
    newParam = new MidifiedFloatParameter(String("Filter Velocity"), nrpmParam, 1, 0, 63, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    // Filter Keyboard
    nrpmParam = 105;
    newParam = new MidifiedFloatParameter(String("Filter Keyboard"), nrpmParam, 1, -63, 63, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;


    // Filter Type

    // =========== Envelope ==============================



    for (int e = 0; e < 3; e++) {
        // " Attk", " Deca", " Sust", " Rele"
        //Envelope 1 attack 0 - 127 16 104
        //Envelope 2 attack 0 - 127 20 108, 73
        nrpmParam = 24 + e * 8;
        newParam = new MidifiedFloatParameter("Env" + String(e + 1) + " Attk", nrpmParam, 1, 0, 127, 5);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;


        //Envelope 1 decay 0 - 127 17 105
        //Envelope 2 decay 0 - 127 21 109
        nrpmParam = 25 + e * 8;
        newParam = new MidifiedFloatParameter("Env" + String(e + 1) + " Deca", nrpmParam, 1, 0, 127, 5);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;


        //Envelope 1 sustain 0 - 127 18 106
        //Envelope 2 sustain 0 - 127 22 110
        nrpmParam = 26 + e * 8;
        newParam = new MidifiedFloatParameter("Env" + String(e + 1) + " Sust", nrpmParam, 1, 0, 127, 63);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;

        //Envelope 1 release 0 - 127 19 107
        //Envelope 2 release 0 - 127 23 111
        nrpmParam = 27 + e * 8;
        newParam = new MidifiedFloatParameter("Env" + String(e + 1) + " Rele", nrpmParam, 1, 0, 127, 10);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
    }


    const int defaultSources[12] = { 0,0,1,1,1,2,21,21,20,21,8,0 };
    const int defaultAmount[12] = { 0,0,0,0,0,0,0,0,63,16,32,16 };
    // Destination are not in the right order
    const int matrixDestValue[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 11, 1, 12, 13, 17, 19, 20, 21, 22, 18, 23, 24, 25, 26, 14, 15, 16 };
    const int defaultTarget[12] = { 2,3,0,1,6,6,0,1,11,11,4,4 };


    for (int r = 0; r < 14; r++) {
        //addAndMakeVisible(matrixSource[r] = new ComboBox("Mtx" + String(r + 1) + " Source"));
        nrpmParam = 50 + r * 3;
        newParam = new MidifiedFloatParameter("Mtx" + String(r + 1) + " Source", nrpmParam, 1, 0, 28, defaultSources[r]);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
        //addAndMakeVisible(matrixDestination[r] = new ComboBox("Mtx" + String(r + 1) + " Destination"));
        nrpmParam = 51 + r * 3;
        newParam = new MidifiedFloatParameter("Mtx" + String(r + 1) + " Destination", nrpmParam, 1, 0, 27, matrixDestValue[defaultTarget[r]]);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
        //addAndMakeVisible(matrixMultipler[r] = new SliderPfm2("Mtx" + String(r + 1) + " Multiplier"));
        nrpmParam = 52 + r * 3;
        newParam = new MidifiedFloatParameter("Mtx" + String(r + 1) + " Multiplier", nrpmParam, 1, -63, 63, defaultAmount[r]);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
    }

    // OPERATORS
    for (int r = 0; r < 4; r++) {
        nrpmParam = 92 + r * 3;
        newParam = new MidifiedFloatParameter("Op" + String(r + 1) + " Source1", nrpmParam, 1, 0, 31, 0);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
        nrpmParam = 93 + r * 3;
        newParam = new MidifiedFloatParameter("Op" + String(r + 1) + " Source2", nrpmParam, 1, 0, 31, 0);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
        nrpmParam = 94 + r * 3;
        newParam = new MidifiedFloatParameter("Op" + String(r + 1) + " Out", nrpmParam, 1, 03, 9, 0);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
    }
    // LFO !!!!!
    for (int l = 0; l < 3; l++) {
        // LFO SHAPE
        nrpmParam = 28 + l * 8;
        newParam = new MidifiedFloatParameter("Lfo" + String(l + 1) + " Shape", nrpmParam, 1, 0, 19, 0);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
        // LFO RATE
        nrpmParam = 29 + l * 8;
        newParam = new MidifiedFloatParameter("Lfo" + String(l + 1) + " Rate", nrpmParam, 1, 0, 144, 20);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;

        // Trigger
        nrpmParam = 31 + l * 8;
        newParam = new MidifiedFloatParameter("LfoEnv" + String(l + 1) + " Trigger", nrpmParam, 1, 0, 2, 0);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
    }


    //    addAndMakeVisible(lfoVoiceShape = new ComboBox("Lfovoice Shape"));
    nrpmParam = 48;
    newParam = new MidifiedFloatParameter("Lfovoice Shape", nrpmParam, 1, 0, 3, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //    addAndMakeVisible(lfoVoiceRate = new SliderPfm2("Lfovoice Rate"));
    nrpmParam = 49;
    newParam = new MidifiedFloatParameter("Lfovoice Rate", nrpmParam, 1, 0, 127, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    // Arpegiator....
    // Offset: 7-
    //uint8_t arp_sequencer_mode;
    //uint8_t arp_direction;
    //uint8_t arp_octave;
    //uint8_t arp_pattern;
    //uint8_t arp_divider;

    //addAndMakeVisible(seqMode = new ComboBox("Seq Mode"));
    //Sequencer mode 0 - 2 100 75
    nrpmParam = 112 + 7;
    newParam = new MidifiedFloatParameter("Seq Mode", nrpmParam, 1, 0, 2, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //addAndMakeVisible(seqDirection = new ComboBox("Seq Direction"));
    //Arpeggiator direction 0 - 3 104 78
    nrpmParam = 112 + 8;
    newParam = new MidifiedFloatParameter("Seq Direction", nrpmParam, 1, 0, 4, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //addAndMakeVisible(seqRange = new SliderPfm2("Seq Range"));
    //Arpeggiator range 1 - 4 105 79
    nrpmParam = 112 + 9;
    newParam = new MidifiedFloatParameter("Seq Range", nrpmParam, 1, 1, 4, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //addAndMakeVisible(seqPattern = new ComboBox("Seq Pattern"));
    //Arpeggiator pattern 0 - 15 106 80
    nrpmParam = 112 + 10;
    newParam = new MidifiedFloatParameter("Seq Pattern", nrpmParam, 1, 0, 21, 0);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //addAndMakeVisible(seqDivision = new ComboBox("Seq Division"));
    //Sequencer clock division 0 - 11 107 81
    nrpmParam = 112 + 11;
    newParam = new MidifiedFloatParameter("Seq Division", nrpmParam, 1, 0, 11, 9);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;





    // "Seq Length"
    for (int s = 0; s < 3; s++) {
        nrpmParam = 112 + 12 + s;
        newParam = new MidifiedFloatParameter("Seq Length" + String(s+1), nrpmParam, 1, 1, 32, 16);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
    }

    //for (int s = 0; s < 16; s++) {
    //    nrpmParam = 112 + 16 + s;
    //    newParam = new MidifiedFloatParameter("Seq1 Step" + String(s + 1), nrpmParam, 1, 0, 255, 128);
    //    addMidifiedParameter(newParam);
    //    nrpmIndex[nrpmParam] = parameterIndex++;
    //    nrpmParam = 112 + 32 + s;
    //    newParam = new MidifiedFloatParameter("Seq2 Step" + String(s + 1), nrpmParam, 1, 0, 255, 128);
    //    addMidifiedParameter(newParam);
    //    nrpmIndex[nrpmParam] = parameterIndex++;
    //}

    // TUNING
    const char* tunningNames[8] = { 
        "volume", "octave", "tuning", "spread", "raga", "legato", "portamento_time", "polyphony_mode"
    };
    const int nrpnOffset[8] = { 0, 1, 2, 3, 4, 5, 6, 15 };
    const int nrpnMin[8] = { 0, -2, -127, 0, 0, 0, 0, 0};
    const int nrpnMax[8] = { 127, 2, 126, 40, 31, 1, 63, 4};
    const int nrpnDefault[8] = { 127, 0, 0, 0, 0, 0, 0, 0 };
    for (int t = 0; t < 8; t++) {
        nrpmParam = 112 + nrpnOffset[t];
        newParam = new MidifiedFloatParameter("Tuning "+ String(tunningNames[t]), nrpmParam, 1, nrpnMin[t], nrpnMax[t], nrpnDefault[t]);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
    }

    isMultiDataUsed = false;
}


void AudioProcessorAmbika::encodeSysexPatch(uint8* patch) {
    const OwnedArray< AudioProcessorParameter >&parameterSet = getParameters();

    for (int b = 0; b < 112; b++) {
        int index = nrpmIndex[b];
        if (index == -1) {
            DBG("nrpmIndex[" << b << "] IS MISSING !!!!!!!");
            continue;
        }
        MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[index];
        patch[b] = midifiedFP->getRealValue();
    }
}




void AudioProcessorAmbika::decodeSysexPatch(const uint8* patch) {
    if (!canReceiveSysexPatch) {
        return;
    }
    canReceiveSysexPatch = false;

    const OwnedArray< AudioProcessorParameter >&parameterSet = getParameters();

    for (int b = 0; b < 112; b++) {
        int index = nrpmIndex[b];
        if (index == -1) {
             DBG("nrpmIndex[" << b << "] IS MISSING !!!!!!!");
            continue;
        }
        uint8 byte = patch[b * 2] * 0x10 + patch[b * 2 + 1];
        MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[index];
        midifiedFP->setValueFromNrpn((int)byte);
    }

    // REDRAW UI   
    redrawUI();
}


void AudioProcessorAmbika::decodeSysexPartData(const uint8* pdata) {
    if (!canReceiveSysexPartData) {
        return;
    }
    canReceiveSysexPartData = false;
    const OwnedArray< AudioProcessorParameter >&parameterSet = getParameters();

    for (int b = 0; b < 84; b++) {
        int index = nrpmIndex[b + 112];
        if (index == -1) {
            DBG("nrpmIndex[" << b << "] IS MISSING !!!!!!!");
            continue;
        }
        uint8 byte = pdata[b * 2] * 0x10 + pdata[b * 2 + 1];
        MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[index];
        midifiedFP->setValueFromNrpn((int)byte);
    }

    // REDRAW UI   
    redrawUI();
}


bool AudioProcessorAmbika::needsPart() {
    return true;
}

bool AudioProcessorAmbika::needsPresetName() {
    return false;
}

char AudioProcessorAmbika::sysexMachineCode() {
    return 0x04;
}


void AudioProcessorAmbika::requestPatchTransfer() {
    char command[] = { 0x00, 0x21, 0x02, 0x00, 0x04, 0x11, 0x00, 0x00, 0x00 };
    DBG("REQUEST PART " << currentPart);
    command[6] = currentPart;
    canReceiveSysexPatch = true;
    sendSysex(MidiMessage::createSysExMessage(command, 9));
    requestPartDataTransfer();
    requestSequencerTransfer();
}


void AudioProcessorAmbika::requestPartDataTransfer() {
    uint8 command[] = { 0x00, 0x21, 0x02, 0x00, 0x04, 0x15, 0x00, 0x00, 0x00 };
    command[6] = currentPart;
    canReceiveSysexPartData = true;
    sendSysex(MidiMessage::createSysExMessage(command, 9));
}


void AudioProcessorAmbika::requestSequencerTransfer() {
    uint8 command[] = { 0x00, 0x21, 0x02, 0x00, 0x04, 0x12, 0x00, 0x00, 0x00 };
    command[6] = currentPart;
    canReceiveSysexSequencer = true;
    sendSysex(MidiMessage::createSysExMessage(command, 9));
}

void AudioProcessorAmbika::requestMultiDataTransfer() {
    uint8 command[] = { 0x00, 0x21, 0x02, 0x00, 0xff, 20, 0x00, 0x00, 0x00 };
    command[4] = sysexMachineCode();
    canReceiveMultiPart = true;
    sendSysex(MidiMessage::createSysExMessage(command, 9));
}


void AudioProcessorAmbika::decodeMultiData(const uint8* message) {
    uint8* buffer = (uint8*)&multiData;
    for (int b = 0; b < 52; b++) {
        buffer[b] = message[b * 2] * 0x10 + message[b * 2 + 1];
    }

    updateMidiChannelFromPart(&multiData);

    const MessageManagerLock mmLock;
    if (audioProcessorEditor != nullptr) {
        ambikaMultiDataUI->setMultiData(&multiData);
    }
}


String AudioProcessorAmbika::getSynthName() {
    return "Ambika";
}

void AudioProcessorAmbika::setSequencerData(uint8* seq) {
    for (int s = 0; s < 64; s++) {
        ((uint8*)&sequencer)[s] = seq[s];
    }
}


void AudioProcessorAmbika::sendSequencerToSynth(uint8* seq) {

    if (seq != nullptr) {
        setSequencerData(seq);
    }

    uint8* buffer = (uint8*) &sequencer;
    for (int s = 0; s < 64; s++) {
        MidifiedFloatParameter mfp("Seq", 112 + 16 + s, 1, 0, 255, 0);
        mfp.setRealValueNoNotification((float) (buffer[s]));
        mfp.addNrpn(midiOutBuffer, currentMidiChannel);
        flushMidiOut();
    }
}


bool AudioProcessorAmbika::needsRealTimeUpdate() {
    return true;
}

void AudioProcessorAmbika::setRealTimeUpdate(int param, int value) {
    // Offset: 16-80
    //  0..15: step sequence 1
    // 16..31: step sequence 2
    // 32..63: (note value | 0x80 if gate), (note velocity | 0x80 if legato)
    if (midiDeviceNumber >= 0) {
        MidifiedFloatParameter mfp("Seq", 112 + 16 + param, 1, 0, 255, 0);
        mfp.setRealValueNoNotification((float)value);
        mfp.addNrpn(midiOutBuffer, currentMidiChannel);
        flushMidiOut();
    }
    ((uint8*)&sequencer)[param] = value;
//     DBG("AudioPRocessorAmbika setRealTimeUpdate : New seq value: " << param << " value : " << value);
}


void AudioProcessorAmbika::decodeSysexSequencer(const uint8* steps) {
    if (!canReceiveSysexSequencer) {
        return;
    }
    canReceiveSysexSequencer = false;
    // In ambika there are the 2 sequences first (32 bits each)
    for (int p = 0; p < 16; p++) {
        DBG("Bizarre " << p << " : " << (int)((int)steps[p * 2] * 16 + steps[p * 2 + 1]));
    }
    // Other info recevied..
    const uint8* patch = steps + 16;
    uint8* seq = (uint8*)&sequencer;
    DBG("YEAH NEW AMBIKA SEQUENCER!!!");
    for (int b = 0; b < 64; b++) {
        seq[b] = patch[b * 2] * 0x10 + patch[b * 2 + 1];
    }

    const MessageManagerLock mmLock;
    if (sequencerUI != nullptr) {
        sequencerUI->setSequencerData((uint8*)&sequencer);
    }
}


void AudioProcessorAmbika::updateMidiChannelFromPart(MultiData* md) {
    for (int p = 0; p < 6; p++) {
        midiChannelForPart[p] = md->part_mapping_[p].midi_channel;
    }
    currentMidiChannel = midiChannelForPart[currentPart - 1];
    // Let midi device know
    midiDevice->setMidiChannelForPart(midiDeviceNumber, midiChannelForPart);
    settingsChangedForUI();
}


void AudioProcessorAmbika::sendMultiDataToAmbika(MultiData* md) {
    if (!isMultiDataUsed) return;

    uint8 sysexMessage[256];
    uint8* patch;

    if (md != nullptr) {
        setMultiData(md);
    }

    patch = (uint8*)&multiData;

    DBG("AudioProcessorAmbika::sendMultiData");

    uint8 startSysex[7] = { 0x00, 0x21, 0x02, // (Manufacturer ID for Mutable Instruments)
        0x00,  0x04, // (Product ID for Ambika)
        0x04, // Command to send Multidata (Docs says 5 !)
        0x00 // // No argument
    };
    memcpy(sysexMessage, startSysex, 7);
    int index = 7;
    int checkSum = 0;

    for (int s = 0; s < 56; s++) {
        sysexMessage[index++] = patch[s] >> 4;
        sysexMessage[index++] = patch[s] & 0xf;

        checkSum = (checkSum + patch[s]) % 256;
    }

    sysexMessage[index++] = checkSum >> 4;
    sysexMessage[index++] = checkSum & 0xf;

    sendSysex(MidiMessage::createSysExMessage(sysexMessage, index));

    updateMidiChannelFromPart(md != nullptr ? md : &multiData);
};


void AudioProcessorAmbika::setStateParamSpecific(XmlElement* xmlState) {
    // Multi Data
    XmlElement* xmlMD = xmlState->getChildByName("MultiData");
    if (xmlMD != nullptr) {
        isMultiDataUsed = true;
        uint8* md = (uint8*)&multiData;
        // loadt MultiData
        for (int k = 0; k < 56; k++) {
            md[k] = xmlMD->getIntAttribute("MD_uint8_" + String(k));
        }
        updateMidiChannelFromPart(&multiData);

        if (audioProcessorEditor != nullptr) {
            ambikaMultiDataUI->setMultiDataUsed(true);
            const MessageManagerLock mmLock;
            ambikaMultiDataUI->setMultiData(&multiData);
        }
        sendMultiDataToAmbika((MultiData*) nullptr);
    }
    else {
        isMultiDataUsed = false;
    }
    if (audioProcessorEditor != nullptr) {
        ambikaMultiDataUI->setMultiDataUsed(isMultiDataUsed);
    }
    // Sequencer
    if (xmlState->hasAttribute("SequencerStep0")) {
        uint8* seq = (uint8*)&sequencer;
        for (int s = 0; s < 16; s++) {
            int stepValue = xmlState->getIntAttribute("SequencerStep" + String(s));
            seq[s * 4] = (stepValue >> 24) & 0xff;
            seq[s * 4 + 1] = (stepValue >> 16) & 0xff;
            seq[s * 4 + 2] = (stepValue >> 8) & 0xff;
            seq[s * 4 + 3] = stepValue & 0xff;
        }

        if (sequencerUI != nullptr) {
            sequencerUI->setSequencerData((uint8*)&sequencer);
        }
        for (int d = 0; d < 4; d++) {
            DBG(">SET Note " << d << " : " << sequencer.seqNotes[d].getNote() << " velocity: " << sequencer.seqNotes[d].getVelocity());
        }
        sendSequencerToSynth((uint8*)nullptr);
    }
}

void AudioProcessorAmbika::getStateParamSpecific(XmlElement* xml) {

    if (isMultiDataUsed) {
        // If UI update with latest version
        if (audioProcessorEditor != nullptr) {
            setMultiData(ambikaMultiDataUI->getMultiData());
        }

        XmlElement* xmlMultiDataElement = new XmlElement("MultiData");

        // update MultiData
        uint8* md = (uint8*)&multiData;
        for (int k = 0; k < 56; k++) {
            xmlMultiDataElement->setAttribute("MD_uint8_" + String(k), md[k]);
        }
        xml->addChildElement(xmlMultiDataElement);
    }

    for (int d = 0; d < 4; d++) {
        DBG("<GET Note " << d << " : " << sequencer.seqNotes[d].getNote() << " velocity: " << sequencer.seqNotes[d].getVelocity());
    }
    uint8* seq = (uint8*)&sequencer;
    for (int s = 0; s < 16; s++) {
        xml->setAttribute("SequencerStep" + String(s), (seq[s * 4] << 24) + (seq[s * 4 + 1] << 16) + (seq[s * 4 + 2] << 8) + seq[s * 4 + 3]);
    }

}

void AudioProcessorAmbika::choseNewMidiDevice() {
    int newDeviceNumber = midiDevice->openChoseDeviceWindow(midiDeviceNumber);
    if (newDeviceNumber >= 0) {
        midiDeviceNumber = newDeviceNumber;
        requestMultiDataTransfer();
    }
}

void AudioProcessorAmbika::setMultiDataUsed(bool mdu) {
    isMultiDataUsed = mdu;
}

void AudioProcessorAmbika::setMultiData(MultiData* md) {
    uint8* source = (uint8*)md;
    uint8* dest = (uint8*)&multiData;
    // loadt MultiData
    for (int k = 0; k < 56; k++) {
        dest[k] = source[k];
    }
}

void AudioProcessorAmbika::createEditorSpecific(AudioProcessorEditor* audioProcessorEditor) {
    ambikaMultiDataUI->setMultiDataUsed(isMultiDataUsed);
    if (isMultiDataUsed) {
        ambikaMultiDataUI->setMultiData(&multiData);
    }
};

void AudioProcessorAmbika::sendPatchToSynth() {

    // For Ambika we consider the 16 first params of PartData is part of the synth
    // So we flush thos 16 params that have been read just before in AudioProcessorCommon
    const OwnedArray< AudioProcessorParameter >&parameterSet = getParameters();
    for (int p = 112; p < 112 + 16; p++) {
        int index = nrpmIndex[p];
        MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[index];
        midifiedFP->addNrpn(midiOutBuffer, currentMidiChannel);
        flushMidiOut();
    }



    // SEND SYSEX
    uint8 sysexMessage[512];
    uint8 patch[256];

    encodeSysexPatch(patch);

    uint8 startSysex[7] = { 0x00, 0x21, 0x02, // (Manufacturer ID for Mutable Instruments)
        0x00,  0x04, // (Product ID for Ambika)
        0x01, // Command to send patch
        (uint8)currentPart // Send to CurrentPart !!!!
    };

    memcpy(sysexMessage, startSysex, 7);
    int index = 7;
    int checkSum = 0;

    for (int s = 0; s < 112; s++) {
        sysexMessage[index++] = patch[s] >> 4;
        sysexMessage[index++] = patch[s] & 0xf;

        checkSum = (checkSum + patch[s]) % 256;
    }

    sysexMessage[index++] = checkSum >> 4;
    sysexMessage[index++] = checkSum & 0xf;

    sendSysex(MidiMessage::createSysExMessage(sysexMessage, index));

}


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    AudioProcessorAmbika* audioProcessor = new AudioProcessorAmbika();
    audioProcessor->initAllParameters();
    return (AudioProcessor*)audioProcessor;
}
#endif

