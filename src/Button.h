#pragma once

#include <Windows.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#include <string>

typedef struct tagButtonProperties {
	int			width		= 10;			/* 长 */
	int			height		= 10;			/* 宽 */
	int			x			= 0;			/* X 坐标 */
	int			y			= 0;			/* Y 坐标 */
	COLORREF	textColor	= 0xFFFFFF;		/* 字体颜色 */
	COLORREF	bgColor		= 0x0;			/* 背景色 */
	int			alignMode	= 1;			/* 对齐选项: 1 - 左, 2 - 右 */
	int			border		= 0;			/* 边框(粗细) */
	COLORREF	borderColor	= 0;			/* 边框颜色 */
} BUTTONPROP;

class Button {
private:

public:
	std::string showStr = "按钮";
	void ((*onClick)());
	bool Activate(HDC hdc);
	BUTTONPROP onShowProp;
	BUTTONPROP onHoverProp;
	BUTTONPROP onClickProp;
};

bool Button::Activate(HDC hdc) {
	return 0;
}