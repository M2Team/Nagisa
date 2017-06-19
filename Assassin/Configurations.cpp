#include "pch.h"
#include "Configurations.h"

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::AccessCache;

Assassin::Configurations::Configurations()
{
	m_FutureAccessList = StorageApplicationPermissions::FutureAccessList;
	//m_LocalSettings = ApplicationData::Current->LocalSettings;

	m_DownloadsFolder = GetDownloadsFolder();
}

StorageFolder^ Assassin::Configurations::GetDownloadsFolder()
{
	StorageFolder^ Folder = nullptr;

	if (m_FutureAccessList->ContainsItem(L"Nagisa.DownloadsFolder"))
	{
		Folder = m2_await(
			m_FutureAccessList->GetFolderAsync(L"Nagisa.DownloadsFolder"));
	}

	return Folder;
}

StorageFolder^ Assassin::Configurations::DownloadsFolder::get()
{
	return m_DownloadsFolder;
}

void Assassin::Configurations::DownloadsFolder::set(StorageFolder^ value)
{
	m_FutureAccessList->AddOrReplace(L"Nagisa.DownloadsFolder", value);
	m_DownloadsFolder = value;
}

String^ Assassin::Configurations::Version::get()
{
	return NAGISA_VERSION_STRING;
}

String^ Assassin::Configurations::UserAgent::get()
{
	return 
		L"Mozilla/5.0 "
		L"(Windows NT 10.0; Nagisa/" NAGISA_VERSION_STRING L") "
		L"AppleWebKit/537.36 (KHTML, like Gecko) "
		L"Chrome/42.0.2311.135 "
		L"Safari/537.36 "
		L"Edge/12.10240";
}