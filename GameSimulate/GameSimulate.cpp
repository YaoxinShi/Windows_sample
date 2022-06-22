// GameSimulate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

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
    AGH_GAME_LANGUAGE_UNKNOWN = -1,          /**< Unkown */
    AGH_GAME_LANGUAGE_EN = 0,           /**< English */
    AGH_GAME_LANGUAGE_CN = 1,           /**< Chinese */
}AghGameLanguage;

void setup(std::wstring window_name, std::wstring process_name)
{
    HWND foreground = GetForegroundWindow();
    SetWindowText(foreground, window_name.c_str());

    // todo: create a process with process_name
}

int main()
{
    int game = AGH_GAME_TITLE_UNKNOWN;
    int lang = AGH_GAME_LANGUAGE_UNKNOWN;
    std::wstring window_name;
    std::wstring process_name;

    while (1)
    {
        std::cout << "   1, Rainbow 6\n";
        std::cout << "   2, Dota 2\n";
        std::cout << "   3, League of Legends\n";
        std::cout << "   4, Overwatch\n";
        std::cout << "   5, CrossFire\n";
        std::cout << "   6, PlayerUnknown's Battlegrounds\n";
        std::cout << "   7, Call of Duty\n";
        std::cout << "   8, World of Tanks\n";
        std::cout << "   9, Fortnite\n";
        std::cout << "  10, CSGO\n";
        std::cout << "  11, APEX\n";
        std::cout << "  12, HOK\n";
        std::cout << "  13, ProEvolutionSoccer\n";
        std::cout << "  14, GameforPeace\n";
        std::cout << "  15, Naraka\n";
        std::cout << "  16, Rocket\n";
        std::cout << "  17, Valorant\n";
        std::cout << "Game ID:\n";
        std::cin >> game;

        std::cout << "   0, English\n";
        std::cout << "   1, Chinese\n";
        std::cout << "Game Language (default en):\n";
        std::cin >> lang;

        switch (game)
        {
        case AGH_GAME_TITLE_RAINBOW6:
            window_name = L"Rainbow Six";
            break;
        case AGH_GAME_TITLE_DOTA2:
            window_name = L"Dota 2";
            break;
        case AGH_GAME_TITLE_LOL:
            window_name = L"League of Legends (TM) Client";
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
            break;
        case AGH_GAME_TITLE_CROSSFIRE:
            window_name = L"穿越火线";
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
            break;
        case AGH_GAME_TITLE_COD:
            window_name = L"Call of Duty";
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
            break;
        case AGH_GAME_TITLE_FORTNITE:
            window_name = L"Fortnite";
            break;
        case AGH_GAME_TITLE_CSGO:
            window_name = L"Counter-Strike: Global Offensive";
            break;
        case AGH_GAME_TITLE_APEX:
            window_name = L"Apex Legends";
            break;
        case AGH_GAME_TITLE_HOK:
            window_name = L"HOK";
            break;
        case AGH_GAME_TITLE_PESOCCER:
            window_name = L"eFootball PES 2021 SEASON UPDATE";
            break;
        case AGH_GAME_TITLE_GameforPeace:
            window_name = L"GOP";
            break;
        case AGH_GAME_TITLE_Naraka:
            window_name = L"Naraka";
            break;
        case AGH_GAME_TITLE_Rocket:
            window_name = L"Rocket League";
            break;
        case AGH_GAME_TITLE_VALORANT:
            window_name = L"VALORANT";
            break;
        default:
            std::cout << "invalid game ID\n";
            window_name = L"???";
        }

        setup(window_name, process_name);
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
