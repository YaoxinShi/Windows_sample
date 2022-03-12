// Hotkey.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <stdio.h>

#define B_KEY (UINT)'B'
#define Q_KEY (UINT)'Q'
int x = 0;

typedef USHORT sc_type; // Scan code.
typedef UCHAR vk_type;  // Virtual key.

HINSTANCE g_hInstance = NULL;
DWORD g_MainThreadID = NULL;
DWORD g_HookThreadID = NULL;
HHOOK g_KeybdHook = NULL;
static bool sHookSyncd = false;
static HANDLE sThreadHandle = NULL;
static bool sQKeyPressed = false;

bool alt_key_down = false;
int b_key_state = 0;
int q_key_state = 0;
#define SC_LALT 0x038
#define SC_RALT 0x138

enum UserMessages {
	AHK_HOOK = WM_USER,
	AHK_UNHOOK,
	AHK_SYNC,
};

LRESULT CALLBACK LowLevelKeybdProc(int aCode, WPARAM wParam, LPARAM lParam)
{
	if (aCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT& event = *(PKBDLLHOOKSTRUCT)lParam;  // For convenience, maintainability, and possibly performance.
		vk_type vk = (vk_type)event.vkCode;
		sc_type sc = (sc_type)event.scanCode;
		//wprintf(L"~~~~~~~~~~~~, %d, %d, %d\n", wParam, vk, sc);

		bool key_up = (wParam == WM_KEYUP || wParam == WM_SYSKEYUP);
		bool key_down = (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN);
		bool alt_key = (sc == SC_LALT || sc == SC_RALT);
		if (key_down && alt_key)
		{
			alt_key_down = true;
		}
		if (key_up && alt_key)
		{
			alt_key_down = false;
		}

		bool b_key = (vk == B_KEY);
		if (key_down && b_key)
		{
			if (b_key_state == 0)
			{
				b_key_state = 1;
			}
			else if (b_key_state == 1)
			{
				b_key_state = 2;
			}
		}
		if (key_up && b_key)
		{
			b_key_state = 0;
		}
		if (alt_key_down && (b_key_state == 1))
		{
			x++;
			wprintf(L"alt+b received, %d\n", x);
			Beep(523, 150);
		}

		bool q_key = (vk == Q_KEY);
		if (key_down && q_key)
		{
			if (q_key_state == 0)
			{
				q_key_state = 1;
			}
			else if (q_key_state == 1)
			{
				q_key_state = 2;
			}
		}
		if (key_up && q_key)
		{
			q_key_state = 0;
		}
		if (alt_key_down && (q_key_state == 1))
		{
			sQKeyPressed = true;
		}
	}

	return CallNextHookEx(0, aCode, wParam, lParam);;
}

DWORD WINAPI HookThreadProc(LPVOID aUnused)
{
	MSG msg;
	bool problem_activating_hooks;

	for (;;)
	{
		if (GetMessage(&msg, NULL, 0, 0) == -1) // -1 is an error, 0 means WM_QUIT.
			continue;

		switch (msg.message)
		{
		case AHK_HOOK:
			problem_activating_hooks = false;
			if (!g_KeybdHook)
			{
				if (!(g_KeybdHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeybdProc, g_hInstance, 0)))
					problem_activating_hooks = true;
			}
			//PostThreadMessage(g_MainThreadID, AHK_HOOK, problem_activating_hooks, 0);
			break;

		case AHK_UNHOOK:
			if (g_KeybdHook)
				if (UnhookWindowsHookEx(g_KeybdHook))
					g_KeybdHook = NULL;
			break;

		case AHK_SYNC:
			sHookSyncd = true;
			break;
		}
	}
}

void method1()
{
	if (RegisterHotKey(NULL, 1, MOD_ALT | MOD_NOREPEAT, B_KEY))
	{
		wprintf(L"Hotkey 'alt+b' registered, using MOD_NOREPEAT flag\n");
	}
	if (RegisterHotKey(NULL, 2, MOD_ALT | MOD_NOREPEAT, Q_KEY))
	{
		wprintf(L"Hotkey 'alt+q' registered, using MOD_NOREPEAT flag\n");
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_HOTKEY)
		{
			if (msg.wParam == 1)
			{
				x++;
				wprintf(L"alt+b received, %d\n", x);
				Beep(523, 150);
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

void method2()
{
	g_hInstance = (HINSTANCE)GetModuleHandle(NULL);
	g_MainThreadID = GetCurrentThreadId();

	if (sThreadHandle = CreateThread(NULL, 8 * 1024, HookThreadProc, NULL, 0, &g_HookThreadID))
		SetThreadPriority(sThreadHandle, THREAD_PRIORITY_TIME_CRITICAL);

	for (int i = 0; i < 50 && !PostThreadMessage(g_HookThreadID, AHK_HOOK, 0, 0); ++i)
		Sleep(10);

	wprintf(L"Hotkey 'alt+b' hooked, no repeat\n");
	wprintf(L"Hotkey 'alt+q' hooked, no repeat\n");

	while (!sQKeyPressed)
	{
		Sleep(100);
	}

	for (int i = 0; i < 50 && !PostThreadMessage(g_HookThreadID, AHK_UNHOOK, 0, 0); ++i)
		Sleep(10);
}

int main()
{
	//method1();
	method2();
    return 0;
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
