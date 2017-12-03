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


#ifndef PANELOFPARAMETERS_CPP_INCLUDED
#define PANELOFPARAMETERS_CPP_INCLUDED

#include <unordered_set>
#include "JuceHeader.h"
#include "EnveloppeAbstract.h"
#include "EnveloppeListener.h"
#include "ComboAndSlider.h"
#include "../Utils/MidifiedFloatParameter.h"

#define TYPE_NOT_HERE  0
#define TYPE_COMBO     1
#define TYPE_SLIDER    2
#define TYPE_STEP_SEQ  3
#define TYPE_ENVELOPPE 4
#define TYPE_COMBO_AND_SLIDER 5
#define TYPE_BUTTON 6


class PanelOfComponents : public EnveloppeListener

{
public:
	~PanelOfComponents() {
	}


	void setParameterSet(AudioProcessor* audioProcessor) {
		this->audioProcessor = audioProcessor;
		parameterMap.clear();
	}

	virtual void buildParameters() = 0;

	void updateSliderFromParameter(Slider* slider) {

		String componentName = slider->getName();
		if (componentMap[componentName] == nullptr) {
			componentMap.set(componentName, slider);
		}

		MidifiedFloatParameter * parameter = checkParamExistence(componentName);

		// And let's update the value and update the UI Without sending modification !!!
		// No modification : we dont want sliderValueChanged to be called in the different panels
		slider->setValue(parameter->getRealValue(), dontSendNotification);

		// Will remove that later but dont' BUG for the moment if that doesn't fit
		if (parameter == nullptr) {
			return;
		}

		updateSliderFromParameter_hook(slider);
	}

	MidifiedFloatParameter* checkParamExistence(String componentName) {

		MidifiedFloatParameter* parameter = parameterMap[componentName];
		if (parameter == nullptr) {
			const OwnedArray<AudioProcessorParameter>& parameters = audioProcessor->getParameters();
			for (int p = 0; p < parameters.size(); p++) {
				parameter = (MidifiedFloatParameter*)parameters[p];
				if (parameter->getName() == componentName) {
					parameterMap.set(componentName, parameter);
					break;
				}
			}
		}
		return parameter;
	}


	void updateComboFromParameter(ComboBox* combo) {

		String componentName = combo->getName();
		if (componentMap[componentName] == nullptr) {
			componentMap.set(componentName, combo);
		}

		MidifiedFloatParameter * parameter = checkParamExistence(componentName);

		// Will remove that later but dont' BUG for the moment if that doesn't fit
		if (parameter == nullptr) {
			return;
		}

		// And let's update the value and update the UI Without sending modification !!!
		// No modification : we dont want sliderValueChanged to be called in the different panels
		if (combo->getSelectedId() != (int)(parameter->getRealValue() + 1.0001f)) {
			combo->setSelectedId((int)(parameter->getRealValue() + 1.0001f), dontSendNotification);
			updateComboFromParameter_hook(combo);
        }
	}

    void updateButtonFromParameter(Button* button) {

        String componentName = button->getName();
        if (componentMap[componentName] == nullptr) {
            componentMap.set(componentName, button);
        }

        MidifiedFloatParameter * parameter = checkParamExistence(componentName);

        // Will remove that later but dont' BUG for the moment if that doesn't fit
        if (parameter == nullptr) {
            return;
        }

        // And let's update the value and update the UI Without sending modification !!!
        int buttonState = button->getToggleState() ? 1 : 0;
        if (buttonState != (int)(parameter->getRealValue())) {
            button->setToggleState(((int)parameter->getRealValue()) == 1, dontSendNotification);
            updateButtonFromParameter_hook(button);
        }
    }

    void updateComboAndSliderFromParameter(ComboAndSlider* comboAndSlider) {

        String componentName = comboAndSlider->getName();
        if (componentMap[componentName] == nullptr) {
            componentMap.set(componentName, comboAndSlider);
        }

        MidifiedFloatParameter * parameter = checkParamExistence(componentName);

        // Will remove that later but dont' BUG for the moment if that doesn't fit
        if (parameter == nullptr) {
            return;
        }

        // And let's update the value and update the UI Without sending modification !!!
        // No modification : we dont want sliderValueChanged to be called in the different panels
        if (comboAndSlider->getValue() != (int)(parameter->getRealValue())) {
            comboAndSlider->setValue((int)parameter->getRealValue());
        }
    }


