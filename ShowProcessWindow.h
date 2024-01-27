#pragma once

//******************
//显示已处理信息界面，仅负责展示已处理信息，以及返回主界面
//******************
#include "UIManager.h"
class ShowProcessWindow
{
private:

	//单例
	static ShowProcessWindow* instance;

public:
	static ShowProcessWindow* Instance();
	ShowProcessWindow();
	~ShowProcessWindow();

	void Init();
	void Run();
};