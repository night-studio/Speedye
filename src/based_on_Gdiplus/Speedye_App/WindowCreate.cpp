#include "WindowCreate.h"
#include "Draw.h"

#include <iostream>

HDC HandleDC =              nullptr;
HWND HandleWnd =            nullptr;
HINSTANCE HandleInstance =  nullptr;
unsigned char KeyCode =		0;
bool Pressing =				true;

extern unsigned int ShowWidth;
extern unsigned int ShowHeight;

void InitWindow(WCHAR* WndTitle, int BorderRadius) {
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = nullptr;
	wcex.hIcon = nullptr/*LoadIcon(HandleInstance, MAKEINTRESOURCE())*/;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = WndTitle;
	wcex.lpszClassName = WndTitle;
	wcex.hIconSm = nullptr/*LoadIcon(HandleInstance, MAKEINTRESOURCE())*/;
	RegisterClassExW(&wcex);

	RECT DesktopSize{};
	const HWND hScreen = GetDesktopWindow();
	GetWindowRect(hScreen, &DesktopSize);

	HandleWnd = CreateWindowW(
		WndTitle, 
		WndTitle, 
		WS_POPUPWINDOW | WS_BORDER,
		int((DesktopSize.right - ShowWidth) / 2), 
		int((DesktopSize.bottom - ShowHeight) / 2), 
		ShowWidth, 
		ShowHeight, 
		nullptr, 
		nullptr, 
		HandleInstance, 
		nullptr
	);

	HRGN hRegion = CreateRoundRectRgn(0, 0, ShowWidth, ShowHeight, BorderRadius, BorderRadius);
	SetWindowRgn(HandleWnd, hRegion, FALSE);
	
	ShowWindow(HandleWnd, SW_SHOW);
	UpdateWindow(HandleWnd);
}

void ProcMessage() {
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(
		&msg,
		HandleWnd,
		0,
		0,
		PM_REMOVE
	)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hDC;
	switch (message) {
		case /*WM_KEYDOWN*/WM_KEYUP:
			KeyCode = static_cast<unsigned char>(wParam);
			Pressing = KeyCode == 0x20 ? false : true;
		case WM_PAINT:
			hDC = BeginPaint(hWnd, &ps);
			MainDraw(hDC);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return 0;
}