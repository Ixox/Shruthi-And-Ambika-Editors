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

#include "MidiDevice.h"

#define MIDI_INPUT "midiInput"
#define MIDI_OUTPUT "midiOutput"
#define MIDI_FOR_PART "midiForPart"

MidiDevice::MidiDevice() {
    String pfm2InputDevice = "##NONE";
    String pfm2OutputDevice = "##NONE";

	PropertiesFile::Options options;
#ifdef AMBIKA
	options.applicationName = "ambikaEditor";
#endif
#ifdef SHRUTHI
    options.applicationName = "shruthiEditor";
#endif

options.osxLibrarySubFolder = "Application Support/Ixox";
	options.filenameSuffix = ".settings";
	options.storageFormat = PropertiesFile::StorageFormat::storeAsXML;
	pfm2AppProps.setStorageParameters(options);

	PropertiesFile* pfm2Settings = pfm2AppProps.getCommonSettings(true);

	if (pfm2Settings->containsKey(MIDI_INPUT)) {
		pfm2InputDevice = pfm2Settings->getValue(MIDI_INPUT);
	}

	if (pfm2Settings->containsKey(MIDI_OUTPUT)) {
		pfm2OutputDevice = pfm2Settings->getValue(MIDI_OUTPUT);
	}

	pfm2MidiOutput = nullptr;
	pfm2MidiInput = nullptr;

	StringArray devices = MidiOutput::getDevices();

	for (int d = 0; d < devices.size(); d++) {
		DBG("Output : " << devices[d]);
		if (devices[d] == pfm2OutputDevice) {
			if ((pfm2MidiOutput = MidiOutput::openDevice(d)) != nullptr) {
				DBG("Output found :)");
				currentMidiOutputDevice = devices[d];
			}
			break;
		}
	}

	devices = MidiInput::getDevices();
	for (int d = 0; d < devices.size(); d++) {
		DBG("Input : " << devices[d]);
		if (devices[d] == pfm2InputDevice) {
			if ((pfm2MidiInput = MidiInput::openDevice(d, this)) != nullptr) {
				pfm2MidiInput->start();
				currentMidiInputDevice = devices[d];
				DBG("Input found :)");
			}
			break;
		}
	}

    for (int p = 0; p < 6; p++) {
        if (pfm2Settings->containsKey(MIDI_FOR_PART + String(p))) {
            midiChannelForPart[p] = pfm2Settings->getIntValue(MIDI_FOR_PART + String(p));
        }
        else {
            midiChannelForPart[p] = p + 1;
        }
    }
}

MidiDevice::~MidiDevice() {
	resetDevices();
}

void MidiDevice::resetDevices() {

	if (pfm2MidiInput) {
		pfm2MidiInput->stop();
		delete pfm2MidiInput;
		pfm2MidiInput = nullptr;
	}
	if (pfm2MidiOutput) {
		delete pfm2MidiOutput;
		pfm2MidiOutput = nullptr;
	}
}


void MidiDevice::sendBlockOfMessagesNow(MidiBuffer& midiBuffer, String synthName) {
	if (pfm2MidiOutput != nullptr && pfm2MidiInput != nullptr) {
		pfm2MidiOutput->sendBlockOfMessagesNow(midiBuffer);
	}
	else {
		choseNewDevices(synthName);
	}
}


int MidiDevice::forceChoseNewDevices(String synthName) {
	showErrorMEssage = true;
	return choseNewDevices(synthName);
}

