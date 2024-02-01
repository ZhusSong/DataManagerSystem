#pragma once
//******************
//主窗口，负责展示已有数据，并进行处理，修改，添加删除数据与返回登录界面等操作事件的响应
//******************
#include "UIManager.h"
#include "SystemConstant.h"

class MainWindow
{
private:
	//按钮事件:创建新数据
	void AddNewData();


	//按钮事件:删除选中数据
	void DeleteData();

	//按钮事件:转到处理数据界面
	void ProcessData();

	//按钮事件:转到已处理数据界面
	void ShowProcessData();

	//按钮事件:返回登录界面
	void Return();

	//按钮事件:按均值从小到大排序
	void SortByMean();

	//按钮事件:按方差从小到大排序
	void SortByVar();

	//按钮事件:按行数从小到大排序
	void SortByRow();
	//单例
	static  MainWindow* instance;
public:
	static  MainWindow* Instance();
	MainWindow() {};
	~MainWindow() {
		delete instance;
	};
	//初始化
	void Init();
};