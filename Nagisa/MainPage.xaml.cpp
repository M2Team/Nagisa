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
		String^ FileName = FileNameTextBox->Text;
		
		if (FileName == L"")
		{
			ConsoleWriteLine(L"Invaild File Name.");
		}
		else
		{	
			ThreadPool::RunAsync(ref new WorkItemHandler([this, FileName](IAsyncAction^ workItem)
			{	
				StorageFile^ file = M2AsyncWait(
					this->m_Config->DownloadsFolder->CreateFileAsync(FileName));
				
				if (file)
				{
					M2AsyncWait(FileIO::WriteTextAsync(file, L"Nagisa Test"));
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

/*void WriteLog(
	_In_z_ _Printf_format_string_ wchar_t const* const _Format,
	...)
{
	if (nullptr != _Format)
	{
		va_list _ArgList = nullptr;
		va_start(_ArgList, _Format);

		// 获取格式化字符串长度
		size_t nLength = _vscwprintf(_Format, _ArgList) + 1;

		// 创建用于存储格式化字符串的内存空间
		std::vector<wchar_t> Buffer(nLength, L'\0');

		// 按格式输出字符串
		int nWritten = _vsnwprintf_s(
			&Buffer[0],
			Buffer.size(),
			nLength,
			_Format,
			_ArgList);
		if (nWritten > 0)
		{
			WriteLogRaw(&Buffer[0]);
		}

		va_end(_ArgList);
	}
}*/

void Nagisa::MainPage::Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ThreadPool::RunAsync(ref new WorkItemHandler([this](IAsyncAction^ workItem)
	{
		//CAsyncSession Test;
		
		//Uri^ uri = ref new Uri(L"http://avatar.csdn.net/0/0/0/1_hulele2009.jpg");

		Uri^ uri = ref new Uri(L"http://dldir1.qq.com/qqfile/qq/TIM1.1.0/20843/TIM1.1.0.exe");

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

		M2AsyncWait(socket->ConnectAsync(hostName, uri->Port.ToString()));

		DataWriter^ writer = ref new DataWriter(socket->OutputStream);

		String^ stringSend =

			L"GET " + uri->Path + " HTTP/1.1" L"\r\n"
			L"Host: " + uri->Host + L"\r\n"
			L"Connection: Keep-Alive"
			L"User-Agent: Mozilla/5.0 (Windows NT 10.0; Nagisa/0.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/12.10240" L"\r\n"
			L"Accept:*/*" L"\r\n"
			L"Range:bytes=0-" L"\r\n"
			L"\r\n";

		writer->UnicodeEncoding = UnicodeEncoding::Utf8;
		writer->WriteString(stringSend);

		auto ActualSendSize = M2AsyncWait(writer->StoreAsync());

		StorageFile^ file = M2AsyncWait(
			this->m_Config->DownloadsFolder->CreateFileAsync(
				L"2.exe",
				CreationCollisionOption::ReplaceExisting));

		
		if (file)
		{
			
			
			unsigned long long position = 0;
			
			auto randomstream = M2AsyncWait(file->OpenAsync(FileAccessMode::ReadWrite));
			
			bool GetHeader = true;

			while (true)
			{
				auto outputstream = randomstream->GetOutputStreamAt(position);
				
				Buffer^ buffer = ref new Buffer(4096);

				M2AsyncWait(socket->InputStream->ReadAsync(buffer, 4096, InputStreamOptions::Partial));
	
				if (GetHeader)
				{
					auto buf = ref new Platform::Array<unsigned char>(4096);

					auto reader = DataReader::FromBuffer(buffer);

					reader->ReadBytes(buf);


					auto a = ref new String();

					for (size_t i = 0; i < buf->Length; ++i)
					{
						if (buf[i] == '\r' && buf[i + 1] == '\n' && buf[i + 2] == '\r' && buf[i + 3] == '\n')
						{
							a += L"\r\n\r\n";
							break;
						}
						else
						{
							a += (wchar_t)buf[i];
						}
					}

					auto ResponseHeaderLength = a->Length();

					auto newBuf = ArrayReference<unsigned char>(&buf[ResponseHeaderLength], 4096 - ResponseHeaderLength);

					this->Dispatcher->RunAsync(
						CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, a]()
					{
						ConsoleWriteLine(a);

					}));

					DataWriter^ writer = ref new DataWriter(outputstream);

					writer->WriteBytes(newBuf);

					M2AsyncWait(writer->StoreAsync());

					position += 4096 - ResponseHeaderLength;


					GetHeader = false;
				}
				else
				{
					auto ActualSize = buffer->Length;

					if (ActualSize == 0)
					{
						break;
					}

					outputstream->WriteAsync(buffer);

					position += ActualSize;
				}


				//M2AsyncWait(outputstream->FlushAsync());
			}

			//M2AsyncWait(randomstream->FlushAsync());



		}

	}));
}
