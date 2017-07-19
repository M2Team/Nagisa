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
	public:
		TransferManager();



		/*void TaskAdd();
		void TaskDelete();
		void TaskStart();
		void TaskPause();
		void TaskStop();*/
	};
}