	// Can be overriden by sub classes
	virtual void updateComboFromParameter_hook(ComboBox* combo) { }
    virtual void updateButtonFromParameter_hook(Button* button) { }
    virtual void updateSliderFromParameter_hook(Slider* slider) { }


	// Enveloppe Listener
	void enveloppeValueChanged(const EnveloppeAbstract* enveloppeThatWasMoved, int pointNumber, bool isX)
	{
		enveloppeValueChanged(enveloppeThatWasMoved, pointNumber, isX, true);
	}

	void enveloppeValueChanged(const EnveloppeAbstract* enveloppeThatWasMoved, int pointNumber, bool isX, bool fromPluginUI)
	{
		// Update the value if the change comes from the UI
		if (fromPluginUI) {
			const char* suffix = enveloppeThatWasMoved->getPointSuffix(pointNumber, isX);
			MidifiedFloatParameter * parameterReady = parameterMap[enveloppeThatWasMoved->getName() + suffix];
			if (parameterReady != nullptr) {
				double value;
				if (isX) {
					value = enveloppeThatWasMoved->getX(pointNumber);
				}
				else {
					value = enveloppeThatWasMoved->getY(pointNumber);
				}
				parameterReady->setValueFromUI((float)value);
			}
		}
	}


	void updateUI(std::unordered_set<String> &paramSet) {
		for (std::unordered_set<String>::iterator it = paramSet.begin(); it != paramSet.end();) {
			String name = *it;

			if (!componentType.contains(name)) {
				Component* component = componentMap[name];
				Slider* slider = dynamic_cast<Slider*>(component);
				ComboBox* combo = dynamic_cast<ComboBox*>(component);
                ComboAndSlider* comboAndSlider = dynamic_cast<ComboAndSlider*>(component);
                Button* button = dynamic_cast<Button*>(component);
                if (slider != nullptr) {
					componentType.set(name, TYPE_SLIDER);
				}
				else if (combo != nullptr) {
					componentType.set(name, TYPE_COMBO);
                }
                else if (comboAndSlider != nullptr) {
                    componentType.set(name, TYPE_COMBO_AND_SLIDER);
                }
                else if (button != nullptr) {
                    componentType.set(name, TYPE_BUTTON);
                }
                else if (containsThisParameterAsStepSequencer(name)) {
					componentType.set(name, TYPE_STEP_SEQ);
				}
				else if (containsThisParameterAsEnveloppe(name)) {
					componentType.set(name, TYPE_ENVELOPPE);
				}
				else {
					componentType.set(name, TYPE_NOT_HERE);
				}
			}

			int otherType = componentType[name];
			switch (otherType) {
			case TYPE_SLIDER: {
				Component* component = componentMap[name];
				Slider* slider = dynamic_cast<Slider*>(component);
				updateSliderFromParameter(slider);
				it = paramSet.erase(it);
				break;
			}
			case TYPE_COMBO: {
				Component* component = componentMap[name];
				ComboBox* combo = dynamic_cast<ComboBox*>(component);
				updateComboFromParameter(combo);
				it = paramSet.erase(it);
				continue;
				break;
			}
            case TYPE_COMBO_AND_SLIDER: {
                Component* component = componentMap[name];
                ComboAndSlider* comboAndSlider = dynamic_cast<ComboAndSlider*>(component);
                updateComboAndSliderFromParameter(comboAndSlider);
                it = paramSet.erase(it);
                continue;
                break;
            }
            case TYPE_BUTTON: {
                Component* component = componentMap[name];
                Button* button = dynamic_cast<Button*>(component);
                updateButtonFromParameter(button);
                it = paramSet.erase(it);
                continue;
                break;
            }
            case TYPE_STEP_SEQ:
				updateUIStepSequencer(name);
				it = paramSet.erase(it);
				break;
			case TYPE_ENVELOPPE:
				updateUIEnveloppe(name);
				it = paramSet.erase(it);
				break;
			case TYPE_NOT_HERE:
				// Look next
				++it;
				break;
			}

		}
	}
	virtual bool containsThisParameterAsEnveloppe(String paramName) { return false; }
	virtual bool containsThisParameterAsStepSequencer(String paramName) { return false; }
	virtual void updateUIEnveloppe(String paramName) {}
	virtual void updateUIStepSequencer(String paramName) {}



protected:
	HashMap<const String, MidifiedFloatParameter *> parameterMap;
	HashMap<const String, Component*> componentMap;
	HashMap<const String, int> componentType;
	AudioProcessor* audioProcessor;
};


#endif  // PANELOFPARAMETERS_CPP_INCLUDED
