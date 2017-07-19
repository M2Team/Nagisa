#include "pch.h"
#include "TransferManager.h"

using namespace Platform;
using namespace Platform::Collections;

using namespace concurrency;
using namespace Assassin;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::AccessCache;

Assassin::TransferTask::TransferTask(String^ Description, float64 Progress, TransferStatus Status)
{
	this->Description = Description;
	this->Progress = Progress;
	this->Status = Status;

}

Assassin::TransferManager::TransferManager()
{
	//sqlite3* db;
	//sqlite3_open("dd", &db);

	m_FutureAccessList = StorageApplicationPermissions::FutureAccessList;

	m_DownloadsFolder = GetDownloadsFolder();
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