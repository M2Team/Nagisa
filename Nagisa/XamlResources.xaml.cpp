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
using namespace Platform::Collections;
using namespace Windows::ApplicationModel::Resources;
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

Nagisa::NagisaStatusCompletedToCollapsedConverter::NagisaStatusCompletedToCollapsedConverter()
{

}

Object^ Nagisa::NagisaStatusCompletedToCollapsedConverter::Convert(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	IBox<TransferStatus>^ status = dynamic_cast<IBox<TransferStatus>^>(value);

	if (status != nullptr && status->Value == TransferStatus::Completed)
	{
		return Visibility::Collapsed;
	}

	return Visibility::Visible;
}

Object^ Nagisa::NagisaStatusCompletedToCollapsedConverter::ConvertBack(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	throw ref new Platform::NotImplementedException();
}

Nagisa::NagisaStatusToOperationButtonIconConverter::NagisaStatusToOperationButtonIconConverter()
{

}

Object^ Nagisa::NagisaStatusToOperationButtonIconConverter::Convert(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	IBox<TransferStatus>^ status = dynamic_cast<IBox<TransferStatus>^>(value);
	String^ IconString = L"\xE72C";

	if (status != nullptr)
	{
		switch (status->Value)
		{
		case TransferStatus::Paused:
			IconString = L"\xE768";
			break;
		case TransferStatus::Running:
			IconString = L"\xE769";
			break;
		default:
			break;
		}
	}

	return IconString;
}

Object^ Nagisa::NagisaStatusToOperationButtonIconConverter::ConvertBack(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	throw ref new Platform::NotImplementedException();
}

Nagisa::NagisaStatusToOperationButtonToolTipConverter::NagisaStatusToOperationButtonToolTipConverter()
{

}

Object^ Nagisa::NagisaStatusToOperationButtonToolTipConverter::Convert(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	IBox<TransferStatus>^ status = dynamic_cast<IBox<TransferStatus>^>(value);
	ResourceLoader^ resourceLoader = ResourceLoader::GetForCurrentView();

	String^ ButtonToolTipResource = L"OperationButtonToolTip_Retry";

	if (status != nullptr)
	{
		switch (status->Value)
		{
		case TransferStatus::Paused:
			ButtonToolTipResource = L"OperationButtonToolTip_Resume";
			break;
		case TransferStatus::Running:
			ButtonToolTipResource = L"OperationButtonToolTip_Pause";
			break;
		default:
			break;
		}
	}

	return resourceLoader->GetString(ButtonToolTipResource);
}

Object^ Nagisa::NagisaStatusToOperationButtonToolTipConverter::ConvertBack(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	throw ref new Platform::NotImplementedException();
}

Nagisa::NagisaItemSourceEmptyToVisibilityConverter::NagisaItemSourceEmptyToVisibilityConverter()
{

}

Object^ Nagisa::NagisaItemSourceEmptyToVisibilityConverter::Convert(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	VectorView<TransferTask^>^ ItemSource = dynamic_cast<VectorView<TransferTask^>^>(value);

	if (ItemSource == nullptr || ItemSource->Size == 0)
	{
		return Visibility::Visible;
	}

	return Visibility::Collapsed;
}

Object^ Nagisa::NagisaItemSourceEmptyToVisibilityConverter::ConvertBack(Platform::Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	throw ref new Platform::NotImplementedException();
}