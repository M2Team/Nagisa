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

#include <Windows.h>

// The m2_await function uses the non-blocking way to try to wait asynchronous
// call.
//
// Parameters:
//
// async
//     The asynchronous call you want to wait.
//
// Return value:
//
// The return value is determined by the asynchronous call.
// The function will throw a COM exception if the function fails. 
template<typename TAsync>
inline auto m2_await(TAsync async) -> decltype(async->GetResults())
{
	// Wait the asynchronous call until the status is not Started.
	while (true)
	{
		// Get and save the status of asynchronous call.
		AsyncStatus status = async->Status;

		if (AsyncStatus::Started == status)
		{
			// Calling SleepEx() for sleep 50ms every time because Microsoft 
			// says that all UWP APIs that can't guarantee to complete within 
			// 50ms has been made asynchronous and its name suffixed with 
			// Async.
			::SleepEx(50, FALSE);
		}
		else if (AsyncStatus::Completed == status)
		{
			// Jump out for return value when asynchronous call succeeded
			break;
		}
		else
		{
			int ErrorCode = E_ABORT;

			if (AsyncStatus::Canceled != status)
			{
				// If the status is not Canceled, get the error code.
				ErrorCode = async->ErrorCode.Value;
			}

			// Throw a COM exception when asynchronous call cancelled or 
			// failed.			
			throw COMException::CreateException(ErrorCode);
		}
	}

	// Return the result of asynchronous call.
	return async->GetResults();
}

// The m2_await function uses the non-blocking way to try to wait asynchronous
// call.
//
// Parameters:
//
// async
//     The asynchronous call you want to wait.
// timeout
//     The maximum time interval for waiting the asynchronous call, in 
//     milliseconds.
//
// Return value:
//
// The return value is determined by the asynchronous call.
// The function will throw a COM exception if the function fails. 
template<typename TAsync>
inline auto m2_await(TAsync async, int32 timeout)
-> decltype(async->GetResults())
{
	while (true)
	{
		// Get and save the status of asynchronous call.
		AsyncStatus status = async->Status;

		// Wait the asynchronous call until the status is not Started or the 
		// timeout interval has been elapsed.
		if (AsyncStatus::Started == status && timeout > 0)
		{
			// Calling SleepEx() for sleep 50ms every time because Microsoft 
			// says that all UWP APIs that can't guarantee to complete within 
			// 50ms has been made asynchronous and its name suffixed with 
			// Async.
			::SleepEx(50, FALSE);
			timeout -= 50;
		}
		else if (AsyncStatus::Completed == status)
		{
			// Jump out for return value when asynchronous call succeeded
			break;
		}
		else
		{
			int ErrorCode = E_ABORT;

			if (AsyncStatus::Started == status)
			{
				// If the status is still Started, the timeout interval has 
				// been elapsed.
				async->Cancel();
				ErrorCode = __HRESULT_FROM_WIN32(ERROR_TIMEOUT);
			}
			else if (AsyncStatus::Canceled != status)
			{
				// If the status is not Canceled, get the error code.
				ErrorCode = async->ErrorCode.Value;
			}

			// Throw a COM exception when asynchronous call cancelled, failed 
			// or timeout.			
			throw COMException::CreateException(ErrorCode);

		}
	}

	// Return the result of asynchronous call.
	return async->GetResults();
}

using namespace Windows::System::Threading;

#include <thread>

namespace M2
{
	namespace Helpers
	{
		template<class T>
		struct RemoveReference
		{
			typedef T Type;
		};

		template<class T>
		struct RemoveReference<T&>
		{
			typedef T Type;
		};

		template<class T>
		struct RemoveReference<T&&>
		{
			typedef T Type;
		};

		template<class T>
		struct RemoveReference<T^>
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

	// Implemention of IAsyncOperation interface
	template<typename TFunction>
	ref class AsyncOperationImpl sealed : IAsyncOperation<typename Helpers::AsyncLambdaTypeTraits<TFunction>::_ReturnType>
	{
	private:
		AsyncStatus m_Status;
		HResult m_ErrorCode;
		uint32 m_Id;

		typename Helpers::AsyncLambdaTypeTraits<TFunction>::_ReturnType m_result = nullptr;
		AsyncOperationCompletedHandler<typename Helpers::AsyncLambdaTypeTraits<TFunction>::_ReturnType>^ m_CompletedHandler = nullptr;

	internal:
		AsyncOperationImpl<TFunction>(const TFunction& function)
			: m_Status(AsyncStatus::Started), m_Id(1)
		{
			m_ErrorCode.Value = S_OK;
			
			std::thread([this, function]()
			{
				m_result = function();

				m_Status = AsyncStatus::Completed;

				if (nullptr != m_CompletedHandler)
				{
					m_CompletedHandler->Invoke(this, Status);
				}
			}).detach();
		}

	public:

		virtual void Cancel()
		{

		}

		virtual void Close()
		{
			
		}

		virtual property HResult ErrorCode
		{
			HResult get()
			{
				return m_ErrorCode;
			}
		}

		virtual property uint32 Id
		{
			uint32 get()
			{
				return m_Id;
			}
		}

		virtual property AsyncStatus Status
		{
			AsyncStatus get()
			{
				return m_Status;
			}
		}

		virtual typename Helpers::AsyncLambdaTypeTraits<TFunction>::_ReturnType GetResults()
		{
			return m_result;
		}

		virtual property AsyncOperationCompletedHandler<typename Helpers::AsyncLambdaTypeTraits<TFunction>::_ReturnType>^ Completed
		{
			AsyncOperationCompletedHandler<typename Helpers::AsyncLambdaTypeTraits<TFunction>::_ReturnType>^ get()
			{
				return m_CompletedHandler;
			}

			void set(AsyncOperationCompletedHandler<typename Helpers::AsyncLambdaTypeTraits<TFunction>::_ReturnType>^ value)
			{
				m_CompletedHandler = value;

				if (AsyncStatus::Started != m_Status)
				{
					std::thread([this]()
					{
						if (nullptr != m_CompletedHandler)
						{
							m_CompletedHandler->Invoke(this, Status);
						}
					}).detach();
				}
			}
		}
	};

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