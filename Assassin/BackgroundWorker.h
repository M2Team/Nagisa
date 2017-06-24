#pragma once

namespace Assassin
{
	using namespace Windows::ApplicationModel::Background;
	using namespace Windows::Foundation::Metadata;

	[WebHostHidden]
	public ref class BackgroundWorker sealed : public IBackgroundTask
	{
	public:
		BackgroundWorker();
		virtual void Run(IBackgroundTaskInstance^ taskInstance);

	};
}
