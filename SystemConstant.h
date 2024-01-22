#pragma once

//******************
//此处定义了一些常量与全局变量
//******************

#include <graphics.h>


//最大文件条数
#define N 999 
//定义窗口分辨率为1024*768
#define WIDTH  1024
#define HEIGHT  768
//所需颜色定义
enum COLORS
{
	//背景色
	BackGround = 0,
	//边线颜色
	LineColor = 1,
	//文字颜色
	TextColor = 2,
	//颜色组01:灰色系
	//常态颜色
	NormalColor_1 = 3,
	//鼠标进入时的颜色
	EnterColor_1 = 4,
	//鼠标点击时的颜色
	ClickColor_1 = 5,

	//颜色组02:黄色系
	//常态颜色
	NormalColor_2 = 6,
	//鼠标进入时的颜色
	EnterColor_2 = 7,
	//鼠标点击时的颜色
	ClickColor_2 = 8,

	//颜色组03:蓝色系
	//常态颜色
	NormalColor_3 = 9,
	//鼠标进入时的颜色
	EnterColor_3 = 10,
	//鼠标点击时的颜色
	ClickColor_3 = 11,
};

//颜色rgb结构体
//初始化颜色RGB值，与枚举Colors一一对应
typedef struct {
	BYTE r, g, b;
}RGBs[12];

RGBs rgb = { {220,220,220},
	{163,148,128},
	{245,245,245},

	{128,138,135},
	{192,192,192},
	{41,36,33},

	{218,165,105},
	{255,227,132},
	{237,145,33},

	{61,89,171},
	{30,144,255},
	{25,25,112}
};
