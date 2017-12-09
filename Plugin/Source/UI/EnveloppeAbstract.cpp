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


#include "EnveloppeAbstract.h"

 //==============================================================================
EnveloppeAbstract::EnveloppeAbstract()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.
	this->scaleX = 1;
	this->scaleY = 1;
	this->draggingPointIndex = -1;
	this->overPointIndex = -1;
	this->xMax = 4.0;
}

EnveloppeAbstract::~EnveloppeAbstract()
{
}

void EnveloppeAbstract::updatePointPositions() {
	float allX = 0;
	for (int p = 0; p < pointList.size(); p++) {
		allX += pointList[p].get()->getX();
	}

	allX = allX < this->xMax ? this->xMax : allX;
	scaleX = (getWidth() - MARGIN_HORIZONTAL - MARGIN_HORIZONTAL) / allX;
	// y is always 0 to 127
    scaleY = (float)(getHeight() - MARGIN_VERTICAL - MARGIN_VERTICAL) / 127.0f;
	float offsetX = MARGIN_HORIZONTAL;
	for (int k = 0; k < pointList.size(); k++) {
		float xPositionOnScreen = offsetX + pointList[k].get()->getX() * scaleX;
		float yPositionOnScreen = getHeight() - pointList[k].get()->getY() * scaleY - MARGIN_VERTICAL;
		pointList[k].get()->setPositionOnScreen(xPositionOnScreen, yPositionOnScreen);
		offsetX = xPositionOnScreen;
	}
}

void EnveloppeAbstract::paint(Graphics& g)
{
    updatePointPositions();

    g.setColour(findColour(ComboBox::backgroundColourId));
    g.fillRect(getLocalBounds().reduced(MARGIN_HORIZONTAL, MARGIN_VERTICAL));

	float lineX = scaleX * 10;
	g.setColour(Colours::grey);
	while (lineX < getWidth() - MARGIN_HORIZONTAL) {
		g.drawVerticalLine((int)(lineX + MARGIN_HORIZONTAL), MARGIN_VERTICAL, (float)getHeight() - MARGIN_VERTICAL);
		lineX += scaleX * 10;
	}
	g.drawVerticalLine(MARGIN_HORIZONTAL, (float)MARGIN_VERTICAL, (float)getHeight() - MARGIN_VERTICAL);
	g.drawVerticalLine(getWidth() - MARGIN_HORIZONTAL, (float)MARGIN_VERTICAL, (float)getHeight() - MARGIN_VERTICAL);
	g.drawHorizontalLine(MARGIN_VERTICAL, (float)MARGIN_HORIZONTAL, (float)getWidth() - MARGIN_HORIZONTAL);
	g.drawHorizontalLine(getHeight() - MARGIN_VERTICAL, (float)MARGIN_HORIZONTAL, (float)getWidth() - MARGIN_HORIZONTAL);

	// Draw main enveloppe shape
	g.setColour(Colours::whitesmoke);
	Path path;
	path.startNewSubPath(pointList[0].get()->getPositionOnScreenX(),
		pointList[0].get()->getPositionOnScreenY());
	for (int p = 1; p < pointList.size(); p++) {
		path.lineTo(pointList[p].get()->getPositionOnScreenX(),
			pointList[p].get()->getPositionOnScreenY());
	}
	g.setColour(Colours::whitesmoke);
	g.strokePath(path, PathStrokeType(1.8f, PathStrokeType::beveled, PathStrokeType::rounded));

	// Back to bottom
	path.lineTo(pointList[pointList.size() - 1].get()->getPositionOnScreenX(),
		pointList[0].get()->getPositionOnScreenY());

	// Back to first point
	path.lineTo(pointList[0].get()->getPositionOnScreenX(),
		pointList[0].get()->getPositionOnScreenY());
	g.setColour(Colour(0x33bbbbbb));
	g.fillPath(path);

    g.setColour(findColour(Slider::rotarySliderFillColourId));
    for (int p = 1; p < pointList.size(); p++) {
		if (draggingPointIndex == p) {
			g.fillEllipse((float)pointList[p].get()->getPositionOnScreenX() - CIRCLE_RAY,
				(float)pointList[p].get()->getPositionOnScreenY() - CIRCLE_RAY,
				CIRCLE_RAY*2.0f, CIRCLE_RAY*2.0f);

			if (!pointList[p].get()->isYConstrained()) {
				g.drawVerticalLine((int)pointList[p].get()->getPositionOnScreenX(), (float)MARGIN_VERTICAL, (float)getHeight() - MARGIN_VERTICAL);
			}
			if (!pointList[p].get()->isXConstrained()) {
				g.drawHorizontalLine((int)pointList[p].get()->getPositionOnScreenY(), (float)MARGIN_HORIZONTAL, (float)getWidth() - MARGIN_HORIZONTAL);
			}
		}
		else {
			if (overPointIndex == p) {
				if (!pointList[p].get()->isYConstrained()) {
					g.drawVerticalLine((int)pointList[p].get()->getPositionOnScreenX(), (float)MARGIN_VERTICAL, (float)getHeight() - MARGIN_VERTICAL);
				}
				if (!pointList[p].get()->isXConstrained()) {
					g.drawHorizontalLine((int)pointList[p].get()->getPositionOnScreenY(), (float)MARGIN_HORIZONTAL, (float)getWidth() - MARGIN_HORIZONTAL);
				}
				g.drawEllipse((float)pointList[p].get()->getPositionOnScreenX() - CIRCLE_RAY,
					(float)pointList[p].get()->getPositionOnScreenY() - CIRCLE_RAY,
					CIRCLE_RAY * 2.0f, CIRCLE_RAY * 2.0f, 1.0f);
			}
			else {
				g.fillEllipse((float)pointList[p].get()->getPositionOnScreenX() - 2,
					(float)pointList[p].get()->getPositionOnScreenY() - 2,
					5.0f, 5.0f);
			}
		}
	}
}


