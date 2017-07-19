//
// XamlResources.xaml.cpp
// XamlResources 类的实现
//

#include "pch.h"
#include "XamlResources.xaml.h"

using namespace Nagisa;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace Assassin;
using namespace Windows::UI;
using namespace Windows::UI::Xaml::Interop;

Nagisa::NagisaStatusToForegroundConverter::NagisaStatusToForegroundConverter()
{
	
}

Object^ Nagisa::NagisaStatusToForegroundConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	IBox<TransferStatus>^ status = dynamic_cast<IBox<TransferStatus>^>(value);
	Color color = Colors::Red;

	if (status != nullptr)
	{
		switch (status->Value)
		{
		case TransferStatus::Completed:
			color = Colors::Transparent;
			break;
		case TransferStatus::Paused:
			color = Colors::Orange;
			break;
		case TransferStatus::Running:
			color = Colors::Green;
			break;
		default:
			break;
		}
	}

	auto brush = ref new SolidColorBrush(color);
	brush->Opacity = 0.8;
	return brush;
}

Object^ Nagisa::NagisaStatusToForegroundConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	throw ref new Platform::NotImplementedException();
}

Nagisa::NagisaStatusToBackgroundConverter::NagisaStatusToBackgroundConverter()
{

}

Object^ Nagisa::NagisaStatusToBackgroundConverter::Convert(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	IBox<TransferStatus>^ status = dynamic_cast<IBox<TransferStatus>^>(value);
	Color color = Colors::Black;

	if (status != nullptr && status->Value == TransferStatus::Completed)
	{
		color = Colors::Transparent;
	}

	auto brush = ref new SolidColorBrush(color);
	brush->Opacity = 0.1;
	return brush;
}

Object^ Nagisa::NagisaStatusToBackgroundConverter::ConvertBack(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	throw ref new Platform::NotImplementedException();
}

Nagisa::NagisaStatusErrorToVisibilityConverter::NagisaStatusErrorToVisibilityConverter()
{

}

Object^ Nagisa::NagisaStatusErrorToVisibilityConverter::Convert(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	IBox<TransferStatus>^ status = dynamic_cast<IBox<TransferStatus>^>(value);

	if (status != nullptr && status->Value == TransferStatus::Error)
	{
		return Visibility::Visible;
	}

	return Visibility::Collapsed;
}

Object^ Nagisa::NagisaStatusErrorToVisibilityConverter::ConvertBack(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	throw ref new Platform::NotImplementedException();
}

Nagisa::NagisaStatusPausedToVisibilityConverter::NagisaStatusPausedToVisibilityConverter()
{

}

Object^ Nagisa::NagisaStatusPausedToVisibilityConverter::Convert(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	IBox<TransferStatus>^ status = dynamic_cast<IBox<TransferStatus>^>(value);

	if (status != nullptr && status->Value == TransferStatus::Paused)
	{
		return Visibility::Visible;
	}

	return Visibility::Collapsed;
}

Object^ Nagisa::NagisaStatusPausedToVisibilityConverter::ConvertBack(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	throw ref new Platform::NotImplementedException();
}

Nagisa::NagisaStatusRunningToVisibilityConverter::NagisaStatusRunningToVisibilityConverter()
{

}

Object^ Nagisa::NagisaStatusRunningToVisibilityConverter::Convert(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	IBox<TransferStatus>^ status = dynamic_cast<IBox<TransferStatus>^>(value);

	if (status != nullptr && status->Value == TransferStatus::Running)
	{
		return Visibility::Visible;
	}

	return Visibility::Collapsed;
}

Object^ Nagisa::NagisaStatusRunningToVisibilityConverter::ConvertBack(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	throw ref new Platform::NotImplementedException();
}
