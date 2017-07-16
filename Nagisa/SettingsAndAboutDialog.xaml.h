//
// SettingsAndAboutDialog.xaml.h
// SettingsAndAboutDialog 类的声明
//

#pragma once

#include "SettingsAndAboutDialog.g.h"

namespace Nagisa
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class SettingsAndAboutDialog sealed
	{
	public:
		SettingsAndAboutDialog();
	private:
		void OKButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
		void CancelButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
	};
}
