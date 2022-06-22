// GameCheck.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "util.h"

#define H_KEY (UINT)'H'
#define Q_KEY (UINT)'Q'

int main()
{
    std::cout << "Create checking thread!\n";
    TimerInput ti{};
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CheckGameRunning, &ti, 0, NULL);

	if (RegisterHotKey(NULL, 1, MOD_ALT | MOD_NOREPEAT, H_KEY))
	{
		wprintf(L"Hotkey 'alt+h' registered, start/stop AGH\n");
	}
	if (RegisterHotKey(NULL, 2, MOD_ALT | MOD_NOREPEAT, Q_KEY))
	{
		wprintf(L"Hotkey 'alt+q' registered, exit app\n");
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_HOTKEY)
		{
			if (msg.wParam == 1)
			{
				GameHighlightHotKey();
			}
			else if (msg.wParam == 2)
			{
				UnregisterHotKey(NULL, 1);
				UnregisterHotKey(NULL, 2);
				break;
			}
		}
	}
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
