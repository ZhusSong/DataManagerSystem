//****************
//主函数入口，仅负责初始化与主管理函数的运行
//****************
#include <iostream>
#include <windows.h>
#include "WindowsManager.h"
#include "DataManager.h"
#include "SystemConstant.h"
#include "UIManager.h"
using namespace std;
// 定义全局枚举变量 myColor
enum WindowsKind NowWindow = loadWindow;
//主函数入口
int  main()
{

	initgraph(WIDTH, HEIGHT);
	//设置背景颜色
	setbkcolor(RGB(rgb[COLORS::BackGround].r, rgb[COLORS::BackGround].g, rgb[COLORS::BackGround].b));
	
	//管理函数初始化
	DataManager::Instance()->Init();
	UIManager::Instance()->Init();
	WindowsManager::Instance()->Init();

	//开始运行
	WindowsManager::Instance()->Run();
	return 0;
}