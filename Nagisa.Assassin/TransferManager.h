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
		using ::Windows::Foundation::Uri;
		using ::Windows::Storage::StorageFile;
		
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
			property String^ Description;
			property Uri^ RequestedUri;
			property StorageFile^ ResultFile;
			property TransferTaskStatus Status;
			property float64 Progress;
			property uint64 BytesReceived;
			property uint64 TotalBytesToReceive;

		internal:
			TransferTask(String^ Description, float64 Progress, TransferTaskStatus Status);
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
