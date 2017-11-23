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

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include <map>
#include <mutex>
#include <unordered_set>
#include "JuceHeader.h"
#include "MidiDevice.h"
#include "MidifiedFloatParameter.h"
#include "UI/ShruthiSequencer.h"


struct Nrpn {
	char paramMSB;
	char paramLSB;
	char valueMSB;
	char valueLSB;
};


#define NRPN_VIRTUAL_FILTER2_CUTOFF 200
#define NRPN_VIRTUAL_FILTER2_RESONNANCE 201
#define NRPN_VIRTUAL_FILTER1_MODE 202
#define NRPN_VIRTUAL_FILTER2_MODE 203
#define NRPN_VIRTUAL_LEGATO 210
#define NRPN_VIRTUAL_PORTAMENTO 211
#define NRPN_VIRTUAL_MIDI_CHANNEL 300
#define NRPN_VIRTUAL_PUSH_BUTTON 301
#define NRPN_VIRTUAL_PULL_BUTTON 302
#define NRPN_VIRTUAL_MAX 350

class ShruthiAudioProcessorEditor;
//==============================================================================
/**
*/

class CanSendSequencerClass {
public:
    virtual void sendSequencer(shruthi::SequenceStep newSteps[16]) = 0;
    virtual void requestSequencerTransfer() = 0;

};


class ShruthiAudioProcessor : public AudioProcessor, public MidiInputCallback, public CanSendSequencerClass
{
public:
	//==============================================================================
	ShruthiAudioProcessor();
	~ShruthiAudioProcessor();

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock);
	void releaseResources();

	void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

	//==============================================================================
	AudioProcessorEditor* createEditor();
	bool hasEditor() const;

	//==============================================================================
	const String getName() const;

	void setParameter(int index, float newValue);

	bool acceptsMidi() const;
	bool producesMidi() const;
	double getTailLengthSeconds() const;

	//==============================================================================
	int getNumPrograms();
	int getCurrentProgram();
	void setCurrentProgram(int index);
	const String getProgramName(int index);
	void changeProgramName(int index, const String& newName);

	//==============================================================================
	void getStateInformation(MemoryBlock& destData);
	void setStateInformation(const void* data, int sizeInBytes);

	void handleIncomingNrpn(int param, int value, int forceIndex = -1);
    void handleIncomingCC(int param, int value);
    // Parameter observer
	bool isRealtimePriority() const;
	void onParameterUpdated(AudioProcessorParameter *parameter);
	// accessed from editor so must be public
	MidiMessageCollector midiMessageCollector;
	struct Nrpn currentNrpn;
	void setPresetName(String newName);
    void editorClosed();

	void addMidifiedParameter(MidifiedFloatParameter *param);
	void flushMidiOut();

	void parameterUpdatedForUI(int p);
	void handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message);
	void handlePartialSysexMessage(MidiInput *source, const uint8 *messageData, int numBytesSoFar, double timestamp);
	void choseNewMidiDevice();

    // Sysex
    void sendPatchToShruthi();
    void requestPatchTransfer();
    void decodeSysexPatch(const uint8* message);
    void encodeSysexPatch(uint8 message[184]);
    void sendSysex(const MidiMessage& sysexMessage);
    void setShruthiSequencer(ShruthiSequencer* shruthiSeq);

    // CanSendSequencerClass
    void requestSequencerTransfer();
    void sendSequencer(shruthi::SequenceStep newSteps[16]);

private:
	int nrpmIndex[NRPN_VIRTUAL_MAX];
    int ccIndex[NRPN_VIRTUAL_MAX];
    int parameterIndex;
	String presetName;
	int currentMidiChannel;
	MidiBuffer midiOutBuffer;
	MidiBuffer newMidiNotes;
	// Shared by all plugin instances
	SharedResourcePointer<MidiDevice> pfm2MidiDevice;
    ShruthiSequencer* shruthiSequencer;
    shruthi::SequenceStep shruthiSteps[16];
    ShruthiAudioProcessorEditor* shruthiEditor;
	LookAndFeel* myLookAndFeel;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ShruthiAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
