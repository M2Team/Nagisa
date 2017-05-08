//
// MainPage.xaml.cpp
// MainPage 类的实现。
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "AddNewTaskDialog.xaml.h"

using namespace Nagisa;

using namespace Platform;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace concurrency;
using namespace Windows::UI::ViewManagement;
using namespace Windows::System;
using namespace Windows::Storage;

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

// Nagisa's User Agent
// Mozilla/5.0 (Windows NT 10.0; Nagisa/0.1.1702.17) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/12.10240

MainPage::MainPage()
{
	InitializeComponent();

	//auto WindowSize = Size(16.0, 16.0);
	auto appCurrentView = ApplicationView::GetForCurrentView();
	auto appTitleBar = appCurrentView->TitleBar;
	
	//appCurrentView->SetPreferredMinSize(WindowSize);
	//appCurrentView->PreferredLaunchViewSize = WindowSize;
	//appCurrentView->PreferredLaunchWindowingMode = 
		//ApplicationViewWindowingMode::PreferredLaunchViewSize;

	//appCurrentView->Title = L"Nagisa 0.3";

	appTitleBar->BackgroundColor = Colors::LightGray;
	appTitleBar->InactiveBackgroundColor = Colors::LightGray;
	appTitleBar->ButtonBackgroundColor = Colors::LightGray;
	appTitleBar->ButtonInactiveBackgroundColor = Colors::LightGray;
	appTitleBar->ButtonHoverBackgroundColor = Colors::DarkGray;
}

void Nagisa::MainPage::AppBarToggleButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	AddNewTaskDialog^ Dialog = ref new AddNewTaskDialog();
	Dialog->ShowAsync();
}


void Nagisa::MainPage::AppBarButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	create_task(
		DownloadsFolder::CreateFolderAsync(
			L"NagisaDownloads", CreationCollisionOption::OpenIfExists))
		.then([this](task<StorageFolder^> task)
	{
		StorageFolder^ NagisaDownloads = task.get();
		Launcher::LaunchFolderAsync(NagisaDownloads);
	});
}
