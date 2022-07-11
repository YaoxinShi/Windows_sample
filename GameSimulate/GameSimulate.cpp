// GameSimulate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <string>
#include "EasyBMP\EasyBMP.h"

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
    AGH_GAME_TITLE_Rocket = 16,       /**< Rocket */
    AGH_GAME_TITLE_VALORANT = 17,       /**< Valorant */
    AGH_GAME_TITLE_MAX,                     /**< supported game number */
}AghGameTitle;

typedef enum AghGameLanguage
{
    AGH_GAME_LANGUAGE_UNKNOWN = 0,      /**< Unkown */
    AGH_GAME_LANGUAGE_EN = 1,           /**< English */
    AGH_GAME_LANGUAGE_CN = 2,           /**< Chinese */
}AghGameLanguage;

void DrwImage(std::string imagePath, HDC* console) {

    BMP image;
    image.ReadFromFile(imagePath.c_str());
    //image.SetBitDepth(32);
    for (int x = 0; x < image.TellWidth(); x++)
    {
        for (int y = 0; y < image.TellHeight(); y++)
        {
            int RED = image.GetPixel(x, y).Red;
            int GREEN = image.GetPixel(x, y).Green;
            int BLUE = image.GetPixel(x, y).Blue;

            int ALPHA = image.GetPixel(x, y).Alpha;

            COLORREF COLOUR = RGB(RED, GREEN, BLUE);
            if (ALPHA == 0) {
                SetPixel(*console, x, y, COLOUR);
            }
        }
    }
}

void setup(std::wstring window_name, std::wstring process_name)
{
    // set window title
    HWND foreground = GetForegroundWindow();
    SetWindowText(foreground, window_name.c_str());

    // todo: create a process with process_name
    std::cout << "THIS ONLY CHANGE WINDOW NAME. TO CHANGE PROCESS NAME, RENAME GameSimulate.exe TO [TARGET] ONE.\n";
}

void show(std::string bmp_name, int& bmp_index)
{
    // Get HWND and HDC
    HWND console = GetDesktopWindow();
    HDC dc = GetDC(console);

    // Call DrwImage. It must be a bitmap image
    std::string file_name = bmp_name + "_" + std::to_string(bmp_index) + ".bmp";
    FILE* file = NULL;
    fopen_s(&file, file_name.c_str(), "rb");
    if (file == NULL) {
        bmp_index = 0;
        file_name = bmp_name + "_" + std::to_string(bmp_index) + ".bmp";
    }
    else
    {
        fclose(file);
        file = NULL;
    }

    DrwImage(file_name.c_str(), &dc);

    bmp_index++;

    // Release
    ReleaseDC(console, dc);
}

void hide()
{
    // do nothing
}

bool m_running = false;

void bmpWorker(LPVOID lparam) {
    char* ige = (char*)lparam;

    std::string bmp_name = ige;
    int bmp_index = 0;
    unsigned int clock = 0;

    while (m_running)
    {
        if (clock % 200 == 0) // 10ms * 200 = 2s
        {
            show(bmp_name, bmp_index);
        }
        std::cout << clock << "\r"; // in order to make screen content always change
        clock++;
        Sleep(10); // 10ms
    }
}

