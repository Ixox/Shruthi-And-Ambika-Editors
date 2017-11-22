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


#ifndef SHRUTHI_SEQUENCER_H_
#define SHRUTHI_SEQUENCER_H_

#include "sequencer_settings.h"

class ShruthiSequencer {
public:
    virtual shruthi::SequenceStep* getSequencerSteps() = 0;
    virtual void setSequencerSteps(shruthi::SequenceStep newSteps[16]) = 0;
};

#endif // SHRUTHI_SEQUENCER_H_
