#include "util.h"
#include <psapi.h>
#include <tlhelp32.h>

//======================================
// Game related
//======================================

typedef enum AghGameTitle
{
    AGH_GAME_TITLE_UNKNOWN = 0,        /**< unknown */
    AGH_GAME_TITLE_RAINBOW6 = 1,        /**< Rainbow 6 */
    AGH_GAME_TITLE_DOTA2 = 2,        /**< Dota 2 */
    AGH_GAME_TITLE_LOL = 3,        /**< League of Legends */
    AGH_GAME_TITLE_OVERWATCH = 4,        /**< Overwatch */
    AGH_GAME_TITLE_CROSSFIRE = 5,        /**< CrossFire */
    AGH_GAME_TITLE_PUBG = 6,        /**< PlayerUnknown's Battlegrounds */
    AGH_GAME_TITLE_COD = 7,        /**< Call of Duty */
    AGH_GAME_TITLE_WOT = 8,        /**< World of Tanks */
    AGH_GAME_TITLE_FORTNITE = 9,        /**< Fortnite */
    AGH_GAME_TITLE_CSGO = 10,       /**< CSGO */
    AGH_GAME_TITLE_APEX = 11,       /**< APEX */
    AGH_GAME_TITLE_HOK = 12,       /**< HOK */
    AGH_GAME_TITLE_PESOCCER = 13,       /**< ProEvolutionSoccer */
    AGH_GAME_TITLE_GameforPeace = 14,       /**< GameforPeace */
    AGH_GAME_TITLE_Naraka = 15,       /**< Naraka */
    AGH_GAME_TITLE_MAX,                     /**< supported game number */
}AghGameTitle;

std::wstring MakeGameName(AghGameTitle game)
{
    switch (game)
    {
    case AGH_GAME_TITLE_UNKNOWN:
        return L"Unknown";
    case AGH_GAME_TITLE_RAINBOW6:
        return L"Rainbow6";
    case AGH_GAME_TITLE_DOTA2:
        return L"Dota2";
    case AGH_GAME_TITLE_LOL:
        return L"LoL";
    case AGH_GAME_TITLE_OVERWATCH:
        return L"Overwatch";
    case AGH_GAME_TITLE_CROSSFIRE:
        return L"CrossFire";
    case AGH_GAME_TITLE_PUBG:
        return L"PubG";
    case AGH_GAME_TITLE_COD:
        return L"CallOfDuty";
    case AGH_GAME_TITLE_WOT:
        return L"WoT";
    case AGH_GAME_TITLE_FORTNITE:
        return L"Fortnite";
    case AGH_GAME_TITLE_CSGO:
        return L"CSGO";
    case AGH_GAME_TITLE_APEX:
        return L"APEX";
    case AGH_GAME_TITLE_HOK:
        return L"HeroOfKing";
    case AGH_GAME_TITLE_PESOCCER:
        return L"PESOCCER";
    case AGH_GAME_TITLE_GameforPeace:
        return L"GameForPeace";
    case AGH_GAME_TITLE_Naraka:
        return L"Naraka";
    default:
        return L"Invalid";
    }
}

AghGameTitle GetAGHGameIdFromWindowTitle(wchar_t* str, wchar_t* wnd_title)
{
    if (wcsstr(str, (L"Rainbow Six")) != NULL)
    {
        return AGH_GAME_TITLE_RAINBOW6;
    }
    else if (wcsstr(str, (L"Dota 2")) != NULL)
    {
        return AGH_GAME_TITLE_DOTA2;
    }
    else if (wcsstr(str, (L"League of Legends (TM) Client")) != NULL)
    {
        return AGH_GAME_TITLE_LOL;
    }
    else if (wcsstr(str, (L"守望先锋")) != NULL ||
        wcsstr(str, (L"Overwatch")) != NULL)
    {
        return AGH_GAME_TITLE_OVERWATCH;
    }
    else if (wcsstr(str, (L"穿越火线")) != NULL)
    {
        return AGH_GAME_TITLE_CROSSFIRE;
    }
    else if (wcsstr(str, (L"绝地求生")) != NULL ||
        wcsstr(str, (L"PLAYERUNKNOWN'S BATTLEGROUNDS")) != NULL ||
        wcsstr(wnd_title, (L"Movies & TV")) != NULL ||
        wcsstr(wnd_title, (L"电影和电视")) != NULL ||
        wcsstr(wnd_title, (L"PotPlayer")) != NULL)
    {
        return AGH_GAME_TITLE_PUBG;
    }
    else if (wcsstr(str, (L"WoT Client")) != NULL ||
        wcsstr(str, (L"《坦克世界》客户端")) != NULL)
    {
        return AGH_GAME_TITLE_WOT;
    }
    else if (wcsstr(str, (L"Fortnite")) != NULL)
    {
        return AGH_GAME_TITLE_FORTNITE;
    }
    else if (wcsstr(str, (L"Counter-Strike: Global Offensive")) != NULL)
    {
        return AGH_GAME_TITLE_CSGO;
    }
    else if (wcsstr(str, (L"Naraka")) != NULL)
    {
        return AGH_GAME_TITLE_Naraka;
    }
    return AGH_GAME_TITLE_UNKNOWN;
}

