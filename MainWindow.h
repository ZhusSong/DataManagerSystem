#pragma once
//******************
//主窗口，负责展示已有数据，并进行处理，修改，添加删除数据与返回登录界面等操作
//******************
#include "UIManager.h"

class MainWindow
{
private:

	//单例
	static  MainWindow* instance;
public:
	static  MainWindow* Instance();
	MainWindow() {};
	~MainWindow() {};
	void Init();
	void Run();
};