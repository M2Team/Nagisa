#include "pch.h"
#include "Nagisa.Configuration.h"

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::AccessCache;


Nagisa::Configuration::Configuration()
{
	m_FutureAccessList = StorageApplicationPermissions::FutureAccessList;
	m_LocalSettings = ApplicationData::Current->LocalSettings;

	m_DownloadsFolder = GetDownloadsFolder();
}

StorageFolder^ Nagisa::Configuration::GetDownloadsFolder()
{
	StorageFolder^ Folder = nullptr;
	
	if (m_FutureAccessList->ContainsItem(L"Nagisa.DownloadsFolder"))
	{
		auto asyncOperation = m_FutureAccessList->GetFolderAsync(L"Nagisa.DownloadsFolder");
		while (asyncOperation->Status == AsyncStatus::Started)
		{
			SwitchToThread();
		}

		if (asyncOperation->Status == AsyncStatus::Completed)
		{
			Folder = asyncOperation->GetResults();
		}
	}

	return Folder;
}

void Nagisa::Configuration::SetDownloadsFolder(StorageFolder ^ Folder)
{
	m_FutureAccessList->AddOrReplace(L"Nagisa.DownloadsFolder", Folder);
	
	m_DownloadsFolder = Folder;
}
