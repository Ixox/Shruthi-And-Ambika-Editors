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


#pragma once

#include "AudioProcessorCommon.h"
#include "UI/Ambika/AmbikaMultiData.h"
#include "UI/Ambika/AmbikaSequencer.h"

class AudioProcessorAmbika : AudioProcessorCommon {
public:
    AudioProcessorAmbika();
    void initAllParameters();
    char sysexMachineCode() override;
    void decodeSysexPatch(const uint8* message) override;
    void decodeSysexSequencer(const uint8* message) override;
    void encodeSysexPatch(uint8* message) override;
    void requestPatchTransfer() override;
    void requestSequencerTransfer() override;
    void requestPartDataTransfer();
    void decodeMultiData(const uint8* message) override;
    String getSynthName() override;
    void sendSequencerToSynth(uint8* seq);
    uint8* getSequencerData() override { return (uint8*)&sequencer; }
    // MISettingsListener
    bool needsPart() override;
    bool needsPresetName() override;
    bool needsRealTimeUpdate() override;
    void setRealTimeUpdate(int param, int value) override;

    void setAmbikaMultiDataUI(AmbikaMultiDataUI* amd) override { ambikaMultiDataUI = amd;  }
    void sendMultiDataToAmbika(MultiData* md) override;
    void setMultiDataUsed(bool mdu) override;

    void requestMultiDataTransfer() override;

    void setStateParamSpecific(XmlElement* xmlState) override;
    void getStateParamSpecific(XmlElement* xmlState) override;

    void updateMidiChannelFromPart(MultiData* md);
    void decodeSysexPartData(const uint8* pdata) override;
    void choseNewMidiDevice() override;

private:
    AmbikaMultiDataUI* ambikaMultiDataUI;
    bool isMultiDataUsed;
    struct MultiData multiData;
    struct AmbikaSequencer sequencer;
    bool canReceiveSysexPartData;
    uint8 seqController[2][16];

};