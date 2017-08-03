# Nagisa - Changelog

## Notice
- This is the changelog about project Nagisa.
- For more information on the names of persons mentioned here, please read 
  People.md.

## Changelog

**Nagisa 0.1 Stage 2 [Revision 29]**

- Changed
  - Nagisa (User Experience)
    - Improve the performance by using asynchronous call in Main UI constructor
    - Reduce the binary size via using std::thread instead of 
      concurrency::create_task()
    - Merge AutoSuggestBox_QuerySubmitted and AutoSuggestBox_TextChanged event 
      to AutoSuggestBox_Search event in Main UI      
    - The "New Task" Dialog has been initially constructed
  - Nagisa.Shared (For sharing source code)
    - Improve implementions about waiting asynchronous call
      (Nagisa.Shared\m2async.h)
    - Improve implementions about creating a IAsyncOperation Windows Runtime 
      asynchronous construct based on a user supplied lambda or function 
      object. (Nagisa.Shared\m2async.h)
  - Assassin (Transfer Engine)
    - Remove all implements to header file for writing code like C#
    - Add TransferManager::GetTasksAsync() for getting all transfer tasks or 
      search specific transfer tasks.
    - Add TransferManager::Version property for getting the version.
    - Add NAGetVersion function for getting the version.
    - Add NAGetDefaultUserAgentString function for getting the default User 
      Agent string.
- Notice
  - None

**Nagisa 0.1 Stage 1 [Revision 26]**

- Changed
  - Nagisa (User Experience)
    - Added a more recognizable icon
    - The color themes follow the Windows settings
    - Add multi languages support (Now support Simplified Chinese and English)
    - Add Voice Commands (aka Cortana) support
    - The SearchBox in the main user interface will show the search result when
      you inputing or after click search button.
    - Using a modified style ContentDialog to implement other user interfaces
    - Using ProgressBar with colors to represent task status (Green represents 
      Running. Orange represents Paused. Red represents Error. Transparent 
      represents Completed.)
    - Add "New Task" and "Settings & About" Dialog
  - Nagisa.Shared (For sharing source code)
    - Add implementions about synchronizing the version number
      (Nagisa.Shared\Nagisa.Version.h)
    - Add implementions about finding a sub string for windows runtime
      (Nagisa.Shared\m2base_winrt.h)
    - Add implementions about charset encoding convertion
      (Nagisa.Shared\m2base.h)
    - Add implementions about waiting asynchronous call
      (Nagisa.Shared\m2async.h)
    - Add implementions about creating a IAsyncOperation Windows Runtime 
      asynchronous construct based on a user supplied lambda or function 
      object. (Nagisa.Shared\m2async.h)
  - Assassin (Transfer Engine)
    - Add BackgroundWorker class to do the actual operation in the background
    - Add TransferStatus enum to represent the status of a transfer task
    - Add TransferTask class to represent a transfer task
    - Add TransferManager class to manage the transfer tasks

- Notice
  - This is the Initial Release
  - Nagisa's source code is complied with "/W4 /WX" option
  - Voice Commands (aka Cortana) support is contributed by 边宇琨. For more 
    information, you can navigate https://github.com/M2Team/Nagisa/pull/1
  - Thanks for Jiaen Lee's help. I have registered the Windows Developer 
    Account with Microsoft Imagine via verified my identity by contacting 
    Microsoft because only teachers have the chance to own their edu e-mail 
    address in my school and I am unable to get a debit card with Visa or 
    MasterCard because my country only have debit cards with UnionPay now.
  - Associate Nagisa to the Windows Developer Account
  - Change default language to "en" in the appxmanifest file for reduce the 
    warnings
  - Thanks to 落樱, 鳶一雨音 and Calyx Hikari for their advice on user 
    interface
  - Thanks for 山宏岳's idea about Vertical ScrollBar support in the 
    ContentDialog
  - Thanks for Force.Charlie-I's implementions about charset encoding 
    convertions in the PrivExec project
  - Thanks to Pointer and Zihan Chen for their help about how to remove C++/CX 
    reference type
