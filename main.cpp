//****************
//主函数入口
//****************
#include <iostream>
#include <windows.h>
#include "WindowsManager.h"
#include "DataManager.h"
#include "SystemConstant.h"
using namespace std;
// 定义全局枚举变量 myColor
enum WindowsKind NowWindow = loadWindow;
//主函数入口
int  main()
{

	DataManager::Instance()->Init();
	WindowsManager::Instance()->Init();
	WindowsManager::Instance()->Run();
	return 0;
}