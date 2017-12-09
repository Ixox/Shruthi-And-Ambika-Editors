/*
 * Copyright 2014 Xavier Hosxe
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


#ifndef ENVELOPPEABTRACT_H_INCLUDED
#define ENVELOPPEABTRACT_H_INCLUDED

#include <stdlib.h>
#include "JuceHeader.h"
#include "EnveloppeListener.h"

namespace juce { class MouseEvent; }

#define CIRCLE_RAY 5
#define MARGIN_VERTICAL 12
#define MARGIN_HORIZONTAL 12

#define RIGHT_TEXT_SIZE  120



class EnveloppePoint;

//==============================================================================


class EnveloppeAbstract : public Component
{
public:
	EnveloppeAbstract();
	~EnveloppeAbstract();

	void paint(Graphics&);
	virtual void resized();
	void updatePointPositions();
	void setXMax(float x) { xMax = x; }
    virtual bool mouseMove_hook(const MouseEvent &event) { return false; };
    void mouseMove(const MouseEvent &event) override;
    void mouseDrag(const MouseEvent &event) override;
	void mouseDown(const MouseEvent &event) override;
	void mouseUp(const MouseEvent &event) override;
    void mouseExit(const MouseEvent &event) override;
    virtual void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) override {};

    // Can be implemented to deal with point value modification
	virtual void newXValue(int draggingPointIndex, float newX) {};
	virtual void newYValue(int draggingPointIndex, float newY) {};

	int getNumberOfPoints() const;
	float getX(int index) const;
	float getY(int index) const;
	void setX(int index, float x);
	void setY(int index, float y);

	virtual const char ** getPointSuffix() const = 0;
	virtual const char *getPointSuffix(int pointNumber, bool isX) const = 0;

	/**
	 * Enveloppe Listener Methods
	 */
	void addListener(EnveloppeListener *listener) {
		listeners.push_back(listener);
	}

	void removeListener(EnveloppeListener *listener) {
		EnveloppeListenerList::iterator iterator = listeners.begin();
		while (iterator != listeners.end() && listeners.size() > 0) {
			if (*iterator == listener) {
				iterator = listeners.erase(iterator);
			}
			else {
				++iterator;
			}
		}
	}

	void notifyObservers(int pointNumber, bool isX) const {
		for (EnveloppeListenerList::const_iterator iterator = listeners.begin(); iterator != listeners.end(); ++iterator) {
			(*iterator)->enveloppeValueChanged(this, pointNumber, isX);
		}
	}


protected:
	LinkedListPointer<EnveloppePoint> pointList;
	volatile int draggingPointIndex;
	int overPointIndex;
	EnveloppeListenerList listeners;

private:

	float xMax;
	float scaleX, scaleY;
	float startDragX, startDragY;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnveloppeAbstract)

};


class EnveloppePoint {
	friend class LinkedListPointer<EnveloppePoint>;
public:
	EnveloppePoint(EnveloppeAbstract* myEnv, int index, float xMin, float xMax, float yMin, float yMax) {
		this->x = 0.0f;
		this->y = 0.0f;
		this->xMin = xMin;
		this->yMin = yMin;
		this->xMax = xMax;
		this->yMax = yMax;
		this->positionInComponentX = 0;
		this->positionInComponentY = 0;
		this->myEnv = myEnv;
		this->index = index;
	}
	void setX(float x, bool notification = true) {
		this->x = x > xMax ? xMax : (x < xMin ? xMin : x);
		if (notification) {
			this->myEnv->newXValue(index, this->x);
		}
	}
	void setY(float y, bool notification = true) {
		this->y = y > yMax ? yMax : (y < yMin ? yMin : y);
		if (notification) {
			this->myEnv->newYValue(index, this->y);
		}
	}

	void setXFixedValue(float value) { this->x = value; this->xMax = value; this->xMin = value; }
	void setYFixedValue(float value) { this->y = value; this->yMax = value; this->yMin = value; }
	bool isXConstrained() { return this->xMax == this->xMin; };
	bool isYConstrained() { return this->yMax == this->yMin; };
	float getX() { return this->x; }
	float getY() { return this->y; }
	float getPositionOnScreenX() { return this->positionInComponentX; }
	float getPositionOnScreenY() { return this->positionInComponentY; }
	void setPositionOnScreen(float xOnScreen, float yOnScreen) {
		this->positionInComponentX = xOnScreen;
		this->positionInComponentY = yOnScreen;
	}
private:
	// A linkable object must contain a member with this name and type, which must be
	// accessible by the LinkedListPointer class. (This doesn't mean it has to be public -
	// you could make your class a friend of a LinkedListPointer<MyObject> instead).
	LinkedListPointer<EnveloppePoint> nextListItem;
	float x, xMin, xMax;
	float y, yMin, yMax;
	float positionInComponentX;
	float positionInComponentY;
	EnveloppeAbstract *myEnv;
	int index;
};



#endif  // ENVELOPPEABTRACT_H_INCLUDED

