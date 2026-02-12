#pragma once

#include "MainWindow.g.h"

namespace winrt::winui3_doctest_poc::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::winui3_doctest_poc::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
