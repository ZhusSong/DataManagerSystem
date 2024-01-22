#include "UIManager.h"


void UIManager::CreateBasicWindow(COLORS color)
{
	//设置背景颜色
	setbkcolor(RGB(rgb[color].r, rgb[color].g, rgb[color].b));
	//刷新窗口
	cleardevice();

}

int UIManager::CreateButton(COLORS normalColor, COLORS enterColor, COLORS clickColor, int size[4], char text[20])
{
	fillroundrect(size[0], size[1], size[2], size[3], 50, 50);
	setfillcolor(RGB(rgb[normalColor].r, rgb[normalColor].g, rgb[normalColor].b));


	settextcolor(RGB(rgb[COLORS::TextColor].r, rgb[COLORS::TextColor].g, rgb[COLORS::TextColor].b));
	//设置文字样式，大小，字体
	settextstyle(40, 0, "宋体");
	setbkmode(TRANSPARENT);
	int width = (size[2] - size[0]) / 2 - textwidth(text) / 2;
	int height = (size[3] - size[0]) / 2 - textheight(text) / 2;
	outtextxy(width + size[0], height + size[1], text);

	int range[4] = {size[0], size[1],size[0] + size[2],size[1] + size[3]};
	return *range;
}

void UIManager::CreateRectangleBox(COLORS color, int size[4], char text[20])
{
	fillrectangle(size[0], size[1], size[2], size[3]);
	setfillcolor(RGB(rgb[color].r, rgb[color].g, rgb[color].b));

	settextcolor(RGB(rgb[COLORS::TextColor].r, rgb[COLORS::TextColor].g, rgb[COLORS::TextColor].b));
	//设置文字样式，大小，字体
	settextstyle(40, 0, "宋体"); 
	setbkmode(TRANSPARENT);
	//设置文字居中
	//|<- (right-left)/2->|
	//***************************************
	//*                                     *
	//*              height                 *
	//*      width <-| {text}               *
	//*                 | |                 *
	//*        (text pixel width)/2         *
	//***************************************
 	int width = (size[2] - size[0]) / 2 - textwidth(text) / 2;
	int height = (size[3] - size[0]) / 2 - textheight(text) / 2;
	outtextxy(width + size[0], height + size[1], text);
	
}

void UIManager::CreateRoundrectBox(COLORS color, int size[4], char text[20])
{

	fillroundrect(size[0], size[1], size[2], size[3],50,50);
	setfillcolor(RGB(rgb[color].r, rgb[color].g, rgb[color].b));
	settextcolor(RGB(rgb[COLORS::TextColor].r, rgb[COLORS::TextColor].g, rgb[COLORS::TextColor].b));
	//设置文字样式，大小，字体
	settextstyle(40, 0, "宋体");
	setbkmode(TRANSPARENT);
	int width = (size[2] - size[0]) / 2 - textwidth(text) / 2;
	int height = (size[3] - size[0]) / 2 - textheight(text) / 2;
	outtextxy(width + size[0], height + size[1], text);
}

void UIManager::CreateInputBox(COLORS color, int size[4], char text[20])
{
	fillrectangle(size[0], size[1], size[2], size[3]);
	setfillcolor(RGB(rgb[color].r, rgb[color].g, rgb[color].b));

	settextcolor(RGB(rgb[COLORS::TextColor].r, rgb[COLORS::TextColor].g, rgb[COLORS::TextColor].b));
	//设置文字样式，大小，字体
	settextstyle(40, 0, "宋体");
	setbkmode(TRANSPARENT);
	int width = (size[2] - size[0]) / 2 - textwidth(text) / 2;
	int height = (size[3] - size[0]) / 2 - textheight(text) / 2;
	outtextxy(width + size[0], height + size[1], text);
}


UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

