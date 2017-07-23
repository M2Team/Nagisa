/******************************************************************************
Project: Assassin
Description: Definition for Transfer Manager
File Name: TransferManager.h
License: The MIT License
******************************************************************************/

#pragma once

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
		TransferTask(Platform::String^ Description, float64 Progress, TransferStatus Status);

		property Platform::String^ Description;
		property Windows::Foundation::Uri^ RequestedUri;
		property Windows::Storage::StorageFile^ ResultFile;
		property Assassin::TransferStatus Status;
		property float64 Progress;
		property uint64 BytesReceived;
		property uint64 TotalBytesToReceive;	
	};

	// Transfer Manager Object
	public ref class TransferManager sealed
	{
	private:
		Windows::Storage::AccessCache::StorageItemAccessList^ m_FutureAccessList = nullptr;
		Windows::Storage::StorageFolder^ m_DownloadsFolder = nullptr;
		Windows::Storage::StorageFolder^ GetDownloadsFolder();


		Platform::Collections::Vector<Assassin::TransferTask^>^ m_Tasks = nullptr;

	public:
		TransferManager();

		// The TransferManager::GetTasksAsync method gets all transfer tasks 
		// which matches the SearchFilter. If the SearchFilter not defined, it 
		// will return all transfer tasks.
		Windows::Foundation::IAsyncOperation<Windows::Foundation::Collections::IVectorView<Assassin::TransferTask^>^>^ GetTasksAsync(Platform::String^ SearchFilter);

		// The TransferManager::GetTasksAsync method gets all transfer tasks.
		Windows::Foundation::IAsyncOperation<Windows::Foundation::Collections::IVectorView<Assassin::TransferTask^>^>^ GetTasksAsync();
		
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
