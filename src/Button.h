#pragma once

#include <Windows.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#include <string>

typedef struct tagButtonProperties {
	int			width		= 10;			/* �� */
	int			height		= 10;			/* �� */
	int			x			= 0;			/* X ���� */
	int			y			= 0;			/* Y ���� */
	COLORREF	textColor	= 0xFFFFFF;		/* ������ɫ */
	COLORREF	bgColor		= 0x0;			/* ����ɫ */
	int			alignMode	= 1;			/* ����ѡ��: 1 - ��, 2 - �� */
	int			border		= 0;			/* �߿�(��ϸ) */
	COLORREF	borderColor	= 0;			/* �߿���ɫ */
} BUTTONPROP;

class Button {
private:

public:
	std::string showStr = "��ť";
	void ((*onClick)());
	bool Activate(HDC hdc);
	BUTTONPROP onShowProp;
	BUTTONPROP onHoverProp;
	BUTTONPROP onClickProp;
};

bool Button::Activate(HDC hdc) {
	return 0;
}