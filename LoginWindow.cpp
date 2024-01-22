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
	instance = new LoginWindow();
}

LoginWindow::~LoginWindow()
{

}

void LoginWindow::Init()
{
}

void LoginWindow::Run()
{
}
