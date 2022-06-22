#pragma once
#include <Windows.h>
#include <string>
#include <wchar.h>

//======================================
// Data Structure
//======================================

struct TimerInput
{
    unsigned int interval_in_ms;
};

//======================================
// Function
//======================================

int StartHighlight();
int StopHighlight();
bool GameHighlightHotKey(); // return "isHighlightOn"
void CheckGameExit(LPVOID lparam);
void CheckGameRunning(LPVOID lparam);

//======================================
// Global variable
//======================================

extern bool isHighlightOn;
