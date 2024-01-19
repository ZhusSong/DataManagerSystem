#include "WindowsManager.h"
#include "LoginWindow.h"
#include "LoadWindow.h"
//指针初始化
WindowsManager* WindowsManager::instance = nullptr;

WindowsManager::WindowsManager()
{
	instance = new WindowsManager();
}

WindowsManager::~WindowsManager()
{
}

WindowsManager* WindowsManager::Instance()
{
	return instance;
}

//加载登录界面
void WindowsManager::Init()
{
	_Window = new LoadWindow();
}
