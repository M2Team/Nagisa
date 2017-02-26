#include <Windows.h>
#include <wrl.h>
#include "pch.h"

#include <wrl\client.h>
#include <wrl\wrappers\corewrappers.h>
#include <roapi.h>

#include <windows.foundation.h>
#include <windows.ui.h>
#include <windows.ui.viewmanagement.h>
#include <windows.ui.xaml.h>

#include <Nagisa.Core.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::ViewManagement;
using namespace ABI::Windows::UI::Xaml;

HRESULT Nagisa::SetWindowSize(
	_In_ FLOAT Width,
	_In_ FLOAT Height)
{
	HRESULT hr = S_OK;
	Size WindowSize = { Width,Height };
	IApplicationViewStatics *pApplicationViewStatics = nullptr;
	IApplicationViewStatics2 *pApplicationViewStatics2 = nullptr;
	IApplicationViewStatics3 *pApplicationViewStatics3 = nullptr;
	IApplicationView *pApplicationView = nullptr;
	IApplicationView3 *pApplicationView3 = nullptr;

	hr = RoGetActivationFactory(
		HStringReference(L"Windows.UI.ViewManagement.ApplicationView").Get(),
		IID_INS_ARGS(&pApplicationViewStatics));
	if (SUCCEEDED(hr))
	{
		hr = pApplicationViewStatics->QueryInterface(IID_INS_ARGS(&pApplicationViewStatics2));
		if (SUCCEEDED(hr))
		{
			hr = pApplicationViewStatics2->GetForCurrentView(&pApplicationView);
			if (SUCCEEDED(hr))
			{
				hr = pApplicationView->QueryInterface(IID_INS_ARGS(&pApplicationView3));
				if (SUCCEEDED(hr))
				{
					hr = pApplicationView3->SetPreferredMinSize(WindowSize);
					pApplicationView3->Release();
				}
				pApplicationView->Release();
			}

			hr = pApplicationViewStatics2->QueryInterface(IID_INS_ARGS(&pApplicationViewStatics3));
			if (SUCCEEDED(hr))
			{
				hr = pApplicationViewStatics3->put_PreferredLaunchViewSize(WindowSize);
				hr = pApplicationViewStatics3->put_PreferredLaunchWindowingMode(ApplicationViewWindowingMode_PreferredLaunchViewSize);
				pApplicationViewStatics3->Release();
			}

			pApplicationViewStatics2->Release();
		}
		pApplicationViewStatics->Release();
	}
	return hr;
}

HRESULT Nagisa::SetXamlElementAsTitleBar(
	_In_ ABI::Windows::UI::Xaml::IUIElement *value)
{
	HRESULT hr = S_OK;
	ComPtr<IWindowStatics> pWindowStatics;
	ComPtr<IWindow> pWindow;
	ComPtr<IWindow2> pWindow2;

	hr = GetActivationFactory(HStringReference(L"Windows.UI.Xaml.Window").Get(), &pWindowStatics);
	if (SUCCEEDED(hr))
	{
		hr = pWindowStatics->get_Current(&pWindow);
		if (SUCCEEDED(hr))
		{
			hr = pWindow.As(&pWindow2);
			if (SUCCEEDED(hr))
			{
				hr = pWindow2->SetTitleBar(value);
			}
		}
	}
	return hr;
}



void Nagisa::SetWindowSize2()
{
	HRESULT hr = S_OK;

	IApplicationViewStatics *pApplicationViewStatics = nullptr;
	IApplicationViewStatics2 *pApplicationViewStatics2 = nullptr;
	IApplicationViewStatics3 *pApplicationViewStatics3 = nullptr;

	IApplicationView *pApplicationView = nullptr;
	IApplicationView3 *pApplicationView3 = nullptr;

	IApplicationViewTitleBar *pApplicationViewTitleBar = nullptr;

	IColorsStatics *pColorsStatics = nullptr;
	
	Size WindowSize = { 0 };
	WindowSize.Width = 540.0;
	WindowSize.Height = 320.0;

	hr = RoGetActivationFactory(HStringReference(RuntimeClass_Windows_UI_ViewManagement_ApplicationView).Get(), IID_INS_ARGS(&pApplicationViewStatics));
	if (SUCCEEDED(hr))
	{
		hr = pApplicationViewStatics->QueryInterface(IID_INS_ARGS(&pApplicationViewStatics2));
		if (SUCCEEDED(hr))
		{
			hr = pApplicationViewStatics2->GetForCurrentView(&pApplicationView);
			if (SUCCEEDED(hr))
			{
				hr = pApplicationView->QueryInterface(IID_INS_ARGS(&pApplicationView3));
				if (SUCCEEDED(hr))
				{
					hr = pApplicationView3->SetPreferredMinSize(WindowSize);

					hr = pApplicationView3->get_TitleBar(&pApplicationViewTitleBar);
					if (SUCCEEDED(hr))
					{
						/*
						appTitleBar->ButtonBackgroundColor = Windows::UI::Colors::Transparent;
						appTitleBar->ButtonInactiveBackgroundColor = Windows::UI::Colors::Transparent;
						appTitleBar->ButtonHoverBackgroundColor = Windows::UI::Colors::DarkGray;
						*/

						hr = RoGetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Colors).Get(), IID_INS_ARGS(&pColorsStatics));
						if (SUCCEEDED(hr))
						{
							Color Color_Transparent = { 0 };
							Color Color_DarkGray = { 0 };

							hr = pColorsStatics->get_Transparent(&Color_Transparent);
							if (SUCCEEDED(hr))
							{
								
								//IPropertyValueStatics 

								
								
								//pApplicationViewTitleBar->put_ButtonBackgroundColor(Color_Transparent);
							}

							


							hr = pColorsStatics->get_DarkGray(&Color_DarkGray);
							if (SUCCEEDED(hr))
							{

							}

							pColorsStatics->Release();
						}
						pApplicationViewTitleBar->Release();
					}

					pApplicationView3->Release();
				}
				pApplicationView->Release();
			}

			hr = pApplicationViewStatics2->QueryInterface(IID_INS_ARGS(&pApplicationViewStatics3));
			if (SUCCEEDED(hr))
			{
				hr = pApplicationViewStatics3->put_PreferredLaunchViewSize(WindowSize);
				hr = pApplicationViewStatics3->put_PreferredLaunchWindowingMode(ApplicationViewWindowingMode_PreferredLaunchViewSize);
				pApplicationViewStatics3->Release();
			}

			pApplicationViewStatics2->Release();
		}
		pApplicationViewStatics->Release();
	}
}
