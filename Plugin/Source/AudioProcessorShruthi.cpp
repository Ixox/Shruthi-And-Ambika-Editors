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

#ifdef SHRUTHI

#include "AudioProcessorShruthi.h"

AudioProcessorShruthi::AudioProcessorShruthi()
    : AudioProcessorCommon() 
{
    for (int k = 0; k < 16; k++) {
        steps[k].data_[0] = 0;
        steps[k].data_[1] = 0;
        steps[k].set_note(36 + ((k * 2) % 16));
        steps[k].set_gate((k % 2) == 0);
        steps[k].set_velocity((7 - (k%2)*5) << 4);
        steps[k].set_controller(5 + ((k *2) % 7));
    }
    filterType = 0;
}




char AudioProcessorShruthi::sysexMachineCode() {
    return 0x02;
}

void AudioProcessorShruthi::initAllParameters() {
    int nrpmParam;
    // ================== OSC1 ===========================================================================
    //Oscillator 1 shape        0 - 34         0    20
    nrpmParam = 0;
    MidifiedFloatParameter* newParam = new MidifiedFloatParameter(String("Osc1 Shape"), nrpmParam, 1, 0, 34, 1);
    addMidifiedParameter(newParam);
    ccIndex[20] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;
    //Oscillator 1 parameter    0 - 127        1    21
    nrpmParam = 1;
    newParam = new MidifiedFloatParameter(String("Osc1 Param"), nrpmParam, 1, 0, 127, 0);
    addMidifiedParameter(newParam);
    ccIndex[21] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;
    //Oscillator 1 range        - 24 - 24      2    22
    nrpmParam = 2;
    newParam = new MidifiedFloatParameter(String("Osc1 Range"), nrpmParam, 1, -24, 24, 0);
    addMidifiedParameter(newParam);
    ccIndex[22] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;
    //Modulation operator       0 - 13         3    28
    nrpmParam = 3;
    newParam = new MidifiedFloatParameter(String("Modulation Operator"), nrpmParam, 1, 0, 13, 0);
    addMidifiedParameter(newParam);
    ccIndex[28] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    // ================== OSC2 ===========================================================================      
    //Oscillator 2 shape0 - 34	4	24
    nrpmParam = 4;
    newParam = new MidifiedFloatParameter(String("Osc2 Shape"), nrpmParam, 1, 0, 34, 2);
    addMidifiedParameter(newParam);
    ccIndex[24] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;
    //Oscillator 2 parameter	0 - 127	5	25
    nrpmParam = 5;
    newParam = new MidifiedFloatParameter(String("Osc2 Param"), nrpmParam, 1, 0, 127, 0);
    addMidifiedParameter(newParam);
    ccIndex[25] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //Oscillator 2 range - 24 - 24	6	26
    nrpmParam = 6;
    newParam = new MidifiedFloatParameter(String("Osc2 Range"), nrpmParam, 1, -24, 24, 0);
    addMidifiedParameter(newParam);
    ccIndex[26] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //Oscillator 2 detune	0 - 127	7	27
    nrpmParam = 7;
    newParam = new MidifiedFloatParameter(String("Osc2 Detune"), nrpmParam, 1, 0, 127, 0);
    addMidifiedParameter(newParam);
    ccIndex[27] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    // ================== MIX ===========================================================================
    //Oscillator balance	0 - 63	8	29
    nrpmParam = 8;
    newParam = new MidifiedFloatParameter(String("Oscillator balance"), nrpmParam, 1, 0, 63, 32);
    addMidifiedParameter(newParam);
    ccIndex[29] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;


    //Sub oscillator volume	0 - 63	9	30
    nrpmParam = 9;
    newParam = new MidifiedFloatParameter(String("Sub oscillator volume"), nrpmParam, 1, 0, 63, 32);
    addMidifiedParameter(newParam);
    ccIndex[30] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //Noise volume	0 - 63	10	31
    nrpmParam = 10;
    newParam = new MidifiedFloatParameter(String("Noise volume"), nrpmParam, 1, 0, 63, 0);
    addMidifiedParameter(newParam);
    ccIndex[31] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //Sub oscillator / transient generator shape	0 - 10	11	23
    nrpmParam = 11;
    newParam = new MidifiedFloatParameter(String("Osc1 SubClick"), nrpmParam, 1, 0, 10, 0);
    addMidifiedParameter(newParam);
    ccIndex[23] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    // ================== FILTER ===========================================================================
    //Filter cutoff	0 - 127	12	14, 74
    nrpmParam = 12;
    newParam = new MidifiedFloatParameter(String("Filter Cutoff"), nrpmParam, 1, 0, 127, 63);
    addMidifiedParameter(newParam);
    ccIndex[14] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;
    //Filter resonance	0 - 63	13	15, 71
    nrpmParam = 13;
    newParam = new MidifiedFloatParameter(String("Filter Resonnance"), nrpmParam, 1, 0, 63, 0);
    addMidifiedParameter(newParam);
    ccIndex[15] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;
    //Envelope->cutoff modulation amount	0 - 63	14	102
    nrpmParam = 14;
    newParam = new MidifiedFloatParameter(String("Filter Env"), nrpmParam, 1, 0, 63, 0);
    addMidifiedParameter(newParam);
    ccIndex[102] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;
    //Lfo->cutoff modulation amount	0 - 63	15	103
    nrpmParam = 15;
    newParam = new MidifiedFloatParameter(String("Filter Lfo"), nrpmParam, 1, 0, 63, 0);
    addMidifiedParameter(newParam);
    ccIndex[103] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;


    // ============================================= SVF ==============================

    //addAndMakeVisible(filterSVFCutoff = new SliderPfm2("Filter2 Cutoff"));
    //addAndMakeVisible(filterSVFResonnance = new SliderPfm2("Filter2 Resonnance"));
    //addAndMakeVisible(filterSVFMode1Label = new Label("Filter2 Mode1", "Filter1 Mode"));
    //addAndMakeVisible(filterSVFMode2 = new ComboBox("Filter2 Mode"));


    //SVF Filter cutoff 2 12
    nrpmParam = NRPN_VIRTUAL_FILTER2_CUTOFF;
    newParam = new MidifiedFloatParameter(String("FilterSVF Cutoff"), nrpmParam, 1, 0, 127, 63);
    newParam->setUseThisCC(12);
    addMidifiedParameter(newParam);
    ccIndex[12] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //SVF Filter resonance 2 13
    nrpmParam = NRPN_VIRTUAL_FILTER2_RESONNANCE;
    newParam = new MidifiedFloatParameter(String("FilterSVF Resonnance"), nrpmParam, 1, 0, 63, 0);
    newParam->setUseThisCC(13);
    addMidifiedParameter(newParam);
    ccIndex[13] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //SVF Filter mode 1 85
    nrpmParam = NRPN_VIRTUAL_FILTER1_MODE;
    // Force CC for this param
    newParam = new MidifiedFloatParameter(String("FilterSVF Mode1"), nrpmParam, 1, 0, 5, 0);
    newParam->setUseThisCC(85);
    addMidifiedParameter(newParam);
    ccIndex[85] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //SVF Filter mode 2 86
    nrpmParam = NRPN_VIRTUAL_FILTER2_MODE;
    // Force CC for this param
    newParam = new MidifiedFloatParameter(String("FilterSVF Mode2"), nrpmParam, 1, 0, 5, 0);
    newParam->setUseThisCC(86);
    addMidifiedParameter(newParam);
    ccIndex[86] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;


    // ============================================= 4PM ==============================
    //addAndMakeVisible(filter4PMMode = new ComboBox("Filter4PM Mode"));
    //addAndMakeVisible(filter4PMFlavor = new ComboBox("Filter4PM Flavor"));
    nrpmParam = NRPN_VIRTUAL_4PM_MODE;
    // Force CC for this param
    newParam = new MidifiedFloatParameter(String("Filter4PM Mode"), nrpmParam, 1, 0, 14, 0);
    newParam->setUseThisCC(92);
    addMidifiedParameter(newParam);
    ccIndex[92] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    nrpmParam = NRPN_VIRTUAL_4PM_FLAVOR;
    // Force CC for this param
    newParam = new MidifiedFloatParameter(String("Filter4PM Flavor"), nrpmParam, 1, 0, 3, 0);
    newParam->setUseThisCC(93);
    addMidifiedParameter(newParam);
    ccIndex[93] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;


    for (int e = 0; e < 2; e++) {
        // " Attk", " Deca", " Sust", " Rele"
        //Envelope 1 attack 0 - 127 16 104
        //Envelope 2 attack 0 - 127 20 108, 73
        nrpmParam = 16 + e * 4;
        newParam = new MidifiedFloatParameter("Env" + String(e + 1) + " Attk", nrpmParam, 1, 0, 127, 5);
        addMidifiedParameter(newParam);
        ccIndex[104 + e * 4] = parameterIndex;
        nrpmIndex[nrpmParam] = parameterIndex++;


        //Envelope 1 decay 0 - 127 17 105
        //Envelope 2 decay 0 - 127 21 109
        nrpmParam = 17 + e * 4;
        newParam = new MidifiedFloatParameter("Env" + String(e + 1) + " Deca", nrpmParam, 1, 0, 127, 5);
        addMidifiedParameter(newParam);
        ccIndex[105 + e * 4] = parameterIndex;
        nrpmIndex[nrpmParam] = parameterIndex++;


        //Envelope 1 sustain 0 - 127 18 106
        //Envelope 2 sustain 0 - 127 22 110
        nrpmParam = 18 + e * 4;
        newParam = new MidifiedFloatParameter("Env" + String(e + 1) + " Sust", nrpmParam, 1, 0, 127, 63);
        addMidifiedParameter(newParam);
        ccIndex[106 + e * 4] = parameterIndex;
        nrpmIndex[nrpmParam] = parameterIndex++;

        //Envelope 1 release 0 - 127 19 107
        //Envelope 2 release 0 - 127 23 111
        nrpmParam = 19 + e * 4;
        newParam = new MidifiedFloatParameter("Env" + String(e + 1) + " Rele", nrpmParam, 1, 0, 127, 10);
        addMidifiedParameter(newParam);
        ccIndex[107 + e * 4] = parameterIndex;
        nrpmIndex[nrpmParam] = parameterIndex++;
    }

    // MATRIX
    const char* matrixSourceNames[] = {
        "Lfo 1","Lfo 2","Sequencer","Seq 1","Seq 2","Arpegiator","M Wheel","Aftertouch","Bender",
        "Offset","cv1","cv2","cv3","cv4","ccA (16)","ccB (17)","Bre (18)","Ped (19)","Noise",
        "Envelope 1","Envelope 2","Velocity","Random","Note","Gate","Audio","Operator 1","Operator 2", nullptr
    };

    // 27
    const char* matrixDestNames[] = {
        "Pwm1","Pwm2","Osc 1","Osc 2","Osc 1+2","Osc 1+2 fine","Mix","Noise","Sub Osc","Cutoff","Resonnance",
        "Vca","Cv1", "Cv2",
        "Env1 trigger","Env1 Attk","Env1 Dec","Env1 Sust","Env1 Rel","Env2 trigger","Env2 Attk",
        "Env2 Dec","Env2 Sust", "Env2 Rel","Env1+2 Attk","Lfo1 Rate","Lfo2 Rate",
        nullptr
    };

    const int defaultSources[12] = { 0,0,1,1,1,2,21,21,20,21,8,0 };
    const int defaultAmount[12] = { 0,0,0,0,0,0,0,0,63,16,32,16 };
    // Destination are not in the right order
    const int matrixDestValue[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 11, 1, 12, 13, 17, 19, 20, 21, 22, 18, 23, 24, 25, 26, 14, 15, 16 };
    const int defaultTarget[12] = { 2,3,0,1,6,6,0,1,11,11,4,4 };


    for (int r = 0; r < 12; r++) {
        //addAndMakeVisible(matrixSource[r] = new ComboBox("Mtx" + String(r + 1) + " Source"));
        nrpmParam = 32 + r * 3;
        newParam = new MidifiedFloatParameter("Mtx" + String(r + 1) + " Source", nrpmParam, 1, 0, 28, defaultSources[r]);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
        //addAndMakeVisible(matrixDestination[r] = new ComboBox("Mtx" + String(r + 1) + " Destination"));
        nrpmParam = 33 + r * 3;
        newParam = new MidifiedFloatParameter("Mtx" + String(r + 1) + " Destination", nrpmParam, 1, 0, 27, matrixDestValue[defaultTarget[r]]);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
        //addAndMakeVisible(matrixMultipler[r] = new SliderPfm2("Mtx" + String(r + 1) + " Multiplier"));
        nrpmParam = 34 + r * 3;
        newParam = new MidifiedFloatParameter("Mtx" + String(r + 1) + " Multiplier", nrpmParam, 1, -63, 63, defaultAmount[r]);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
    }

    // OPERATORS
    for (int r = 0; r < 2; r++) {
        nrpmParam = 94 + r * 3;
        newParam = new MidifiedFloatParameter("Op" + String(r + 1) + " Source1", nrpmParam, 1, 0, 31, 0);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
        nrpmParam = 95 + r * 3;
        newParam = new MidifiedFloatParameter("Op" + String(r + 1) + " Source2", nrpmParam, 1, 0, 31, 0);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
        nrpmParam = 96 + r * 3;
        newParam = new MidifiedFloatParameter("Op" + String(r + 1) + " Out", nrpmParam, 1, 03, 9, 0);
        addMidifiedParameter(newParam);
        nrpmIndex[nrpmParam] = parameterIndex++;
    }
    // LFO !!!!!
    for (int l = 0; l < 2; l++) {
        //addAndMakeVisible(lfoShape[l] = new ComboBox("Lfo" + String(l + 1) + " Shape"));
        nrpmParam = 24 + l * 4;
        newParam = new MidifiedFloatParameter("Lfo" + String(l + 1) + " Shape", nrpmParam, 1, 0, 21, 0);
        addMidifiedParameter(newParam);
        ccIndex[112 + l * 4] = parameterIndex;
        nrpmIndex[nrpmParam] = parameterIndex++;
        //addAndMakeVisible(lfoShape[l] = new ComboBox("Lfo" + String(l + 1) + " Rate"));
        nrpmParam = 25 + l * 4;
        newParam = new MidifiedFloatParameter("Lfo" + String(l + 1) + " Rate", nrpmParam, 1, 0, 144, 20);
        addMidifiedParameter(newParam);
        ccIndex[113 + l * 4] = parameterIndex;
        nrpmIndex[nrpmParam] = parameterIndex++;
        //addAndMakeVisible(lfoAttack[l] = new SliderPfm2("Lfo" + String(l + 1) + " Attack"));
        nrpmParam = 26 + l * 4;
        newParam = new MidifiedFloatParameter("Lfo" + String(l + 1) + " Attack", nrpmParam, 1, 0, 127, 0);
        addMidifiedParameter(newParam);
        ccIndex[114 + l * 4] = parameterIndex;
        nrpmIndex[nrpmParam] = parameterIndex++;
        //addAndMakeVisible(lfoMode[l] = new ComboBox("Lfo" + String(l + 1) + " Mode"));
        nrpmParam = 27 + l * 4;
        newParam = new MidifiedFloatParameter("Lfo" + String(l + 1) + " Mode", nrpmParam, 1, 0, 4, 0);
        addMidifiedParameter(newParam);
        ccIndex[115 + l * 4] = parameterIndex;
        nrpmIndex[nrpmParam] = parameterIndex++;
    }


    //addAndMakeVisible(seqMode = new ComboBox("Seq Mode"));
    //Sequencer mode 0 - 2 100 75
    nrpmParam = 100;
    newParam = new MidifiedFloatParameter("Seq Mode", nrpmParam, 1, 0, 2, 0);
    addMidifiedParameter(newParam);
    ccIndex[75] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //addAndMakeVisible(seqBpm = new ComboAndSlider("Seq Bpm"));
    //Tempo 35 - 248 101
    nrpmParam = 101;
    newParam = new MidifiedFloatParameter("Seq Bpm", nrpmParam, 1, 38, 240, 90);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;

    //    addAndMakeVisible(seqGroove = new ComboBox("Seq Groove"));
    //Groove template 0 - 5 102 76
    nrpmParam = 102;
    newParam = new MidifiedFloatParameter("Seq Groove", nrpmParam, 1, 0, 5, 0);
    addMidifiedParameter(newParam);
    ccIndex[76] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //addAndMakeVisible(seqAmount = new SliderPfm2("Seq Amount"));
    //Groove amount 0 - 127 103 77
    nrpmParam = 103;
    newParam = new MidifiedFloatParameter("Seq Amount", nrpmParam, 1, 0, 127, 0);
    addMidifiedParameter(newParam);
    ccIndex[77] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //addAndMakeVisible(seqDirection = new ComboBox("Seq Direction"));
    //Arpeggiator direction 0 - 3 104 78
    nrpmParam = 104;
    newParam = new MidifiedFloatParameter("Seq Direction", nrpmParam, 1, 0, 4, 0);
    addMidifiedParameter(newParam);
    ccIndex[78] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //addAndMakeVisible(seqRange = new SliderPfm2("Seq Range"));
    //Arpeggiator range 1 - 4 105 79
    nrpmParam = 105;
    newParam = new MidifiedFloatParameter("Seq Range", nrpmParam, 1, 1, 4, 0);
    addMidifiedParameter(newParam);
    ccIndex[79] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //addAndMakeVisible(seqPattern = new ComboBox("Seq Pattern"));
    //Arpeggiator pattern 0 - 15 106 80
    nrpmParam = 106;
    newParam = new MidifiedFloatParameter("Seq Pattern", nrpmParam, 1, 0, 15, 0);
    addMidifiedParameter(newParam);
    ccIndex[80] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //addAndMakeVisible(seqDivision = new ComboBox("Seq Division"));
    //Sequencer clock division 0 - 11 107 81
    nrpmParam = 107;
    newParam = new MidifiedFloatParameter("Seq Division", nrpmParam, 1, 0, 11, 9);
    addMidifiedParameter(newParam);
    ccIndex[81] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    // "Seq NumberOfSteps"

    nrpmParam = 108;
    newParam = new MidifiedFloatParameter("Seq NumberOfSteps", nrpmParam, 1, 1, 16, 16);
    addMidifiedParameter(newParam);
    nrpmIndex[nrpmParam] = parameterIndex++;


    //Legato 0 - 1 68
    nrpmParam = NRPN_VIRTUAL_LEGATO;
    newParam = new MidifiedFloatParameter("Tuning Legato", nrpmParam, 1, 0, 1, 0);
    newParam->setUseThisCC(68);
    addMidifiedParameter(newParam);
    ccIndex[68] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //Portamento 0 - 63 84
    nrpmParam = NRPN_VIRTUAL_PORTAMENTO;
    newParam = new MidifiedFloatParameter("Tuning Portamento", nrpmParam, 1, 0, 63, 0);
    newParam->setUseThisCC(84);
    addMidifiedParameter(newParam);
    ccIndex[84] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

}


