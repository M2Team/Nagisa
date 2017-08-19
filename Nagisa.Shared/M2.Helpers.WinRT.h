/******************************************************************************
Project: M2-Team Common Library
Description: Definition for Windows Runtime part of M2-Team Common Library
File Name: M2.Helpers.WinRT.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _M2_HELPERS_WINRT_
#define _M2_HELPERS_WINRT_

#include <Windows.h>

#include <robuffer.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;
using Platform::COMException;
using Platform::Object;
using Windows::Storage::Streams::IBuffer;

// The M2GetInspectable function retrieves the IInspectable interface from the 
// provided C++/CX object. 
//
// Parameters:
//
// object
//     The C++/CX object you want to retrieve the raw pointer.
//
// Return value:
//
// The return value is the IInspectable interface from the provided C++/CX 
// object.
inline ComPtr<IInspectable> M2GetInspectable(Object^ object) throw()
{
	return ComPtr<IInspectable>(reinterpret_cast<IInspectable*>(object));
}

// The m2_await_internal function uses the non-blocking way to try to wait 
// asynchronous call.
//
// Parameters:
//
// async
//     The asynchronous call you want to wait.
// timeout
//     The maximum time interval for waiting the asynchronous call, in 
//     milliseconds. A value of -1 indicates that the suspension should not 
//     time out.
//
// Return value:
//
// If the function succeeds, the return value is S_OK.
// If the function fails, the return value is the HRESULT error code.
HRESULT m2_await_internal(ComPtr<IInspectable>& async, int32 timeout) throw();

// The m2_await function uses the non-blocking way to try to wait 
// asynchronous call.
//
// Parameters:
//
// async
//     The asynchronous call you want to wait.
// timeout
//     The maximum time interval for waiting the asynchronous call, in 
//     milliseconds. A value of -1 indicates that the suspension should not 
//     time out.
//
// Return value:
//
// The return value is determined by the asynchronous call.
// The function will throw a COM exception if the function fails. 
template<typename TAsync>
inline auto m2_await(
	TAsync async, int32 timeout = -1) -> decltype(async->GetResults())
{
	// Wait the asynchronous call until the status is not Started or the 
	// timeout interval has been elapsed.
	HRESULT hr = m2_await_internal(M2GetInspectable(async), timeout);
	if (FAILED(hr))
	{
		throw COMException::CreateException(hr);
	}

	// Return the result of asynchronous call.
	return async->GetResults();
}

// The M2GetPointerFromIBuffer function retrieves the raw pointer from the 
// provided IBuffer object. 
//
// Parameters:
//
// Buffer
//     The IBuffer object you want to retrieve the raw pointer.
//
// Return value:
//
// If the function succeeds, the return value is the raw pointer from the 
// provided IBuffer object. If the function fails, the return value is nullptr.
//
// Warning: 
// The lifetime of the returned buffer is controlled by the lifetime of the 
// buffer object that's passed to this method. When the buffer has been 
// released, the pointer becomes invalid and must not be used.
byte* M2GetPointerFromIBuffer(IBuffer^ Buffer) throw();

#endif // _M2_HELPERS_WINRT_
