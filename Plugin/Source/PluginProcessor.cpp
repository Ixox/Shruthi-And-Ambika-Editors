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


#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "UI/MyLookAndFeel.h"




 //==============================================================================
ShruthiAudioProcessor::ShruthiAudioProcessor()
{
	myLookAndFeel = new MyLookAndFeel();
	LookAndFeel::setDefaultLookAndFeel(myLookAndFeel);

	// Register to midi device even if not initialized correctly
	pfm2MidiDevice->addListener(this);

	// Important !!!! reset paramIndexCounter.
	MidifiedFloatParameter::resetParamIndexCounter();

	shruthiEditor = nullptr;
	MidifiedFloatParameter* newParam;
	parameterIndex = 0;
    editorWidth = 0;
    editorHeight = 0;

	for (int k = 0; k < NRPN_VIRTUAL_MAX; k++) {
		nrpmIndex[k] = -1;
        ccIndex[k] = -1;
    }


	
	int nrpmParam;
    // ================== OSC1 ===========================================================================
    //Oscillator 1 shape        0 - 34         0    20
	nrpmParam = 0;
	newParam = new MidifiedFloatParameter(String("Osc1 Shape"), nrpmParam, 1, 0, 34, 1);
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
    newParam->setUseThisCC(86);
    addMidifiedParameter(newParam);
    ccIndex[12] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //SVF Filter resonance 2 13
    nrpmParam = NRPN_VIRTUAL_FILTER2_RESONNANCE;
    newParam = new MidifiedFloatParameter(String("FilterSVF Resonnance"), nrpmParam, 1, 0, 63, 0);
    newParam->setUseThisCC(86);
    addMidifiedParameter(newParam);
    ccIndex[13] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;

    //SVF Filter mode 1 85
    nrpmParam = NRPN_VIRTUAL_FILTER1_MODE;
    // Force CC for this param
    newParam->setUseThisCC(85);
    newParam = new MidifiedFloatParameter(String("FilterSVF Mode1"), nrpmParam, 1, 0, 5, 0);
    addMidifiedParameter(newParam);
    ccIndex[85] = parameterIndex;    
    nrpmIndex[nrpmParam] = parameterIndex++;

    //SVF Filter mode 2 86
    nrpmParam = NRPN_VIRTUAL_FILTER2_MODE;
    // Force CC for this param
    newParam->setUseThisCC(86);
    newParam = new MidifiedFloatParameter(String("FilterSVF Mode2"), nrpmParam, 1, 0, 5, 0);
    addMidifiedParameter(newParam);
    ccIndex[86] = parameterIndex;
    nrpmIndex[nrpmParam] = parameterIndex++;


    for (int e = 0; e < 2; e++) {
        // " Attk", " Deca", " Sust", " Rele"
        //Envelope 1 attack 0 - 127 16 104
        //Envelope 2 attack 0 - 127 20 108, 73
        nrpmParam = 16 + e*4;
        newParam = new MidifiedFloatParameter("Env" + String(e+1) + " Attk", nrpmParam, 1, 0, 127, 5);
        addMidifiedParameter(newParam);
        ccIndex[104 + e*4] = parameterIndex;
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
    const int defaultAmount[12] = {0,0,0,0,0,0,0,0,63,16,32,16};
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

    // ============================================================
    presetName = "No patch";


	// Midi Channel
	currentMidiChannel = 1;
    nrpmParam = NRPN_VIRTUAL_MIDI_CHANNEL;
	newParam = new MidifiedFloatParameter("Midi Channel", nrpmParam, 1, 0, 16, 1);
	newParam->setIsAutomatable(false);
	addMidifiedParameter(newParam);
	nrpmIndex[nrpmParam] = parameterIndex++;

	nrpmParam = NRPN_VIRTUAL_PUSH_BUTTON;
	newParam = new MidifiedFloatParameter("push button", nrpmParam, 1, 0, 127, 0);
	newParam->setIsAutomatable(false);
	addMidifiedParameter(newParam);
	// Put in last slot
	nrpmIndex[nrpmParam] = parameterIndex++;

	nrpmParam = NRPN_VIRTUAL_PULL_BUTTON;
	newParam = new MidifiedFloatParameter("pull button", nrpmParam, 1, 0, 127, 0);
	newParam->setIsAutomatable(false);
	addMidifiedParameter(newParam);
	// Put in last slot
	nrpmIndex[nrpmParam] = parameterIndex++;

	midiMessageCollector.reset(44100);


    // Sequencer init
    shruthiSequencer = nullptr;
    srand(time(NULL));
    for (int s = 0; s< 16; s++) {
        shruthiSteps[s].data_[0] = 48 + s + (s % 2 == 0 ? 0x80: 0);
        shruthiSteps[s].data_[1] = ((s % 3) == 2 ? 0x80 : 0) + (((7 + s) % 7) << 4) + (rand() % 15);
    }
}

ShruthiAudioProcessor::~ShruthiAudioProcessor()
{
	delete myLookAndFeel;

	pfm2MidiDevice->removeListener(this);

}

//==============================================================================
const String ShruthiAudioProcessor::getName() const
{
	return "preenfm2 Editor"; // JucePlugin_Name;
}


bool ShruthiAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool ShruthiAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

double ShruthiAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int ShruthiAudioProcessor::getNumPrograms()
{
	return 1;
}

int ShruthiAudioProcessor::getCurrentProgram()
{
	return 1;
}

void ShruthiAudioProcessor::setCurrentProgram(int index)
{
	// Nothing to do;
}

const String ShruthiAudioProcessor::getProgramName(int index)
{
	return presetName;
}

void ShruthiAudioProcessor::changeProgramName(int index, const String& newName)
{
	setPresetName(newName);
}

//==============================================================================
void ShruthiAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
}

void ShruthiAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}


void ShruthiAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{

	buffer.clear();

	if (midiMessages.getNumEvents() > 0 && pfm2MidiDevice->getMidiOutput() != nullptr) {
		MidiBuffer::Iterator i(midiMessages);
		MidiMessage message;
		int samplePosition; // Note: not actually used, so no need to initialise.
		newMidiNotes.clear();


		int now = Time::getMillisecondCounter();

		while (i.getNextEvent(message, samplePosition)) {
			if (message.getChannel() == currentMidiChannel) {
				//				DBG(message.getDescription());
				//				DBG("timestamp : " << message.getTimeStamp() << " / " << buffer.getNumSamples());
				newMidiNotes.addEvent(message, now);
			}
		}
		if (newMidiNotes.getNumEvents() > 0) {
			if (newMidiNotes.getNumEvents() > 1) {
				DBG("MIDI NOTES : " << newMidiNotes.getNumEvents());
			}
			pfm2MidiDevice->getMidiOutput()->sendBlockOfMessagesNow(newMidiNotes);
		}
	}

	midiMessages.clear();
}

//==============================================================================
bool ShruthiAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

void ShruthiAudioProcessor::editorClosed() {
    editorWidth = shruthiEditor->getWidth();
    editorHeight = shruthiEditor->getHeight();
    shruthiEditor = nullptr;
    shruthiSequencer = nullptr;    
}


AudioProcessorEditor* ShruthiAudioProcessor::createEditor()
{

	shruthiEditor = new ShruthiAudioProcessorEditor(this);
	shruthiEditor->setMidiChannel(currentMidiChannel);
	shruthiEditor->setMidiOutBuffer(&midiOutBuffer);
	shruthiEditor->setPresetName(presetName);
    if (editorWidth > 0 && editorHeight > 0) {
        shruthiEditor->setSize(editorWidth, editorHeight);
    }

    shruthiSequencer->setSequencerSteps(shruthiSteps);
	return shruthiEditor;
}

//==============================================================================
void ShruthiAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// Here's an example of how you can use XML to make it easy and more robust:

	// Create an outer XML element..
	XmlElement xml("ShruthiAppStatus");

	xml.setAttribute("presetName", presetName);

	// add some attributes to it..
	const OwnedArray< AudioProcessorParameter >&parameterSet = getParameters();
	for (int p = 0; p < parameterSet.size(); p++) {
		MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[p];
		xml.setAttribute(midifiedFP->getNameForXML(), midifiedFP->getRealValue());
	}
    
    // If shruthi sequencer UI is open, let's use latest data
    if (shruthiSequencer != nullptr) {
        shruthi::SequenceStep *currentSteps = shruthiSequencer->getSequencerSteps();
        for (int s = 0; s < 16; s++) {
            shruthiSteps[s] = currentSteps[s];
        }
    }

    for (int s = 0; s < 16; s++) {
        xml.setAttribute("SequencerStep" + String(s), (shruthiSteps[s].data_[0] << 8) + shruthiSteps[s].data_[1]);
    }

    // Update editorWidth and editorHeight
    if (shruthiEditor != nullptr) {
        editorWidth = shruthiEditor->getWidth();
        editorHeight = shruthiEditor->getHeight();
    }

    xml.setAttribute("EditorWidth", editorWidth);
    xml.setAttribute("EditorHeight", editorHeight);


	// then use this helper function to stuff it into the binary blob and return it..
	copyXmlToBinary(xml, destData);
}

void ShruthiAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.

	// This getXmlFromBinary() helper function retrieves our XML from the binary blob..
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr)
	{
		presetName = xmlState->getStringAttribute("presetName");

		if (shruthiEditor) {
			shruthiEditor->setPresetName(presetName);
		}

		if (xmlState->hasTagName("ShruthiAppStatus")) {
			const OwnedArray< AudioProcessorParameter >&parameterSet = getParameters();

			float value;
			for (int p = 0; p < parameterSet.size(); p++) {
				// We stop at midiChannel
				if (p >= nrpmIndex[NRPN_VIRTUAL_MIDI_CHANNEL]) break;

				MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[p];
				if (xmlState->hasAttribute(midifiedFP->getNameForXML())) {
					value = (float)xmlState->getDoubleAttribute(midifiedFP->getNameForXML());
					midifiedFP->setRealValueNoNotification(value);
					DBG(String(p) << " '" << midifiedFP->getName() << "'  value " << (midifiedFP->getRealValue()));
				}
			}

            for (int s = 0; s < 16; s++) {
                if (xmlState->hasAttribute("SequencerStep" + String(s))) {
                    int stepValue = xmlState->getIntAttribute("SequencerStep" + String(s));
                    shruthiSteps[s].data_[0] = stepValue >> 8;
                    shruthiSteps[s].data_[1] = stepValue & 0xff;
                }
            }

            if (xmlState->hasAttribute("EditorWidth")) {
                editorWidth = xmlState->getIntAttribute("EditorWidth");
            }
            if (xmlState->hasAttribute("EditorHeight")) {
                editorHeight = xmlState->getIntAttribute("EditorHeight");
            }
            if (shruthiEditor != nullptr && editorWidth > 0 && editorHeight > 0) {
                shruthiEditor->setSize(editorWidth, editorHeight);
            }


			// If no UI we must set current
			MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_MIDI_CHANNEL]];
			currentMidiChannel = (int)midifiedFP->getRealValue();

			// REDRAW UI
			for (int p = 0; p < parameterSet.size(); p++) {
				parameterUpdatedForUI(p);
			}

			// Start Flushing NRPN
            if (shruthiSequencer != nullptr) {
                shruthiSequencer->setSequencerSteps(shruthiSteps);
            }
            sendPatchToShruthi();
		}
	}
}

void ShruthiAudioProcessor::parameterUpdatedForUI(int p) {
	if (shruthiEditor) {
		MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)getParameters()[p];
		shruthiEditor->parametersToUpdate.insert(midifiedFP->getName());
	}
}



bool ShruthiAudioProcessor::isRealtimePriority() const {
	return true;
}



/**
 * Values updated by the HOST
 * . Modify value
	. Send NRPN
	. Refresh UI
 */
void ShruthiAudioProcessor::setParameter(int index, float newValue)
{
	MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)getParameters()[index];

	midifiedFP->setValue(newValue);
	// send nrpn
	midifiedFP->addNrpn(midiOutBuffer, currentMidiChannel);
	flushMidiOut();
	// REDRAW UI 
	parameterUpdatedForUI(index);
}


/**
 * Values updated by the Shruthi hardware
 * Here the values has to be modified
  . Modify Value
  . tell host
  . refresh UI
 */
void ShruthiAudioProcessor::handleIncomingNrpn(int param, int nrpnValue, int forceIndex) {

	int index = (forceIndex == -1 ? nrpmIndex[param] : forceIndex);

	if (index == -1) {
		// NRN Param not registered
		return;
	}

	const OwnedArray< AudioProcessorParameter >&parameters = getParameters();
	MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameters[index];
	// Set the value 
	midifiedFP->setValueFromNrpn(nrpnValue);
	// Notify host we're not in the message thread so :
	MessageManager::callAsync(
		[=]() {
		sendParamChangeMessageToListeners(index, midifiedFP->getValue());
	}
	);
	parameterUpdatedForUI(index);
}

void ShruthiAudioProcessor::handleIncomingCC(int param, int value) {
    int index = ccIndex[param];
    if (index == -1) {
        return;
    }
    const OwnedArray< AudioProcessorParameter >&parameters = getParameters();
    MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameters[index];
    midifiedFP->setValueFromCC(value);

    // Notify host we're not in the message thread so :
    MessageManager::callAsync(
        [=]() {
        sendParamChangeMessageToListeners(index, midifiedFP->getValue());
        }
    );

    parameterUpdatedForUI(index);
}