void AudioProcessorShruthi::encodeSysexPatch(uint8* patch) {
    const OwnedArray< AudioProcessorParameter >&parameterSet = getParameters();

    MidifiedFloatParameter* midifiedFP;

    for (int b = 0; b < 68; b++) {
        int index = nrpmIndex[b];
        if (index == -1) {
            DBG("nrpmIndex[" << b << "] IS MISSING !!!!!!!");
            continue;
        }
        MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[index];

        patch[b] = midifiedFP->getRealValue();
        uint8 byte = patch[b * 2] * 0x10 + patch[b * 2 + 1];
    }

    // 68 - 75 : preset name
    char presetNameChar[8];
    memset(presetNameChar, ' ', 8);
    for (int s = 0; s < presetName.length(); s++) {
        presetNameChar[s] = presetName.getCharPointer()[s];
    }
    for (int b = 68; b < 76; b++) {
        patch[b] = presetNameChar[b - 68];
    }

    // 76 - 83 : Arpegiator 
    uint8 extra_data_[8];

    //Legato 0 - 1 68
    //Portamento 0 - 63 84
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_LEGATO]];
    extra_data_[0] = midifiedFP->getRealValue() > 0 ? 0x40 : 0x00;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_PORTAMENTO]];
    extra_data_[0] |= (uint8)midifiedFP->getRealValue();

    //extra_data_[1] = sequencer_settings.seq_mode;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[100]];
    extra_data_[1] = midifiedFP->getRealValue();

    //extra_data_[2] = sequencer_settings.seq_tempo;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[101]];
    extra_data_[2] = midifiedFP->getRealValue();

    //extra_data_[3] = sequencer_settings.seq_groove_template;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[102]];
    extra_data_[3] = midifiedFP->getRealValue();

    //extra_data_[4] = sequencer_settings.seq_groove_amount;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[103]];
    extra_data_[4] = midifiedFP->getRealValue();

    //extra_data_[5] = (sequencer_settings.arp_direction << 4) |  sequencer_settings.arp_range;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[104]];
    extra_data_[5] = (int)midifiedFP->getRealValue() << 4;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[105]];
    extra_data_[5] |= (int)midifiedFP->getRealValue();;

    //extra_data_[6] = sequencer_settings.arp_pattern;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[106]];
    extra_data_[6] = midifiedFP->getRealValue();

    //extra_data_[7] = sequencer_settings.arp_clock_division;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[107]];
    extra_data_[7] = midifiedFP->getRealValue();
    for (int b = 76; b < 84; b++) {
        patch[b] = extra_data_[b - 76];
    }

    // 84 - 85 :   uint8_t filter_cutoff_2 uint8_t filter_resonance_2;
    for (int b = 84; b < 86; b++) {
        uint8 byte = patch[b * 2] * 0x10 + patch[b * 2 + 1];
        int index = nrpmIndex[NRPN_VIRTUAL_FILTER2_CUTOFF + b - 84];
        MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[index];
        patch[b] = midifiedFP->getRealValue();
    }

    if (filterType == 1) {
        // 86 : SVF Filter
        midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_FILTER1_MODE]];
        patch[86] = (uint8)((int)midifiedFP->getRealValue() << 4);
        midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_FILTER2_MODE]];
        patch[86] |= (uint8)((int)midifiedFP->getRealValue() & 0xff);
    }
    else if (filterType == 2) {
        // 4PM
        midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_4PM_MODE]];
        patch[86] = (uint8)((int)midifiedFP->getRealValue() << 4);
        midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_4PM_FLAVOR]];
        patch[86] |= (uint8)((int)midifiedFP->getRealValue() & 0xff);
    }

    // 87 - 91 : OPERATORS
    uint8 op_data_[4];
    for (int o = 0; o < 2; o++) {
        // From SHRUTHI Code !
        MidifiedFloatParameter* midifiedFP1 = (MidifiedFloatParameter*)parameterSet[nrpmIndex[94 + 3 * o]];
        MidifiedFloatParameter* midifiedFP2 = (MidifiedFloatParameter*)parameterSet[nrpmIndex[95 + 3 * o]];
        MidifiedFloatParameter* midifiedFP3 = (MidifiedFloatParameter*)parameterSet[nrpmIndex[96 + 3 * o]];

        op_data_[o * 2] = (uint8)midifiedFP1->getRealValue();
        op_data_[o * 2 + 1] = (uint8)(((int)midifiedFP2->getRealValue() << 3) | ((int)midifiedFP3->getRealValue() & 0x7));
    }
    for (int b = 87; b < 91; b++) {
        patch[b] = op_data_[b - 87];
    }
    patch[91] = '%';

}

