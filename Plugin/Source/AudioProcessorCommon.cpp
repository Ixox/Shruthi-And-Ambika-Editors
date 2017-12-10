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


#include "AudioProcessorCommon.h"
#include "UI/PluginEditor.h"
#include "UI/MyLookAndFeel.h"




 //==============================================================================
AudioProcessorCommon::AudioProcessorCommon()
{
	myLookAndFeel = new MyLookAndFeel();
	LookAndFeel::setDefaultLookAndFeel(myLookAndFeel);

    midiDeviceNumber = midiDevice->getDefaultDeviceNumber();
    currentPart = 1;
    currentMidiChannel = 1;

#ifdef AMBIKA
    if (midiDeviceNumber == -1) {
        currentMidiChannel = 1;
        for (int c = 0; c < 6; c++) {
            midiChannelForPart[c] = c + 1;
        }
    }
    else {
        int* cfp = midiDevice->getMidiChannelForPart(midiDeviceNumber);
        for (int c = 0; c < 6; c++) {
            midiChannelForPart[c] = cfp[c];
        }
        currentMidiChannel = midiChannelForPart[currentPart - 1];
    }
#endif

    askForMidiDevice = true;


	// Important !!!! reset paramIndexCounter.
	MidifiedFloatParameter::resetParamIndexCounter();

	audioProcessorEditor = nullptr;
	MidifiedFloatParameter* newParam;
	parameterIndex = 0;
    editorWidth = 0;
    editorHeight = 0;
    currentNrpn.paramMSB = -1;
    currentNrpn.paramLSB = -1;

	for (int k = 0; k < NRPN_VIRTUAL_MAX; k++) {
		nrpmIndex[k] = -1;
        ccIndex[k] = -1;
    }



	midiMessageCollector.reset(44100);

    // Sequencer init
    sequencerUI = nullptr;
    srand(time(NULL));

    // ============================================================
    presetName = "No patch";

    // Midi Channel & Part
    midiDevice->addListener(this);
    receivingMultiPart = false;
    canReceiveSysexPatch = false;
    canReceiveSysexSequencer = false;
    canReceiveMultiPart = false;
    muteMidiDuringInitialisation = false;
    selectedTab = 0;
}



AudioProcessorCommon::~AudioProcessorCommon()
{
	delete myLookAndFeel;

	midiDevice->removeListener(this);

}



//==============================================================================
const String AudioProcessorCommon::getName() const
{
	return "Ixox MI Editor"; // JucePlugin_Name;
}


bool AudioProcessorCommon::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool AudioProcessorCommon::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

double AudioProcessorCommon::getTailLengthSeconds() const
{
	return 0.0;
}

int AudioProcessorCommon::getNumPrograms()
{
	return 1;
}

int AudioProcessorCommon::getCurrentProgram()
{
	return 1;
}

void AudioProcessorCommon::setCurrentProgram(int index)
{
	// Nothing to do;
}

const String AudioProcessorCommon::getProgramName(int index)
{
	return presetName;
}

void AudioProcessorCommon::changeProgramName(int index, const String& newName)
{
	setPresetName(newName);
}

//==============================================================================
void AudioProcessorCommon::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
}

void AudioProcessorCommon::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}


void AudioProcessorCommon::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{

	buffer.clear();

	if (midiMessages.getNumEvents() > 0) {
		MidiBuffer::Iterator i(midiMessages);
		MidiMessage message;
		int samplePosition; // Note: not actually used, so no need to initialise.
		newMidiNotes.clear();
		int now = Time::getMillisecondCounter();

		while (i.getNextEvent(message, samplePosition)) {
            message.setChannel(currentMidiChannel);
			newMidiNotes.addEvent(message, now);
		}

		if (newMidiNotes.getNumEvents() > 0) {
			DBG("MIDI NOTES : " << newMidiNotes.getNumEvents());
            if (!midiDevice->sendBlockOfMessagesNow(midiDeviceNumber, newMidiNotes)) {
            }
		}
	}

	midiMessages.clear();
}

//==============================================================================
bool AudioProcessorCommon::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

void AudioProcessorCommon::editorClosed() {
    editorWidth = audioProcessorEditor->getWidth();
    editorHeight = audioProcessorEditor->getHeight();
    audioProcessorEditor = nullptr;
    sequencerUI = nullptr;    
}


AudioProcessorEditor* AudioProcessorCommon::createEditor()
{
    // FALSE ::: TEST !!!
    muteMidiDuringInitialisation = false;
	audioProcessorEditor = new AudioProcessorEditorCommon(this);
	audioProcessorEditor->setPresetName(presetName);
    if (editorWidth > 0 && editorHeight > 0) {
        audioProcessorEditor->setSize(editorWidth, editorHeight);
    }
    sequencerUI->setSequencerData(getSequencerData());
    createEditorSpecific(audioProcessorEditor);

    // Update Editor Channel and Part
    settingsChangedForUI();

    muteMidiDuringInitialisation = false;
    return audioProcessorEditor;
}

