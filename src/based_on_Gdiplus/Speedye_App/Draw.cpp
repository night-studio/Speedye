#include "Draw.h"
#include "resource.h"
#include "FileIO.h"

#include <chrono>
#include <atlstr.h>

extern unsigned char KeyCode;
extern wchar_t* fileNameAndPath;
extern Gdiplus::Bitmap img;
extern std::wifstream* fileProps;

extern unsigned int ShowWidth;
extern unsigned int ShowHeight;

static auto timePoint = std::chrono::steady_clock::now();
static int count = 1;

ULONG_PTR InitGdiplus() {
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	return gdiplusToken;
}

void FinishGdiplus(ULONG_PTR ptr) {
	Gdiplus::GdiplusShutdown(ptr);
}

void MainDraw(HDC hDC) {
	timePoint = std::chrono::steady_clock::now();

	Gdiplus::Graphics gph(hDC);
	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0));
	Gdiplus::Rect rect(10, 10, 50, 50);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 85, 85, 85));

	Gdiplus::FontFamily font_OPPOSansR(L"OPPOSans R");
	Gdiplus::FontFamily font_OPPOSansM(L"OPPOSans M");
	Gdiplus::FontFamily font_OPPOSansB(L"OPPOSans B");
	Gdiplus::Font font(&font_OPPOSansB, 13, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

	Gdiplus::PointF origin(10, 10);
	gph.FillRectangle(&brush, -5, -5, ShowWidth + 10, 36 + 5); 

	gph.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	gph.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

	brush.SetColor(Gdiplus::Color(255, 255, 255, 255));
	gph.DrawString(fileNameAndPath == nullptr ? L"无文件" : fileNameAndPath, -1, &font, origin, &brush);
	Draw_TopRightTags(gph, &font, &brush);

	// Gdiplus::Bitmap& Img = *img;
	rect.X = 36;
	rect.Y = 0;
	rect.Height = ShowHeight - 36;
	rect.Width = int((ShowHeight - 36) / img.GetHeight() * (img.GetWidth()));;
	gph.DrawImage(&img, 10, 10);
	
	auto timeCount = std::chrono::steady_clock::now();
	CString strFormat;
	strFormat.Format(L"%d", ++count);
	origin.X = 10;
	origin.Y = 60;
	
	brush.SetColor(Gdiplus::Color(255, 255, 255, 255));
	rect.X = 10,
		rect.Y = 60,
		rect.Width = 100,
		rect.Height = 100;
	gph.FillRectangle(&brush, rect);
	brush.SetColor(Gdiplus::Color(255, 0, 0, 0));
	gph.DrawString(strFormat, -1, &font, origin, &brush);

	Draw_RightContents(gph);
}

void Draw_TopRightTags(Gdiplus::Graphics& gf, Gdiplus::Font* font, Gdiplus::SolidBrush* brush) {
	HRGN hRgn = CreateRoundRectRgn(ShowWidth - 90, 6, ShowWidth - 10, 30, 24, 24);
	Gdiplus::Region region(hRgn);
	Gdiplus::PointF origin(ShowWidth - 165, 10);
	gf.DrawString(L"Speedye", -1, font, origin, brush);
	brush->SetColor(Gdiplus::Color(255, 255, 213, 213));
	gf.FillRegion(brush, &region);
	brush->SetColor(Gdiplus::Color(255, 189, 32, 32));
	origin.X = ShowWidth - 80;
	origin.Y = 10;
	gf.DrawString(L"松开空格", -1, font, origin, brush);
}

void Draw_RightContents(Gdiplus::Graphics& gf) {
	int STPx = ShowWidth - 300; // StarT Point
	int STPy = 36;
	Gdiplus::PointF point(STPx, STPy);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));

	Gdiplus::FontFamily font_OPPOSansB(L"OPPOSans B");
	Gdiplus::Font fontSm(&font_OPPOSansB, 13, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::Font fontBig(&font_OPPOSansB, 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	
	int wcharp = 0;
	for (int i = 0; fileNameAndPath[i] != 0; ++i)
		wcharp = (fileNameAndPath[i] == 0x5C ? i : wcharp);
	wchar_t* fileName = &(fileNameAndPath[++wcharp]);
	
	point.X += 20, point.Y += 40;
	brush.SetColor(Gdiplus::Color(255, 111, 111, 111));
	gf.DrawString(fileName, -1, &fontBig, point, &brush);

	point.Y += 40;
	brush.SetColor(Gdiplus::Color(255, 0, 0, 0));
	gf.DrawString(L"长", -1, &fontSm, point, &brush);
	point.X = STPx + 150;
	gf.DrawString(L"宽", -1, &fontSm, point, &brush);

	point.X = STPx + 20;
	point.Y += 15;
	CString strFormat;
	strFormat.Format(L"%d 像素", img.GetWidth());
	gf.DrawString(strFormat, -1, &fontBig, point, &brush);
	point.X = STPx + 150;
	strFormat.Format(L"%d 像素", img.GetHeight());
	gf.DrawString(strFormat, -1, &fontBig, point, &brush);

	point.X = STPx + 20;
	point.Y += 40;
	gf.DrawString(L"文件大小", -1, &fontSm, point, &brush);
	point.Y += 15;
	strFormat.Format(L"%d KB", fileProps->tellg());
}