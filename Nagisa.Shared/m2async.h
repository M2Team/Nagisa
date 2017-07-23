/******************************************************************************
Project: M2-Team Common Library
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


namespace M2
{
	namespace Helpers
	{
		template<class T>
		struct RemoveCXReference
		{
			typedef T Type;
		};

		template<class T>
		struct RemoveCXReference<T^>
		{
			typedef T Type;
		};

		template<typename _Class, typename _ReturnType>
		_ReturnType ReturnTypeClassHelperThunk(_ReturnType(_Class::*)() const);

		template<typename _Function>
		struct AsyncLambdaTypeTraits
		{
			typedef decltype(ReturnTypeClassHelperThunk(&(_Function::operator()))) _ReturnType;
		};
	}

	// The M2::AsyncWaitInternal function tries to wait asynchronous call and 
	// return nothing.
	// Throw a COM exception if the function fails.
	template<typename TAsyncResult>
	inline void AsyncWaitInternal(TAsyncResult result)
	{
		// Create an event object for wait the asynchronous call.
		HANDLE hEvent = CreateEventExW(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
		if (nullptr != hEvent)
		{
			// Set event signaled to end wait when completed.
			result->Completed =
				ref new Helpers::RemoveCXReference<decltype(result->Completed)>::Type(
					[hEvent](IAsyncInfo^ asyncInfo, AsyncStatus asyncStatus)
			{
				UNREFERENCED_PARAMETER(asyncInfo);
				UNREFERENCED_PARAMETER(asyncStatus);

				if (asyncStatus != AsyncStatus::Started)
				{
					SetEvent(hEvent);
				}		
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

	// Implemention of IAsyncOperation interface
	template<typename TFunction>
	ref class AsyncOperationImpl sealed : IAsyncOperation<typename Helpers::AsyncLambdaTypeTraits<TFunction>::_ReturnType>
	{
	private:
		IAsyncAction^ m_action = nullptr;
		typename Helpers::AsyncLambdaTypeTraits<TFunction>::_ReturnType m_result = nullptr;

	internal:
		AsyncOperationImpl<TFunction>(const TFunction& function)
		{
			m_action = ThreadPool::RunAsync(ref new WorkItemHandler([this, function](IAsyncAction^ workItem)
			{
				m_result = function();
			}));

			// Call completed handler when completed.
			m_action->Completed =
				ref new Helpers::RemoveCXReference<decltype(m_action->Completed)>::Type(
					[this](IAsyncInfo^ asyncInfo, AsyncStatus asyncStatus)
			{
				UNREFERENCED_PARAMETER(asyncInfo);
				UNREFERENCED_PARAMETER(asyncStatus);

				if (Completed)
				{
					Completed->Invoke(this, Status);
				}
			});
		}

	public:

		virtual void Cancel()
		{
			m_action->Cancel();
		}

		virtual void Close()
		{
			m_action->Close();
		}

		virtual property HResult ErrorCode
		{
			HResult get()
			{
				return m_action->ErrorCode;
			}
		}

		virtual property uint32 Id
		{
			uint32 get()
			{
				return m_action->Id;
			}
		}

		virtual property AsyncStatus Status
		{
			AsyncStatus get()
			{
				return m_action->Status;
			}
		}

		virtual typename Helpers::AsyncLambdaTypeTraits<TFunction>::_ReturnType GetResults()
		{
			return m_result;
		}

		virtual property AsyncOperationCompletedHandler<typename Helpers::AsyncLambdaTypeTraits<TFunction>::_ReturnType>^ Completed;
	};
}

// The m2_await function tries to wait asynchronous call and return result.
// Throw a COM exception if the function fails.
template<typename TResult>
inline TResult m2_await(IAsyncOperation<TResult>^ operation)
{
	M2::AsyncWaitInternal(operation);
	return operation->GetResults();
}

// The m2_await function tries to wait asynchronous call and return result.
// Throw a COM exception if the function fails.
template<typename TResult, typename TProgress>
inline TResult m2_await(IAsyncOperationWithProgress<TResult, TProgress>^ operation)
{
	M2::AsyncWaitInternal(operation);
	return operation->GetResults();
}

// The m2_await function tries to wait asynchronous call and return nothing.
// Throw a COM exception if the function fails.
template<typename TAsyncAction>
inline void m2_await(TAsyncAction action)
{
	M2::AsyncWaitInternal(action);
}

// The m2_create_async_operation function creates a IAsyncOperation Windows 
// Runtime asynchronous construct based on a user supplied lambda or function
// object. Lambdas that return a result of type TResult cause the creation of 
// operations of IAsyncOperation<TResult>.
template<typename TFunction>
IAsyncOperation<typename M2::Helpers::AsyncLambdaTypeTraits<TFunction>::_ReturnType>^ m2_create_async_operation(const TFunction& function)
{
	return ref new M2::AsyncOperationImpl<TFunction>(function);
}



#endif