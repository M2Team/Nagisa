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
#include <wrl\client.h>

#include <string>

using Microsoft::WRL::ComPtr;

using ::Platform::COMException;
using ::Platform::Object;
using ::Platform::String;
using ::Windows::Storage::Streams::IBuffer;

using ::std::string;
using ::std::wstring;

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

// The M2AsyncWait function uses the non-blocking way to try to wait 
// asynchronous call.
//
// Parameters:
//
// Async
//     The asynchronous call you want to wait.
// Timeout
//     The maximum time interval for waiting the asynchronous call, in 
//     milliseconds. A value of -1 indicates that the suspension should not 
//     time out.
//
// Return value:
//
// If the function succeeds, the return value is S_OK.
// If the function fails, the return value is the HRESULT error code.
HRESULT M2AsyncWait(ComPtr<IInspectable>& Async, int32 Timeout) throw();

// The M2AsyncWait function uses the non-blocking way to try to wait 
// asynchronous call.
//
// Parameters:
//
// Async
//     The asynchronous call you want to wait.
// Timeout
//     The maximum time interval for waiting the asynchronous call, in 
//     milliseconds. A value of -1 indicates that the suspension should not 
//     time out.
//
// Return value:
//
// The return value is determined by the asynchronous call.
// The function will throw a COM exception if the function fails. 
template<typename TAsync>
inline auto M2AsyncWait(
	TAsync Async, int32 Timeout = -1) -> decltype(Async->GetResults())
{
	// Wait the asynchronous call until the status is not Started or the 
	// timeout interval has been elapsed.
	HRESULT hr = M2AsyncWait(M2GetInspectable(Async), Timeout);
	if (FAILED(hr))
	{
		throw COMException::CreateException(hr);
	}

	// Return the result of asynchronous call.
	return Async->GetResults();
}

// The M2GetPointer function retrieves the raw pointer from the provided 
// IBuffer object. 
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
byte* M2GetPointer(IBuffer^ Buffer) throw();

// The M2MakeIBuffer function retrieves the IBuffer object from the provided 
// raw pointer.
//
// Parameters:
//
// Pointer
//     The raw pointer you want to retrieve the IBuffer object.
// Capacity
//     The size of raw pointer you want to retrieve the IBuffer object.
//
// Return value:
//
// If the function succeeds, the return value is the IBuffer object from the 
// provided raw pointer. If the function fails, the return value is nullptr.
//
// Warning: 
// The lifetime of the returned IBuffer object is controlled by the lifetime of
// the raw pointer that's passed to this method. When the raw pointer has been 
// released, the IBuffer object becomes invalid and must not be used.
IBuffer^ M2MakeIBuffer(byte* Pointer, UINT32 Capacity) throw();

// The M2MakeUTF16String function converts from UTF-8 string to UTF-16 string.
//
// Parameters:
//
// UTF8String
//     The UTF-8 string you want to convert.
//
// Return value:
//
// The return value is the UTF-16 string.
wstring M2MakeUTF16String(const string& UTF8String);

// The M2MakeUTF8String function converts from UTF-16 string to UTF-8 string.
//
// Parameters:
//
// UTF16String
//     The UTF-16 string you want to convert.
//
// Return value:
//
// The return value is the UTF-8 string.
string M2MakeUTF8String(const wstring& UTF16String);

// The M2MakeUTF16String function converts from C++/CX string to UTF-16 string.
//
// Parameters:
//
// PlatformString
//     The C++/CX string you want to convert.
//
// Return value:
//
// The return value is the UTF-16 string.
wstring M2MakeUTF16String(String^& PlatformString);

// The M2MakeUTF8String function converts from C++/CX string to UTF-8 string.
//
// Parameters:
//
// PlatformString
//     The C++/CX string you want to convert.
//
// Return value:
//
// The return value is the UTF-8 string.
string M2MakeUTF8String(String^& PlatformString);

#endif // _M2_HELPERS_WINRT_
