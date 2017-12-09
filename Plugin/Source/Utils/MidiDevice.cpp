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

#define MIDI_LAST_INPUT_PROP "midiInput"
#define MIDI_LAST_OUTPUT_PROP "midiOutput"
#define MIDI_LAST_FOR_PART_PROP "midiForPart"

#define NOT_FOUND -1
#define ERROR_INCORECT_CHOICE -2
#define ERROR_OPENING -3


//This can be called to suggest a file that should be used, based on the values in this structure.
//So on a Mac, this will return a file called : ~/ Library / [osxLibrarySubFolder] / [folderName] / [applicationName].[filenameSuffix]
//On Windows it'll return something like: C:\Documents and Settings\username\Application Data\[folderName]\[applicationName].[filenameSuffix]
//On Linux it'll return ~/[folderName]/[applicationName].[filenameSuffix]
//If the folderName variable is empty, it'll use the app name for this (or omit the folder name on the Mac).
//The paths will also vary depending on whether commonToAllUsers is true.

MidiDevice::MidiDevice()
{
    for (int d = 0; d < NUMBER_OF_DEVICES; d++) {
        devices[d].numberOfUsage = 0;
        devices[d].deviceNameInput = ""; 
        devices[d].deviceNameOutput = "";
        for (int p = 0; p < 6; p++) {
            devices[d].midiChannelForPart[p] = p + 1;
            devices[d].partUsed[p] = false;
        }
    }
    lastUsedDevice = NOT_FOUND;
#ifdef AMBIKA
    synthName = "Ambika";
#endif
#ifdef SHRUTHI
    synthName = "Shruthi";
#endif

    PropertiesFile::Options options;
    options.applicationName = synthName + "Editor";
    options.osxLibrarySubFolder = "Application Support";
    options.folderName = "Ixox";
    options.filenameSuffix = ".settings";
    options.storageFormat = PropertiesFile::StorageFormat::storeAsXML;
    appProperties.setStorageParameters(options);


    defaultDeviceNumber = NOT_FOUND;
    PropertiesFile* propertiesFile = appProperties.getCommonSettings(true);
    String fileName = propertiesFile->getFile().getFullPathName();
    DBG("PROPERTIES FULL PATH NAME : " + fileName);
    if (propertiesFile->containsKey(MIDI_LAST_INPUT_PROP) && propertiesFile->containsKey(MIDI_LAST_OUTPUT_PROP)) {
        String inputProp = propertiesFile->getValue(MIDI_LAST_INPUT_PROP);
        String outputProp = propertiesFile->getValue(MIDI_LAST_OUTPUT_PROP);
        if (inputProp.length() > 0 && outputProp.length() > 0) {
            defaultDeviceNumber = openDevice(NOT_FOUND, propertiesFile->getValue(MIDI_LAST_INPUT_PROP), propertiesFile->getValue(MIDI_LAST_OUTPUT_PROP));
            if (defaultDeviceNumber >= 0) {
                for (int p = 0; p < 6; p++) {
                    if (propertiesFile->containsKey(MIDI_LAST_FOR_PART_PROP + String(p))) {
                        devices[defaultDeviceNumber].midiChannelForPart[p] = propertiesFile->getIntValue(MIDI_LAST_FOR_PART_PROP + String(p));
                    }
                }
            }
        }
    }
}


void MidiDevice::saveLastChosenDevice() {

	PropertiesFile* propertiesFile = appProperties.getCommonSettings(true);
    propertiesFile->setValue(MIDI_LAST_INPUT_PROP, devices[lastUsedDevice].deviceNameInput);
    propertiesFile->setValue(MIDI_LAST_OUTPUT_PROP, devices[lastUsedDevice].deviceNameOutput);
    appProperties.saveIfNeeded();


}

MidiDevice::~MidiDevice() {
    closeAllDevices();
}


int MidiDevice::getDeviceNumber(String deviceNameInput, String deviceNameOutput) {
    if (deviceNameInput == "" || deviceNameOutput == "") {
        return ERROR_INCORECT_CHOICE;
    }
    for (int d = 0; d < NUMBER_OF_DEVICES; d++) {
        if ((devices[d].deviceNameInput == deviceNameInput && devices[d].deviceNameOutput != deviceNameOutput) 
            || (devices[d].deviceNameInput != deviceNameInput && devices[d].deviceNameOutput == deviceNameOutput)) {
            // Error
            return ERROR_INCORECT_CHOICE;
        }

        if (devices[d].deviceNameInput == deviceNameInput && devices[d].deviceNameOutput == deviceNameOutput) {
            return d;
        }
    }
    // Does not exist
    return NOT_FOUND;
}


