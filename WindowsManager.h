#pragma once
//******************
//窗口管理，负责各窗口的初始化
//******************
#include <iostream>
#include <stdlib.h>
#include "BasicWindow.h"

class WindowsManager
{
private:
	//单例
	static  WindowsManager* instance;
	//窗口管理指针，每次更换窗口时更换指定对象
	BasicWindow* _Window;
public:
	//界面种类
	enum WindowsKind
	{

	};
	static  WindowsManager* Instance();

	//加载初始界面
	void Init();

	WindowsManager();
	~WindowsManager();

};