int MidiDevice::choseNewDevices(String synthName) {
	const ScopedTryLock myScopedTryLock(messageLock);
    int result = 0;

	if (!myScopedTryLock.isLocked()) {
		return result;
	}

    if (showErrorMEssage) {
		showErrorMEssage = false;

		AlertWindow midiWindow("Where is your " + synthName +" ?",
			"",
			AlertWindow::QuestionIcon);

		Label errorMessage("");
		errorMessage.setColour(Label::textColourId, Colour::fromRGB(200, 80, 80));
		errorMessage.setSize(400, 20);
		midiWindow.addCustomComponent(&errorMessage);

		StringArray devicesFrom = MidiInput::getDevices();
		devicesFrom.insert(0, "<Select>");
		midiWindow.addComboBox("From", devicesFrom, "Input from your "+ synthName);
		int currentInput = devicesFrom.indexOf(currentMidiInputDevice);
		if (currentInput > -1) {
			midiWindow.getComboBoxComponent("From")->setSelectedId(currentInput + 1);
		}

		StringArray devicesTo = MidiOutput::getDevices();
		devicesTo.insert(0, "<Select>");
		midiWindow.addComboBox("To", devicesTo, "Output to your "+ synthName);
		int currentOutput = devicesTo.indexOf(currentMidiOutputDevice);
		if (currentOutput > -1) {
			midiWindow.getComboBoxComponent("To")->setSelectedId(currentOutput + 1);
		}
#ifdef AMBIKA
        midiWindow.addTextBlock("Clicking OK will also update your part/midi association.");
#endif
		//void addButton(const String &name, int returnValue, const KeyPress &shortcutKey1 = KeyPress(), const KeyPress &shortcutKey2 = KeyPress())
		midiWindow.addButton("Cancel", 0);
		midiWindow.addButton("OK", 1);

		result = 1;
		do {

			do {
				result = midiWindow.runModalLoop();
				errorMessage.setText("You must select both input and output", NotificationType::sendNotification);
				midiWindow.repaint();
			} while ((midiWindow.getComboBoxComponent("From")->getSelectedId() == 1 || midiWindow.getComboBoxComponent("To")->getSelectedId() == 1) && result == 1);

			if (result == 1) {

				if (pfm2MidiOutput != nullptr) {
					delete pfm2MidiOutput;
					pfm2MidiOutput = nullptr;
				}
				if (pfm2MidiInput != nullptr) {
					pfm2MidiInput->stop();
					delete pfm2MidiInput;
					pfm2MidiInput = nullptr;
				}

				// -2 because of the <Select>.
				int deviceFrom = midiWindow.getComboBoxComponent("From")->getSelectedId() - 2;
				currentMidiInputDevice = devicesFrom[deviceFrom + 1];
				int deviceTo = midiWindow.getComboBoxComponent("To")->getSelectedId() - 2;
				currentMidiOutputDevice = devicesTo[deviceTo + 1];

				pfm2MidiInput = MidiInput::openDevice(deviceFrom, this);
				if (pfm2MidiInput != nullptr) {
					pfm2MidiInput->start();
				}
				else {
					errorMessage.setText("Input cannot be open", NotificationType::dontSendNotification);
				}
				// No need to test output if input did not work
				if (pfm2MidiInput != nullptr) {
					pfm2MidiOutput = MidiOutput::openDevice(deviceTo);
					if (pfm2MidiOutput == nullptr) {
						errorMessage.setText("Output cannot be open", NotificationType::dontSendNotification);
						// let's close input before rexiting
						resetDevices();
					}
					else {
						// We're good
						PropertiesFile* pfm2Settings = pfm2AppProps.getCommonSettings(true);
						pfm2Settings->setValue(MIDI_INPUT, currentMidiInputDevice);
						pfm2Settings->setValue(MIDI_OUTPUT, currentMidiOutputDevice);
						pfm2AppProps.saveIfNeeded();
					}
				}
			}
		} while ((pfm2MidiInput == nullptr || pfm2MidiOutput == nullptr) && result == 1);
	}
    return result;
}

void MidiDevice::addListener(MidiInputCallback *listener) {
	listeners.push_back(listener);
}

void MidiDevice::removeListener(MidiInputCallback *listener) {
	MidiInputCallbackList::iterator iterator = listeners.begin();
	while (iterator != listeners.end() && listeners.size() > 0) {
		if (*iterator == listener) {
			iterator = listeners.erase(iterator);
		}
		else {
			++iterator;
		}
	}
}

void MidiDevice::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &midiMessage) {
	for (MidiInputCallbackList::const_iterator iterator = listeners.begin(); iterator != listeners.end(); ++iterator) {
		(*iterator)->handleIncomingMidiMessage(source, midiMessage);
	}
}

void MidiDevice::handlePartialSysexMessage(MidiInput *source, const uint8 *messageData, int numBytesSoFar, double timestamp) {

}


void MidiDevice::setMidiChannelForPart(int a[6]) {
    PropertiesFile* pfm2Settings = pfm2AppProps.getCommonSettings(true);
    for (int p = 0; p < 6; p++) {
        if (midiChannelForPart[p] != a[p]) {
            midiChannelForPart[p] = a[p];
            pfm2Settings->setValue(MIDI_FOR_PART + String(p), midiChannelForPart[p]);
        }
    }
    pfm2AppProps.saveIfNeeded();
}

int* MidiDevice::getMidiChannelForPart() {
    return midiChannelForPart;
}





