#pragma once

// // ���� SDKDDKVer.h �ɶ�����õ���߰汾�� Windows ƽ̨��
// ���ϣ��Ϊ֮ǰ�� Windows ƽ̨����Ӧ�ó����ڰ��� SDKDDKVer.h ֮ǰ���Ȱ��� WinSDKVer.h ��
// �� _WIN32_WINNT ������Ϊ��Ҫ֧�ֵ�ƽ̨��
#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ�ļ����ų�����ʹ�õ�����
// Windows ͷ�ļ�
#include <windows.h>
// ͷ�ļ�
#include <thread>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#define IDS_APP_TITLE			103

#define IDR_MAINFRAME			128
#define IDD_DESIGNER_DIALOG	    102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDI_DESIGNER			107
#define IDI_SMALL				108
#define IDC_DESIGNER			109
#define IDC_MYICON				2
#ifndef IDC_STATIC
#define IDC_STATIC				-1
#endif


class Window {
private:
    HINSTANCE mainHInst;
    HWND hWnd;
    WCHAR szTitle[100];                  // �������ı�
    WCHAR szWindowClass[100];            // ����������
    WPARAM mouseMsg;

    MSG msg;

	void RegisterWndClass(HINSTANCE hInstance);
    void gotoMainMsg();
    bool InitInstance(HINSTANCE hInstance);
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
    int returnValue;
    HWND GetHWnd();
    WPARAM getMouseMsg();
    void InitWindow();
};

void Window::RegisterWndClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;
    wcex.cbSize =           sizeof(WNDCLASSEX);
    wcex.style =            CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc =      this->WndProc;
    wcex.cbClsExtra =       0;
    wcex.cbWndExtra =       0;
    wcex.hInstance =        hInstance;
    wcex.hIcon =            LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DESIGNER));
    wcex.hCursor =          LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground =    (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName =     MAKEINTRESOURCEW(IDC_DESIGNER);
    wcex.lpszClassName =    this->szWindowClass;
    wcex.hIconSm =          /*LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL))*/ NULL;

    RegisterClassExW(&wcex);
}

bool Window::InitInstance(HINSTANCE hInstance) {
    
    this->mainHInst = hInstance;

    this->hWnd = CreateWindowExW(
        0,
        this->szWindowClass, 
        this->szTitle, 
        WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, 
        0, 
        CW_USEDEFAULT, 
        0, 
        nullptr, 
        nullptr, 
        hInstance, 
        nullptr
    );

    if (!this->hWnd) {
        return FALSE;
    }

    ShowWindow(this->hWnd, 1);
    UpdateWindow(this->hWnd);
    
    return TRUE;
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int wmId;
    HDC hdc;
    switch (message) {
        case WM_COMMAND:
            wmId = LOWORD(wParam);
            // �����˵�ѡ��:
            switch (wmId) {
                case IDM_ABOUT:
                    // DialogBox(this->mainHInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_PAINT:
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
            // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HWND Window::GetHWnd() {
    return this->hWnd;
}

void Window::InitWindow() {
    this->mainHInst = (HINSTANCE)0;
    LoadStringW(this->mainHInst, IDS_APP_TITLE, this->szTitle, 100);
    LoadStringW(this->mainHInst, IDC_DESIGNER, this->szWindowClass, 100);
    this->RegisterWndClass(this->mainHInst);

    if (!InitInstance(this->mainHInst)) {
        this->returnValue = FALSE;
    }

    // ����Ϣѭ��
    this->gotoMainMsg();
    /*
    HACCEL hAccelTable = LoadAccelerators(this->mainHInst, MAKEINTRESOURCE(IDC_DESIGNER));
    while (GetMessage(&(this->msg), nullptr, 0, 0)) {
        if (!TranslateAccelerator(this->msg.hwnd, hAccelTable, &(this->msg))) {
            TranslateMessage(&(this->msg));
            DispatchMessage(&(this->msg));
        }
    }
    */
    
    this->returnValue = (int)msg.wParam;
}

void Window::gotoMainMsg() {
    std::thread newThread([this]() {
        HACCEL hAccelTable = LoadAccelerators(this->mainHInst, MAKEINTRESOURCE(IDC_DESIGNER));
        while (GetMessageA(&(this->msg), this->hWnd, 0, 0)) {
            if (!TranslateAccelerator(this->msg.hwnd, hAccelTable, &(this->msg))) {
                TranslateMessage(&(this->msg));
                DispatchMessage(&(this->msg));
            }
        }
    });
    newThread.join();
}

