﻿/******************************************************************************
Project: M2-Team Common Library
Description: Implemention for Windows Runtime part of M2-Team Common Library
File Name: M2.Helpers.WinRT.cpp
License: The MIT License
******************************************************************************/

#include "pch.h"

#include "M2.Helpers.WinRT.h"

#include <Windows.h>
#include <wrl/client.h>

#include <asyncinfo.h>
#include <robuffer.h>

using Microsoft::WRL::ComPtr;
using ABI::Windows::Foundation::AsyncStatus;
using Windows::Storage::Streams::IBuffer;
using Windows::Storage::Streams::IBufferByteAccess;

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
HRESULT m2_await_internal(ComPtr<IInspectable>& async, int32 timeout) throw()
{
	HRESULT hr = S_OK;
	HRESULT hrResult = S_OK;
	ComPtr<IAsyncInfo> asyncInfo;
	AsyncStatus status = AsyncStatus::Started;	

	// Get the IAsyncInfo interface.
	hr = async.As(&asyncInfo);
	if (SUCCEEDED(hr))
	{
		// Wait the asynchronous call until the status is not Started or the 
		// timeout interval has been elapsed.
		while (
			SUCCEEDED(hr = asyncInfo->get_Status(&status)) &&
			AsyncStatus::Started == status &&
			(timeout == -1 || timeout > 0))
		{
			// Calling SleepEx() for sleep 50ms every time because 
			// Microsoft says that all UWP APIs that can't guarantee to 
			// complete within 50ms has been made asynchronous and its name
			// suffixed with Async.
			::SleepEx(50, FALSE);
			if (timeout != -1)
				timeout -= 50;
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
byte* M2GetPointerFromIBuffer(IBuffer^ Buffer) throw()
{
	byte* pBuffer = nullptr;
	ComPtr<IBufferByteAccess> bufferByteAccess;
	if (SUCCEEDED(M2GetInspectable(Buffer).As(&bufferByteAccess)))
	{
		bufferByteAccess->Buffer(&pBuffer);
	}

	return pBuffer;
}