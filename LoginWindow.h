#pragma once
//****************
//登录界面头文件
//****************
#include "UIManager.h"
#include "SystemConstant.h"
#include "DataManager.h"
#include <string>
class LoginWindow
{
private:

	//单例
	static  LoginWindow* instance;
	//按钮事件:登录
	void Login();
	//按钮事件:注册
	void Register();
	//按钮事件:退出
	void Exit();

public:
	static  LoginWindow* Instance();
	LoginWindow();
	~LoginWindow();
	
	void Init();
	void Run();
};