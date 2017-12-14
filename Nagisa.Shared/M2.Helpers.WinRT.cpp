/******************************************************************************
Project: M2-Team Common Library
Description: Implemention for Windows Runtime part of M2-Team Common Library
File Name: M2.Helpers.WinRT.cpp
License: The MIT License
******************************************************************************/

#include "pch.h"

#include "M2.Helpers.WinRT.h"

#include <Windows.h>
#include <wrl\client.h>
#include <wrl\implements.h>
#include <robuffer.h>
#include <windows.foundation.h>
#include <windows.storage.streams.h>

#include <string>

using Microsoft::WRL::ComPtr;
using Microsoft::WRL::MakeAndInitialize;
using Microsoft::WRL::RuntimeClass;
using Microsoft::WRL::RuntimeClassFlags;
using Microsoft::WRL::RuntimeClassType;

using Platform::Object;
using Platform::String;

using Windows::Storage::Streams::IBuffer;

using abi_IBuffer = ABI::Windows::Storage::Streams::IBuffer;
using abi_IBufferByteAccess = Windows::Storage::Streams::IBufferByteAccess;

using std::string;
using std::wstring;

#include <type_traits>

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
byte* M2GetPointer(IBuffer^ Buffer) throw()
{
	byte* pBuffer = nullptr;
	ComPtr<abi_IBufferByteAccess> bufferByteAccess;
	if (SUCCEEDED(M2GetInspectable(Buffer).As(&bufferByteAccess)))
	{
		bufferByteAccess->Buffer(&pBuffer);
	}

	return pBuffer;
}

class BufferReference : public RuntimeClass<
	RuntimeClassFlags<RuntimeClassType::WinRtClassicComMix>,
	abi_IBuffer,
	abi_IBufferByteAccess>
{
private:
	UINT32 m_Capacity;
	UINT32 m_Length;
	byte* m_Pointer;

public:
	virtual ~BufferReference() throw()
	{
	}

	STDMETHODIMP RuntimeClassInitialize(
		byte* Pointer, UINT32 Capacity) throw()
	{
		m_Capacity = Capacity;
		m_Length = Capacity;
		m_Pointer = Pointer;
		return S_OK;
	}

	// IBufferByteAccess::Buffer
	STDMETHODIMP Buffer(byte **value) throw()
	{
		*value = m_Pointer;
		return S_OK;
	}

	// IBuffer::get_Capacity
	STDMETHODIMP get_Capacity(UINT32 *value) throw()
	{
		*value = m_Capacity;
		return S_OK;
	}

	// IBuffer::get_Length
	STDMETHODIMP get_Length(UINT32 *value) throw()
	{
		*value = m_Length;
		return S_OK;
	}

	// IBuffer::put_Length
	STDMETHODIMP put_Length(UINT32 value) throw()
	{
		if (value > m_Capacity)
			return E_INVALIDARG;
		m_Length = value;
		return S_OK;
	}
};

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
IBuffer^ M2MakeIBuffer(byte* Pointer, UINT32 Capacity) throw()
{
	IBuffer^ buffer = nullptr;
	
	ComPtr<BufferReference> bufferReference;
	if (SUCCEEDED(MakeAndInitialize<BufferReference>(
		&bufferReference, Pointer, Capacity)))
	{
		buffer = reinterpret_cast<IBuffer^>(bufferReference.Get());
	}

	return buffer;
}

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
wstring M2MakeUTF16String(const string& UTF8String)
{
	wstring UTF16String;

	int UTF16StringLength = MultiByteToWideChar(
		CP_UTF8,
		0,
		UTF8String.data(),
		(int)UTF8String.size(),
		nullptr,
		0);
	if (UTF16StringLength > 0)
	{
		UTF16String.resize(UTF16StringLength);
		MultiByteToWideChar(
			CP_UTF8,
			0,
			UTF8String.data(),
			(int)UTF8String.size(),
			&UTF16String[0],
			UTF16StringLength);
	}

	return UTF16String;
}

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
string M2MakeUTF8String(const wstring& UTF16String)
{
	string UTF8String;

	int UTF8StringLength = WideCharToMultiByte(
		CP_UTF8,
		0,
		UTF16String.data(),
		(int)UTF16String.size(),
		nullptr,
		0,
		nullptr,
		nullptr);
	if (UTF8StringLength > 0)
	{
		UTF8String.resize(UTF8StringLength);
		WideCharToMultiByte(
			CP_UTF8,
			0,
			UTF16String.data(),
			(int)UTF16String.size(),
			&UTF8String[0],
			UTF8StringLength,
			nullptr,
			nullptr);
	}

	return UTF8String;
}

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
wstring M2MakeUTF16String(String^& PlatformString)
{
	return wstring(PlatformString->Data(), PlatformString->Length());
}

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
string M2MakeUTF8String(String^& PlatformString)
{
	return M2MakeUTF8String(M2MakeUTF16String(PlatformString));
}

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
	String^& SourceString, String^& SubString, bool IgnoreCase)
{
	return (::FindNLSStringEx(
		nullptr,
		(IgnoreCase ? NORM_IGNORECASE : 0) | FIND_FROMSTART,
		SourceString->Data(),
		SourceString->Length(),
		SubString->Data(),
		SubString->Length(),
		nullptr,
		nullptr,
		nullptr,
		0) >= 0);
}
