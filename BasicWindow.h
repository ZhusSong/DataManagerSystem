#pragma once
#include <graphics.h>
#include "DataManager.h"
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <math.h>
using namespace std;


//所有界面的父类，定义了一些基本窗口组件函数
class BasicWindow
{
//受保护的对象，仅可被该类及子类对象访问
protected:
	//创建窗口
	//color:背景颜色
	void CreateBasicWindow(Colors color);

	//创建按钮
	//normalColor:常态颜色
	//enterColor:当鼠标进入按钮范围时的颜色
	//clickColor:当鼠标点击时的颜色
	//size[4]:按钮的四个角的坐标
	//char[20]:文字显示，最大20个字符
	void CreateButton(Colors normalColor, Colors enterColor, Colors clickColor,int size[4],char text[20]);

	//创建输入框
	//color:输入框颜色
	//size[4]:输入框位置
	//text[20]:输入的字符，最大20个
	void CreateInputBox(Colors color,int size[4],char text[20]);
	//创建文字框
	//color:输入框颜色
	//size[4]:输入框位置
	//text[20]:输入的字符，最大20个
	void CreateTextBox(Colors color, int size[4], char text[20]);


private:

public:
	BasicWindow();
	virtual ~BasicWindow();
};