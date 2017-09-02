/******************************************************************************
Project: Assassin - The transfer engine of Nagisa
Description: Definition for Transfer Manager
File Name: TransferManager.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _NAGISA_ASSASSIN_TRANSFERMANAGER_
#define _NAGISA_ASSASSIN_TRANSFERMANAGER_

namespace Nagisa
{
	namespace Assassin
	{	
		// TransferTaskStatus - Defines the status of a transfer task.
		public enum class TransferTaskStatus
		{
			Canceled,
			Completed,
			Error,
			Paused,
			Queued,
			Running
		};

		// TransferTask - Defines an object that represents a transfer task.
		public ref class TransferTask sealed
		{
		public:
			property Platform::String^ Description;
			property Windows::Foundation::Uri^ RequestedUri;
			property Windows::Storage::StorageFile^ ResultFile;
			property TransferTaskStatus Status;
			property float64 Progress;
			property uint64 BytesReceived;
			property uint64 TotalBytesToReceive;

		internal:
			TransferTask(
				Platform::String^ Description,
				float64 Progress, 
				TransferTaskStatus Status);
		};
		
		// TransferManager - Provide ways to manage the transfer engine.
		public ref class TransferManager sealed
		{
		public:
			TransferManager();
		};
	}
}

#endif
