#include "pch.h"
#include "TransferManager.h"

using namespace Platform;
using namespace Platform::Collections;

using namespace Assassin;
using namespace Windows::UI::Xaml;

Assassin::TransferTask::TransferTask(String^ Description, float64 Progress, TransferStatus Status)
{
	this->Description = Description;
	this->Progress = Progress;
	this->Status = Status;

}

Assassin::TransferManager::TransferManager()
{

	
}