void EnveloppeAbstract::mouseMove(const MouseEvent &event) {
    int legacyOverPointIndex = overPointIndex;
    if (mouseMove_hook(event)) {
        if (legacyOverPointIndex != overPointIndex) {
            repaint();
        }
        return;
    }
    int closestPoint = -1;
    float smallestDistance = 999999999999;
    for (int p = pointList.size() - 1; p > 0; p--) {
        float distance = pow(event.x - pointList[p].get()->getPositionOnScreenX(), 2) + pow(event.y - pointList[p].get()->getPositionOnScreenY(), 2);
        if (closestPoint == -1 || distance < smallestDistance) {
            closestPoint = p;
            smallestDistance = distance;
        }
    }

	if (overPointIndex != closestPoint) {
		overPointIndex = closestPoint;
		repaint();
	}
    return;
}

void EnveloppeAbstract::mouseExit(const MouseEvent &event) {
	overPointIndex = -1;
	repaint();
}



void EnveloppeAbstract::mouseDown(const MouseEvent &event) {
	if (overPointIndex != -1) {
		draggingPointIndex = overPointIndex;
		startDragX = (float)event.x;
		startDragY = (float)event.y;
		repaint();
		return;
	}
}

void EnveloppeAbstract::mouseUp(const MouseEvent &event) {
	if (draggingPointIndex != -1) {
		draggingPointIndex = -1;
	}
	setMouseCursor(MouseCursor::NormalCursor);
	repaint();
}

void EnveloppeAbstract::mouseDrag(const MouseEvent &event) {
	if (draggingPointIndex == -1) {
		return;
	}
	float slowMoveRatio = (event.mods.isCtrlDown() || event.mods.isRightButtonDown() ? .05f : 1.0f);
	float oldVX = pointList[draggingPointIndex].get()->getX();
	pointList[draggingPointIndex].get()->setX(pointList[draggingPointIndex].get()->getX() + (event.x - startDragX) / scaleX * slowMoveRatio);
	float oldVY = pointList[draggingPointIndex].get()->getY();
	pointList[draggingPointIndex].get()->setY(pointList[draggingPointIndex].get()->getY() - (event.y - startDragY) / scaleY * slowMoveRatio);
	if (oldVX != pointList[draggingPointIndex].get()->getX()) {
		// Tell listeners
		notifyObservers(draggingPointIndex, true);
		startDragX = (float)event.x;
	}
	if (oldVY != pointList[draggingPointIndex].get()->getY()) {
		// Tell listeners
		notifyObservers(draggingPointIndex, false);
		startDragY = (float)event.y;
	}
	repaint();
}

void EnveloppeAbstract::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
}

int EnveloppeAbstract::getNumberOfPoints() const { return pointList.size(); }
float EnveloppeAbstract::getX(int index) const { return pointList[index].get()->getX(); }
float EnveloppeAbstract::getY(int index) const { return pointList[index].get()->getY(); }
void EnveloppeAbstract::setX(int index, float x) { pointList[index].get()->setX(x); }
void EnveloppeAbstract::setY(int index, float y) { pointList[index].get()->setY(y); }


