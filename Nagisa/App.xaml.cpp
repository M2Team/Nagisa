//
// App.xaml.cpp
// App 类的实现。
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Nagisa;

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace concurrency;
using namespace Windows::Storage;
using namespace Windows::ApplicationModel::VoiceCommands;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Popups;
using namespace Windows::ApplicationModel::DataTransfer;


/// <summary>
/// 初始化单一实例应用程序对象。这是执行的创作代码的第一行，
/// 已执行，逻辑上等同于 main() 或 WinMain()。
/// </summary>
App::App()
{
	InitializeComponent();
	Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
}

/// <summary>
/// 在应用程序由最终用户正常启动时进行调用。
/// 将在启动应用程序以打开特定文件等情况下使用。
/// </summary>
/// <param name="e">有关启动请求和过程的详细信息。</param>
void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{
	/*安装VCD文件来响应Cortana，参考“https://github.com/Microsoft/Windows-universal-samples/blob/master/Samples/CortanaVoiceCommand/cpp/AdventureWorks/App.xaml.cpp”。
	Install VCD file to use Cortana, see "https://github.com/Microsoft/Windows-universal-samples/blob/master/Samples/CortanaVoiceCommand/cpp/AdventureWorks/App.xaml.cpp". */
	try
	{
		create_task(Windows::Storage::StorageFile::GetFileFromApplicationUriAsync(ref new Uri("ms-appx:///VCD.xml")))
			.then([this](StorageFile^ vcdStorageFile)
		{
			return VoiceCommandDefinitionManager::InstallCommandDefinitionsFromStorageFileAsync(vcdStorageFile);
		});
	}
	catch (const std::exception&)
	{

	}

	auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);

	// 不要在窗口已包含内容时重复应用程序初始化，
	// 只需确保窗口处于活动状态
	if (rootFrame == nullptr)
	{
		// 创建一个 Frame 以用作导航上下文并将其与
		// SuspensionManager 键关联
		rootFrame = ref new Frame();

		rootFrame->NavigationFailed += ref new Windows::UI::Xaml::Navigation::NavigationFailedEventHandler(this, &App::OnNavigationFailed);

		if (e->PreviousExecutionState == ApplicationExecutionState::Terminated)
		{
			// TODO: 仅当适用时还原保存的会话状态，并安排
			// 还原完成后的最终启动步骤

		}

		if (e->PrelaunchActivated == false)
		{
			if (rootFrame->Content == nullptr)
			{
				// 当导航堆栈尚未还原时，导航到第一页，
				// 并通过将所需信息作为导航参数传入来配置
				// 参数
				rootFrame->Navigate(TypeName(MainPage::typeid), e->Arguments);
			}
			// 将框架放在当前窗口中
			Window::Current->Content = rootFrame;
			// 确保当前窗口处于活动状态
			Window::Current->Activate();
		}
	}
	else
	{
		if (e->PrelaunchActivated == false)
		{
			if (rootFrame->Content == nullptr)
			{
				// 当导航堆栈尚未还原时，导航到第一页，
				// 并通过将所需信息作为导航参数传入来配置
				// 参数
				rootFrame->Navigate(TypeName(MainPage::typeid), e->Arguments);
			}
			// 确保当前窗口处于活动状态
			Window::Current->Activate();
		}
	}
}

/// <summary>
/// 在将要挂起应用程序执行时调用。  在不知道应用程序
/// 无需知道应用程序会被终止还是会恢复，
/// 并让内存内容保持不变。
/// </summary>
/// <param name="sender">挂起的请求的源。</param>
/// <param name="e">有关挂起请求的详细信息。</param>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
	(void)sender;  // 未使用的参数
	(void)e;   // 未使用的参数

	//TODO: 保存应用程序状态并停止任何后台活动
}

/// <summary>
/// 导航到特定页失败时调用
/// </summary>
///<param name="sender">导航失败的框架</param>
///<param name="e">有关导航失败的详细信息</param>
void App::OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e)
{
	throw ref new FailureException("Failed to load Page " + e->SourcePageType.Name);
}

void App::OnActivated(Windows::ApplicationModel::Activation::IActivatedEventArgs^ e)
{
	/*让Nagisa从Cortana启动时能够响应命令，参考“http://www.it165.net/pro/html/201509/53876.html”。
	Let Nagisa respond Cortana voice commands, see "http://www.it165.net/pro/html/201509/53876.html". */
	__super::OnActivated(e);
	if (e->Kind != ActivationKind::VoiceCommand)
	{
		return;
	}
	auto args = (VoiceCommandActivatedEventArgs^)e;
	auto results = args->Result;
	auto cmdName = results->RulePath->GetAt(0)->ToString();
	if (cmdName == "DownloadFromClipboard")
	{
		//DataPackageView^ dpv = Clipboard::GetContent();
		//if (dpv->Contains(StandardDataFormats::Text))
		//{
		//	create_task(dpv->GetTextAsync()).then(
		//		[this](task<String^> textTask)
		//	{
		//		try
		//		{
		//			String^ text = textTask.get();
		//			/*正则表达式未完成。
		//			Regex Unfinished. */
		//			MessageDialog^ md = ref new MessageDialog(text, "Nagisa：");
		//			md->ShowAsync();
		//		}
		//		catch (Exception^ ex)
		//		{
		//			MessageDialog^ md = ref new MessageDialog("获取剪贴板文本失败！", "Nagisa：");
		//			md->ShowAsync();
		//		}
		//	});
		//}
		//else
		//{
		//	MessageDialog^ md = ref new MessageDialog("剪贴板中不含有文本内容。","Nagisa：");
		//	md->ShowAsync();
		//}
		//上面的代码好像有问题，会导致Nagisa从Cortana启动后闪退。
		MessageDialog^ md = ref new MessageDialog("你好！", "Nagisa：");
		md->ShowAsync();
	}
	auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);
	if (rootFrame == nullptr)
	{
		rootFrame = ref new Frame();
		Window::Current->Content = rootFrame;
	}
	rootFrame->Navigate(TypeName(MainPage::typeid));
	Window::Current->Activate();
}