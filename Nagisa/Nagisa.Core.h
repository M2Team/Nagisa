#pragma once

#include <windows.ui.xaml.h>

namespace Nagisa
{
	HRESULT SetWindowSize(
		_In_ FLOAT Width,
		_In_ FLOAT Height);

	HRESULT SetXamlElementAsTitleBar(
		_In_ ABI::Windows::UI::Xaml::IUIElement *value);

	void SetWindowSize2();
}