/**
 * Values updated by the UI
 * Here values are already up to date
 . tell host
 . Send NRPN
 */
void ShruthiAudioProcessor::onParameterUpdated(AudioProcessorParameter *parameter) {

	MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameter;
	if (midifiedFP != nullptr) {
		int index = midifiedFP->getParamIndex();

		if (index == nrpmIndex[NRPN_VIRTUAL_PUSH_BUTTON]) {
			// Push button
			sendPatchToShruthi();
		}
		else if (index == nrpmIndex[NRPN_VIRTUAL_MIDI_CHANNEL]) {
			// Midi Channel changed
			currentMidiChannel = (int)midifiedFP->getRealValue();
		}
		else if (index == nrpmIndex[NRPN_VIRTUAL_PULL_BUTTON]) {
			// Don't notify host
			// send nrpn
            requestPatchTransfer();
		}
		else {
			// Notify host
			sendParamChangeMessageToListeners(index, midifiedFP->getValue());

			// send nrpn
            if (midifiedFP->isCCOnly()) {
                midifiedFP->sendCC(midiOutBuffer, currentMidiChannel);
            }
            else {
                midifiedFP->addNrpn(midiOutBuffer, currentMidiChannel);
            }
			flushMidiOut();
		}
	}
}

void ShruthiAudioProcessor::flushMidiOut() {
	pfm2MidiDevice->sendBlockOfMessagesNow(midiOutBuffer);
	midiOutBuffer.clear();
}

void ShruthiAudioProcessor::setPresetName(String newName) {
	presetName = newName;
}


void ShruthiAudioProcessor::requestPatchTransfer() {
    const char command[] = { 0x00, 0x21, 0x02, 0x00, 0x02, 0x11, 0x00, 0x00, 0x00 };
    sendSysex(MidiMessage::createSysExMessage(command, 9));
}

void ShruthiAudioProcessor::requestSequencerTransfer() {
    const char command[] = { 0x00, 0x21, 0x02, 0x00, 0x02, 0x12, 0x00, 0x00, 0x00 };
    sendSysex(MidiMessage::createSysExMessage(command, 9));
}



void ShruthiAudioProcessor::sendPatchToShruthi() {

    // SEND SYSEX
    DBG(" SEND SYSEX --------------------------");
    uint8 sysexMessage[256];
    uint8 patch[92];

    encodeSysexPatch(patch);

    uint8 startSysex[7] = { 0x00, 0x21, 0x02, // (Manufacturer ID for Mutable Instruments)
        0x00,  0x02, // (Product ID for Shruthi)
        0x01, // Command to send patch
        0x00 // // No argument
    };
    memcpy(sysexMessage, startSysex, 7);
    int index = 7;
    int checkSum = 0;

    for (int s = 0; s < 92; s++) {
        sysexMessage[index++] = patch[s] >> 4;
        sysexMessage[index++] = patch[s] & 0xf;

        checkSum = (checkSum + patch[s]) % 256;
    }

    sysexMessage[index++] = checkSum >> 4;
    sysexMessage[index++] = checkSum & 0xf;

    sendSysex(MidiMessage::createSysExMessage(sysexMessage, index));

    flushMidiOut();
}



