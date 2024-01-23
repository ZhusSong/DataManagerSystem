#pragma once
//****************
//登录界面头文件
//****************
#include "UIManager.h"
#include "SystemConstant.h"
#include "DataManager.h"
class LoginWindow
{
private:

	//单例
	static  LoginWindow* instance;
public:
	static  LoginWindow* Instance();
	LoginWindow();
	~LoginWindow();
	void Init();
	void Run();
};