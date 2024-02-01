#pragma once

//******************
//显示已处理信息界面，仅负责展示已处理信息，以及返回主界面
//******************
#include "UIManager.h"
class ShowProcessWindow
{
private:
	void Return();
	//单例
	static ShowProcessWindow* instance;
	//按钮事件:按均值从小到大排序
	void SortByMean();

	//按钮事件:按方差从小到大排序
	void SortByVar();

	//按钮事件:按行数从小到大排序
	void SortByRow();
public:
	static ShowProcessWindow* Instance();
	ShowProcessWindow();
	~ShowProcessWindow();

	void Init();
};