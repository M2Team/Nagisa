//
// MainPage.xaml.cpp
// MainPage 类的实现
//

#include "pch.h"
#include "MainPage.xaml.h"

#include "NewTaskDialog.xaml.h"
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
using namespace Platform::Collections;


// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

MainPage::MainPage()
{
	InitializeComponent();
}


void Nagisa::MainPage::ListView_Loaded(Object^ sender, RoutedEventArgs^ e)
{	
	Tasks = ref new Vector<TransferTask^>();

	Tasks->Append(ref new TransferTask(L"Task #1", 10, TransferStatus::Running));
	Tasks->Append(ref new TransferTask(L"Task #2", 30, TransferStatus::Error));
	Tasks->Append(ref new TransferTask(L"Task #3", 60, TransferStatus::Paused));
	Tasks->Append(ref new TransferTask(L"Task #4", 100, TransferStatus::Completed));

	TaskList->ItemsSource = Tasks->GetView();
}




void Nagisa::MainPage::NewTaskButton_Click(Object^ sender, RoutedEventArgs^ e)
{
	NewTaskDialog^ dialog = ref new NewTaskDialog();
	dialog->ShowAsync();
}

void Nagisa::MainPage::SettingsAndAboutButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	SettingsAndAboutDialog^ dialog = ref new SettingsAndAboutDialog();
	dialog->ShowAsync();
}

void Nagisa::MainPage::AutoSuggestBox_QuerySubmitted(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs^ args)
{
	if (sender->Text == nullptr || sender->Text->IsEmpty())
	{
		TaskList->ItemsSource = Tasks->GetView();
	}
	else
	{
		Vector<TransferTask^>^ result = ref new Vector<TransferTask^>();
		
		for (auto Task : Tasks)
		{	
			
			
			
			if (m2_base_winrt_find_sub_string(Task->Description, sender->Text, true))
			{
				result->Append(Task);
			}
		}

		TaskList->ItemsSource = result->GetView();
	}
}

void Nagisa::MainPage::AutoSuggestBox_TextChanged(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs^ args)
{
	if (sender->Text == nullptr || sender->Text->IsEmpty())
	{
		TaskList->ItemsSource = Tasks->GetView();
	}
	else
	{
		Vector<TransferTask^>^ result = ref new Vector<TransferTask^>();

		for (auto Task : Tasks)
		{
			if (m2_base_winrt_find_sub_string(Task->Description, sender->Text, true))
			{
				result->Append(Task);		
			}
		}

		TaskList->ItemsSource = result->GetView();
	}
}