uint32_t GetAGHGameFromEXE(std::wstring gameName)
{
    if (gameName.find(L"RainbowSix") != std::string::npos) // RainbowSix_BE.exe
    {
        //return (1 << AGH_GAME_TITLE_RAINBOW6); // hotkey "Alt+H" is disabled by RainbowSix game, so don't show notification.
    }
    if (gameName.find(L"dota2.exe") != std::wstring::npos) // dota2.exe
    {
        return (1 << AGH_GAME_TITLE_DOTA2);
    }
    if (gameName.find(L"LeagueClientUx") != std::string::npos) // LeagueClientUx.exe, LeagueClientUxRender.exe
    {
        return (1 << AGH_GAME_TITLE_LOL);
    }
    if (gameName.find(L"Overwatch.exe") != std::wstring::npos) // Overwatch.exe
    {
        return (1 << AGH_GAME_TITLE_OVERWATCH);
    }
    if (gameName.find(L"crossfire.exe") != std::wstring::npos) // crossfire.exe
    {
        return (1 << AGH_GAME_TITLE_CROSSFIRE);
    }
    if (gameName.find(L"TslGame.exe") != std::wstring::npos) // TslGame.exe
    {
        return (1 << AGH_GAME_TITLE_PUBG);
    }
    if (gameName.find(L"WorldOfTanks.exe") != std::wstring::npos) // WorldOfTanks.exe
    {
        return (1 << AGH_GAME_TITLE_WOT);
    }
    if (gameName.find(L"FortniteClient") != std::wstring::npos) // FortniteClient-Win64-Shipping_BE.exe
    {
        return (1 << AGH_GAME_TITLE_FORTNITE);
    }
    if (gameName.find(L"csgo.exe") != std::wstring::npos) // csgo.exe, csgo.exe(32 bit)
    {
        return (1 << AGH_GAME_TITLE_CSGO);
    }
    if (gameName.find(L"NarakaBladepoint.exe") != std::wstring::npos) // NarakaBladepoint.exe
    {
        return (1 << AGH_GAME_TITLE_Naraka);
    }

    return 0;
}

#define USE_CHECK_GAME_RUNNING 1

//=================================================
#include <tchar.h>
typedef int(__stdcall* MSGBOXAAPI)(IN HWND hWnd,
        IN LPCSTR lpText, IN LPCSTR lpCaption,
        IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);
typedef int(__stdcall* MSGBOXWAPI)(IN HWND hWnd,
        IN LPCWSTR lpText, IN LPCWSTR lpCaption,
        IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);

int MessageBoxTimeoutA(IN HWND hWnd, IN LPCSTR lpText,
    IN LPCSTR lpCaption, IN UINT uType,
    IN WORD wLanguageId, IN DWORD dwMilliseconds);
int MessageBoxTimeoutW(IN HWND hWnd, IN LPCWSTR lpText,
    IN LPCWSTR lpCaption, IN UINT uType,
    IN WORD wLanguageId, IN DWORD dwMilliseconds);

#ifdef UNICODE
#define MessageBoxTimeout MessageBoxTimeoutW
#else
#define MessageBoxTimeout MessageBoxTimeoutA
#endif

#define MB_TIMEDOUT 32000

int MessageBoxTimeoutA(HWND hWnd, LPCSTR lpText,
    LPCSTR lpCaption, UINT uType, WORD wLanguageId,
    DWORD dwMilliseconds)
{
    static MSGBOXAAPI MsgBoxTOA = NULL;

    if (!MsgBoxTOA)
    {
        HMODULE hUser32 = GetModuleHandle(_T("user32.dll"));
        if (hUser32)
        {
            MsgBoxTOA = (MSGBOXAAPI)GetProcAddress(hUser32,
                                      "MessageBoxTimeoutA");
            //fall through to 'if (MsgBoxTOA)...'
        }
        else
        {
            //stuff happened, add code to handle it here
            //(possibly just call MessageBox())
            return 0;
        }
    }

    if (MsgBoxTOA)
    {
        return MsgBoxTOA(hWnd, lpText, lpCaption,
              uType, wLanguageId, dwMilliseconds);
    }

    return 0;
}

int MessageBoxTimeoutW(HWND hWnd, LPCWSTR lpText,
    LPCWSTR lpCaption, UINT uType, WORD wLanguageId, DWORD dwMilliseconds)
{
    static MSGBOXWAPI MsgBoxTOW = NULL;

    if (!MsgBoxTOW)
    {
        HMODULE hUser32 = GetModuleHandle(_T("user32.dll"));
        if (hUser32)
        {
            MsgBoxTOW = (MSGBOXWAPI)GetProcAddress(hUser32,
                                      "MessageBoxTimeoutW");
            //fall through to 'if (MsgBoxTOW)...'
        }
        else
        {
            //stuff happened, add code to handle it here 
            //(possibly just call MessageBox())
            return 0;
        }
    }

    if (MsgBoxTOW)
    {
        return MsgBoxTOW(hWnd, lpText, lpCaption,
               uType, wLanguageId, dwMilliseconds);
    }

    return 0;
}
//=================================================

