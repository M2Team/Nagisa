#pragma once

namespace Assassin
{
	using namespace Platform;
	using namespace Windows::Storage;
	using namespace Windows::Storage::AccessCache;
	
	public ref class Configurations sealed
	{
	private:
		StorageItemAccessList^ m_FutureAccessList = nullptr;
		//ApplicationDataContainer^ m_LocalSettings = nullptr;

		StorageFolder^ m_DownloadsFolder = nullptr;

		StorageFolder^ GetDownloadsFolder();

	public:
		Configurations();

		property StorageFolder^ DownloadsFolder
		{
			StorageFolder^ get();
			void set(StorageFolder^ value);
		}

		property String^ Version
		{
			String^ get();
		}

		property String^ UserAgent
		{
			String^ get();
		}
	};
}
