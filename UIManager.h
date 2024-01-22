#pragma once
#include <graphics.h>
#include "DataManager.h"
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include "SystemConstant.h"
using namespace std;


//UI组件管理
class UIManager
{
//受保护的对象，仅可被该类及子类对象访问
protected:
	//创建窗口
	//color:背景颜色
	void CreateBasicWindow(COLORS color);

	//创建按钮，默认为圆角矩形
	//返回值为按钮的xy范围数组,顺序与easyX创建矩形顺序相同
	//normalColor:常态颜色
	//enterColor:当鼠标进入按钮范围时的颜色
	//clickColor:当鼠标点击时的颜色
	//size[4]:按钮的四个角的坐标
	//char[20]:文字显示，最大20个字符
	int CreateButton(COLORS normalColor, COLORS enterColor, COLORS clickColor,int size[4],char text[20]);

	//创建矩形框体 
	//color:输入框颜色
	//size[4]:输入框位置
	void CreateRectangleBox(COLORS color, int size[4], char text[20]);

	//创建圆角矩形框体 
	//color:输入框颜色
	//size[4]:输入框位置
	void CreateRoundrectBox(COLORS color, int size[4], char text[20]);

	//创建一个输入框
	//color:输入框颜色
	//size[4]:输入框位置
	//text[20]:输入的字符，最大20个
	void CreateInputBox(COLORS color,int size[4],char text[20]);


private:

public:
	UIManager();
	virtual ~UIManager();
};