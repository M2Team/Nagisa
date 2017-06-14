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

#include <Windows.h>

/*
The m2_await function tries to wait asynchronous call and return result.
Throw a COM exception if the function fails.
*/
template<typename TResult>
inline TResult m2_await(IAsyncOperation<TResult>^ operation)
{
	// Create an event object for wait the asynchronous call.
	HANDLE hEvent = CreateEventExW(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
	if (nullptr != hEvent)
	{
		// Set event signaled to end wait when completed.
		operation->Completed = ref new AsyncOperationCompletedHandler<TResult>(
			[hEvent](IAsyncOperation<TResult>^ asyncInfo, AsyncStatus asyncStatus)
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
	if (AsyncStatus::Error == operation->Status)
	{
		throw ref new COMException(operation->ErrorCode.Value);
	}

	return operation->GetResults();
}

/*
The m2_await function tries to wait asynchronous call and return result.
Throw a COM exception if the function fails.
*/
template<typename TResult, typename TProgress>
inline TResult m2_await(IAsyncOperationWithProgress<TResult, TProgress>^ operation)
{
	// Create an event object for wait the asynchronous call.
	HANDLE hEvent = CreateEventExW(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
	if (nullptr != hEvent)
	{
		// Set event signaled to end wait when completed.
		operation->Completed = ref new AsyncOperationWithProgressCompletedHandler<TResult, TProgress>(
			[hEvent](IAsyncOperationWithProgress<TResult, TProgress>^ asyncInfo, AsyncStatus asyncStatus)
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
	if (AsyncStatus::Error == operation->Status)
	{
		throw ref new COMException(operation->ErrorCode.Value);
	}

	return operation->GetResults();
}

/*
The m2_await function is a wrapper of m2_await_internal.
It tries to wait asynchronous call and return nothing.
Throw a COM exception if the function fails.
*/
inline void m2_await(IAsyncAction^ action)
{
	// Create an event object for wait the asynchronous call.
	HANDLE hEvent = CreateEventExW(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
	if (nullptr != hEvent)
	{
		// Set event signaled to end wait when completed.
		action->Completed = ref new AsyncActionCompletedHandler(
			[hEvent](IAsyncAction^ asyncInfo, AsyncStatus asyncStatus)
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
	if (AsyncStatus::Error == action->Status)
	{
		throw ref new COMException(action->ErrorCode.Value);
	}
}

/*
The m2_await function is a wrapper of m2_await_internal.
It tries to wait asynchronous call and return nothing.
Throw a COM exception if the function fails.
*/
template<typename TProgress>
inline void m2_await(IAsyncActionWithProgress<TProgress>^ action)
{
	// Create an event object for wait the asynchronous call.
	HANDLE hEvent = CreateEventExW(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
	if (nullptr != hEvent)
	{
		// Set event signaled to end wait when completed.
		action->Completed = ref new AsyncActionWithProgressCompletedHandler<TProgress>(
			[hEvent](IAsyncActionWithProgress<TProgress>^ asyncInfo, AsyncStatus asyncStatus)
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
	if (AsyncStatus::Error == action->Status)
	{
		throw ref new COMException(action->ErrorCode.Value);
	}
}

#endif