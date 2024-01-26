#pragma once
//******************
//窗口管理，负责各窗口的初始化,以及整个程序的运行流程管理
//******************
#include <iostream>
#include <stdlib.h>
#include "UIManager.h"
#include "LoginWindow.h"
#include "LoadWindow.h"
#include "MainWindow.h"
#include "SystemConstant.h"

class WindowsManager
{
private:
	//单例
	static  WindowsManager* instance;
	//窗口管理指针，每次更换窗口时更换指定对象
	UIManager* Window;

public:
	
	static  WindowsManager* Instance();

	//加载初始界面
	void Init();

	void Run();

	void Close();
	WindowsManager();
	~WindowsManager();

};