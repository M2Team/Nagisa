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

// The m2_await function tries to wait asynchronous call and return result or 
// nothing. The function will throw a COM exception if the function fails.
template<typename TAsync>
inline auto m2_await(TAsync async) -> decltype(async->GetResults())
{
	// Save the status of asynchronous call.
	AsyncStatus asyncStatus = AsyncStatus::Started;

	// Wait the asynchronous call until asyncStatus is not Started via calling 
	// SleepEx() for sleep 50ms every time because Microsoft says that all UWP 
	// APIs that can't guarantee to complete within 50ms has been made 
	// asynchronous and its name suffixed with Async. 
	while (AsyncStatus::Started == asyncStatus)
	{
		::SleepEx(50, FALSE);

		asyncStatus = async->Status;
	}

	// Throw a COM exception if asynchronous call failed.
	if (AsyncStatus::Error == asyncStatus)
	{
		throw COMException::CreateException(async->ErrorCode.Value);
	}

	// Return the result of asynchronous call.
	return async->GetResults();
}

#endif