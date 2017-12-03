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


// This class must be used with a SharedResourcePointer so that multiple instance of a plugin use the same port
class MidiDevice : public MidiInputCallback
{
public:
    // There's no need to ever create an instance of this class directly yourself,
    // but it does need a public constructor that does the initialisation.
    MidiDevice();
    ~MidiDevice();

    MidiOutput* getMidiOutput() {
        return pfm2MidiOutput;
    }

    MidiInput* getMidiInput() {
        return pfm2MidiInput;
    }
    void resetDevices();
    int choseNewDevices(String synthName);
    int forceChoseNewDevices(String synthName);
    void sendBlockOfMessagesNow(MidiBuffer& midiBuffer, String synthName);
    // == MidiInputCallback
    void handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message);
    void handlePartialSysexMessage(MidiInput *source, const uint8 *messageData, int numBytesSoFar, double timestamp);
    // Listeners
    void addListener(MidiInputCallback *listener);
    void removeListener(MidiInputCallback *listener);

    // Maintain a part/channel association for all plugin instance
    void setMidiChannelForPart(int a[6]);
    int* getMidiChannelForPart();

private:
	ApplicationProperties pfm2AppProps;
	bool showErrorMEssage;
	CriticalSection messageLock;
	MidiOutput* pfm2MidiOutput;
	String currentMidiOutputDevice;
	MidiInput* pfm2MidiInput;
	String currentMidiInputDevice;
	MidiInputCallbackList listeners;
    int midiChannelForPart[6];
};




#endif