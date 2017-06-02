#pragma once

#ifndef _M2_ASYNC_WAIT_H_
#define _M2_ASYNC_WAIT_H_

using namespace Platform;
using namespace Windows::Foundation;

template<typename TResult>
inline TResult M2AsyncWait(IAsyncOperation<TResult>^ Operation)
{
	TResult value;

	HANDLE hEvent = CreateEventExW(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
	if (hEvent)
	{
		Operation->Completed = ref new AsyncOperationCompletedHandler<TResult>(
			[hEvent, &value](IAsyncOperation<TResult>^ asyncInfo, AsyncStatus asyncStatus)
		{
			if (asyncStatus == AsyncStatus::Error)
				throw ref new COMException(asyncInfo->ErrorCode.Value);
			
			value = asyncInfo->GetResults();
			SetEvent(hEvent);
		});

		WaitForSingleObjectEx(hEvent, INFINITE, FALSE);

		CloseHandle(hEvent);
	}
	else
	{
		throw ref new COMException(__HRESULT_FROM_WIN32(GetLastError()));
	}

	return value;
}

inline void M2AsyncWait(IAsyncAction^ Action)
{
	HANDLE hEvent = CreateEventExW(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
	if (hEvent)
	{
		Action->Completed = ref new AsyncActionCompletedHandler(
			[hEvent](IAsyncAction^ asyncInfo, AsyncStatus asyncStatus)
		{		
			if (asyncStatus == AsyncStatus::Error)
				throw ref new COMException(asyncInfo->ErrorCode.Value);
			
			SetEvent(hEvent);
		});

		WaitForSingleObjectEx(hEvent, INFINITE, FALSE);

		CloseHandle(hEvent);
	}
	else
	{
		throw ref new COMException(__HRESULT_FROM_WIN32(GetLastError()));
	}
}

template<typename TResult, typename TProgress>
inline TResult M2AsyncWait(IAsyncOperationWithProgress<TResult, TProgress>^ Operation)
{
	TResult value;

	HANDLE hEvent = CreateEventExW(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
	if (hEvent)
	{	
		Operation->Completed = ref new AsyncOperationWithProgressCompletedHandler<TResult, TProgress>(
			[hEvent, &value](IAsyncOperationWithProgress<TResult, TProgress>^ asyncInfo, AsyncStatus asyncStatus)
		{
			if (asyncStatus == AsyncStatus::Error)
				throw ref new COMException(asyncInfo->ErrorCode.Value);
			
			value = asyncInfo->GetResults();
			SetEvent(hEvent);
		});

		WaitForSingleObjectEx(hEvent, INFINITE, FALSE);

		CloseHandle(hEvent);
	}
	else
	{
		throw ref new COMException(__HRESULT_FROM_WIN32(GetLastError()));
	}

	return value;
}

template<typename TProgress>
inline void M2AsyncWait(IAsyncActionWithProgress<TProgress>^ Action)
{
	HANDLE hEvent = CreateEventExW(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
	if (hEvent)
	{
		Action->Completed = ref new AsyncActionWithProgressCompletedHandler<TProgress>(
			[hEvent](IAsyncActionWithProgress<TProgress>^ asyncInfo, AsyncStatus asyncStatus)
		{
			if (asyncStatus == AsyncStatus::Error)
				throw ref new COMException(asyncInfo->ErrorCode.Value);
			
			SetEvent(hEvent);
		});

		WaitForSingleObjectEx(hEvent, INFINITE, FALSE);

		CloseHandle(hEvent);
	}
	else
	{
		throw ref new COMException(__HRESULT_FROM_WIN32(GetLastError()));
	}
}

#endif // !_M2_ASYNC_WAIT_H_
