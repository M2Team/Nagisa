# Nagisa - Changelog

## Nagisa 0.1.24

**New Features**
- The Initial Release
- Added a more recognizable icon
- The color themes follow the Windows settings
- Nagisa will show the search result when you inputing or after click search 
  button.
- [Underconstruction] Add support for multi languages (Now Nagisa support 
  Simplified Chinese and English)
- [Underconstruction] Now you can use Voice Commands (aka Cortana) to activate
  Nagisa now
  - Contributed by 边宇琨 (https://github.com/bianyukun1213)
    - Pull #1: Let Nagisa respond Cortana voice commands.

**Development**
- Set options for all sub-projects:
  - Set output folder
  - Set compiler options /W4 /WX
  - Exclude some useless folders and files for privacy
- Add the Version Info for Nagisa's binaries
- Add Nagisa.Shared Project for implementing the common part
- dd implementions about synchronizing the version number 
  (Nagisa.Shared\Nagisa.Version.h)
- Add implementions about finding a sub string for windows runtime 
  (Nagisa.Shared\m2base_winrt.h)
- Add implementions about charset encoding convertion (Nagisa.Shared\m2base.h)
  - Thanks to Force.Charlie-I (https://github.com/fcharlie)
- Add implementions about waiting asynchronous call (Nagisa.Shared\m2async.h)
  - Thanks to Pointer ([Vczh]GacUI讨论群)
  - Thanks to Zihan Chen (https://github.com/vczh)
- Add Assassin Project for implementing the Nagisa's engine
- I have registered the Windows Developer Account with Microsoft Imagine via 
  verified my identity by contacting Microsoft because only teachers have the 
  chance to own their edu e-mail address in my school and I am unable to get a 
  debit card with Visa or MasterCard because my country only have debit cards 
  with UnionPay now.
  - Thanks to Jiaen Lee (Microsoft Imagine Student Support)
- Associate Nagisa to the Windows Developer Account
- Change default language to "en" in the appxmanifest file for reduce the 
  warnings
- Add BackgroundTask to AppX manifest 
- Add XamlResources.xaml for defining the Nagisa's Xaml Definitions
- Add NagisaContentDialogStyle custom style in XamlResources.xaml 
  for Vertical ScrollBar support in the ContentDialog
  - Thanks to 山宏岳 (https://social.msdn.microsoft.com/Profile/山宏岳)
- Add NagisaListViewItemExpandedStylein XamlResources.xaml to define the 
  ListViewItem style
- Add NagisaListViewItemButtonStyle in XamlResources.xaml to Define the Button 
  style in the ListViewItem
- Add NagisaStatusToForegroundConverter in XamlResources.xaml to binding the 
  ProgressBar
- Add NagisaStatusCompletedToCollapsedConverter in XamlResources.xaml to hide 
  the ProgressBar and operation button at the right time
- Add NagisaStatusToOperationButtonIconConverter in XamlResources.xaml to show
  the icon of operation button at the right time
- Add NagisaStatusToOperationButtonToolTipConverter in XamlResources.xaml to 
  show the tooltip of operation button at the right time 
- Add NagisaItemSourceEmptyToVisibilityConverter in XamlResources.xaml to show 
  the message if the ListView is empty
- [Added, but thinking] Add sqlite3 library for saving configurations
- [Only thinking] Add implementions about finding a sub string (m2base.h)
- [Underconstruction] Add Assassin.BackgroundWorker class for implementing 
  the background task
- [Underconstruction] Add Assassin.TransferManager class for controlling the 
  background task
- [Underconstruction] Add Assassin.TransferTask class for managing the single 
  task
- [Underconstruction] Add Assassin.TransferStatus enum for getting the task 
  status
- [Underconstruction] Add new MainPage UI
  - Thanks to 落樱 (https://github.com/SakuraNeko)
  - Thanks to 鳶一雨音 (https://github.com/TobiichiAmane)
  - Thanks to Calyx Hikari (https://github.com/HikariCalyx)
- [Underconstruction] Add NewTaskDialog
- [Underconstruction] Add SettingsAndAboutDialog
- [Underconstruction] Add implementions about implementing asynchronous call 
  (Nagisa.Shared\m2async.h)
