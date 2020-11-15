#pragma once

#include <Windows.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

ULONG_PTR InitGdiplus();
void FinishGdiplus(ULONG_PTR);

void MainDraw(HDC hDC);
void Draw_TopRightTags(Gdiplus::Graphics& gf, Gdiplus::Font* font, Gdiplus::SolidBrush* brush);
void Draw_RightContents(Gdiplus::Graphics& gf);