#pragma once
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