//==============================================================================
void AudioProcessorCommon::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// Here's an example of how you can use XML to make it easy and more robust:

	// Create an outer XML element..
	XmlElement xml(getSynthName() + "AppStatus");

	xml.setAttribute("presetName", presetName);

	// add some attributes to it..
	const OwnedArray< AudioProcessorParameter >&parameterSet = getParameters();
	for (int p = 0; p < parameterSet.size(); p++) {
		MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[p];
		xml.setAttribute(midifiedFP->getNameForXML(), midifiedFP->getRealValue());
	}
    
    // Update editorWidth and editorHeight
    if (audioProcessorEditor != nullptr) {
        editorWidth = audioProcessorEditor->getWidth();
        editorHeight = audioProcessorEditor->getHeight();
    }

    xml.setAttribute("EditorWidth", editorWidth);
    xml.setAttribute("EditorHeight", editorHeight);

    if (midiDeviceNumber >= 0) {
        xml.setAttribute("MidiDeviceInputName", midiDevice->getMidiInputDeviceName(midiDeviceNumber));
        xml.setAttribute("MidiDeviceOutputName", midiDevice->getMidiOutputDeviceName(midiDeviceNumber));
    }

    if (needsPart()) {
        xml.setAttribute("CurrentPart", currentPart);
    }
    xml.setAttribute("MidiChannel", currentMidiChannel);



    // Different for Ambika and Shurthi
    getStateParamSpecific(&xml);

	// then use this helper function to stuff it into the binary blob and return it..
	copyXmlToBinary(xml, destData);
}

void AudioProcessorCommon::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.

	// This getXmlFromBinary() helper function retrieves our XML from the binary blob..
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr)
	{
		presetName = xmlState->getStringAttribute("presetName");

		if (audioProcessorEditor != nullptr) {
			audioProcessorEditor->setPresetName(presetName);
		}

		if (xmlState->hasTagName(getSynthName() + "AppStatus")) {


            // RED all params
            const OwnedArray< AudioProcessorParameter >&parameterSet = getParameters();
            float value;
            for (int p = 0; p < parameterSet.size(); p++) {
                MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameterSet[p];
                if (xmlState->hasAttribute(midifiedFP->getNameForXML())) {
                    value = (float)xmlState->getDoubleAttribute(midifiedFP->getNameForXML());
                    midifiedFP->setRealValueNoNotification(value);
                    DBG(String(p) << " '" << midifiedFP->getName() << "'  value " << (midifiedFP->getRealValue()));
                }
            }

            // Reinit midiDevice
            String midiDeviceInputName = xmlState->getStringAttribute("MidiDeviceInputName");
            String midiDeviceOutputName = xmlState->getStringAttribute("MidiDeviceOutputName");
            if (midiDeviceInputName.length() > 0 && midiDeviceOutputName.length() > 0) {
                midiDeviceNumber = midiDevice->openDevice(midiDeviceNumber, midiDeviceInputName, midiDeviceOutputName);
            }
            // Midi and Part
            if (xmlState->hasAttribute("CurrentPart")) {
                currentPart = xmlState->getIntAttribute("CurrentPart", 1);
            }
            currentMidiChannel = xmlState->getIntAttribute("MidiChannel", 1);
            settingsChangedForUI();

            // Different for Ambika and Shurthi
            setStateParamSpecific(xmlState);

            // Flush patch 
            sendPatchToSynth();

            if (xmlState->hasAttribute("EditorWidth")) {
                editorWidth = xmlState->getIntAttribute("EditorWidth");
            }
            if (xmlState->hasAttribute("EditorHeight")) {
                editorHeight = xmlState->getIntAttribute("EditorHeight");
            }
            if (audioProcessorEditor != nullptr && editorWidth > 0 && editorHeight > 0) {
                audioProcessorEditor->setSize(editorWidth, editorHeight);
            }

            // REDRAW UI
			for (int p = 0; p < parameterSet.size(); p++) {
				parameterUpdatedForUI(p);
			}
        }
	}
}

void AudioProcessorCommon::settingsChangedForUI() {
    if (audioProcessorEditor) {        
        audioProcessorEditor->parametersToUpdate.insert("_Settings");
    }
}


void AudioProcessorCommon::parameterUpdatedForUI(int p) {
	if (audioProcessorEditor) {
		MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)getParameters()[p];
		audioProcessorEditor->parametersToUpdate.insert(midifiedFP->getName());
	}
}

void AudioProcessorCommon::midiChannelChanged(int newMidiChannel) {
    currentMidiChannel = newMidiChannel;
}

void AudioProcessorCommon::partChanged(int newPart) {
    currentPart = newPart;
    currentMidiChannel = midiChannelForPart[currentPart -1];
    settingsChangedForUI();
}



bool AudioProcessorCommon::isRealtimePriority() const {
	return true;
}



/**
 * Values updated by the HOST
 * . Modify value
	. Send NRPN
	. Refresh UI
 */
