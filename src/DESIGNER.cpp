// DESIGNER.cpp : 定义应用程序的入口点。
//

#include "Window.h"

#include <commdlg.h>
#include <thread>
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "Comdlg32.lib")



int __stdcall wWinMain(
    _In_        HINSTANCE hInstance,
    _In_opt_    HINSTANCE hPrevInstance,
    _In_        LPWSTR    lpCmdLine,
    _In_        int       nCmdShow
) {
    Window window;

    Gdiplus::GdiplusStartupInput GdiplusStartupInput;

    window.InitWindow();
    /*
    LPOPENFILENAMEA f{};
    f->lStructSize = sizeof(OPENFILENAME);
    f->hwndOwner = window.GetHWnd();
    f->hInstance = NULL;
    f->lpstrFilter = NULL;


    GetOpenFileNameA(f);
    SetWindowLong(window.GetHWnd(), GWL_STYLE, 0);
    ShowWindow(window.GetHWnd(), SW_SHOW);*/

    return window.returnValue;
}