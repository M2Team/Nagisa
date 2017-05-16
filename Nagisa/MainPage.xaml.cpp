//
// MainPage.xaml.cpp
// MainPage 类的实现。
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Nagisa;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace concurrency;
using namespace Platform::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::AccessCache;
using namespace Windows::Storage::Pickers;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

MainPage::MainPage()
{
	InitializeComponent();

	create_async([this]()
	{
		this->ConsoleContent += L"M2-Team Nagisa Version 0.1.4\r\n© M2-Team. All rights reserved.\r\n";
		
		auto FutureAccessList = StorageApplicationPermissions::FutureAccessList;
		auto LocalSettings = ApplicationData::Current->LocalSettings;
		auto token = dynamic_cast<String^>(LocalSettings->Values->Lookup(L"CurrentSaveFolderToken"));

		if (token != nullptr && FutureAccessList->ContainsItem(token))
		{
			auto GetFolderTask = create_task(FutureAccessList->GetFolderAsync(token));
			GetFolderTask.wait();
			StorageFolder^ folder = GetFolderTask.get();

			if (folder)
			{
				this->CurrentSaveFolder = folder;
			}
		}

		if (this->CurrentSaveFolder)
		{
			this->ConsoleContent += "Current: " + this->CurrentSaveFolder->Path + L"\r\n";
		}
		else
		{
			this->ConsoleContent += "Current: None" + L"\r\n";
		}

		this->OutputConsole->Text = ConsoleContent;
	});
}


void Nagisa::MainPage::Nagisa_Test_SaveAsButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (this->CurrentSaveFolder)
	{
		if (FileNameTextBox->Text == L"")
		{
			this->ConsoleContent += "Invaild File Name." + L"\r\n";
		}
		else
		{
			create_task(this->CurrentSaveFolder->CreateFileAsync(FileNameTextBox->Text)).then([this](StorageFile^ file)
			{
				if (file)
				{
					create_task(FileIO::WriteTextAsync(file, L"Nagisa Test")).then([this](task<void> task)
					{
						try
						{
							task.get();
						}
						catch (COMException^ ex)
						{

						}
					});
				}
			});
		}
	}
	else
	{
		this->ConsoleContent += "Invaild Root Folder. Please set the root." + L"\n";
	}

	this->OutputConsole->Text = ConsoleContent;
}


void Nagisa::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FolderPicker^ picker = ref new FolderPicker();
	picker->FileTypeFilter->Append(L"*");
	picker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;

	create_task(picker->PickSingleFolderAsync()).then([this](StorageFolder^ folder)
	{
		if (folder)
		{
			auto FutureAccessList = StorageApplicationPermissions::FutureAccessList;
			auto LocalSettings = ApplicationData::Current->LocalSettings;

			if (this->CurrentSaveFolder)
			{
				auto token = dynamic_cast<String^>(LocalSettings->Values->Lookup(L"CurrentSaveFolderToken"));
				if (token != nullptr && FutureAccessList->ContainsItem(token))
				{
					FutureAccessList->Remove(token);
				}
			}

			LocalSettings->Values->Insert(L"CurrentSaveFolderToken", FutureAccessList->Add(folder));
			this->CurrentSaveFolder = folder;

			this->ConsoleContent += "Current: " + this->CurrentSaveFolder->Path + L"\r\n";
		}
		else
		{
			this->ConsoleContent += "Operation cancelled." + L"\r\n";
		}

		this->OutputConsole->Text = ConsoleContent;
	});
}
