# Shruthi software editor

Here is the github repository of the Ixox Shruthi Editor. <br />
<br />
This is a software editor for mac and windows. It's available as a standalone editor and as a plugin (VST/AU).<br />
This editor talks directly to the Shruthi, so it's very easy to setup and should work with all DAWs. <br />
The midi device you select in the plugin must not be used by your DAW.<br />
The plugin keeps in sync the 3 references :<br />
* The DAW for automation
* The shruthi itself
* The plugin UI<br />

Each modification you make one one of the 3 is propagated to the 2 others.<br />
Once you have a preset you like on your Shruthi, just press the PULL button to retrieve the current preset. After that you can start use the automation in your DAW for any parameter or just modify the preset with the plugin UI.<br />
The states of the UI is saved with your song, and next time you'll load it, you'll retrieve the exact same sounds. You don't even need to save the preset on your Shruthi Eprom.<br />
<br />

It's using the very nice [JUCE library](https://www.juce.com/discover) and looks like this :<br />
<img src='Images/shruthiEditor1.png' width='400px' /><br />
<img src='Images/shruthiEditor2.png' width='400px' /><br />
<img src='Images/shruthiEditor3.png' width='400px' /><br />
<br />
Binaries are available in the Releases area, <a href="https://github.com/Ixox/shruthiEditor/releases">here</a>.<br />
<br />
Xavier Hosxe
