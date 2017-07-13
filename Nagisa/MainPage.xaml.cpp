//
// MainPage.xaml.cpp
// MainPage 类的实现
//

#include "pch.h"
#include "MainPage.xaml.h"

#include "NewTaskDialog.xaml.h"

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

using namespace Platform::Collections;


// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

MainPage::MainPage()
{
	InitializeComponent();
}


void Nagisa::MainPage::ListView_Loaded(Object^ sender, RoutedEventArgs^ e)
{
	using namespace Assassin;
	
	Vector<TransferTask^>^ Tasks = ref new Vector<TransferTask^>();

	Tasks->Append(ref new TransferTask());

	TaskList->ItemsSource = Tasks;

	


}




void Nagisa::MainPage::NewTaskButton_Click(Object^ sender, RoutedEventArgs^ e)
{
	NewTaskDialog^ dialog = ref new NewTaskDialog();
	dialog->ShowAsync();
}
