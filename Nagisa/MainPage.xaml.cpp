//
// MainPage.xaml.cpp
// MainPage 类的实现。
//

#include "pch.h"
#include "Nagisa.Core.h"
#include "MainPage.xaml.h"

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

using namespace Windows::UI::ViewManagement;

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

// Nagisa's User Agent
// Mozilla/5.0 (Windows NT 10.0; Nagisa/0.1.1702.17) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/12.10240

MainPage::MainPage()
{
	InitializeComponent();

	auto WindowSize = Size(540.0, 320.0);
	auto appCurrentView = ApplicationView::GetForCurrentView();
	auto appTitleBar = appCurrentView->TitleBar;
	auto coreTitleBar = CoreApplication::GetCurrentView()->TitleBar;
	
	appCurrentView->SetPreferredMinSize(WindowSize);
	appCurrentView->PreferredLaunchViewSize = WindowSize;
	appCurrentView->PreferredLaunchWindowingMode = 
		ApplicationViewWindowingMode::PreferredLaunchViewSize;
	
	appTitleBar->ButtonBackgroundColor = Colors::Transparent;
	appTitleBar->ButtonInactiveBackgroundColor = Colors::Transparent;
	appTitleBar->ButtonHoverBackgroundColor = Colors::DarkGray;

	coreTitleBar->ExtendViewIntoTitleBar = true;
	coreTitleBar->LayoutMetricsChanged += 
		ref new TypedEventHandler<CoreApplicationViewTitleBar^, Object^>(
			this, &MainPage::CoreTitleBar_LayoutMetricsChanged);
	
	Window::Current->SetTitleBar(NagisaTitleBarBackground);
}

void Nagisa::MainPage::CoreTitleBar_LayoutMetricsChanged(
	Windows::ApplicationModel::Core::CoreApplicationViewTitleBar^ sender, 
	Platform::Object^ e)
{
	NagisaTitleBar->Height = sender->Height;
	NagisaTitleBar->Padding = Thickness(
		sender->SystemOverlayLeftInset,
		0.0,
		sender->SystemOverlayRightInset,
		0.0);
}