void AudioProcessorShruthi::decodeSysexPatch(const uint8* patch) {
    if (!canReceiveSysexPatch) {
        return;
    }
    canReceiveSysexPatch = true;

    const OwnedArray< AudioProcessorParameter >&parameterSet = getParameters();
    MidifiedFloatParameter* midifiedFP;

    for (int b = 0; b < 68; b++) {
        int index = nrpmIndex[b];
        if (index == -1) {
            DBG("nrpmIndex[" << b << "] IS MISSING !!!!!!!");
            continue;
        }
        // DBG("SYSEX DECODE : b " << b << " / index : " << index);
        uint8 byte = patch[b * 2] * 0x10 + patch[b * 2 + 1];
        MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[index];
        midifiedFP->setValueFromNrpn((int)byte);
    }

    // 68 - 75 : preset name
    presetName = "";
    for (int p = 0; p < 8; p++) {
        presetName += (char)(patch[(68 + p) * 2] * 0x10 + patch[(68 + p) * 2 + 1]);
    }
    DBG("PRESET NAME : '" << presetName << "' size : " << presetName.length());

    // 76 - 83 : Arpegiator 
    uint8 extra_data_[8];
    for (int b = 76; b < 84; b++) {
        extra_data_[b - 76] = patch[b * 2] * 0x10 + patch[b * 2 + 1];
    }
    // extra_data_[0] = system_settings.legato ? 0x40 : 0x00;
    // extra_data_[0] |= system_settings.portamento;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_LEGATO]];
    midifiedFP->setValueFromNrpn((extra_data_[0] & 0x40) > 0 ? 1 : 0);
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_PORTAMENTO]];
    midifiedFP->setValueFromNrpn(extra_data_[0] & 0x3f);

    //extra_data_[1] = sequencer_settings.seq_mode;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[100]];
    midifiedFP->setValueFromNrpn(extra_data_[1]);

    //extra_data_[2] = sequencer_settings.seq_tempo;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[101]];
    midifiedFP->setValueFromNrpn(extra_data_[2]);

    //extra_data_[3] = sequencer_settings.seq_groove_template;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[102]];
    midifiedFP->setValueFromNrpn(extra_data_[3]);

    //extra_data_[4] = sequencer_settings.seq_groove_amount;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[103]];
    midifiedFP->setValueFromNrpn(extra_data_[4]);

    //extra_data_[5] = (sequencer_settings.arp_direction << 4) |  sequencer_settings.arp_range;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[104]];
    midifiedFP->setValueFromNrpn(extra_data_[5] >> 4);
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[105]];
    midifiedFP->setValueFromNrpn(extra_data_[5] & 0xf);

    //extra_data_[6] = sequencer_settings.arp_pattern;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[106]];
    midifiedFP->setValueFromNrpn(extra_data_[6]);

    //extra_data_[7] = sequencer_settings.arp_clock_division;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[107]];
    midifiedFP->setValueFromNrpn(extra_data_[7]);



    if (filterType == 1) {
        // 86 : SVF Filter
        // 84 - 85 :   uint8_t filter_cutoff_2 uint8_t filter_resonance_2;
        for (int b = 84; b < 86; b++) {
            uint8 byte = patch[b * 2] * 0x10 + patch[b * 2 + 1];
            int index = nrpmIndex[NRPN_VIRTUAL_FILTER2_CUTOFF + b - 84];
            MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[index];
            midifiedFP->setValueFromNrpn((int)byte);
        }

        uint8 filter_topology_ = patch[86 * 2] * 0x10 + patch[86 * 2 + 1];
        uint8 filter_1_mode_ = filter_topology_ >> 4;
        midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_FILTER1_MODE]];
        midifiedFP->setValueFromNrpn(filter_1_mode_);
        uint8 filter_2_mode_ = filter_topology_ & 0xf;
        midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_FILTER2_MODE]];
        midifiedFP->setValueFromNrpn(filter_2_mode_);
    }
    else if (filterType == 2) {
        // 4PM
        uint8 filter_topology_ = patch[86 * 2] * 0x10 + patch[86 * 2 + 1];
        uint8 filter_mode = filter_topology_ >> 4;
        midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_4PM_MODE]];
        midifiedFP->setValueFromNrpn(filter_mode);
        uint8 filter_flavor = filter_topology_ & 0xf;
        midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_4PM_FLAVOR]];
        midifiedFP->setValueFromNrpn(filter_flavor);
    }

    // 87 - 91 : OPERATORS
    uint8 op_data_[4];
    for (int b = 87; b < 91; b++) {
        op_data_[b - 87] = patch[b * 2] * 0x10 + patch[b * 2 + 1];
    }
    for (int o = 0; o < 2; o++) {
        // From SHRUTHI Code !
        int opSource1 = op_data_[0 + o * 2] & 0x3f;
        int opSource2 = op_data_[1 + o * 2] >> 3;
        int opOut = op_data_[1 + o * 2] & 0x7;
        if (op_data_[0 + o * 2] & 0x80) {
            opOut |= 0x8;
        }
        if (op_data_[0 + o * 2] & 0x40) {
            opSource1 |= 0x20;
        }

        MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[94 + 3 * o]];
        midifiedFP->setValueFromNrpn(opSource1);

        midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[95 + 3 * o]];
        midifiedFP->setValueFromNrpn(opSource2);

        midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[96 + 3 * o]];
        midifiedFP->setValueFromNrpn(opOut);
    }


    redrawUI();
}


