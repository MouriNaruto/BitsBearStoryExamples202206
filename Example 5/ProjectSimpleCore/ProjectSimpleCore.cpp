#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "winrt/Windows.Foundation.Collections.h"
#include "winrt/Windows.Web.Syndication.h"

namespace winrt
{
    using namespace Windows::Foundation;
    using namespace Windows::Web::Syndication;
}

extern "C" void Test()
{
    winrt::init_apartment();

    winrt::Uri rssFeedUri{ L"https://blogs.windows.com/feed" };
    winrt::SyndicationClient syndicationClient;
    winrt::SyndicationFeed syndicationFeed =
        syndicationClient.RetrieveFeedAsync(rssFeedUri).get();
    ::MessageBoxW(
        nullptr,
        syndicationFeed.Items().First().Current().Title().Text().c_str(),
        L"ProjectSimpleCore.dll",
        0);

    winrt::uninit_apartment();
}

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

