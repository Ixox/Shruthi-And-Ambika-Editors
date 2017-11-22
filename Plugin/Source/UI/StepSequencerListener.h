/*
  ==============================================================================

    StepSequencer.h
    Created: 7 Apr 2014 9:40:09pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef STEPSEQUENCERLISTENER_H_INCLUDED
#define STEPSEQUENCERLISTENER_H_INCLUDED

class StepSequencer;

class StepSequencerListener {
public:
    virtual ~StepSequencerListener() {}
    virtual void stepSeqSequencerChanged(const StepSequencer* stepSeqThatChanged, int stepNumber) = 0;
};

typedef std::vector<StepSequencerListener *> StepSequencerListenerList;

#endif  // STEPSEQUENCERLISTENER_H_INCLUDED