String AudioProcessorShruthi::getSynthName() {
    return "Shruthi";
}

void AudioProcessorShruthi::requestPatchTransfer() {
    char command[] = { 0x00, 0x21, 0x02, 0x00, 0x02, 0x11, 0x00, 0x00, 0x00 };
    sendSysex(MidiMessage::createSysExMessage(command, 9));
    canReceiveSysexPatch = true;
}

void AudioProcessorShruthi::requestSequencerTransfer() {
    char command[] = { 0x00, 0x21, 0x02, 0x00, 0x02, 0x12, 0x00, 0x00, 0x00 };
    sendSysex(MidiMessage::createSysExMessage(command, 9));
    canReceiveSysexSequencer = true;
}

void AudioProcessorShruthi::sendSequencerToSynth(uint8* sequencer) {

    if (sequencer != nullptr) {
        for (int s = 0; s < 16; s++) {
            steps[s].data_[0] = sequencer[s * 2];
            steps[s].data_[1] = sequencer[s * 2 + 1];
        }
    }

    // SEND SYSEX
    DBG(" SEND SYSEX --------------------------");
    uint8 message[128];
    uint8 startSysex[7] = { 0x00, 0x21, 0x02, // (Manufacturer ID for Mutable Instruments)
    0x00,  0x02, // (Product ID for Shruthi)
    0x02, // Command to send sequencer
    0x00 // // No argument
    };
    memcpy(message, startSysex, 7);
    int index = 7;
    int checkSum = 0;
    for (int s = 0; s < 16; s++) {
        uint8 data1 = steps[s].data_[0];
        uint8 data2 = steps[s].data_[1];

        message[index++] = data1 >> 4;
        message[index++] = data1 & 0xf;
        message[index++] = data2 >> 4;
        message[index++] = data2 & 0xf;
        checkSum = (checkSum + data1 + data2) % 256;

        DBG(" SEND SYSEX : s " << s << " data 1 : " << data1 << " data 2 " << data2);
    }
    message[index++] = checkSum >> 4;
    message[index++] = checkSum & 0xf;

    sendSysex(MidiMessage::createSysExMessage(message, index));
}
void AudioProcessorShruthi::decodeSysexSequencer(const uint8* sysexSteps) {
    if (!canReceiveSysexSequencer) {
        return;
    }
    canReceiveSysexSequencer = true;

    DBG("YEAH NEW SHRUTHI SEQUENCER!!!");
    for (int b = 0; b < 16; b++) {
        steps[b].data_[0] = sysexSteps[b * 4] * 0x10 + sysexSteps[b * 4 + 1];
        steps[b].data_[1] = sysexSteps[b * 4 + 2] * 0x10 + sysexSteps[b * 4 + 3];
    }
    const MessageManagerLock mmLock;
    if (sequencerUI != nullptr) {
        sequencerUI->setSequencerData((uint8*)steps);
    }
}