void ShruthiAudioProcessor::sendSequencer(shruthi::SequenceStep steps[16]) {
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
        shruthiSteps[s] = steps[s];
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

void ShruthiAudioProcessor::sendSysex(const MidiMessage& sysexMessage) {
    midiOutBuffer.addEvent(sysexMessage, 8);
    flushMidiOut();
}



void ShruthiAudioProcessor::addMidifiedParameter(MidifiedFloatParameter *param) {
	addParameter(param);
	param->setProcessor(this);
}


void ShruthiAudioProcessor::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &midiMessage) {

    if (midiMessage.isController()) {
        if (midiMessage.isController() && midiMessage.getChannel() == currentMidiChannel) {
            switch (midiMessage.getControllerNumber()) {
            case 99:
                currentNrpn.paramMSB = midiMessage.getControllerValue();
                break;
            case 98:
                currentNrpn.paramLSB = midiMessage.getControllerValue();
                break;
            case 6:
                currentNrpn.valueMSB = midiMessage.getControllerValue();
                break;
            case 38:
            {
                currentNrpn.valueLSB = midiMessage.getControllerValue();
                int param = (int)(currentNrpn.paramMSB << 7) + currentNrpn.paramLSB;
                int value = (int)(currentNrpn.valueMSB << 7) + currentNrpn.valueLSB;
                // Xavier ???
                // const MessageManagerLock mmLock;
                DBG("incoming NRPN : " << param << " value " << value);
                handleIncomingNrpn(param, value);
                break;
            }
            default:
                DBG("Incoming CC : " << midiMessage.getControllerNumber() << " value " << midiMessage.getControllerValue());
                handleIncomingCC(midiMessage.getControllerNumber(), midiMessage.getControllerValue());
            }
        }
    }
    else if (midiMessage.isSysEx()) {
        const uint8* message = midiMessage.getSysExData();
        const uint8 toVerify[5] = { 0x00, 0x21, 0x02, 0x00, 0x02 };
        for (int i = 0; i < 5; i++) {
            if (message[i] != toVerify[i]) {
                DBG("SYSEX MESSAGE NOT FOR THE SHRUTHI");
                return;
            }
        }

        uint8 command = message[5];
        switch (command) {
        case 1:
            decodeSysexPatch(message + 7);
            break;
        case 2: {
            const uint8* patch = message + 7;
            DBG("YEAH NEW SEQUENCER!!!");
            for (int b = 0; b < 16; b++) {
                shruthiSteps[b].data_[0] = patch[b * 4] * 0x10 + patch[b * 4 + 1];
                shruthiSteps[b].data_[1] = patch[b * 4 + 2] * 0x10 + patch[b * 4 + 3];
            }
            const MessageManagerLock mmLock;
            if (shruthiSequencer != nullptr) {
                shruthiSequencer->setSequencerSteps(shruthiSteps);
            }

            break;
        }
        default:
            DBG("sysex command " << command << ": I do nothing...");
            break;
        }
    }
}

void ShruthiAudioProcessor::encodeSysexPatch(uint8 patch[92]) {
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
        patch[b] = extra_data_[b- 76];
    }

    // 84 - 85 :   uint8_t filter_cutoff_2 uint8_t filter_resonance_2;
    for (int b = 84; b < 86; b++) {
        uint8 byte = patch[b * 2] * 0x10 + patch[b * 2 + 1];
        int index = nrpmIndex[NRPN_VIRTUAL_FILTER2_CUTOFF + b - 84];
        MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[index];
        patch[b] = midifiedFP->getRealValue();
    }

    // 86 : SVF Filter
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_FILTER1_MODE]];
    patch[86] = (uint8)((int)midifiedFP->getRealValue() << 4);
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_FILTER2_MODE]];
    patch[86] |= (uint8)((int)midifiedFP->getRealValue() & 0xff);

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

void ShruthiAudioProcessor::decodeSysexPatch(const uint8* patch) {
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


    // 84 - 85 :   uint8_t filter_cutoff_2 uint8_t filter_resonance_2;
    for (int b = 84; b < 86; b++) {
        uint8 byte = patch[b * 2] * 0x10 + patch[b * 2 + 1];
        int index = nrpmIndex[NRPN_VIRTUAL_FILTER2_CUTOFF + b - 84];
        MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[index];
        midifiedFP->setValueFromNrpn((int)byte);
    }

    // 86 : SVF Filter
    uint8 filter_topology_ = patch[86 * 2] * 0x10 + patch[86 * 2 + 1];
    uint8 filter_1_mode_ = filter_topology_ >> 4;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_FILTER1_MODE]];
    midifiedFP->setValueFromNrpn(filter_1_mode_);
    uint8 filter_2_mode_ = filter_topology_ & 0xf;
    midifiedFP = (MidifiedFloatParameter*)parameterSet[nrpmIndex[NRPN_VIRTUAL_FILTER2_MODE]];
    midifiedFP->setValueFromNrpn(filter_2_mode_);

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

    


    // Notify host we're not in the message thread so :
    MessageManager::callAsync(
        [=]() {
        shruthiEditor->setPresetName(presetName);
    });

    // REDRAW UI   
    for (int p = 0; p < parameterSet.size(); p++) {
        parameterUpdatedForUI(p);
    }
}

void ShruthiAudioProcessor::handlePartialSysexMessage(MidiInput *source, const uint8 *messageData, int numBytesSoFar, double timestamp) {

}

void ShruthiAudioProcessor::choseNewMidiDevice() {
	pfm2MidiDevice->forceChoseNewDevices();
}


void ShruthiAudioProcessor::setShruthiSequencer(ShruthiSequencer* shruthiSeq) {
    this->shruthiSequencer = shruthiSeq;
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new ShruthiAudioProcessor();
}

