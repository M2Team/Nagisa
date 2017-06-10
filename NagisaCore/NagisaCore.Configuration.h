#pragma once

using namespace Windows::Storage;
using namespace Windows::Storage::AccessCache;

namespace NagisaCore
{
	public ref class Configuration sealed
	{
	private:
		StorageItemAccessList^ m_FutureAccessList = nullptr;
		//ApplicationDataContainer^ m_LocalSettings = nullptr;

		StorageFolder^ m_DownloadsFolder = nullptr;

		StorageFolder^ GetDownloadsFolder();

	public:
		Configuration();

		property StorageFolder^ DownloadsFolder
		{
			StorageFolder^ get();
			void set(StorageFolder^ value);
		}
	};
}
