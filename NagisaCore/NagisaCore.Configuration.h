#pragma once

using namespace Windows::Storage;
using namespace Windows::Storage::AccessCache;

namespace NagisaCore
{
	public ref class Configuration sealed
	{
	private:
		StorageItemAccessList^ m_FutureAccessList = nullptr;
		ApplicationDataContainer^ m_LocalSettings = nullptr;

		StorageFolder^ m_DownloadsFolder = nullptr;

		StorageFolder^ GetDownloadsFolder();
		void SetDownloadsFolder(StorageFolder^ Folder);

	public:
		Configuration();

		property StorageFolder^ DownloadsFolder
		{
			StorageFolder^ get()
			{
				return m_DownloadsFolder;
			}

			void set(StorageFolder^ value)
			{
				SetDownloadsFolder(value);
			}
		}
	};
}