void AudioProcessorCommon::setParameter(int index, float newValue)
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
void AudioProcessorCommon::handleIncomingNrpn(int param, int nrpnValue, int forceIndex) {

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

void AudioProcessorCommon::handleIncomingCC(int param, int value) {
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
void AudioProcessorCommon::onParameterUpdated(AudioProcessorParameter *parameter) {

	MidifiedFloatParameter* midifiedFP = (MidifiedFloatParameter*)parameter;
	if (midifiedFP != nullptr) {
		int index = midifiedFP->getParamIndex();

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

void AudioProcessorCommon::flushMidiOut() {
    if (!muteMidiDuringInitialisation) {
        if (!midiDevice->sendBlockOfMessagesNow(midiDeviceNumber, midiOutBuffer)) {
            if (askForMidiDevice) {
                askForMidiDevice = false;
                choseNewMidiDevice();
            }
        }
    }
	midiOutBuffer.clear();
}

void AudioProcessorCommon::setPresetName(String newName) {
	presetName = newName;
}






void AudioProcessorCommon::sendSysex(const MidiMessage& sysexMessage) {
    // int now = Time::getMillisecondCounter();
    DBG("SEND SYSEX : size : " << sysexMessage.getSysExDataSize());
    midiOutBuffer.addEvent(sysexMessage, 1);
    flushMidiOut();
}



void AudioProcessorCommon::addMidifiedParameter(MidifiedFloatParameter *param) {
	addParameter(param);
	param->setProcessor(this);
}


void AudioProcessorCommon::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &midiMessage) {

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
                if (currentNrpn.paramMSB != -1 && currentNrpn.paramLSB != -1) {
                    currentNrpn.valueLSB = midiMessage.getControllerValue();
                    int param = (int)(currentNrpn.paramMSB << 7) + currentNrpn.paramLSB;
                    int value = (int)(currentNrpn.valueMSB << 7) + currentNrpn.valueLSB;
                    // Xavier ???
                    // const MessageManagerLock mmLock;               
                    DBG("incoming NRPN : " << param << " value " << value);
                    handleIncomingNrpn(param, value);
                }
                break;
            }
            default:
                DBG("incoming CC : " << midiMessage.getControllerNumber() << " value " << midiMessage.getControllerValue());
                handleIncomingCC(midiMessage.getControllerNumber(), midiMessage.getControllerValue());
            }
        }
    }
    else if (midiMessage.isSysEx()) {
        const uint8* message = midiMessage.getSysExData();
        uint8 toVerify[5] = { 0x00, 0x21, 0x02, 0x00, 0x02 };
        toVerify[4] = sysexMachineCode();


        for (int i = 0; i < 5; i++) {
            if (message[i] != toVerify[i]) {
                DBG("SYSEX MESSAGE FOR ANOTHER MACHINE");
                return;
            }
        }

        uint8 command = message[5];
        uint8 param = message[6];
        uint8 actualCommand = command;

        DBG("SYSEX Command : " << command << " Argument : " << param << " Size : " << ((midiMessage.getSysExDataSize() - 9) / 2));

        if (receivingMultiPart) {
            command = 4;
        }

        switch (command) {
        case 1:
            decodeSysexPatch(message + 7);
            break;
        case 2: {
            decodeSysexSequencer(message + 7);
            break;
        }
        case 4: {
            DBG("Current part : "<< currentPart << "SYSEX MULTI PART ("<< (canReceiveMultiPart ? "Can" : "CANNOT") <<") argument : " << param << " Size : " << midiMessage.getSysExDataSize());
            if (canReceiveMultiPart && !receivingMultiPart) {
                canReceiveMultiPart = false;
                receivingMultiPart = true;
                decodeMultiData(message + 7);
            }
            else if (receivingMultiPart) {
                if (actualCommand == 5 && param == 6) {
                    DBG("END OF SYSEX MULTI PART!!!");
                    // End of the infos !
                    receivingMultiPart = false;
                }
                else {
                    // DBG(".. SYSEX MULTI PART!!!..");
                }
            }
            break;
        }
        case 5: {
            decodeSysexPartData(message + 7);
        }
        default:
            DBG("sysex command " << command << ": I do nothing...");
            break;
        }
    }
}


void AudioProcessorCommon::handlePartialSysexMessage(MidiInput *source, const uint8 *messageData, int numBytesSoFar, double timestamp) {
    DBG("handlePartialSysexMessage " << numBytesSoFar);
}



void AudioProcessorCommon::setMISequencer(MISequencer* shruthiSeq) {
    this->sequencerUI = shruthiSeq;
}


void AudioProcessorCommon::redrawUI() {
    
    MessageManager::callAsync(
        [=]() {
        if (audioProcessorEditor != nullptr) {
            audioProcessorEditor->setPresetName(presetName);
        }
    });

    const OwnedArray< AudioProcessorParameter >&parameterSet = getParameters();
    for (int p = 0; p < parameterSet.size(); p++) {
        parameterUpdatedForUI(p);
    }
}

void AudioProcessorCommon::pushButtonPressed() {
    sendPatchToSynth();
}

void AudioProcessorCommon::pullButtonPressed() {
    requestPatchTransfer();
}


void AudioProcessorCommon::setSelectedTab(int t) {
    this->selectedTab = t;
}

int AudioProcessorCommon::getSelectedTab() {
    return this->selectedTab;
}
