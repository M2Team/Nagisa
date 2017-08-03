/******************************************************************************
Project: Assassin
Description: Definition and implemention for Background Worker
File Name: BackgroundWorker.h
License: The MIT License
******************************************************************************/

#pragma once

#include "pch.h"

using namespace Platform;
using namespace Windows::ApplicationModel::Background;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage::Streams;

namespace Assassin
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class BackgroundWorker sealed : public IBackgroundTask
	{
	public:
		BackgroundWorker()
		{

		}

		virtual void Run(IBackgroundTaskInstance^ taskInstance)
		{
			auto deferral = taskInstance->GetDeferral();

			try
			{
				auto details = dynamic_cast<SocketActivityTriggerDetails^>(taskInstance->TriggerDetails);
				auto socketInformation = details->SocketInformation;
				switch (details->Reason)
				{
				case SocketActivityTriggerReason::SocketActivity:
				{
					auto socket = socketInformation->StreamSocket;
					DataReader^ reader = ref new DataReader(socket->InputStream);
					reader->InputStreamOptions = InputStreamOptions::Partial;
					m2_await(reader->LoadAsync(250));
					auto dataString = reader->ReadString(reader->UnconsumedBufferLength);
					//ShowToast(dataString);
					socket->TransferOwnership(socketInformation->Id);
					break;
				}
				case SocketActivityTriggerReason::KeepAliveTimerExpired:
				{
					auto socket = socketInformation->StreamSocket;
					DataWriter^ writer = ref new DataWriter(socket->OutputStream);
					writer->UnicodeEncoding = UnicodeEncoding::Utf8;
					writer->WriteString("Keep alive");
					m2_await(writer->StoreAsync());
					writer->DetachStream();
					delete writer;
					socket->TransferOwnership(socketInformation->Id);
					break;
				}
				case SocketActivityTriggerReason::SocketClosed:
				{
					auto socket = ref new StreamSocket();
					socket->EnableTransferOwnership(taskInstance->Task->TaskId, SocketActivityConnectedStandbyAction::Wake);
					/*if (ApplicationData.Current.LocalSettings.Values["hostname"] == null)
					{
					break;
					}
					var hostname = (String)ApplicationData.Current.LocalSettings.Values["hostname"];
					var port = (String)ApplicationData.Current.LocalSettings.Values["port"];
					await socket.ConnectAsync(new HostName(hostname), port);
					socket.TransferOwnership(socketId);*/
					break;
				}
				default:
					break;
				}

				deferral->Complete();
			}
			catch (Exception^ exception)
			{
				// ShowToast(exception->Message);
				deferral->Complete();
			}

			throw ref new NotImplementedException();
		}

		/*
		Assassin.BackgroundWorker
		Assassin.TransferManager
		*/

	};
}
