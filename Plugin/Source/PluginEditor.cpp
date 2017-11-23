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

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "UI/MainTabs.h"

//==============================================================================
ShruthiAudioProcessorEditor::ShruthiAudioProcessorEditor(ShruthiAudioProcessor* ownerFilter)
	: AudioProcessorEditor(ownerFilter)
{
    setResizable(true, true);
    this->ownerFilter = ownerFilter;
	addAndMakeVisible(mainTabs = new MainTabs());
	mainTabs->buildParameters(getAudioProcessor());

	// This is where our plugin's editor size is set.
	setSize(1000, 750);

	startTimer(100);
	uiOutOfSync = false;
}

ShruthiAudioProcessorEditor::~ShruthiAudioProcessorEditor()
{
	this->ownerFilter->editorClosed();
	delete mainTabs;
}

//==============================================================================
void ShruthiAudioProcessorEditor::paint(Graphics& g)
{
}


void ShruthiAudioProcessorEditor::resized() {
	mainTabs->setSize(getWidth(), getHeight());
}


void ShruthiAudioProcessorEditor::updateUIWith(std::unordered_set<String> &paramSet) {
	this->parametersToUpdateMutex.lock();
	for (std::unordered_set<String>::iterator it = paramSet.begin(); it != paramSet.end(); ++it) {
		this->parametersToUpdate.insert(*it);
	}
	this->parametersToUpdateMutex.unlock();
}


void ShruthiAudioProcessorEditor::removeParamToUpdateUI(String paramName) {
	this->parametersToUpdateMutex.lock();
	if (this->parametersToUpdate.count(paramName) > 0) {
		this->parametersToUpdate.erase(paramName);
	}
	this->parametersToUpdateMutex.unlock();
}

void ShruthiAudioProcessorEditor::timerCallback() {
	if (this->parametersToUpdate.size() > 0) {
		std::unordered_set<String> newSet;
		this->parametersToUpdateMutex.lock();
		newSet.swap(this->parametersToUpdate);
		this->parametersToUpdateMutex.unlock();
		mainTabs->updateUI(newSet);
	}
}


void ShruthiAudioProcessorEditor::setMidiOutBuffer(MidiBuffer *midiOutBuffer) {
	mainTabs->setMidiOutBuffer(midiOutBuffer);
}


void ShruthiAudioProcessorEditor::setMidiChannel(int newMidiChannel) {
	mainTabs->setMidiChannel(newMidiChannel);
}


void ShruthiAudioProcessorEditor::setPresetName(String presetName) {
	mainTabs->setPresetName(presetName);
}




