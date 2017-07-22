/******************************************************************************
Project:M2-Team Common Library
Description: Implemention for asynchronous functions
File Name: m2async.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _M2ASYNC_
#define _M2ASYNC_

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;

#include <Windows.h>

template<class T>
struct m2_remove_cx_ref
{
	typedef T type;
};

template<class T>
struct m2_remove_cx_ref<T^>
{
	typedef T type;
};

/*
The m2_await function tries to wait asynchronous call and return nothing.
Throw a COM exception if the function fails.
*/
template<typename TAsyncResult>
inline void m2_await_internal(TAsyncResult result)
{
	// Create an event object for wait the asynchronous call.
	HANDLE hEvent = CreateEventExW(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
	if (nullptr != hEvent)
	{
		// Set event signaled to end wait when completed.
		result->Completed =
			ref new m2_remove_cx_ref<decltype(result->Completed)>::type(
				[hEvent](IAsyncInfo^ asyncInfo, AsyncStatus asyncStatus)
		{
			UNREFERENCED_PARAMETER(asyncInfo);
			UNREFERENCED_PARAMETER(asyncStatus);

			SetEvent(hEvent);
		});

		// Wait event object signaled.
		WaitForSingleObjectEx(hEvent, INFINITE, FALSE);

		// Close the event object handle before return.
		CloseHandle(hEvent);
	}
	else
	{
		// Throw a COM exception if failed to create an event object.
		throw ref new COMException(__HRESULT_FROM_WIN32(GetLastError()));
	}

	// Throw a COM exception if asynchronous call failed.
	if (AsyncStatus::Error == result->Status)
	{
		throw ref new COMException(result->ErrorCode.Value);
	}
}

/*
The m2_await function is a wrapper of m2_await_internal.
It tries to wait asynchronous call and return result.
Throw a COM exception if the function fails.
*/
template<typename TResult>
inline TResult m2_await(IAsyncOperation<TResult>^ operation)
{
	m2_await_internal(operation);
	return operation->GetResults();
}

/*
The m2_await function is a wrapper of m2_await_internal.
It tries to wait asynchronous call and return result.
Throw a COM exception if the function fails.
*/
template<typename TResult, typename TProgress>
inline TResult m2_await(IAsyncOperationWithProgress<TResult, TProgress>^ operation)
{
	m2_await_internal(operation);
	return operation->GetResults();
}

/*
The m2_await function is a wrapper of m2_await_internal.
It tries to wait asynchronous call and return nothing.
Throw a COM exception if the function fails.
*/
template<typename TAsyncAction>
inline void m2_await(TAsyncAction action)
{
	m2_await_internal(action);
}


#endif