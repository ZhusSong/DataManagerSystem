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
	//当前进度
	int Progress = 0;
	//绘制进度条
	void DrawProgressBar();
	//得到数据量
	int DataCount = 0;

public:
	static  LoadWindow* Instance();
	LoadWindow();
	~LoadWindow();
	//初始化
	void Init();
	//初始化
	void UnInit();
	//运行
	void Run();
};