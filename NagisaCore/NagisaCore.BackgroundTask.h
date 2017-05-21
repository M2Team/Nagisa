#pragma once

namespace NagisaCore
{
	public ref class BackgroundTask sealed : public Windows::ApplicationModel::Background::IBackgroundTask
	{
	public:
		BackgroundTask();
		virtual void Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance^ taskInstance);
	};
}

