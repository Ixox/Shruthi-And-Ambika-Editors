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



#include "Enveloppe.h"


 //==============================================================================
Enveloppe::Enveloppe()
{

	this->nrpnBase = -5106546;
	EnveloppePoint* point0 = new EnveloppePoint(this, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	EnveloppePoint* point1 = new EnveloppePoint(this, 1, 0.0f, 127.0f, 127.0f, 127.0f);
	EnveloppePoint* point2 = new EnveloppePoint(this, 2, 0.0f, 127.0f, 63.0f, 63.0f);
	EnveloppePoint* point3 = new EnveloppePoint(this, 3, 10.0f, 10.0f, 0.0f, 127.0f);
	EnveloppePoint* point4 = new EnveloppePoint(this, 4, 0.0f, 127.0f, 0.0f, 0.0f);
	point0->setX(0.0f, false);
	point0->setY(0.0f, false);
	point1->setX(5.0f, false);
	point1->setY(127.0f, false);
	point2->setX(5.0f, false);
	point2->setY(63.0f, false);
	point3->setX(5.0f, false);
	point3->setY(63.0f, false);
	point4->setX(10.0f, false);
	point4->setY(0.0f, false);
	pointList.append(point0);
	pointList.append(point1);
	pointList.append(point2);
	pointList.append(point3);
	pointList.append(point4);
}


Enveloppe::~Enveloppe()
{
}


void Enveloppe::paint(Graphics& g)
{
    Rectangle<int> theseBounds = getBounds();
    setBounds(theseBounds.reduced(10));
    g.setOrigin(10, 15);

	EnveloppeAbstract::paint(g);


	static const String adsr[] = { "A", "D", "S", "R" };
	for (int v = 0; v < 4; v++) {


		if (overPointIndex == v + 1) {
            g.setColour(findColour(Slider::rotarySliderFillColourId));
		}
		else {
			g.setColour(Colours::whitesmoke);
		}
        g.drawText(adsr[v], getWidth() - 80, 10 + v * 20, 50, 20, Justification::centred, true);
        switch (v) {
		case 0:
			g.drawText(String((int)pointList[v + 1].get()->getX()), getWidth() - 50, 10 + v * 20, 50, 20, Justification::centred, true);
			break;
		case 1:
			g.drawText(String((int)pointList[v + 1].get()->getX()), getWidth() - 50, 10 + v * 20, 50, 20, Justification::centred, true);
			break;
		case 2:
			g.drawText(String((int)pointList[v + 1].get()->getY()), getWidth() - 50, 10 + v * 20, 50, 20, Justification::centred, true);
			break;
		case 3:
			g.drawText(String((int)pointList[v + 1].get()->getX()), getWidth() - 50, 10 + v * 20, 50, 20, Justification::centred, true);
			break;
		}
	}
    setBounds(theseBounds);

}


void Enveloppe::newXValue(int draggingPointIndex, float newX) {
}

void Enveloppe::newYValue(int draggingPointIndex, float newY) {
	if (draggingPointIndex == 3) {
		pointList[2].get()->setYFixedValue(newY);
	}
}

static const char* __enveloppeFree2PointSuffix[] = { " Attk", " Deca", " Sust", " Rele" };
const char ** Enveloppe::getPointSuffix() const {
	return __enveloppeFree2PointSuffix;
}

const char* Enveloppe::getPointSuffix(int pointNumber, bool isX) const {
	return __enveloppeFree2PointSuffix[(pointNumber - 1)];
}

bool Enveloppe::mouseMove_hook(const MouseEvent &event) {
    for (int p = 0; p < 4; p++) {
        Point<int> mousePos = event.getPosition();
        mousePos.addXY(-10, -15);
        Rectangle<int> labelRect(getWidth() - 80, 10 + p * 20, 80, 20);
        if (labelRect.contains(mousePos)) {
            overPointIndex = p + 1;
            return true;
        }
    }
    return false;
}

void Enveloppe::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) {
    if (overPointIndex != -1) {
        switch (overPointIndex) {
        case 1:
        case 2:
        case 4:
            pointList[overPointIndex].get()->setX(pointList[overPointIndex].get()->getX() + (wheel.deltaY < 0 ? -1 : 1));
            notifyObservers(overPointIndex, true);
            break;
        case 3:
            pointList[overPointIndex].get()->setY(pointList[overPointIndex].get()->getY() + (wheel.deltaY < 0 ? -1 : 1));
            notifyObservers(overPointIndex, false);
            break;
        }
    }
};


