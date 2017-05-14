//
// MainPage.xaml.cpp
// MainPage 类的实现。
//

#include "pch.h"
#include "MainPage.xaml.h"

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

using namespace concurrency;
using namespace Platform::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

MainPage::MainPage()
{
	InitializeComponent();
}


void Nagisa::MainPage::Nagisa_Test_SaveAsButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FolderPicker^ picker = ref new FolderPicker();
	picker->FileTypeFilter->Append(L"*");
	picker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;

	create_task(picker->PickSingleFolderAsync()).then([this](StorageFolder^ folder)
	{
		if (folder)
		{
			OutputConsole->Text= "Picked folder: " + folder->Path;
		}
		else
		{
			OutputConsole->Text = "Operation cancelled.";
		}
	});

}
