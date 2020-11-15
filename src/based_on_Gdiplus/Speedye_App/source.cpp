#include "Draw.h"
#include "WindowCreate.h"
#include "FileIO.h"
#include "resource.h"

unsigned int ShowWidth = 890;
unsigned int ShowHeight = 480;
wchar_t* fileNameAndPath = nullptr;
std::wifstream* fileProps;
Gdiplus::Bitmap img(1280, 853);

extern unsigned char KeyCode;
extern bool Pressing;

int wmain(int argc, wchar_t** argv, wchar_t** envp) {
	if (argc == 2) {
		fileNameAndPath = argv[1];
		
		img.FromFile(fileNameAndPath);
		std::wifstream file(fileNameAndPath);
		fileProps = &file;
		ShowWidth = (ShowHeight - 36) / img.GetHeight() * img.GetWidth() + 300;
	} else {
		img.FromResource(nullptr, L"beach_1280x853.jpg");
	}

	ULONG_PTR gdiplusPtr = InitGdiplus();
	if (!ReadParameters()) {
		// ShowWidth = 640;
	}

	InitWindow((WCHAR*)L"Speedye", 20);

	while (Pressing) {
		ProcMessage();
	}

	FinishGdiplus(gdiplusPtr);

	return 0;
}