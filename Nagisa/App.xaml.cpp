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
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::DataTransfer;
using namespace Windows::ApplicationModel::Resources;
using namespace Windows::ApplicationModel::VoiceCommands;
using namespace Windows::Globalization;
using namespace Windows::Storage;
using namespace Windows::UI::Popups;



/// <summary>
/// Initializes the singleton application object. This is the first line of 
/// authored code executed, and as such is the logical equivalent of main() or 
/// WinMain().
/// </summary>
App::App()
{
	InitializeComponent();
	Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
}

/// <summary>
/// Invoked when the application is launched normally by the end user. Other 
/// entry points will be used such as when the application is launched to open 
/// a specific file.
/// </summary>
/// <param name="e">Details about the launch request and process.</param>
void App::OnLaunched(LaunchActivatedEventArgs^ e)
{
#if _DEBUG
	// Show graphics profiling information while debugging.
	if (IsDebuggerPresent())
	{
		// Display the current frame rate counters
		DebugSettings->EnableFrameRateCounter = true;
	}
#endif
	auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);

	// Do not repeat app initialization when the Window already has content,
	// just ensure that the window is active
	if (rootFrame == nullptr)
	{
		// Create a Frame to act as the navigation context and associate it with
		// a SuspensionManager key
		rootFrame = ref new Frame();

		// Set the default language
		rootFrame->Language = ApplicationLanguages::Languages->GetAt(0);

		rootFrame->NavigationFailed += ref new NavigationFailedEventHandler(this, &App::OnNavigationFailed);

		if (e->PreviousExecutionState == ApplicationExecutionState::Terminated)
		{
			// TODO: Restore the saved session state only when appropriate, 
			// scheduling the final launch steps after the restore is complete

		}

		if (e->PrelaunchActivated == false)
		{
			if (rootFrame->Content == nullptr)
			{
				// When the navigation stack isn't restored navigate to the 
				// first page, configuring the new page by passing required 
				// information as a navigation parameter
				rootFrame->Navigate(TypeName(MainPage::typeid), e->Arguments);
			}
			// Place the frame in the current Window
			Window::Current->Content = rootFrame;
			// Ensure the current window is active
			Window::Current->Activate();
		}
	}
	else
	{
		if (e->PrelaunchActivated == false)
		{
			if (rootFrame->Content == nullptr)
			{
				// When the navigation stack isn't restored navigate to the 
				// first page, configuring the new page by passing required 
				// information as a navigation parameter
				rootFrame->Navigate(TypeName(MainPage::typeid), e->Arguments);
			}

			// Ensure the current window is active
			Window::Current->Activate();
		}
	}

	/*
	Install Voice Command Definition File if you want to use Nagisa via Cortana
	or update the phrase list for use Nagisa via Cortana better.
	*/
	try
	{
		StorageFolder^ appFolder = Package::Current->InstalledLocation;
		StorageFile^ vcdStorageFile = m2_await(appFolder->GetFileAsync(L"NagisaVoiceCommands.xml"));
		m2_await(VoiceCommandDefinitionManager::InstallCommandDefinitionsFromStorageFileAsync(vcdStorageFile));
	}
	catch (Exception^ ex)
	{
		ResourceLoader^ resourceLoader = ResourceLoader::GetForCurrentView();

		String^ dialogTitle = resourceLoader->GetString(L"ErrorText_MessageDialog_Title");
		String^ dialogText = resourceLoader->GetString(L"ErrorText_FailedToLoadVCDFile");
		MessageDialog^ messageDialog = ref new MessageDialog(dialogText, dialogTitle);
		messageDialog->ShowAsync();
	}
}

/// <summary>
/// Invoked when application execution is being suspended. Application state is
/// saved without knowing whether the application will be terminated or resumed
/// with the contents of memory still intact.
/// </summary>
/// <param name="sender">The source of the suspend request.</param>
/// <param name="e">Details about the suspend request.</param>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
	UNREFERENCED_PARAMETER(sender);
	UNREFERENCED_PARAMETER(e);

	// TODO: Save application state and stop any background activity
}

/// <summary>
/// Invoked when Navigation to a certain page fails
/// </summary>
/// <param name="sender">The Frame which failed navigation</param>
/// <param name="e">Details about the navigation failure</param>
void App::OnNavigationFailed(Platform::Object ^sender, NavigationFailedEventArgs ^e)
{
	throw ref new FailureException("Failed to load Page " + e->SourcePageType.Name);
}

void App::OnActivated(IActivatedEventArgs^ e)
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