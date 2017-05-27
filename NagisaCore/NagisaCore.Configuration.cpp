#include "pch.h"
#include "NagisaCore.Configuration.h"

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::AccessCache;


NagisaCore::Configuration::Configuration()
{
	m_FutureAccessList = StorageApplicationPermissions::FutureAccessList;
	m_LocalSettings = ApplicationData::Current->LocalSettings;

	m_DownloadsFolder = GetDownloadsFolder();
}

StorageFolder^ NagisaCore::Configuration::GetDownloadsFolder()
{
	StorageFolder^ Folder = nullptr;
	
	if (m_FutureAccessList->ContainsItem(L"Nagisa.DownloadsFolder"))
	{
		Folder = M2AsyncWait(
			m_FutureAccessList->GetFolderAsync(L"Nagisa.DownloadsFolder"));
	}

	return Folder;
}

void NagisaCore::Configuration::SetDownloadsFolder(StorageFolder ^ Folder)
{
	m_FutureAccessList->AddOrReplace(L"Nagisa.DownloadsFolder", Folder);
	
	m_DownloadsFolder = Folder;
}
