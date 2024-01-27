#pragma once
//******************
//主窗口，负责展示已有数据，并进行处理，修改，添加删除数据与返回登录界面等操作
//******************
#include "UIManager.h"

class MainWindow
{
private:
	//按钮事件:创建新数据
	void AddNewData();

	//判断字符串数组是否是数字
	bool JudgementNumber(char* s);

	//按钮事件:删除选中数据
	void DeleteData();

	//按钮事件:转到处理数据界面
	void ProcessData();

	//按钮事件:转到已处理数据界面
	void ShowProcessData();

	//按钮事件:返回登录界面
	void Return();
	//单例
	static  MainWindow* instance;
public:
	static  MainWindow* Instance();
	MainWindow() {};
	~MainWindow() {};
	//初始化
	void Init();
	//运行
	void Run();
};