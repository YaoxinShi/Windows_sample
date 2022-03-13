// CheckFullScreen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <tchar.h>

int GetWindowTextSafe(HWND hWnd, LPTSTR lpString, int nMaxCount)
{
    if (NULL == hWnd || FALSE == IsWindow(hWnd) || NULL == lpString || 0 == nMaxCount)
    {
        return GetWindowText(hWnd, lpString, nMaxCount);
    }
    DWORD dwHwndProcessID = 0;
    DWORD dwHwndThreadID = 0;
    dwHwndThreadID = GetWindowThreadProcessId(hWnd, &dwHwndProcessID); // Get window's process ID and thread ID

    // (window's process ID != current process ID)
    if (dwHwndProcessID != GetCurrentProcessId())
    {
        return GetWindowText(hWnd, lpString, nMaxCount);
    }

    // (window's process ID == current process ID) && (window's thread ID == current thread ID)
    if (dwHwndThreadID == GetCurrentThreadId())
    {
        return GetWindowText(hWnd, lpString, nMaxCount);
    }

    // (window's process ID == current process ID) && (window's thread ID != current thread ID)
    // Need use InternalGetWindowText(), GetWindowText() may be blocked. e.g. main_video_agh
#ifndef _UNICODE
    WCHAR* lpStringUnicode = new WCHAR[nMaxCount];
    InternalGetWindowText(hWnd, lpStringUnicode, nMaxCount);
    int size = WideCharToMultiByte(CP_ACP, 0, lpStringUnicode, -1, NULL, 0, NULL, NULL);
    if (size <= nMaxCount)
    {
        size = WideCharToMultiByte(CP_ACP, 0, lpStringUnicode, -1, lpString, size, NULL, NULL);
        if (NULL != lpStringUnicode)
        {
            delete[]lpStringUnicode;
            lpStringUnicode = NULL;
        }
        return size;
    }
    if (NULL != lpStringUnicode)
    {
        delete[]lpStringUnicode;
        lpStringUnicode = NULL;
    }
    return 0;

#else
    return InternalGetWindowText(hWnd, lpString, nMaxCount);
#endif
}

#define TYPE_ERROR -1
#define TYPE_FULL_SCREEN 0
#define TYPE_NORMAL_WINDOW 1
#define TYPE_BORDERLESS_WINDOW 2
int GetWindowType()
{
    //HWND hwnd = GetDesktopWindow();
    //HWND hwnd = ::FindWindow(NULL, L"Dota 2");
    HWND hwnd = GetForegroundWindow();

    if (hwnd == NULL)
    {
        return TYPE_ERROR;
    }

#if 1
    TCHAR wnd_title[512] = _T("");
    GetWindowTextSafe(hwnd, wnd_title, sizeof(wnd_title));
#ifndef _UNICODE
    std::cout << wnd_title << std::endl;
#else
    std::wcout << wnd_title << std::endl;
#endif
#endif

    WINDOWINFO winInfo = { 0 };
    GetWindowInfo(hwnd, &winInfo);
#if 0
    std::cout << "rcWindow: " << winInfo.rcWindow.left
        << " " << winInfo.rcWindow.top
        << " " << winInfo.rcWindow.right
        << " " << winInfo.rcWindow.bottom << std::endl
        << "rcWindow: " << winInfo.rcClient.left
        << " " << winInfo.rcClient.top
        << " " << winInfo.rcClient.right
        << " " << winInfo.rcClient.bottom << std::endl
        << "dwStyle: " << std::hex << winInfo.dwStyle << std::endl
        << "dwExStyle: " << winInfo.dwExStyle << std::endl
        << "dwWindowStatus: " << winInfo.dwWindowStatus << std::endl
        << "cxWindowBorders: " << std::dec << winInfo.cxWindowBorders << std::endl
        << "cyWindowBorders: " << winInfo.cyWindowBorders << std::endl;
#endif

    if (winInfo.dwStyle & WS_POPUP)
    {
        return TYPE_BORDERLESS_WINDOW;
    }
    else
    {
        if (winInfo.dwStyle & WS_BORDER)
        {
            return TYPE_NORMAL_WINDOW;
        }
        else
        {
            return TYPE_FULL_SCREEN;
        }
    }
}

int main()
{
    while (1)
    {
        switch (GetWindowType())
        {
        case TYPE_FULL_SCREEN:
            std::cout << "================ Full screen\n";
            break;
        case TYPE_NORMAL_WINDOW:
            std::cout << "================ Normal window\n";
            break;
        case TYPE_BORDERLESS_WINDOW:
            std::cout << "================ Borderless window\n";
            break;
        default:
            std::cout << "================ Error\n";
            break;
        }
        Sleep(1000);
    }

    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
