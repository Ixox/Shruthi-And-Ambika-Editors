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

#include "JuceHeader.h"


struct AmbikaNotes {
    uint8 data1;
    uint8 data2;
    uint8 getNote() {
        return data1 & 0x7F;
    }
    uint8 getVelocity() {
        return data2 & 0x7F;
    }
    bool isLegato() {
        return data2 & 0x80;
    }
    bool isGate() {
        return data1 & 0x80;
    }
};
struct AmbikaSequencer {
    uint8 seqController1[16];
    uint8 seqController2[16];
    struct AmbikaNotes seqNotes[16];
};