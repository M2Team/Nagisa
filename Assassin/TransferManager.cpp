#include "pch.h"
#include "TransferManager.h"

using namespace Platform;
using namespace Platform::Collections;

using namespace Assassin;

Assassin::TransferTask::TransferTask()
{
	IsSelected = true;
	
	Status = TransferStatus::Paused;

	Name = L"Task #2";

}


Assassin::TransferManager::TransferManager()
{

	
}