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
#include "Utils/MidiDevice.h"
#include "Utils/MidifiedFloatParameter.h"
#include "UI/ShruthiSequencer.h"
#include "UI/MISettingsListener.h"


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
#define NRPN_VIRTUAL_MAX 250

class AudioProcessorEditorCommon;
#ifdef AMBIKA
class AmbikaMultiData;
#endif
//==============================================================================
/**
*/

class CanSendSequencerClass {
public:
    virtual void sendSequencer(uint8 steps[32]) = 0;
    virtual void requestSequencerTransfer() = 0;
    virtual bool needsRealTimeUpdate() = 0;
    virtual void setRealTimeUpdate(int param, int value) = 0;
};


class AudioProcessorCommon : public AudioProcessor, public MidiInputCallback, public CanSendSequencerClass, public MISettingsListener
{
public:
	//==============================================================================
	AudioProcessorCommon();
	~AudioProcessorCommon();

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock);
	void releaseResources();
	void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

	//==============================================================================
	AudioProcessorEditor* createEditor();
	bool hasEditor() const;
    void redrawUI();

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
    // Different Ambika/Shruthi
    virtual void setStateParamSpecific(XmlElement* xmlState) = 0;
    virtual void getStateParamSpecific(XmlElement* xmlState) = 0;


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
    void settingsChangedForUI();

	void handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message);
	void handlePartialSysexMessage(MidiInput *source, const uint8 *messageData, int numBytesSoFar, double timestamp);
	void choseNewMidiDevice();

    // Sysex
    void sendSysexPatch();
    virtual void requestPatchTransfer() = 0;
    virtual void decodeSysexPatch(const uint8* message) = 0;
    virtual void decodeSysexSequencer(const uint8* message) = 0;
    virtual void encodeSysexPatch(uint8* message) = 0;
    virtual void decodeMultiData(const uint8* message) {};
    virtual String getSynthName() = 0;


    void sendSysex(const MidiMessage& sysexMessage);
    void setMISequencer(MISequencer* shruthiSeq);

    // CanSendSequencerClass
    virtual void requestSequencerTransfer() override  = 0;
    void sendSequencer(uint8 steps[32]) override;
    virtual bool needsRealTimeUpdate() override { return false; }
    virtual void setRealTimeUpdate(int param, int value) override {}

    virtual void sendSequencerToSynth() = 0;
    // Different in Shruthi and Ambika
    virtual char sysexMachineCode() = 0;

    // MISettingsListener
    void midiChannelChanged(int newMidiChannel);
    void partChanged(int newPart);
    void pushButtonPressed();
    void pullButtonPressed();
    virtual bool needsPart() { return false; }
    virtual bool needsPresetName() { return true; }
    int getMidiChannel() { return currentMidiChannel; }
    int getPart() { return currentPart; }
#ifdef AMBIKA
    virtual void setAmbikaMultiData(AmbikaMultiData* amd) = 0;
#endif


protected:
    int nrpmIndex[NRPN_VIRTUAL_MAX];
    int ccIndex[NRPN_VIRTUAL_MAX];
    int parameterIndex;
    String presetName;
    AudioProcessorEditorCommon* audioProcessorEditor;
    int currentPart;
    int currentMidiChannel;
    int midiChannelForPart[6];
    uint8 miSteps[32];
    MidiBuffer midiOutBuffer;
    bool canReceiveSysexPatch; // 
    bool canReceiveSysexSequencer; // 
    MISequencer* shruthiSequencer;
    SharedResourcePointer<MidiDevice> midiDevice;
private:
    bool receivingMultiPart;
    int editorWidth, editorHeight;
	MidiBuffer newMidiNotes;
	// Shared by all plugin instances
	LookAndFeel* myLookAndFeel;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioProcessorCommon)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
