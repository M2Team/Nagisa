//
// MainPage.xaml.h
// MainPage 类的声明
//

#pragma once

#include "MainPage.g.h"
#include "XamlResources.xaml.h"

namespace Nagisa
{
	/// <summary>
	/// 可用于自身或导航至 Frame 内部的空白页。
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class MainPage sealed
	{
	public:
		MainPage();

	internal:
		Assassin::TransferManager^ m_TransferManager = nullptr;

	private:
		void ListView_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void NewTaskButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void SettingsAndAboutButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void AutoSuggestBox_Search(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::DependencyObject^ args);

		void MenuFlyoutItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
