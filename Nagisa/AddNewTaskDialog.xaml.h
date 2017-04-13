//
// AddNewTaskDialog.xaml.h
// AddNewTaskDialog 类的声明
//

#pragma once

#include "AddNewTaskDialog.g.h"

namespace Nagisa
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AddNewTaskDialog sealed
	{
	public:
		AddNewTaskDialog();
	private:
		void ContentDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
		void ContentDialog_SecondaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
	};
}
