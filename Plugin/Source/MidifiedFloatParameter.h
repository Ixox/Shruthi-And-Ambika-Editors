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


#ifndef MIDIFIEDPARAMETER_H_INCLUDED
#define MIDIFIEDPARAMETER_H_INCLUDED


#include <stdlib.h>
#include <map>
#include "JuceHeader.h"


class ShruthiAudioProcessor;


class MidifiedFloatParameter : public AudioProcessorParameter {
public:

	MidifiedFloatParameter(String componentName,
		int nrpnParam,
		float valueMultipler,
		float minValue,
		float maxValue,
		float defaultValue
	)
		: AudioProcessorParameter(),
		range(minValue, maxValue), value(defaultValue), defaultValue(defaultValue),
		oldXmlName("")
	{
		this->componentName = componentName;
		rangeFloat = maxValue - minValue;
		this->valueMultiplier = valueMultipler;
		this->nrpnParam = nrpnParam;

		bias = 0;
		paramIndex = paramIndexCounter++;
		bIsAutomatable = true;
		isBitField = false;
        useThisCCInteadOfNRPN = -1;
	}


	int getNrpnValueLSB() const {
        int iv = (int)value;
        if (iv >= 0) {
            return iv & 0x7f;
        }
        else {
            return 128 + iv;
        }
	}
	int getNrpnValueMSB() const {
		int iv = (int)value;
        if (iv >= 0) {
            return iv >> 7;
        }
        else {
            return 1;
        }
	}
	int getNrpnParamMSB() const {
		return nrpnParam >> 7;
	}
	int getNrpnParamLSB() const {
		return nrpnParam & 0xff;
	}


	void setProcessor(ShruthiAudioProcessor* audioProcessor) {
		this->audioProcessor = audioProcessor;
	}

	void addNrpn(MidiBuffer& midiBuffer, const int midiChannel);
    void sendCC(MidiBuffer& midiBuffer, const int midiChannel);

	static void resetParamIndexCounter() {
		paramIndexCounter = 0;
	}

	int getParamIndex() const {
		return paramIndex;
	}
	void setBias(float b) {
		this->bias = b;
	}

	float getBias() const {
		return this->bias;
	}
	void setValueFromNrpn(int nrpnValue);
    void setValueFromCC(int ccValue);

	// parameter float
	float get() const noexcept { return value; }
	operator float() const noexcept { return value; }

	void setValue(float newValue);
	void setRealValue(float newValue);
	void setRealValueNoNotification(float newValue) { value = newValue; }

	float getValue() const { return range.convertTo0to1(value); }
	float getRealValue() const { return value; }
	float getDefaultValue() const { return range.convertTo0to1(defaultValue); }
	float getValueForText(const String& text) const { return range.convertTo0to1(text.getFloatValue()); }

	String getText(float v, int length) const
	{
		String asText(range.convertFrom0to1(v), 2);
		return length > 0 ? asText.substring(0, length) : asText;
	}

	String getName() {
		return componentName;
	}

	void setOldName(String oldName) {
		for (int i = 0; i < oldName.length(); ++i) {
			if (((oldName[i] >= 'a' && oldName[i] <= 'z') ||
				(oldName[i] >= '0' && oldName[i] <= '9') ||
				(oldName[i] >= 'A' && oldName[i] <= 'Z'))) {
				oldXmlName += oldName[i];
			}
		}
	}


	String getNameForXML() {
		if (oldXmlName.length() == 0) {
			setOldName(componentName);
		}
		return oldXmlName;
	}

	float getMin() const {
		return range.getRange().getStart();
	}

	float getMax() const {
		return range.getRange().getEnd();
	}

	String getName(int maximumStringLength) const {
		return componentName.substring(0, maximumStringLength);
	}
	String getLabel() const {
		return componentName;
	}

	void setIsAutomatable(bool automatable) {
		bIsAutomatable = automatable;
	}

	bool isAutomatable() const {
		return bIsAutomatable;
	}

	void setIsBitField(bool b);

    void setUseThisCC(int cc);
    bool isCCOnly() { return useThisCCInteadOfNRPN > -1; };

private:
	static int paramIndexCounter;
	float valueMultiplier;
	int nrpnParam;
	int paramIndex;
	float bias;
	String componentName;
	String oldXmlName; // To save XML for compatibility
	NormalisableRange<float> range;
	float value, defaultValue;
	ShruthiAudioProcessor* audioProcessor;
	float rangeFloat;
	bool bIsAutomatable;
	bool isBitField;
    int useThisCCInteadOfNRPN;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidifiedFloatParameter)
};

#endif  // MIDIFIEDPARAMETER_H_INCLUDED
