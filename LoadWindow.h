#pragma once

//****************
//加载界面，负责文件的加载动画
//****************
#include "UIManager.h"
#include "SystemConstant.h"
#include "DataManager.h"
class LoadWindow 
{
private:
	//单例
	static  LoadWindow* instance;
	int Progress = 0;
	void DrawProgressBar();
	int DataCount = 0;

public:
	static  LoadWindow* Instance();
	LoadWindow();
	~LoadWindow();
	void Init();
	void Run();
};