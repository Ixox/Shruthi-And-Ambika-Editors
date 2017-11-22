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

#include "MyLookAndFeel.h"
#include "SliderPfm2.h"

MyLookAndFeel::MyLookAndFeel() : LookAndFeel_V4() {

	setUsingNativeAlertWindows(false);    
    setColourScheme({
        0xff061723,   // windowBackground = 0,
        0xff061723,  // widgetBackground
        0xff061723,   // menuBackground,
        0xffa6a6a6,   // outline,
        0xffffffff,   // defaultText,
        0xff21ba90,   // defaultFill,
        0xff01FF70,   // highlightedText,
        0xff446686,   // highlightedFill,
        0xffffffff    // menuText,
    });


    Colour selectableItemColour = Colour::fromString("0xff98FB98");
    setColour(ComboBox::textColourId, selectableItemColour);
    // setColour(PopupMenu::textColourId, selectableItemColour);
    setColour(Slider::rotarySliderFillColourId, selectableItemColour);


    Colour backgroundColour = Colour::fromString("0xff002224");
    setColour(PopupMenu::backgroundColourId, backgroundColour);
    setColour(ComboBox::backgroundColourId, backgroundColour);
    setColour(TextButton::buttonOnColourId, backgroundColour);
    setColour(TextButton::buttonColourId, Colour::fromString("0xff173e5a"));



    setColour(Slider::thumbColourId, Colours::white);

    setColour(Slider::rotarySliderOutlineColourId, Colour::fromString("0xff888888"));

    setColour(Label::textColourId, Colour::fromString("0xffe3e3e3"));
}



void MyLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
	const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    const auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
    const auto fill = slider.findColour(Slider::rotarySliderFillColourId);

	const auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(5);

    auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    const auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = jmin(8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;




	Path backgroundArc;
	backgroundArc.addCentredArc(bounds.getCentreX(),
		bounds.getCentreY(),
		arcRadius,
		arcRadius,
		0.0f,
		rotaryStartAngle,
		rotaryEndAngle,
		true);

	g.setColour(outline);
	g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::butt));


	if (slider.isEnabled())
	{
		Path valueArc;
		valueArc.addCentredArc(bounds.getCentreX(),
			bounds.getCentreY(),
			arcRadius ,
			arcRadius ,
			0.0f,
			rotaryStartAngle,
			toAngle,
			true);

        g.setColour(fill);
		g.strokePath(valueArc, PathStrokeType(lineW*.4f , PathStrokeType::curved, PathStrokeType::butt));

		const Point<float> thumbPoint(bounds.getCentreX() + radius * std::cos(toAngle - float_Pi * 0.5f),
			bounds.getCentreY() + radius * std::sin(toAngle - float_Pi * 0.5f));

        g.setColour(slider.findColour(Slider::thumbColourId));
        g.drawLine(bounds.getCentreX(), bounds.getCentreY(), thumbPoint.getX(), thumbPoint.getY());
	}
}


void MyLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
	float sliderPos,
	float minSliderPos,
	float maxSliderPos,
	const Slider::SliderStyle style, Slider& slider)
{
    if (!slider.isEnabled()) {
        return;
    }
    const auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
    const auto fill = slider.findColour(Slider::rotarySliderFillColourId);

    Rectangle<int> sliderBounds(x, y, width, height);
    sliderBounds.reduce(10, 0);
    g.setColour(outline);
    g.fillRect(sliderBounds);

    int newSize = slider.getValue()  * height / slider.getMaximum();               
    if (newSize != 0) {
        g.setColour(fill);
        g.fillRect(sliderBounds.removeFromBottom(newSize).reduced(2, 2));
    }
}


void MyLookAndFeel::drawComboBox(Graphics& g, int width, int height, bool,
	int, int, int, int, ComboBox& box)
{
	const auto cornerSize = box.findParentComponentOfClass<ChoicePropertyComponent>() != nullptr ? 0.0f : 3.0f;
	const Rectangle<int> boxBounds(0, 0, width, height);

	g.setColour(box.findColour(ComboBox::backgroundColourId));
	g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

	g.setColour(box.findColour(ComboBox::outlineColourId));
	g.drawRoundedRectangle(boxBounds.toFloat().reduced(0.5f, 0.5f), cornerSize, 1.0f);

    if (dynamic_cast<RotatingComboBox*>(&box) == nullptr) {
        Rectangle<int> arrowZone(width - 18, 0, 15, height);
        Path path;
        path.startNewSubPath(arrowZone.getX() + 3.0f, arrowZone.getCentreY() - 2.0f);
        path.lineTo(static_cast<float> (arrowZone.getCentreX()), arrowZone.getCentreY() + 3.0f);
        path.lineTo(arrowZone.getRight() - 3.0f, arrowZone.getCentreY() - 2.0f);

        g.setColour(box.findColour(ComboBox::arrowColourId).withAlpha((box.isEnabled() ? 0.9f : 0.2f)));
        g.strokePath(path, PathStrokeType(1.5f));
    }
}


Font MyLookAndFeel::getComboBoxFont(ComboBox& box)
{
	return Font(jmin(14.0f, box.getHeight() * 0.85f));
}


void MyLookAndFeel::positionComboBoxText(ComboBox& box, Label& label)
{
    int arrowSize;
    if (dynamic_cast<RotatingComboBox*>(&box) == nullptr) {
        arrowSize = 18;
    }
    else {
        arrowSize = 0;
    }

	label.setBounds(1, 1,
		box.getWidth() - arrowSize,
		box.getHeight() - 2);

	label.setFont(getComboBoxFont(box));
}





