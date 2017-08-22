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

using ::Microsoft::WRL::MakeAndInitialize;
using ::Microsoft::WRL::RuntimeClass;
using ::Microsoft::WRL::RuntimeClassFlags;
using ::Microsoft::WRL::RuntimeClassType;

using abi_AsyncStatus = ::ABI::Windows::Foundation::AsyncStatus;
using abi_IBuffer = ABI::Windows::Storage::Streams::IBuffer;
using abi_IBufferByteAccess = ::Windows::Storage::Streams::IBufferByteAccess;

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
HRESULT M2AsyncWait(ComPtr<IInspectable>& Async, int32 Timeout) throw()
{
	HRESULT hr = S_OK;
	HRESULT hrResult = S_OK;
	ComPtr<IAsyncInfo> asyncInfo;
	abi_AsyncStatus status = AsyncStatus::Started;	

	// Get the IAsyncInfo interface.
	hr = Async.As(&asyncInfo);
	if (SUCCEEDED(hr))
	{
		// Wait the asynchronous call until the status is not Started or the 
		// timeout interval has been elapsed.
		while (
			SUCCEEDED(hr = asyncInfo->get_Status(&status)) &&
			AsyncStatus::Started == status &&
			(Timeout == -1 || Timeout > 0))
		{
			// Calling SleepEx() for sleep 50ms every time because 
			// Microsoft says that all UWP APIs that can't guarantee to 
			// complete within 50ms has been made asynchronous and its name
			// suffixed with Async.
			::SleepEx(50, FALSE);
			if (Timeout != -1)
				Timeout -= 50;
		}

		// Check the status if no error when call the interface.
		if (SUCCEEDED(hr))
		{
			if (AsyncStatus::Completed == status)
			{
				// Just do nothing if succeeded.
			}
			else if (AsyncStatus::Started == status)
			{
				// Cancel the asynchronous call and set error code if the 
				// status is still Started, the timeout interval has been 
				// elapsed.
				hr = asyncInfo->Cancel();
				hrResult = __HRESULT_FROM_WIN32(ERROR_TIMEOUT);
			}
			else if (AsyncStatus::Canceled == status)
			{
				// If the status is Cancelled, set the error code.
				hrResult = E_ABORT;
			}
			else
			{
				// If the status is other value, get and set the error code.
				hr = asyncInfo->get_ErrorCode(&hrResult);
			}
		}
	}

	return (SUCCEEDED(hr) ? hrResult : hr);
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

	int UTF16StringLength = ::MultiByteToWideChar(
		CP_UTF8,
		0,
		UTF8String.data(),
		(int)UTF8String.size(),
		nullptr,
		0);
	if (UTF16StringLength > 0)
	{
		UTF16String.resize(UTF16StringLength);
		::MultiByteToWideChar(
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

	int UTF8StringLength = ::WideCharToMultiByte(
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
		::WideCharToMultiByte(
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
