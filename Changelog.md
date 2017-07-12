# Nagisa - Changelog

**Nagisa 0.1.19**
- I have registered the Windows Developer Account with Microsoft Imagine
  - I verified my identity by contacting Microsoft because the following reasons: 
    - Only teachers have the chance to own their edu e-mail address in my school.
	- I am unable to get a debit card with Visa or MasterCard because my country only have debit cards with UnionPay now.
  - Thanks to Jiaen Lee (Microsoft Imagine Student Support)
- Associate Nagisa to the Windows Developer Account
- Add Assassin.TransferStatus enum
  - Add Transfering enum
  - Add Paused enum
  - Add Error enum
  - Add Completed enum
- Add Assassin.TransferTask class
  - Add Link property
  - Add Name property
  - Add StorageAccessName property
  - Add IsSelected property
  - Add Status property
  - Add TotalBytesToReceive property
  - Add BytesReceived property
  - Add Bandwidth property
  - Add MaxBandwidth property
- Exclude the AppXPackage output folder

**Nagisa 0.1.18**
- Change default language to "en" in the appxmanifest file for reduce the warning
- The color themes follow the Windows settings
- Exclude the AppXPackage output folder
- Add new MainPage UI and make command bar and search box multilingual
  - Thanks to 落樱 (https://github.com/SakuraNeko)
  - Thanks to 鳶一雨音 (https://github.com/TobiichiAmane)
  - Thanks to Calyx Hikari (https://github.com/HikariCalyx)

**Nagisa 0.1.17**
- Update the license's copyright
- Add Assassin.TransferManager class for controlling the background task
- Add support for multi languages (Now support Simplified Chinese and English)
- Replace MainPage.xaml to blank page for adding new UI

**Nagisa 0.1.16**
- Add sqlite3 library for saving configurations

**Nagisa 0.1.15**
- Improve the implemention of m2_async function
  - Add m2_remove_cx_ref for get asynchronous completed hander type 
    - Thanks to Pointer ([Vczh]GacUI讨论群)
	- Thanks to Zihan Chen (https://github.com/vczh)
  - Add m2_await_internal for streamlining the code
- Using "using namespace Assassin;" in Assassin project for streamlining the code
- Add Assassin.BackgroundWorker class for implementing the background task
- Change the previous description of Changelog.md

**Nagisa 0.1.14**
- Add Assassin project for replacing NagisaCore project
  - Move NagisaCore.Configuration class to Assassin.Configurations class
  - Add Version property in Assassin.Configurations class
  - Add UserAgent property in Assassin.Configurations class
- Remove NagisaCore project

**Nagisa 0.1.13**
- Add m2_await function for waiting asynchronous call in m2async.h
- Remove M2AsyncWait.h because M2AsyncWait function is replaced by m2_await
- Fix a bug from SocketDemo
- Using IBufferByteAccess to read IBuffer instead of DataReader::FromBuffer
- Add comment in m2base.h

**Nagisa 0.1.12**
- Modify the implementation of NagisaCore.Configuration Class
- Ignore *.user for privacy

**Nagisa 0.1.11**
- Add M2-Team Common Library (m2base.h) for charset encoding convertion
  - Thanks to Force.Charlie-I (https://github.com/fcharlie)
- Add Nagisa.Version.h for synchronizing the version number
- Set compiler options for all sub-projects: /W4 /WX
- Remove *.user for privacy

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
