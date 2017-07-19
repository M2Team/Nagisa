#pragma once

namespace Assassin
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class BackgroundWorker sealed : public Windows::ApplicationModel::Background::IBackgroundTask
	{
	public:
		BackgroundWorker();
		virtual void Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance^ taskInstance);

	};
}
