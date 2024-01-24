#include "LoginWindow.h"
//****************
//登录界面
//****************

//指针初始化
LoginWindow* LoginWindow::instance = nullptr;
LoginWindow* LoginWindow::Instance()
{
	return instance;
}

LoginWindow::LoginWindow()
{

}

LoginWindow::~LoginWindow()
{

}

void LoginWindow::Init()
{
	instance = new LoginWindow();

	DataManager::Instance()->LoadAccount();
	/*char a[20] = "user02";
	char b[20] = "1234";

	DataManager::Instance()->CreateAccount(a, b);*/
}

void LoginWindow::Run()
{
	
}
