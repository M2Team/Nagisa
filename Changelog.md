# Nagisa - Changelog

**Nagisa 0.1.11**
- Add M2-Team Common Library (m2base.h) for charset encoding convertion
- Add Nagisa.Version.h for synchronizing the version number
- Set compiler options for all sub-projects: /W4 /WX
- Ignore *.user

**Nagisa 0.1.10**
- Add support for HTTPS
- Add get ErrorCode by COMException for await for C++/CX in Nagisa.Shared\M2AsyncWait.h

**Nagisa 0.1.9**
- Add Nagisa.Shared Project
- Implement await for C++/CX in Nagisa.Shared\M2AsyncWait.h
- Add WebHostHidden attribute for NagisaCore.BackgroundTask
- Fix HTTP Request Header for get non-compressed content
- Nagisa now can split HTTP Response Header and show them in the OutputConsole
- Nagisa now can write to file correctly

**Nagisa 0.1.8**
- Add and start implementing SocketDemo
- SocketDemo now can save HTTP Response in a file 

**Nagisa 0.1.7**
- Remove year in the LegalCopyright element in Version Resources
- Add NagisaCore.BackgroundTask Class
- Add BackgroundTask to AppX manifest

**Nagisa 0.1.6**
- Add NagisaCore Component
- Move Nagisa.Configuration Class to NagisaCore.Configuration Class

**Nagisa 0.1.5**
- Add Nagisa.Configuration Class
- Fix Debug Console can't display any content when loaded
- Fix crash when the Root Folder was deleted
- Remove C++/CX PPL library to Reduce the binary size
- Add ConsoleWriteLine function for print text to the Debug Console

**Nagisa 0.1.4**
- Add the Default Save Folder Settings
- Add the Console for Debug
- Start implementing FileWriter

**Nagisa 0.1.3**
- Add the FilePicker and some controls to UI

**Nagisa 0.1.2**
- Modify the Icon to improve effects in Start
- Add the Version Info
- Implement the rough UI

**Nagisa 0.1.1**
- Initial Release after Nagisa Restart
- Add Source of Nagisa's Icon
- Update the Nagisa's Assets
- Change the MSBuild Output Folder
- Add the Changelog Document
