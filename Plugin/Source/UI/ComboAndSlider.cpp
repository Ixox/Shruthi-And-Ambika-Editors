/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ComboAndSlider.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "SliderPfm2.h"
#define COMBO_SLIDER 9999

//[/MiscUserDefs]

//==============================================================================
ComboAndSlider::ComboAndSlider (String name)
    : Component(name)
{
    //[Constructor_pre] You can add your own custom stuff here..
    addAndMakeVisible(myCombo = new ComboBox(name + "combo"));
    myCombo->setEditableText(false);
    myCombo->setJustificationType(Justification::centred);
    myCombo->setColour(ComboBox::buttonColourId, Colours::blue);
    myCombo->setScrollWheelEnabled(true);
    myCombo->addListener(this);

    addAndMakeVisible(mySlider = new SliderPfm2(name + "slider"));
    mySlider->setSliderStyle(Slider::RotaryVerticalDrag);
    mySlider->setTextBoxStyle(Slider::TextBoxLeft, false, 35, 16);
    mySlider->setDoubleClickReturnValue(true, 0.0f);
    mySlider->setValue(0.0f, dontSendNotification);
    mySlider->addListener(this);
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ComboAndSlider::~ComboAndSlider()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ComboAndSlider::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ComboAndSlider::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    if (myCombo == nullptr || mySlider == nullptr) {
        return;
    }
    Rectangle<int> totalBounds = getLocalBounds();
    myCombo->setBounds(totalBounds.removeFromTop(20).reduced(5, 0));
    mySlider->setBounds(totalBounds);
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void ComboAndSlider::setValue(int v) {
    value = v;
    if (v <= comboLastNrpmParam ) {
        myCombo->setSelectedId(v + 1, dontSendNotification);
        mySlider->setEnabled(false);
    }
    else {
        myCombo->setSelectedId(COMBO_SLIDER, dontSendNotification);
        mySlider->setValue(v - sliderBias, dontSendNotification);
        mySlider->setEnabled(true);
    }
    repaint();
}
int ComboAndSlider::getValue() {
    return value;
}



void ComboAndSlider::sliderValueChanged(Slider *slider) {
    if (myCombo->getSelectedId() != COMBO_SLIDER) {
        myCombo->setSelectedId(COMBO_SLIDER, dontSendNotification);
    }
    value = mySlider->getValue() + sliderBias;
    notifyListeners();
}

void ComboAndSlider::comboBoxChanged(ComboBox *comboBoxThatHasChanged) {
    if (myCombo->getSelectedId() == COMBO_SLIDER) {
        mySlider->setEnabled(true);
        value = mySlider->getValue() + sliderBias;
    }
    else {
        mySlider->setEnabled(false);
        value = comboBoxThatHasChanged->getSelectedId() - 1;
    }
    notifyListeners();
}

void ComboAndSlider::setComboParams(const char* labels[], int comboFirstNrpmParam) {
    myCombo->addItem(labels[0], COMBO_SLIDER);
    int i;
    for (i = 0; labels[i + 1] != nullptr; i++) {
        // item Id is nrpn + 1
        myCombo->addItem(labels[i + 1], comboFirstNrpmParam + i + 1);
        comboLastNrpmParam = comboFirstNrpmParam + i;
    }
    this->comboFirstNrpmParam = comboFirstNrpmParam;
}

void ComboAndSlider::setSliderParams(float min, float max, float bias ) {
    mySlider->setRange(min, max, 1.00f);
    sliderBias = bias;
}


void ComboAndSlider::addListener(Listener *listener) {
    listeners.push_back(listener);
}

void ComboAndSlider::removeListener(Listener *listener) {
    ComboAndSliderListenerList::iterator iterator = listeners.begin();
    while (iterator != listeners.end() && listeners.size() > 0) {
        if (*iterator == listener) {
            iterator = listeners.erase(iterator);
        }
        else {
            ++iterator;
        }
    }
}

void ComboAndSlider::notifyListeners(){
    for (ComboAndSliderListenerList::const_iterator iterator = listeners.begin(); iterator != listeners.end(); ++iterator) {
        (*iterator)->comboOrSliderValueChanged(this);
    }
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ComboAndSlider" componentName=""
                 parentClasses="public Component, public ComboBox::Listener, public Slider::Listener"
                 constructorParams="String name" variableInitialisers="Component(name)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