int MidiDevice::openDevice(int deviceNumber, String deviceNameInput, String deviceNameOutput) {
    MidiInput* midiInput = nullptr;
    MidiOutput* midiOutput = nullptr;

    // Check if device already exists or if only one of input/output is selected
    int newDeviceNumber = getDeviceNumber(deviceNameInput, deviceNameOutput);
    if (newDeviceNumber == ERROR_INCORECT_CHOICE) {
        return ERROR_INCORECT_CHOICE;
    }


    // Already exists
    if (newDeviceNumber != NOT_FOUND) {
        if (newDeviceNumber != deviceNumber) {
            if (deviceNumber >= 0) {
                closeDevice(deviceNumber, false);
            }
            devices[newDeviceNumber].numberOfUsage++;
        }
        return newDeviceNumber;
    }


    StringArray outputDevices = MidiOutput::getDevices();
    for (int d = 0; d < outputDevices.size(); d++) {
        DBG("Output : " << outputDevices[d]);
        if (outputDevices[d] == deviceNameOutput) {
            if ((midiOutput = MidiOutput::openDevice(d)) != nullptr) {
                DBG("Output found :)");
            }
            break;
        }
    }

    if (midiOutput != nullptr) {
        StringArray inputDevices = MidiInput::getDevices();
        for (int d = 0; d < inputDevices.size(); d++) {
            DBG("Input : " << inputDevices[d]);
            if (inputDevices[d] == deviceNameInput) {
                if ((midiInput = MidiInput::openDevice(d, this)) != nullptr) {
                    midiInput->start();
                    DBG("Input found :)");
                }
                break;
            }
        }

        if (midiInput == nullptr) {
            delete midiOutput;
            return ERROR_OPENING;
        }
    }
    else {
        return ERROR_OPENING;
    }

    // All Devices are busy ?
    int toReturn = ERROR_OPENING;

    for (int d = 0; d < NUMBER_OF_DEVICES; d++) {
        if (devices[d].numberOfUsage == 0) {
            devices[d].numberOfUsage = 1;
            devices[d].deviceNameInput = deviceNameInput;
            devices[d].deviceNameOutput = deviceNameOutput;
            devices[d].midiInput = midiInput;
            devices[d].midiOutput = midiOutput;
            toReturn = d;
            break;
        }
    }

    // Let's close old device
    if (deviceNumber >= 0) {
        closeDevice(deviceNumber, false);
    }


    return toReturn;
}

void MidiDevice::closeDevice(int deviceNumber, bool force) {
    devices[deviceNumber].numberOfUsage--;
    if (devices[deviceNumber].numberOfUsage == 0
        || (force && devices[deviceNumber].numberOfUsage >=0)) {
        devices[deviceNumber].numberOfUsage = 0;
        if (devices[deviceNumber].midiInput != nullptr) {
            devices[deviceNumber].midiInput->stop();
            delete devices[deviceNumber].midiInput;
            devices[deviceNumber].midiInput = nullptr;
        }
        if (devices[deviceNumber].midiOutput != nullptr) {
            delete devices[deviceNumber].midiOutput;
            devices[deviceNumber].midiOutput = nullptr;
        }
        devices[deviceNumber].deviceNameInput = "";
        devices[deviceNumber].deviceNameOutput = "";
    }
}

void MidiDevice::closeAllDevices() {
    for (int d = 0; d < NUMBER_OF_DEVICES; d++) {
        closeDevice(d, true);
    }
}




//int MidiDevice::forceChoseNewDevices(String synthName) {
//	showErrorMEssage = true;
//	return choseNewDevices(synthName);
//}

