/******************************************************************************
Project: Assassin - The transfer engine of Nagisa
Description: Implemention for Transfer Manager
File Name: TransferManager.cpp
License: The MIT License
******************************************************************************/

#include "pch.h"
#include "TransferManager.h"

using namespace Nagisa::Assassin;

using namespace Platform;

TransferTask::TransferTask(String ^ Description, float64 Progress, TransferTaskStatus Status)
{
	this->Description = Description;
	this->Progress = Progress;
	this->Status = Status;
}

TransferManager::TransferManager()
{
}


