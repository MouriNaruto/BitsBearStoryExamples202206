﻿#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern "C" void Test();

#include "resource.h"

#define MAX_LOADSTRING 100

HINSTANCE g_Instance = nullptr;

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            ::DialogBoxParamW(
                g_Instance,
                MAKEINTRESOURCE(IDD_ABOUTBOX),
                hWnd,
                ::About,
                0);
            break;
        case IDM_EXIT:
            ::DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    ::Test();

    WCHAR szTitle[MAX_LOADSTRING];
    WCHAR szWindowClass[MAX_LOADSTRING];

    ::LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    ::LoadStringW(hInstance, IDC_PROJECTSIMPLE, szWindowClass, MAX_LOADSTRING);

    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECTSIMPLE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROJECTSIMPLE);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    ::RegisterClassExW(&wcex);

    g_Instance = hInstance;

    HWND hWnd = CreateWindowExW(
        0,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        0,
        CW_USEDEFAULT,
        0,
        nullptr,
        nullptr,
        hInstance,
        nullptr);
    if (!hWnd)
    {
        return FALSE;
    }

    ::ShowWindow(hWnd, nCmdShow);
    ::UpdateWindow(hWnd);

    HACCEL hAccelTable = ::LoadAcceleratorsW(
        hInstance,
        MAKEINTRESOURCE(IDC_PROJECTSIMPLE));

    MSG msg;
    while (::GetMessageW(&msg, nullptr, 0, 0))
    {
        if (!::TranslateAcceleratorW(msg.hwnd, hAccelTable, &msg))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessageW(&msg);
        }
    }

    return (int) msg.wParam;
}
