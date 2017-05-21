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

using namespace NagisaCore;
using namespace concurrency;
using namespace Platform::Collections;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Storage;
using namespace Windows::Storage::AccessCache;
using namespace Windows::Storage::Pickers;
using namespace Windows::System::Threading;
using namespace Windows::UI::Core;

#include <string>
using namespace std;

MainPage::MainPage()
{
	InitializeComponent();
}


void Nagisa::MainPage::ConsoleWriteLine(Platform::String ^ String)
{
	this->OutputConsole->Text += String + L"\r\n";
}

void Nagisa::MainPage::Nagisa_Test_SaveAsButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{	
	if (this->m_Config->DownloadsFolder)
	{
		if (FileNameTextBox->Text == L"")
		{
			ConsoleWriteLine(L"Invaild File Name.");
		}
		else
		{
			ThreadPool::RunAsync(ref new WorkItemHandler([this](IAsyncAction^ workItem)
			{
				//Uri^ uri = ref new Uri(L"ed2k://|file|cn_windows_8_1_enterprise_x64_dvd_2971863.iso|4039327744|08BAF18320B8FFC58D4C35BCC7A32012|/");
				//String^ x = uri->SchemeName;
				
				auto asyncOperation = this->m_Config->DownloadsFolder->CreateFileAsync(FileNameTextBox->Text);
				while (asyncOperation->Status == AsyncStatus::Started)
				{
					SwitchToThread();
				}

				StorageFile^ file = asyncOperation->GetResults();
				if (file)
				{
					IAsyncAction^ asyncAction = FileIO::WriteTextAsync(file, L"Nagisa Test");
					while (asyncAction->Status == AsyncStatus::Started)
					{
						SwitchToThread();
					}
				}
			}));
		}
	}
	else
	{
		ConsoleWriteLine(L"Invaild Root Folder. Please set the root.");
	}
}


void Nagisa::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FolderPicker^ picker = ref new FolderPicker();
	picker->FileTypeFilter->Append(L"*");
	picker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;

	(picker->PickSingleFolderAsync())->Completed =
		ref new AsyncOperationCompletedHandler<StorageFolder^>(
			[this](IAsyncOperation<StorageFolder^>^ asyncInfo, AsyncStatus asyncStatus)
	{
		StorageFolder^ folder = asyncInfo->GetResults();

		this->Dispatcher->RunAsync(
			CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, folder]()
		{
			if (folder)
			{
				this->m_Config->DownloadsFolder = folder;

				ConsoleWriteLine(L"Current: " + this->m_Config->DownloadsFolder->Path);
			}
			else
			{
				ConsoleWriteLine(L"Operation cancelled.");
			}
		}));
	});
}


void Nagisa::MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ConsoleWriteLine(L"M2-Team Nagisa Version 0.1.7");
	ConsoleWriteLine(L"© M2-Team. All rights reserved.");
	ConsoleWriteLine(L"");

	this->m_Config = ref new Configuration();
	if (this->m_Config)
	{
		if (this->m_Config->DownloadsFolder)
		{
			ConsoleWriteLine(L"Current: " + this->m_Config->DownloadsFolder->Path);
		}
		else
		{
			ConsoleWriteLine(L"Current: None");
		}
	}
}
