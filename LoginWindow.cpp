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
}

void LoginWindow::Run()
{

}
