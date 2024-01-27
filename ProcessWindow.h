#pragma once
//******************
//处理信息界面，负责对选中的信息进行处理，以及返回主界面
//******************
#include "UIManager.h"
class ProcessWindow
{
private:

	//单例
	static ProcessWindow* instance;

public:
	static ProcessWindow* Instance();
	ProcessWindow();
	~ProcessWindow();
	//初始化
	void Init();
	//运行
	void Run();
};