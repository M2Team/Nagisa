//
// NewTaskDialog.xaml.h
// NewTaskDialog 类的声明
//

#pragma once

#include "NewTaskDialog.g.h"

namespace Nagisa
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class NewTaskDialog sealed
	{
	public:
		NewTaskDialog();
	private:
		void ContentDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
		void ContentDialog_SecondaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
	};
}
