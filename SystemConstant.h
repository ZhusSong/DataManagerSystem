#pragma once

//******************
//此处定义了一些常量与全局变量
//******************
#include <graphics.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <wchar.h>


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
	//文字颜色_白
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

//颜色对应的rgb值
RGBs rgb = { {105 ,105 ,105},
	{163,148,128},
	{245,245,245},

	{128,138,135},
	{192,192,192},
	{110,110,110},

	{218,165,105},
	{255,227,132},
	{237,145,33},

	{61,89,171},
	{30,144,255},
	{25,25,112}
};
//界面种类
enum WindowsKind
{
	loadWindow = 0,
	loginWindow = 1,
	mainWindow = 2,
	processWindow = 3,
	showProcessWindow = 4,
};
//当前界面的全局变量
extern enum WindowsKind NowWindow;



//排序种类
enum SortKind
{
	//通过均值
	ByMean = 0,
	//通过方差
	ByVar = 1,
	//通过行数
	ByRow = 2,
};
//数据操作种类
enum DataProcessKind
{
	//正常显示
	Normal = 0,
	//平滑
	Smoothness = 1,
	//去除离群值
	Removal = 2,
};
//工具函数
class SystemUtiliy
{
public:

	 /// 将wstring转为char*，以便easyX使用
	 static char* ChangeStringToChar(std::wstring& text)
	{
		int length = text.size()+1;
		char* _text=new char[length];

		size_t bufferSize = 0;
		wcstombs_s(&bufferSize, nullptr, 0, text.c_str(), 0);
		std::vector<char> buffer(bufferSize + 1);
		if (wcstombs_s(&bufferSize, buffer.data(), bufferSize + 1, text.c_str(), bufferSize) == 0)
		{
			strcpy_s(_text, length, buffer.data());
		}
		return _text;
	}

	 /// 将wchar转为char*，以便获取inputbox内容
	 static char* ChangeWcharToChar( wchar_t* text)
	 {
		 char* m_char;
		 size_t len ;
		 if (wcstombs_s(&len, NULL, 0, text, _TRUNCATE) != 0) {
			 perror("wcstombs_s");
			 exit(EXIT_FAILURE);
		 }
		 // Allocate memory for the char string
		 m_char = (char*)malloc((len + 1) * sizeof(char)); // Include space for null terminator
		 if (m_char == NULL) {
			 perror("malloc");
			 exit(EXIT_FAILURE);
		 }

		 // Convert wide character string to multibyte character string
		 if (wcstombs_s(NULL, m_char, len + 1, text, _TRUNCATE) != 0) {
			 perror("wcstombs_s");
			 exit(EXIT_FAILURE);
		 }
		 return m_char;
	 }

	 //判断输入是否是数字
	 static bool JudgementNumber(const char* s)
	 {
		 int len = strlen(s);
		 for (int i = 0; i < len; i++)
		 {
			 if (!isdigit(s[i]))
				 return false;
		 }
		 return true;

	 }
};


