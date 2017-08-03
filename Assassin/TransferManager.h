/******************************************************************************
Project: Assassin
Description: Definition and implemention for Transfer Manager
File Name: TransferManager.h
License: The MIT License
******************************************************************************/

#pragma once

#include "pch.h"

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::AccessCache;

// The NAGetVersion function gets the version.
String^ NAGetVersion()
{
	return NAGISA_VERSION_STRING;
}

// The NAGetDefaultUserAgentString function gets the default User Agent string.
String^ NAGetDefaultUserAgentString()
{
	return
		L"Mozilla/5.0 "
		L"(Windows NT 10.0; Nagisa/" NAGISA_VERSION_STRING L") "
		L"AppleWebKit/537.36 (KHTML, like Gecko) "
		L"Chrome/42.0.2311.135 "
		L"Safari/537.36 "
		L"Edge/12.10240";
}

namespace Assassin
{
	// Transfer Task Status
	public enum class TransferStatus
	{
		Running,
		Paused,
		Error,
		Completed
	};
	
	// Transfer Task Object
	public ref class TransferTask sealed
	{
	public:
		TransferTask(String^ Description, float64 Progress, TransferStatus Status)
		{
			this->Description = Description;
			this->Progress = Progress;
			this->Status = Status;
		}

		property String^ Description;
		property Uri^ RequestedUri;
		property StorageFile^ ResultFile;
		property TransferStatus Status;
		property float64 Progress;
		property uint64 BytesReceived;
		property uint64 TotalBytesToReceive;	
	};

	// Transfer Manager Object
	public ref class TransferManager sealed
	{
	private:
		StorageItemAccessList^ m_FutureAccessList = nullptr;
		StorageFolder^ m_DownloadsFolder = nullptr;

		StorageFolder^ GetDownloadsFolder()
		{
			StorageFolder^ Folder = nullptr;

			if (m_FutureAccessList->ContainsItem(L"Nagisa.DownloadsFolder"))
			{
				Folder = m2_await(
					m_FutureAccessList->GetFolderAsync(L"Nagisa.DownloadsFolder"));
			}

			return Folder;
		}


		Vector<TransferTask^>^ m_Tasks = nullptr;

	public:
		TransferManager()
		{
			/*auto applicationData = ApplicationData::Current;
			auto version = applicationData->Version;

			version = version;
			
			ApplicationDataContainer^ localSettings = ApplicationData::Current->LocalSettings;
			ApplicationDataContainer^ container = localSettings->CreateContainer("Nagisa", ApplicationDataCreateDisposition::Always);*/

			
			
			
			m_Tasks = ref new Vector<TransferTask^>();

			m_Tasks->Append(ref new TransferTask(L"Task #1", 10, TransferStatus::Running));
			m_Tasks->Append(ref new TransferTask(L"Task #2", 30, TransferStatus::Error));
			m_Tasks->Append(ref new TransferTask(L"Task #3", 60, TransferStatus::Paused));
			m_Tasks->Append(ref new TransferTask(L"Task #4", 100, TransferStatus::Completed));

			m_FutureAccessList = StorageApplicationPermissions::FutureAccessList;

			m_DownloadsFolder = GetDownloadsFolder();
		}

		// The TransferManager::GetTasksAsync property gets the version
		property String^ Version
		{
			String^ get()
			{
				return ::NAGetVersion();
			}
		}

		// Add TransferManager::UserAgent property gets or sets the User Agent 
		// string.
		property String^ UserAgent
		{
			String^ get()
			{
				return ::NAGetDefaultUserAgentString();
			}

			/*
			
			    - Add TransferManager::UserAgent property for getting or setting the User Agent string.
			*/

			void set(String^ value)
			{

			}
		}

		// The TransferManager::GetTasksAsync method gets all transfer tasks 
		// which matches the SearchFilter. If the SearchFilter not defined, it 
		// will return all transfer tasks.
		IAsyncOperation<IVectorView<TransferTask^>^>^ GetTasksAsync(
			String^ SearchFilter)
		{
			return m2_create_async_operation([this, SearchFilter]() -> IVectorView<TransferTask^>^
			{
				IVectorView<TransferTask^>^ Result = nullptr;

				if (SearchFilter == nullptr || SearchFilter->IsEmpty())
				{
					Result = m_Tasks->GetView();
				}
				else
				{
					Vector<TransferTask^>^ FilteredResult = ref new Vector<TransferTask^>();

					for (auto Task : m_Tasks)
					{
						if (m2_base_winrt_find_sub_string(Task->Description, SearchFilter, true))
						{
							FilteredResult->Append(Task);
						}
					}

					Result = FilteredResult->GetView();
				}

				return Result;
			});
		}

		// The TransferManager::GetTasksAsync method gets all transfer tasks.
		IAsyncOperation<IVectorView<TransferTask^>^>^ GetTasksAsync()
		{
			return GetTasksAsync(nullptr);
		}

		property StorageFolder^ DownloadsFolder
		{
			StorageFolder^ get()
			{
				return m_DownloadsFolder;
			}

			void set(StorageFolder^ value)
			{
				m_FutureAccessList->AddOrReplace(L"Nagisa.DownloadsFolder", value);
				m_DownloadsFolder = value;
			}
		}

		


		/*void TaskAdd();
		void TaskDelete();
		void TaskStart();
		void TaskPause();
		void TaskStop();*/
	};
}
