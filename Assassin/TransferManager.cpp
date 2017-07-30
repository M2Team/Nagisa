/******************************************************************************
Project: Assassin
Description: Implemention for Transfer Manager
File Name: TransferManager.cpp
License: The MIT License
******************************************************************************/

#include "pch.h"
#include "TransferManager.h"

using namespace Platform;
using namespace Platform::Collections;

using namespace concurrency;
using namespace Assassin;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::AccessCache;
using namespace Windows::System::Threading;

Assassin::TransferTask::TransferTask(String^ Description, float64 Progress, TransferStatus Status)
{
	this->Description = Description;
	this->Progress = Progress;
	this->Status = Status;

}

Assassin::TransferManager::TransferManager()
{
	m_Tasks = ref new Vector<TransferTask^>();

	m_Tasks->Append(ref new TransferTask(L"Task #1", 10, TransferStatus::Running));
	m_Tasks->Append(ref new TransferTask(L"Task #2", 30, TransferStatus::Error));
	m_Tasks->Append(ref new TransferTask(L"Task #3", 60, TransferStatus::Paused));
	m_Tasks->Append(ref new TransferTask(L"Task #4", 100, TransferStatus::Completed));

	m_FutureAccessList = StorageApplicationPermissions::FutureAccessList;

	m_DownloadsFolder = GetDownloadsFolder();
}

// The TransferManager::GetTasksAsync method gets all transfer tasks which 
// matches the SearchFilter. If the SearchFilter not defined, it will return 
// all transfer tasks.
IAsyncOperation<IVectorView<TransferTask^>^>^ Assassin::TransferManager::GetTasksAsync(String ^ SearchFilter)
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
IAsyncOperation<IVectorView<TransferTask^>^>^ Assassin::TransferManager::GetTasksAsync()
{
	return GetTasksAsync(nullptr);
}











StorageFolder^ Assassin::TransferManager::GetDownloadsFolder()
{
	StorageFolder^ Folder = nullptr;

	if (m_FutureAccessList->ContainsItem(L"Nagisa.DownloadsFolder"))
	{
		Folder = m2_await(
			m_FutureAccessList->GetFolderAsync(L"Nagisa.DownloadsFolder"));
	}

	return Folder;
}

StorageFolder^ Assassin::TransferManager::DownloadsFolder::get()
{
	return m_DownloadsFolder;
}

void Assassin::TransferManager::DownloadsFolder::set(StorageFolder^ value)
{
	m_FutureAccessList->AddOrReplace(L"Nagisa.DownloadsFolder", value);
	m_DownloadsFolder = value;
}

String^ Assassin::TransferManager::Version::get()
{
	return NAGISA_VERSION_STRING;
}

String^ Assassin::TransferManager::UserAgent::get()
{
	return
		L"Mozilla/5.0 "
		L"(Windows NT 10.0; Nagisa/" NAGISA_VERSION_STRING L") "
		L"AppleWebKit/537.36 (KHTML, like Gecko) "
		L"Chrome/42.0.2311.135 "
		L"Safari/537.36 "
		L"Edge/12.10240";
}