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

#ifndef PFM2MIDIDEVICE_H_INCLUDED
#define PFM2MIDIDEVICE_H_INCLUDED

#include "JuceHeader.h"

typedef std::vector<MidiInputCallback *> MidiInputCallbackList;

#define NUMBER_OF_DEVICES 32

struct OpenedDevice {
    int numberOfUsage;
    int midiChannelForPart[6];
    bool partUsed[6];
    MidiInput* midiInput;
    MidiOutput* midiOutput;
    String deviceNameInput;
    String deviceNameOutput;
};


// This class must be used with a SharedResourcePointer so that multiple instance of a plugin use the same ports
class MidiDevice : public MidiInputCallback
{
public:
    MidiDevice();
    ~MidiDevice();

    void setSynthName(String sn) { synthName = sn;  }
    void saveLastChosenDevice();

    // return deviceNumber or -1
    int openChoseDeviceWindow(int deviceNumber);
    int getDeviceNumber(String deviceNameInput, String deviceNameOutput);
    // return deviceNumber or -1
    int openDevice(int deviceNumber, String deviceNameInput, String deviceNameOutput);

    void closeDevice(int deviceNumber, bool force);
    void closeAllDevices();

    MidiOutput* getMidiOutput(int deviceNumber);
    MidiInput* getMidiInput(int deviceNumber);
    String getMidiInputDeviceName(int deviceNumber) { return devices[deviceNumber].deviceNameInput; }
    String getMidiOutputDeviceName(int deviceNumber) { return devices[deviceNumber].deviceNameOutput; }

    bool sendBlockOfMessagesNow(int deviceNumber, MidiBuffer& midiBuffer);

    // Listeners
    void addListener(MidiInputCallback *listener);
    void removeListener(MidiInputCallback *listener);

    // Maintain a part/channel association for all plugin instance
    void setMidiChannelForPart(int deviceNumber, int a[6]);
    int* getMidiChannelForPart(int deviceNumber);

    // == MidiInputCallback
    void handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message);
    void handlePartialSysexMessage(MidiInput *source, const uint8 *messageData, int numBytesSoFar, double timestamp);

    int getDefaultDeviceNumber() { return defaultDeviceNumber; }

private:
    String synthName;
	ApplicationProperties appProperties;
	bool showErrorMEssage;
	CriticalSection messageLock;
	MidiInputCallbackList listeners;
    int lastUsedDevice;
    int defaultDeviceNumber;
    struct OpenedDevice devices[NUMBER_OF_DEVICES];

};


#endif