int MidiDevice::openChoseDeviceWindow(int deviceNumber) {
	const ScopedTryLock myScopedTryLock(messageLock);
    int result = 0;

    // use lastUsedDevice if no current device
    deviceNumber = deviceNumber < 0 ? lastUsedDevice : deviceNumber;

	if (!myScopedTryLock.isLocked()) {
		return result;
	}

	AlertWindow midiWindow("Where is your " + synthName +" ?",
		"",
		AlertWindow::QuestionIcon);

	Label errorMessage("");
	errorMessage.setColour(Label::textColourId, Colour::fromRGB(200, 80, 80));
	errorMessage.setSize(400, 20);
	midiWindow.addCustomComponent(&errorMessage);

	StringArray inputDevices = MidiInput::getDevices();
    inputDevices.insert(0, "<Select>");
	midiWindow.addComboBox("From", inputDevices, "Input from your "+ synthName);
    if (deviceNumber >= 0) {
        int currentInput = inputDevices.indexOf(devices[deviceNumber].deviceNameInput);
        if (currentInput >= 0) {
            midiWindow.getComboBoxComponent("From")->setSelectedId(currentInput + 1);
        }
    }

	StringArray outputDevices = MidiOutput::getDevices();
    outputDevices.insert(0, "<Select>");
	midiWindow.addComboBox("To", outputDevices, "Output to your "+ synthName);
    if (deviceNumber >= 0) {
        int currentOutput = outputDevices.indexOf(devices[deviceNumber].deviceNameOutput);
        if (currentOutput >= 0) {
            midiWindow.getComboBoxComponent("To")->setSelectedId(currentOutput + 1);
        }
    }

#ifdef AMBIKA
    midiWindow.addTextBlock("Clicking OK will also retrieve the Ambika multi data information.");
#endif

	//void addButton(const String &name, int returnValue, const KeyPress &shortcutKey1 = KeyPress(), const KeyPress &shortcutKey2 = KeyPress())
	midiWindow.addButton("Cancel", 0);
	midiWindow.addButton("OK", 1);

	result = 1;
    int newDeviceNumber = deviceNumber;
    do {
		do {
			result = midiWindow.runModalLoop();
			errorMessage.setText("You must select both input and output", NotificationType::sendNotification);
			midiWindow.repaint();
		} while ((midiWindow.getComboBoxComponent("From")->getSelectedId() == 1 || midiWindow.getComboBoxComponent("To")->getSelectedId() == 1) && result == 1);

        if (result == 1) {

            // -2 because of the <Select>.
            int deviceFrom = midiWindow.getComboBoxComponent("From")->getSelectedId() - 2;
            String midiInputDevice = inputDevices[deviceFrom + 1];
            int deviceTo = midiWindow.getComboBoxComponent("To")->getSelectedId() - 2;
            String midiOutputDevice = outputDevices[deviceTo + 1];

            newDeviceNumber = openDevice(deviceNumber, midiInputDevice, midiOutputDevice);

            if (newDeviceNumber == ERROR_INCORECT_CHOICE) {
                errorMessage.setText("Cannot use this Input/output Pair. Check the other devices you chose.", NotificationType::sendNotification);
                midiWindow.repaint();
            } 
            else if (newDeviceNumber == ERROR_OPENING) {
                errorMessage.setText("Error opening the midi devices.", NotificationType::sendNotification);
                midiWindow.repaint();
            }
            else {
                lastUsedDevice = newDeviceNumber;
                saveLastChosenDevice();
            }
        }
	} while (newDeviceNumber < 0 && result == 1);

    return result == 0 ? -1 : newDeviceNumber;
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

MidiOutput* MidiDevice::getMidiOutput(int deviceNumber) {
    if (deviceNumber >= 0) {
        return devices[deviceNumber].midiOutput;
    }
}
 
MidiInput* MidiDevice::getMidiInput(int deviceNumber) {
    if (deviceNumber >= 0) {
        return devices[deviceNumber].midiInput;
    }
}

void MidiDevice::setMidiChannelForPart(int deviceNumber, int a[6]) {
    PropertiesFile* propertiesFile = appProperties.getCommonSettings(true);
    for (int p = 0; p < 6; p++) {
        if (devices[deviceNumber].midiChannelForPart[p] != a[p]) {
            devices[deviceNumber].midiChannelForPart[p] = a[p];
            propertiesFile->setValue(MIDI_LAST_FOR_PART_PROP + String(p), devices[deviceNumber].midiChannelForPart[p]);
        }
    }
    appProperties.saveIfNeeded();
}

int* MidiDevice::getMidiChannelForPart(int deviceNumber) {
    return devices[deviceNumber].midiChannelForPart;
}



bool MidiDevice::sendBlockOfMessagesNow(int deviceNumber, MidiBuffer& midiBuffer) {
    if (deviceNumber >=0 && devices[deviceNumber].midiOutput != nullptr && devices[deviceNumber].midiInput != nullptr) {
        const ScopedTryLock myScopedTryLock(midiLock);
        devices[deviceNumber].midiOutput->sendBlockOfMessagesNow(midiBuffer);
        return true;
    }
    else {
        return false;
    }
}