void AudioProcessorShruthi::setStateParamSpecific(XmlElement* xmlState) {
    currentMidiChannel = xmlState->getIntAttribute("CurrentMidiChannel", 1);
    settingsChangedForUI();

    int filterType = xmlState->getIntAttribute("FilterType");
    if (audioProcessorEditor != nullptr) {
        filterTypeUI->setFitlerType(filterType);
    }

    if (xmlState->hasAttribute("SequencerStep0")) {
        for (int s = 0; s < 8; s++) {
            int stepValue = xmlState->getIntAttribute("SequencerStep" + String(s));
            steps[s * 2].data_[0] = (stepValue >> 24) & 0xff;
            steps[s * 2].data_[1] = (stepValue >> 16) & 0xff;
            steps[s * 2 + 1].data_[0] = (stepValue >> 8) & 0xff;
            steps[s * 2 + 1].data_[1] = stepValue & 0xff;
        }
        if (sequencerUI != nullptr) {
            sequencerUI->setSequencerData((uint8*)steps);
        }
        sendSequencerToSynth((uint8*)nullptr);
    }
}

void AudioProcessorShruthi::getStateParamSpecific(XmlElement* xml) {
    xml->setAttribute("CurrentMidiChannel", currentMidiChannel);

    // If shruthi sequencer UI is open, let's use latest data
    if (sequencerUI != nullptr) {
        uint8 *currentSteps = sequencerUI->getSequencerData();
        for (int s = 0; s < 16; s++) {
            steps[s].data_[0] = currentSteps[s * 2];
            steps[s].data_[1] = currentSteps[s * 2 + 1];
        }
    }
    for (int s = 0; s < 8; s++) {
        xml->setAttribute("SequencerStep" + String(s), (steps[s * 2].data_[0] << 24) + (steps[s * 2].data_[1] << 16) + (steps[s * 2 + 1].data_[0] << 8) + steps[s * 2 + 1].data_[1]);
    }

    xml->setAttribute("FilterType", filterType);

}

void AudioProcessorShruthi::choseNewMidiDevice() {
    int newDeviceNumber = midiDevice->openChoseDeviceWindow(midiDeviceNumber);
    if (newDeviceNumber >= 0) {
        midiDeviceNumber = newDeviceNumber;
    }
}

void AudioProcessorShruthi::setFilterType(int ft) {
    filterType = ft;
    DBG("NEW FILTER TYPE...");
}

void AudioProcessorShruthi::setFilterTypeUI(FilterTypeUI* ftUI) {
    filterTypeUI = ftUI;
}


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    AudioProcessorShruthi* audioProcessor = new AudioProcessorShruthi();
    audioProcessor->initAllParameters();
    return (AudioProcessor*)audioProcessor;
}
#endif


