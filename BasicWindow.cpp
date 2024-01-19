#include "BasicWindow.h"


void BasicWindow::CreateBasicWindow(Colors color)
{
	//生成一个分辨率WIDTH*HEIGHT的窗口
	initgraph(WIDTH, HEIGHT);
	//设置背景颜色
	setbkcolor(RGB(rgb[color].r, rgb[color].g, rgb[color].b));
	//刷新窗口
	cleardevice();
	//保持窗口存在
	while (true);
	//关闭图形化窗口
	closegraph();

}

void BasicWindow::CreateButton(Colors normalColor, Colors enterColor, Colors clickColor, int size[4], char text[20])
{
}

void BasicWindow::CreateInputBox(Colors color, int size[4], char text[20])
{
}

void BasicWindow::CreateTextBox(Colors color, int size[4], char text[20])
{
}

BasicWindow::BasicWindow()
{
}

BasicWindow::~BasicWindow()
{
}

