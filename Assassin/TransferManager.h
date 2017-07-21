#pragma once

namespace Assassin
{
	public enum class TransferStatus
	{
		Running,
		Paused,
		Error,
		Completed
	};
	
	public ref class TransferTask sealed
	{
	public:
		TransferTask(Platform::String^ Description, float64 Progress, TransferStatus Status);

		property Platform::String^ Description;
		property Windows::Foundation::Uri^ RequestedUri;
		property Windows::Storage::StorageFile^ ResultFile;
		property Assassin::TransferStatus Status;
		property float64 Progress;
		property uint64 BytesReceived;
		property uint64 TotalBytesToReceive;	
	};

	public ref class TransferManager sealed
	{
	private:
		Windows::Storage::AccessCache::StorageItemAccessList^ m_FutureAccessList = nullptr;
		Windows::Storage::StorageFolder^ m_DownloadsFolder = nullptr;
		Windows::Storage::StorageFolder^ GetDownloadsFolder();


		Platform::Collections::Vector<Assassin::TransferTask^>^ m_TaskList = nullptr;

	public:
		TransferManager();

		//Windows::Foundation::IAsyncOperation<Windows::Foundation::Collections::IVectorView<Assassin::TransferTask^>^>^ GetCurrentDownloadsAsync();

		property String^ Version
		{
			Platform::String^ get();
		}

		property String^ UserAgent
		{
			Platform::String^ get();
		}

		property Windows::Storage::StorageFolder^ DownloadsFolder
		{
			Windows::Storage::StorageFolder^ get();
			void set(Windows::Storage::StorageFolder^ value);
		}

		


		/*void TaskAdd();
		void TaskDelete();
		void TaskStart();
		void TaskPause();
		void TaskStop();*/
	};
}
