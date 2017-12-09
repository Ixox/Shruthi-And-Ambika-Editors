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

#ifdef AMBIKA
#include "Ambika/AmbikaMultiData.h"
#endif
#ifdef SHRUTHI
#include "Shruthi/FilterTypeUI.h"
#endif

class MISettingsListener {
public:
    virtual void midiChannelChanged(int newMidiChannel) = 0;
    virtual void partChanged(int newPart) = 0;
    virtual void pushButtonPressed() = 0;
    virtual void pullButtonPressed() = 0;
    virtual bool needsPart() = 0;
    virtual bool needsPresetName() = 0;
    virtual int getMidiChannel() = 0;
    virtual int getPart() = 0;
    virtual void setSelectedTab(int t) = 0;
    virtual int getSelectedTab() = 0;
#ifdef SHRUTHI
    virtual void setFilterType(int ft) = 0;
    virtual void setFilterTypeUI(FilterTypeUI* ftUI) = 0;

#endif
#ifdef AMBIKA
    virtual void setAmbikaMultiDataUI(AmbikaMultiDataUI* amd) = 0;
    virtual void setMultiDataUsed(bool mdu) = 0;
    virtual void setMultiData(MultiData* md) = 0;
    virtual void sendMultiDataToAmbika(MultiData* md) = 0;
    virtual void requestMultiDataTransfer() = 0;
#endif

};