int main()
{
    int game = AGH_GAME_TITLE_UNKNOWN;
    int lang = AGH_GAME_LANGUAGE_UNKNOWN;
    char showbmp = '0';
    std::wstring window_name;
    std::wstring process_name;
    std::string bmp_name;

    while (1)
    {
        std::cout << "---------------------------------------------------------------------------------------------------\n";
L_GAME_LANG:
        std::cout << "   1, English\n";
        std::cout << "   2, Chinese\n";
        std::cout << "Game Language:\n";
        std::cin >> lang;

        switch (lang)
        {
        case AGH_GAME_LANGUAGE_EN:
            break;
        case AGH_GAME_LANGUAGE_CN:
            break;
        default:
            std::cout << ">>>>>> invalid game language\n";
            std::cin.clear();
            std::cin.ignore();
            goto L_GAME_LANG;
        }

L_GAME_TITLE:
        std::cout << "   1, Rainbow 6 [RainbowSix_BE.exe]\n";
        std::cout << "   2, Dota 2 [dota2.exe]\n";
        std::cout << "   3, League of Legends [LeagueClientUx.exe]\n";
        std::cout << "   4, Overwatch [Overwatch.exe]\n";
        std::cout << "   5, CrossFire [crossfire.exe]\n";
        std::cout << "   6, PlayerUnknown's Battlegrounds [TslGame.exe]\n";
        std::cout << "   7, Call of Duty\n";
        std::cout << "   8, World of Tanks [WorldOfTanks.exe]\n";
        std::cout << "   9, Fortnite [FortniteClient-Win64-Shipping_BE.exe]\n";
        std::cout << "  10, CSGO [csgo.exe]\n";
        std::cout << "  11, APEX\n";
        std::cout << "  12, HOK\n";
        std::cout << "  13, ProEvolutionSoccer\n";
        std::cout << "  14, GameforPeace\n";
        std::cout << "  15, Naraka [NarakaBladepoint.exe]\n";
        std::cout << "  16, Rocket\n";
        std::cout << "  17, Valorant\n";
        std::cout << "Game ID:\n";
        std::cin >> game;

        switch (game)
        {
        case AGH_GAME_TITLE_RAINBOW6:
            window_name = L"Rainbow Six";
            bmp_name = "rainbow";
            break;
        case AGH_GAME_TITLE_DOTA2:
            window_name = L"Dota 2";
            bmp_name = "dota";
            break;
        case AGH_GAME_TITLE_LOL:
            window_name = L"League of Legends (TM) Client";
            bmp_name = "lol";
            break;
        case AGH_GAME_TITLE_OVERWATCH:
            if (lang == AGH_GAME_LANGUAGE_CN)
            {
                window_name = L"守望先锋";
            }
            else
            {
                window_name = L"Overwatch";
            }
            bmp_name = "overwatch";
            break;
        case AGH_GAME_TITLE_CROSSFIRE:
            window_name = L"穿越火线";
            bmp_name = "crossfire";
            break;
        case AGH_GAME_TITLE_PUBG:
            if (lang == AGH_GAME_LANGUAGE_CN)
            {
                window_name = L"绝地求生";
            }
            else
            {
                window_name = L"PLAYERUNKNOWN'S BATTLEGROUNDS";
            }
            bmp_name = "pubg";
            break;
        case AGH_GAME_TITLE_COD:
            window_name = L"Call of Duty";
            bmp_name = "cod";
            break;
        case AGH_GAME_TITLE_WOT:
            if (lang == AGH_GAME_LANGUAGE_CN)
            {
                window_name = L"《坦克世界》客户端";
            }
            else
            {
                window_name = L"WoT Client";
            }
            bmp_name = "wot";
            break;
        case AGH_GAME_TITLE_FORTNITE:
            window_name = L"Fortnite";
            bmp_name = "fortnite";
            break;
        case AGH_GAME_TITLE_CSGO:
            window_name = L"Counter-Strike: Global Offensive";
            bmp_name = "csgo";
            break;
        case AGH_GAME_TITLE_APEX:
            window_name = L"Apex Legends";
            bmp_name = "apex";
            break;
        case AGH_GAME_TITLE_HOK:
            window_name = L"HOK";
            bmp_name = "hok";
            break;
        case AGH_GAME_TITLE_PESOCCER:
            window_name = L"eFootball PES 2021 SEASON UPDATE";
            bmp_name = "pes";
            break;
        case AGH_GAME_TITLE_GameforPeace:
            window_name = L"GOP";
            bmp_name = "gop";
            break;
        case AGH_GAME_TITLE_Naraka:
            window_name = L"Naraka";
            bmp_name = "naraka";
            break;
        case AGH_GAME_TITLE_Rocket:
            window_name = L"Rocket League";
            bmp_name = "rocket";
            break;
        case AGH_GAME_TITLE_VALORANT:
            window_name = L"VALORANT";
            bmp_name = "valorant";
            break;
        default:
            std::cout << ">>>>>> invalid game ID\n";
            std::cin.clear();
            std::cin.ignore();
            goto L_GAME_TITLE;
        }

        setup(window_name, process_name);

        int bmp_index = 0;
        HANDLE m_bmpThread = NULL;

L_ACTION:
        std::cout << "   n, Not show game BMP\n";
        std::cout << "   p, Show game BMPs one by one\n";
        std::cout << "   v, Show game BMPs automatically (0.5fps)\n";
        std::cout << "   r, Run next game\n";
        std::cout << "   e, Exit app\n";
        std::cout << "Action:\n";
        std::cin >> showbmp;

        switch (showbmp)
        {
        case 'n':
            hide();
            goto L_ACTION;
        case 'p':
            show(bmp_name, bmp_index);
            goto L_ACTION;
        case 'v':
            if (m_bmpThread == NULL)
            {
                m_running = true;
                m_bmpThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bmpWorker, (LPVOID)bmp_name.c_str(), 0, NULL);
            }
            else
            {
                m_running = false;
                WaitForSingleObject(m_bmpThread, INFINITE);
                CloseHandle(m_bmpThread);
                m_bmpThread = NULL;
            }

            goto L_ACTION;
        case 'r':
            continue;
        case 'e':
            exit(0);
        default:
            std::cout << ">>>>>> invalid action\n";
            goto L_ACTION;
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
