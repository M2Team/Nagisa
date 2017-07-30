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
using namespace concurrency;
using namespace Platform::Collections;
using namespace Windows::System::Threading;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;


// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

MainPage::MainPage()
{
	InitializeComponent();

	std::thread([this]()
	{
		m_TransferManager = ref new TransferManager();

		IVectorView<TransferTask^>^ tasks = m2_await(m_TransferManager->GetTasksAsync());

		this->Dispatcher->RunAsync(
			CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, tasks]()
		{
			TaskList->ItemsSource = tasks;
		}));
	}).detach();
}

void Nagisa::MainPage::ListView_Loaded(Object^ sender, RoutedEventArgs^ e)
{
	
}

void Nagisa::MainPage::NewTaskButton_Click(Object^ sender, RoutedEventArgs^ e)
{
	NewTaskDialog^ dialog = ref new NewTaskDialog();
	dialog->ShowAsync();
}

void Nagisa::MainPage::SettingsAndAboutButton_Click(Object^ sender, RoutedEventArgs^ e)
{
	SettingsAndAboutDialog^ dialog = ref new SettingsAndAboutDialog();
	dialog->ShowAsync();
}

void Nagisa::MainPage::AutoSuggestBox_Search(AutoSuggestBox^ sender, DependencyObject^ args)
{
	String^ SearchFilter = sender->Text;
	
	std::thread([this, SearchFilter]()
	{
		auto result = m2_await(m_TransferManager->GetTasksAsync(SearchFilter));

		this->Dispatcher->RunAsync(
			CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, result]()
		{
			TaskList->ItemsSource = result;
		}));
	}).detach();
}



void Nagisa::MainPage::MenuFlyoutItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	TransferTask^ Task = dynamic_cast<TransferTask^>(dynamic_cast<FrameworkElement^>(sender)->DataContext);

	auto a = TaskList->SelectedItems;

	MessageDialog^ messageDialog = ref new MessageDialog(Task->Description, L"dialogTitle");
	messageDialog->ShowAsync();
}
