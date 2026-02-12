#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#define DOCTEST_CONFIG_IMPLEMENT
#include "third_party/doctest.h"

#include <string>
#include <stdexcept>
#include <windows.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

inline std::wstring utf8_to_wstring(const std::string& utf8)
{
    if (utf8.empty()) return std::wstring();

    // First, get wcharSize size (in wchar_t units), excluding null-terminator
    int wcharSize = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8.data(), static_cast<int>(utf8.size()), nullptr, 0);

    if (wcharSize == 0)
    {
        throw std::runtime_error("MultiByteToWideChar(size) failed");
    }

    std::wstring wide(wcharSize, L'\0');

    // Now convert
    int written = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8.data(), static_cast<int>(utf8.size()), wide.data(), wcharSize);
    if (written == 0) 
    {
        throw std::runtime_error("MultiByteToWideChar(convert) failed");
    }
    return wide;
}

namespace winrt::winui3_doctest_poc::implementation
{
    void MainWindow::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        std::stringstream ss;
        std::ostream& os_ref = static_cast<std::ostream&>(ss);
        doctest::Context context;
        context.setCout(&ss);

        if (OutputTypeToggle().IsOn())
        {
            context.setOption("reporters", "xml");
        }

        int res = context.run(); // run
        auto s = ss.str();
        auto ws = utf8_to_wstring(s);
        ResultOutput().Text(ws.c_str());
    }
}
