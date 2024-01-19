//****************
//主函数入口
//****************
#include <iostream>
#include <windows.h>
#include "WindowsManager.h"
#include "DataManager.h"
using namespace std;

//主函数入口
int  main()
{
	WindowsManager::Instance()->Init();
	return 0;
}