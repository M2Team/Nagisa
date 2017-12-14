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

#include "M2RemoveReference.h"
#include "M2AsyncWait.h"

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
inline Microsoft::WRL::ComPtr<IInspectable> M2GetInspectable(
	Platform::Object^ object) throw()
{
	return Microsoft::WRL::ComPtr<IInspectable>(
		reinterpret_cast<IInspectable*>(object));
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
byte* M2GetPointer(Windows::Storage::Streams::IBuffer^ Buffer) throw();

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
Windows::Storage::Streams::IBuffer^ M2MakeIBuffer(
	byte* Pointer, UINT32 Capacity) throw();

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
std::wstring M2MakeUTF16String(const std::string& UTF8String);

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
std::string M2MakeUTF8String(const std::wstring& UTF16String);

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
std::wstring M2MakeUTF16String(Platform::String^& PlatformString);

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
std::string M2MakeUTF8String(Platform::String^& PlatformString);

// The M2MakeUTF8String function finds a sub string from a source string.
//
// Parameters:
//
// SourceString
//     The source string.
// SubString
//     The sub string.
// IgnoreCase
//     The option can determines whether to ignore case.
//
// Return value:
//
// If success, it will return true.
bool M2FindSubString(
	Platform::String^& SourceString,
	Platform::String^& SubString,
	bool IgnoreCase);

#endif // _M2_HELPERS_WINRT_
