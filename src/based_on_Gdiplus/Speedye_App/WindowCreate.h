#pragma once
#include <Windows.h>

void InitWindow(WCHAR* WndTitle, int BorderRadius);
void ProcMessage();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