bool isHighlightOn = false;
std::wstring aghFileName = L"";
AghGameTitle gameTitle = AGH_GAME_TITLE_UNKNOWN;
HANDLE timerThread = NULL;
bool timerStop = false;
uint32_t prevGame = 0;

int StartHighlight()
{
    HWND foreground = GetForegroundWindow(); // get handle of currently active window
    if (foreground)
    {
        wchar_t wnd_title[512] = L"";
        GetWindowTextW(foreground, wnd_title, sizeof(wnd_title) / sizeof(wnd_title[0]));
        //std::wcout << wnd_title << std::endl;

        // Trim leading space
        wchar_t* str = wnd_title;
        while (isspace((wchar_t)*str)) str++;
        // All spaces?
        if (*str != 0)
        {
            // Trim trailing space
            wchar_t* end;
            end = str + wcslen(str) - 1;
            while (end > str && isspace((wchar_t)*end)) end--;
            // Write new null terminator character
            end[1] = '\0';
        }

        gameTitle = GetAGHGameIdFromWindowTitle(str, wnd_title);
        if (gameTitle != AGH_GAME_TITLE_UNKNOWN)
        {
            MessageBoxTimeout(NULL, (LPCWSTR)L"Game highlight begins.", (LPCWSTR)L"", MB_OK | MB_TOPMOST, 0, 3000);

#if ! USE_CHECK_GAME_RUNNING
            TimerInput ti{};
            timerThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CheckGameExit, &ti, 0, NULL);
#endif
            return 0;
        }
        else
        {
            MessageBoxTimeout(NULL, (LPCWSTR)L"Game is not running,\nor highlight is not supported for this game.", (LPCWSTR)L"", MB_OK | MB_TOPMOST, 0, 3000);
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

int StopHighlight()
{
    std::wstring msg = L"Game highlight stops.";
    MessageBoxTimeout(NULL, msg.c_str(), (LPCWSTR)L"", MB_OK | MB_TOPMOST, 0, 3000);

#if ! USE_CHECK_GAME_RUNNING
    if (timerThread != NULL)
    {
        timerStop = true;
        WaitForSingleObject(timerThread, INFINITE);
        CloseHandle(timerThread);
        timerThread = NULL;
    }
#endif

    return 0;
}

bool GameHighlightHotKey()
{
    if (isHighlightOn)
    {
        StopHighlight();
        isHighlightOn = false;
    }
    else
    {
        if (StartHighlight() == 0)
        {
            isHighlightOn = true;
        }
    }
    return isHighlightOn;
}

uint32_t CheckGameProcess()
{
    uint32_t ret = 0;
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        OutputDebugString(L"CreateToolhelp32Snapshot fail.");
        return ret;
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32))
    {
        OutputDebugString(L"Process32First fail.");
        CloseHandle(hProcessSnap);
        return(FALSE);
    }

    //char out[256];
    //sprintf_s(out, "~~~~~~~~~~ %d ~~~~~~~~~~", pe32.dwSize);
    //OutputDebugStringA(out);

    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do
    {
        std::wstring str = pe32.szExeFile;

        //char out[256];
        //sprintf_s(out, "[%d]", pe32.th32ProcessID);
        //OutputDebugStringA(out);
        //OutputDebugString(str.c_str());

        ret |= GetAGHGameFromEXE(str);

    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);

    return ret;
}

void CheckGameExit(LPVOID lparam)
{
    TimerInput* in = (TimerInput*)lparam;

    timerStop = false;
    while (!timerStop)
    {
        Sleep(1000);

        if (isHighlightOn && ((CheckGameProcess() & (1 << gameTitle)) == 0))
        {
            std::wstring msg = L"Game highlight stops.";
            MessageBoxTimeout(NULL, msg.c_str(), (LPCWSTR)L"", MB_OK | MB_TOPMOST, 0, 3000);

            isHighlightOn = false;
            break;
        }
    }

    return;
}

#if USE_CHECK_GAME_RUNNING
void CheckGameRunning(LPVOID lparam)
{
    TimerInput* in = (TimerInput*)lparam;

    timerStop = false;
    while (!timerStop)
    {
        Sleep(1000);

        uint32_t currGame = CheckGameProcess();

        if (isHighlightOn)
        {
            // auto stop highlight
            if ((currGame & (1 << gameTitle)) == 0)
            {
                std::wstring msg = L"Game highlight stops.";
                MessageBoxTimeout(NULL, msg.c_str(), (LPCWSTR)L"", MB_OK | MB_TOPMOST, 0, 3000);

                isHighlightOn = false;
            }
        }
        else
        {
            // notify highlight support
            if ((currGame & (~prevGame)) != 0)
            {
                std::wstring msg = L"This game supports auto highlight.\nPress Alt+H to start capturing highlight video.";
                MessageBoxTimeout(NULL, msg.c_str(), (LPCWSTR)L"", MB_OK | MB_TOPMOST, 0, 5000);
            }
        }

        prevGame = currGame;
    }

    return;
}
#endif
