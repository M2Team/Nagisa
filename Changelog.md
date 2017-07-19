# Nagisa - Changelog

**Nagisa 0.1.23**
- The Initial Release
- Add Source of Nagisa's Icon
- Add the Nagisa's Assets
- Set the MSBuild Output Folder
- Exclude some useless folders and files for privacy
- Add the Version Info for Nagisa's binaries
- Add Nagisa.Shared Project
- Add M2-Team Common Library (m2base.h) for charset encoding convertion
  - Thanks to Force.Charlie-I (https://github.com/fcharlie)
- Add Nagisa.Version.h for synchronizing the version number
- Set compiler options for all sub-projects: /W4 /WX
- Add m2_await function for waiting asynchronous call in m2async.h
  - Thanks to Pointer ([Vczh]GacUI讨论群)
  - Thanks to Zihan Chen (https://github.com/vczh)
- Add support for multi languages (Now support Simplified Chinese and English)
- Change default language to "en" in the appxmanifest file for reduce the
  warning
- The color themes follow the Windows settings
- I have registered the Windows Developer Account with Microsoft Imagine.
  - I verified my identity by contacting Microsoft because the following 
    reasons:
    - Only teachers have the chance to own their edu e-mail address in my 
	  school.
	- I am unable to get a debit card with Visa or MasterCard because my 
	  country only have debit cards with UnionPay now.
  - Thanks to Jiaen Lee (Microsoft Imagine Student Support)
- Associate Nagisa to the Windows Developer Account
- Merged the source code from 边宇琨 (https://github.com/bianyukun1213)
  - Pull #1: Let Nagisa respond Cortana voice commands.
- Now you can use Voice Commands (aka Cortana) to activate Nagisa now, and it 
  support Simplified Chinese and English.
- Add sqlite3 library for saving configurations
- Add Assassin Project
  - Add Assassin.BackgroundWorker class for implementing the background task
    - Add BackgroundTask to AppX manifest
  - Add Assassin.TransferManager class for controlling the background task
  - Add Assassin.TransferTask class for managing the single task
  - Add Assassin.TransferStatus enum for getting the task status
- Add XamlResources.xaml for defining the Nagisa's Xaml Definitions
  - Add NagisaContentDialogStyle custom style for Vertical ScrollBar support in 
    the ContentDialog
    - Thanks to 山宏岳 (https://social.msdn.microsoft.com/Profile/山宏岳)
  - Add NagisaListViewItemExpandedStyle to define the ListViewItem style
  - Add NagisaListViewItemButtonStyle to Define the Button style in the ListViewItem
  - Add NagisaStatusToForegroundConverter to binding the ProgressBar
  - Add NagisaStatusToBackgroundConverter to binding the ProgressBar
  - Add NagisaStatusErrorToVisibilityConverter to binding the Buttons in the ListViewItem
  - Add NagisaStatusPausedToVisibilityConverter to binding the Buttons in the ListViewItem
  - Add NagisaStatusRunningToVisibilityConverter to binding the Buttons in the ListViewItem
- Add new MainPage UI
  - Add AutoSuggestBox for searching the task items
  - Add CommandBar for controlling the global opitions
  - Add ListView for viewing the tasks items
  - Add a fake ItemsSource for debugging
  - Thanks to 落樱 (https://github.com/SakuraNeko)
  - Thanks to 鳶一雨音 (https://github.com/TobiichiAmane)
  - Thanks to Calyx Hikari (https://github.com/HikariCalyx)
- Add NewTaskDialog
- Add SettingsAndAboutDialog
  - Add "Default Download Folder" Section
  - Add "About This App" Section
