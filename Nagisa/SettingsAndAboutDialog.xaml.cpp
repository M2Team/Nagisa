//
// SettingsAndAboutDialog.xaml.cpp
// SettingsAndAboutDialog 类的实现
//

#include "pch.h"
#include "SettingsAndAboutDialog.xaml.h"

using namespace Nagisa;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace Assassin;
using namespace Windows::UI::Core;

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“内容对话框”项模板

Nagisa::SettingsAndAboutDialog::SettingsAndAboutDialog()
{
	InitializeComponent();
}

void Nagisa::SettingsAndAboutDialog::OKButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args)
{
	if (m_TransferManager->UserAgent != RestoreDefaultUserAgentTextBox->Text)
	{
		m_TransferManager->UserAgent = RestoreDefaultUserAgentTextBox->Text;
	}
}

void Nagisa::SettingsAndAboutDialog::CancelButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args)
{
}


void Nagisa::SettingsAndAboutDialog::ContentDialog_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	AboutNagisaText->Text = L"M2-Team Nagisa " + m_TransferManager->Version + L"\r\n© M2-Team. All rights reserved.";
	RestoreDefaultUserAgentTextBox->Text = m_TransferManager->UserAgent;
}


void Nagisa::SettingsAndAboutDialog::RestoreDefaultUserAgentButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	m_TransferManager->UserAgent = nullptr;
	RestoreDefaultUserAgentTextBox->Text = m_TransferManager->UserAgent;
}
