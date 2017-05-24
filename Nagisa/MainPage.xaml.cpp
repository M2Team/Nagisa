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
using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage;
using namespace Windows::Storage::AccessCache;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
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
	ConsoleWriteLine(L"M2-Team Nagisa Version 0.1.8");
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


void Nagisa::MainPage::Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ThreadPool::RunAsync(ref new WorkItemHandler([this](IAsyncAction^ workItem)
	{
		Uri^ uri = ref new Uri(L"http://avatar.csdn.net/0/0/0/1_hulele2009.jpg");


		HostName^ hostName = nullptr;
		try
		{
			hostName = ref new HostName(uri->Host);
		}
		catch (InvalidArgumentException^ e)
		{
			//throw L"Error: Invalid host name.";
			return;
		}

		StreamSocket^ socket = ref new StreamSocket();

		socket->Control->KeepAlive = true;

		(socket->ConnectAsync(hostName, uri->Port.ToString()))->Completed = 
			ref new AsyncActionCompletedHandler(
			[this,uri,socket](IAsyncAction^ asyncInfo, AsyncStatus asyncStatus)
		{
			if (asyncStatus == AsyncStatus::Completed)
			{
				DataWriter^ writer = ref new DataWriter(socket->OutputStream);

				String^ stringSend = 
					
					L"GET " + uri->Path +" HTTP/1.1" L"\r\n"
					L"Host: " + uri->Host + L"\r\n"
					L"Connection: Keep-Alive"
					L"User-Agent: Mozilla/5.0 (Windows NT 10.0; Nagisa/0.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/12.10240" L"\r\n"		
					L"Accept:*/*" L"\r\n"
					L"Accept-Encoding:gzip, deflate" L"\r\n"
					L"Accept-Language:zh-CN" L"\r\n"
					L"Range:bytes=0-" L"\r\n"				;

				writer->UnicodeEncoding = UnicodeEncoding::Utf8;
				writer->WriteString(stringSend);

				(writer->StoreAsync())->Completed =
					ref new AsyncOperationCompletedHandler<unsigned int>(
						[this, socket, writer](IAsyncOperation<unsigned int>^ asyncInfo, AsyncStatus asyncStatus)
				{
					writer->DetachBuffer();
					
					//unsigned int size = asyncInfo->GetResults();

					DataReader^ reader = ref new DataReader(socket->InputStream);

					//reader->InputStreamOptions = InputStreamOptions::Partial;

					auto asyncOperation = this->m_Config->DownloadsFolder->CreateFileAsync(L"1.jpg");
					while (asyncOperation->Status == AsyncStatus::Started)
					{
						SwitchToThread();
					}

					StorageFile^ file = asyncOperation->GetResults();
					if (file)
					{
						IAsyncAction^ asyncAction = FileIO::WriteBufferAsync(file, reader->ReadBuffer(asyncInfo->GetResults()));
						while (asyncAction->Status == AsyncStatus::Started)
						{
							SwitchToThread();
						}
					}

					/*(reader->LoadAsync(reader->ReadUInt32()))->Completed =
						ref new AsyncOperationCompletedHandler<unsigned int>(
							[this, reader](IAsyncOperation<unsigned int>^ asyncInfo, AsyncStatus asyncStatus)
					{
						
						
						
						
					});*/
					
				});

				

			}
		});
	}));
}
