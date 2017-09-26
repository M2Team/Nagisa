# Nagisa - Changelog

## Notice
- This is the changelog about project Nagisa.
- For more information on the names of persons mentioned here, please read 
  People.md.
- "r" is the abbreviation of "revision". For example, r1 is revision 1.

## Changelog

**Nagisa 0.1 Preview 1**
- [r89] Synchronize the version and add missing changelog.
- [r88] Update Package.appxmanifest.
- [r87] Update Nagisa.Version.h.
- [r86] Update Changelog.md.
- [r85] Update README.md.
- [r84] Update People.md.
- [r83] Update README.md.
- [r82] Update Documents (#6).
- [r81] Revert "Update Documents" (#5).
- [r80] Merge pull request #4 from MouriNaruto/master.
- [r79] Update People.md.
- [r78] Update the Readme.
- [r77] Modify the format of Changelog.
- [r76] Modify the format of Changelog.
- [r76] Modify the AppX Package output folder.
- [r75] Fix the source code license.
- [r75] Add CustomListViewItemStyle and CustomIconButtonStyle to implement the 
  Nagisa's Task List.
- [r74] Update the copyright of the source code license.
- [r74] Add CustomContentDialogStyle to make the ContentDialog of the Windows 
  10 Build 10240 support the ScrollViewer.
- [r74] Add the warning tip in the "First Run" dialog.
- [r73] Update the documents.
- [r73] Add "First Run" dialog.
- [r72] Improve the implementions. 
- [r71] Fix compile errors in revision 70.
- [r71] Add M2FindSubString() function in Nagisa.Shared project.
- [r70] Remove the useless Nagisa.Assassin.Class1 class created via Visual 
  Studio.
- [r70] Add Nagisa.Assassin.TransferTaskStatus enum to define the status 
  (Canceled, Completed, Error, Paused, Queued, Running) of a transfer task.
- [r70] Add Nagisa.Assassin.TransferTask class to define an object that 
  represents a transfer task.
- [r70] Add Nagisa.Assassin.TransferManager class to provide ways to manage the
  transfer engine.
- [r70] Fix the "local" namespace definition in xaml files.
- [r70] Define the "Assassin" namespace in xaml files.
- [r70] Add fundamental multi languages support (Now plan to support Simplified
  Chinese and English)
- [r69] Add functions in Nagisa.Shared project.
  - M2MakeIBuffer()
  - M2MakeUTF16String()
  - M2MakeUTF8String()
- [r69] Rename functions in Nagisa.Shared project.
  - m2_await_internal() to M2AsyncWait()
  - m2_await() to M2AsyncWait()
  - M2GetPointerFromIBuffer() to M2GetPointer()
- [r68] Update the copyright of the source code license.
- [r68] Add M2GetInspectable() function in Nagisa.Shared project.
- [r68] Modify functions in Nagisa.Shared project
  - m2_await_internal()
  - m2_await()
  - M2GetPointerFromIBuffer()
- [r67] The color themes of Nagisa follows the options in Windows Settings.
- [r67] Change the project type of Nagisa.Shared project.
- [r67] Add functions in Nagisa.Shared project.
  - m2_await_internal()
  - m2_await()
  - M2GetPointerFromIBuffer()
- [r66] Add Nagisa.Application project for implementing the user interface.
- [r66] Add Nagisa.Assassin project for implementing the transfer library.
- [r66] Add Nagisa.Shared project for sharing the source code.
- [r66] Set the output folder.
- [r66] Exclude the output file
- [r66] Use "/W4 /WX" option to compile source code.
- [r66] Add the icon asset.
- [r66] Add the version info in the binaries and version definition header.
- [r66] Associate Nagisa's configuation with my Windows Developer Account.
- [r65] The second time to reset the project.
- [r64] m2_await(): Improve the implementation, use non-blocking way to wait
  asynchronous call and add timeout support. (Nagisa.Shared\m2async.h)
- [r63] The "Settings & About" Dialog has been initially constructed.
- [r62] The "New Task" Dialog has been initially constructed.
- [r62] Add NAGetVersion function for getting the version.
- [r62] Add NAGetDefaultUserAgentString function for getting the default User
  Agent string.
- [r61] Remove all implements to header file for writing code like C#.
- [r61] Add TransferManager::Version property for getting Nagisa's version.
- [r60] Improve the performance by using asynchronous call in Main UI 
  constructor.
- [r60] Reduce the binary size via using std::thread instead of 
  concurrency::create_task()
- [r60] Merge AutoSuggestBox_QuerySubmitted and AutoSuggestBox_TextChanged 
  event to AutoSuggestBox_Search event in Main UI.
- [r60] Improve implementions about waiting asynchronous call.
   (Nagisa.Shared\m2async.h)
- [r60] Improve implementions about creating a IAsyncOperation Windows Runtime 
  asynchronous construct based on a user supplied lambda or function object.
  (Nagisa.Shared\m2async.h)
- [r60] Add TransferManager::GetTasksAsync() for get all transfer tasks or 
  search specific transfer tasks.
- [r59] Add implementions about creating a IAsyncOperation Windows Runtime
  asynchronous construct based on a user supplied lambda or function
  object. (Nagisa.Shared\m2async.h)
- [r59] Add Assassin Library, the transfer engine of project Nagisa
  - Add BackgroundWorker class to do the actual operation in the background
- [r59] Add TransferStatus enum to represent the status of a transfer task
- [r59] Add TransferTask class to represent a transfer task
  - Add TransferManager class to manage the transfer tasks
- [r58] Fix Changelog.
- [r57] Improve the source code. (Unknown Status)
- [r56] Improve the source code. (Unknown Status)
- [r55] Add SettingsAndAboutDialog.
- [r54] Add Assassin.Configurations class
- [r54] Add Assassin.BackgroundWorker class for implementing the background 
  task.
- [r54] Improve Assassin.TransferManager class for controlling the background 
  task.
- [r54] Improve Assassin.TransferTask class for managing the single task.
- [r54] Improve Assassin.TransferStatus enum for getting the task status.
- [r54] Add NagisaListViewItemExpandedStyle to define the ListViewItem style.
- [r54] Add NagisaListViewItemButtonStyle to Define the Button style in the 
  ListViewItem.
- [r54] Add NagisaStatusToForegroundConverter to binding the ProgressBar.
- [r54] Add NagisaStatusToBackgroundConverter to binding the ProgressBar.
- [r54] Add NagisaStatusErrorToVisibilityConverter to binding the Buttons in 
  the ListViewItem.
- [r54] Add NagisaStatusPausedToVisibilityConverter to binding the Buttons in 
  the ListViewItem.
- [r54] Add NagisaStatusRunningToVisibilityConverter to binding the Buttons in 
  the ListViewItem.
- [r54] Add new MainPage UI.
- [r53] Add XamlResources.xaml for defining the Nagisa's Xaml Definitions.
- [r53] Add NagisaContentDialogStyle custom style for Vertical ScrollBar 
  support inthe ContentDialog.
- [r53] Add SettingsAndAboutDialog.
- [r52] Merged the source code from Pull #1.
- [r52] Now you can use Voice Commands (aka Cortana) to activate Nagisa now, 
  and it support Simplified Chinese and English..
- [r52] Add NewTaskDialog.
- [r51] Merge pull request #1 from bianyukun1213/master.
- [r50] Merge branch 'master' into master.
- [r49] Delete VCD.xml. (Commit by bianyukun1213.)
- [r48] Let Nagisa respond Cortana voice commands. (Commit by bianyukun1213.)
- [r47] I have registered the Windows Developer Account with Microsoft Imagine.
- [r47] Associate Nagisa to the Windows Developer Account.
- [r47] Add Assassin.TransferStatus enum.
- [r47] Add Assassin.TransferTask class.
- [r46] Change default language to "en" in the appxmanifest file for reduce the
  warning.
- [r46] The color themes follow the Windows settings.
- [r46] Exclude the AppXPackage output folder.
- [r46] Add new MainPage UI and make command bar and search box multilingual.
- [r45] Update the license's copyright.
- [r45] Add Assassin.TransferManager class for controlling the background task.
- [r45] Add support for multi languages (Now support Simplified Chinese and 
  English).
- [r45] Replace MainPage.xaml to blank page for adding new UI.
- [r44] Update license.
- [r43] Add sqlite3 library for saving configurations.
- [r42] Update Changelog.
- [r41] Update readme.
- [r40] Rechange the license to MIT.
- [r39] Update license and readme.
- [r38] Update readme and license.
- [r37] Update License.
- [r36] Modify the readme.
- [r35] Modify the readme.
- [r34] Modify the changelog.
- [r33] Change the license.
- [r32] Add m2_remove_cx_ref for get asynchronous completed hander type.
- [r32] Add m2_await_internal for streamlining the code.
- [r32] Using "using namespace Assassin;" in Assassin project for streamlining 
  the code.
- [r32] Add Assassin.BackgroundWorker class for implementing the background 
  task.
- [r32] Change the previous description of Changelog.md.
- [r31] Add Assassin project for replacing NagisaCore project.
- [r31] Move NagisaCore.Configuration class to Assassin.Configurations class.
- [r31] Add Version property in Assassin.Configurations class.
- [r31] Add UserAgent property in Assassin.Configurations class.
- [r31] Remove NagisaCore project.
- [r30] Add m2_await function for waiting asynchronous call in m2async.h.
- [r30] Remove M2AsyncWait.h because M2AsyncWait function is replaced by 
  m2_await.
- [r30] Fix a bug from SocketDemo.
- [r30] Using IBufferByteAccess to read IBuffer instead of 
  DataReader::FromBuffer.
- [r30] Add comment in m2base.h.
- [r29] Modify the implementation of NagisaCore.Configuration Class.
- [r29] Ignore *.user for privacy.
- [r28] Remove *.user for privacy.
- [r27] Add M2-Team Common Library (m2base.h) for charset encoding convertion.
- [r27] Add Nagisa.Version.h for synchronizing the version number.
- [r27] Set compiler options for all sub-projects: /W4 /WX.
- [r26] Add get ErrorCode by COMException for await for C++/CX in 
  Nagisa.Shared\M2AsyncWait.h.
- [r25] Add support for HTTPS.
- [r24] Fix version.
- [r23] Add Nagisa.Shared Project.
- [r23] Implement await for C++/CX in Nagisa.Shared\M2AsyncWait.h.
- [r23] Add WebHostHidden attribute for NagisaCore.BackgroundTask.
- [r23] Fix HTTP Request Header for get non-compressed content.
- [r23] Nagisa now can split HTTP Response Header and show them in the 
  OutputConsole.
- [r23] Nagisa now can write to file correctly.
- [r22] SocketDemo now can save HTTP Response in a file.
- [r21] Add and start implementing SocketDemo.
- [r20] Remove year in the LegalCopyright element in Version Resources.
- [r20] Add NagisaCore.BackgroundTask Class.
- [r20] Add BackgroundTask to AppX manifest.
- [r19] Add NagisaCore Component.
- [r19] Move Nagisa.Configuration Class to NagisaCore.Configuration Class.
- [r18] Add Nagisa.Configuration Class.
- [r18] Fix Debug Console can't display any content when loaded.
- [r18] Fix crash when the Root Folder was deleted.
- [r18] Remove C++/CX PPL library to Reduce the binary size.
- [r18] Add ConsoleWriteLine function for print text to the Debug Console.
- [r17] Add the Default Save Folder Settings.
- [r17] Add the Console for Debug.
- [r17] Start implementing FileWriter.
- [r16] Add the FilePicker and some controls to UI.
- [r15] Modify the Icon to improve effects in Start.
- [r15] Add the Version Info.
- [r15] Implement the rough UI.
- [r14] Initial Release after Nagisa Restart.
- [r14] Add Source of Nagisa's Icon.
- [r14] Update the Nagisa's Assets.
- [r14] Change the MSBuild Output Folder.
- [r14] Add the Changelog Document.
- [r13] The first time to reset the project.
- [r12] Fix Source Bug & Add an Event.
- [r11] Remove useless codes.
- [r10] Update Visual Studio 2015 to Visual Studio 2017.
- [r10] Change the UI.
- [r10] Add the "Add New Task" Dialog.
- [r9] Move to Windows 10 LTSB 2015 Development Platform and Change the UI.
- [r8] Merge branch 'master' of https://github.com/M2Team/Nagisa.git.
- [r7] Make a note for Nagisa's User Agent.
- [r6] Update Readme for fix format bug.
- [r5] Create README.md.
- [r4] Change Build Directory.
- [r3] Upload Nagisa 0.1.1702.17.
- [r2] Upload Nagisa 0.1.1702.17.
- [r1] Initial commit.
