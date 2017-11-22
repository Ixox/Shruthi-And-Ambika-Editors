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


#ifndef ENVELOPPE_H_INCLUDED
#define ENVELOPPE_H_INCLUDED



#include "JuceHeader.h"
#include "EnveloppeAbstract.h"

 //==============================================================================
 /*
 */
class Enveloppe : public  EnveloppeAbstract
{
public:
	Enveloppe();
	~Enveloppe();

	void paint(Graphics&);
	// override
	// Must be implemented to deal with point value modification
	void newXValue(int draggingPointIndex, float newX);
	void newYValue(int draggingPointIndex, float newY);
	const char ** getPointSuffix() const;
	const char *getPointSuffix(int pointNumber, bool isX) const;
    void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) override;
    bool mouseMove_hook(const MouseEvent &event);

private:

	int nrpnBase;
	EnveloppePoint* decayPoint;
	EnveloppePoint* sustainPoint;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Enveloppe)

};

#endif  // ENVELOPPE_H_INCLUDED
