//
// FirstRunDialog.xaml.h
// FirstRunDialog 类的声明
//

#pragma once

#include "FirstRunDialog.g.h"

namespace Nagisa
{
	namespace Application
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class FirstRunDialog sealed
		{
		public:
			FirstRunDialog();
		private:
			void ContentDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
			void ContentDialog_SecondaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
		};
	}	
}
