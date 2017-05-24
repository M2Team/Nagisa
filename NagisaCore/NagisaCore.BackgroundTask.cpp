#include "pch.h"
#include "NagisaCore.BackgroundTask.h"

using namespace Windows::ApplicationModel::Background;
using namespace Windows::Networking::Sockets;


NagisaCore::BackgroundTask::BackgroundTask()
{
}

void NagisaCore::BackgroundTask::Run(IBackgroundTaskInstance ^ taskInstance)
{
	//StreamSocket^ socket = ref new StreamSocket();

	//socket->

	throw ref new Platform::NotImplementedException();
}
