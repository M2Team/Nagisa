#include "pch.h"
#include "NagisaCore.BackgroundTask.h"


NagisaCore::BackgroundTask::BackgroundTask()
{
}

void NagisaCore::BackgroundTask::Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance ^ taskInstance)
{
	throw ref new Platform::NotImplementedException();
}
