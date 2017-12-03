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



#define NUMBER_OF_VOICES 6
#define NUMBER_OF_KNOBS 8



struct KnobAssignment {
    uint8_t part;
    uint8_t parameter;
    uint8_t instance;
};

struct PartMapping {
    uint8_t midi_channel;
    uint8_t keyrange_low;
    uint8_t keyrange_high;
    uint8_t voice_allocation;

    inline uint8_t receive_channel(uint8_t channel) const {
        return !midi_channel || (channel + 1 == midi_channel);
    }

    inline uint8_t accept_note(uint8_t note) const {
        if (keyrange_low <= keyrange_high) {
            return (note >= keyrange_low && note <= keyrange_high);
        }
        else {
            return note <= keyrange_high || note >= keyrange_low;
        }
    }

    inline uint8_t accept_channel_note(uint8_t channel, uint8_t note) const {
        return receive_channel(channel) && accept_note(note);
    }

    inline uint8_t tx_channel() const {
        return midi_channel == 0 ? 0 : midi_channel - 1;
    }
};

struct MultiData {
    // Offset: 0-24
    PartMapping part_mapping_[NUMBER_OF_VOICES];

    // Offset: 24-28
    uint8_t clock_bpm;
    uint8_t clock_groove_template;
    uint8_t clock_groove_amount;
    uint8_t clock_release;

    // Offset: 28-52
    KnobAssignment knob_assignment[NUMBER_OF_KNOBS];

    // Offset: 52-56
    uint8_t padding2[4];
};


class AmbikaMultiData {
public:
    virtual MultiData* getMultiData() = 0;
    virtual void setMultiData(MultiData* md) = 0;
    virtual bool isMultiDataUsed() = 0;
    virtual void setMultiDataUsed(bool mdu) = 0;
};