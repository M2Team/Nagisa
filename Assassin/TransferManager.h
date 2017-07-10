#pragma once

namespace Assassin
{
	public enum class TransferStatus
	{
		Transfering,
		Paused,
		Error,
		Completed
	};

	
	public ref class TransferTask sealed
	{
	public:
		TransferTask();

		property Uri^ Link;

		property String^ Name;
		property String^ StorageAccessName;

		property Platform::Boolean IsSelected;
		property TransferStatus Status;
		
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
