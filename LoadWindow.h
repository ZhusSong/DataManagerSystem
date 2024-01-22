#pragma once

//****************
//加载界面头文件
//****************
#include "UIManager.h"
#include "SystemConstant.h"
class LoadWindow 
{
private:
	//单例
	static  LoadWindow* instance;
	int Progress = 0;
	void DrawProgressBar();

public:
	static  LoadWindow* Instance();
	LoadWindow();
	~LoadWindow();
	void Init();
	void Run();
};