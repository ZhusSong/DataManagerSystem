#include "WindowsManager.h"
#include "LoginWindow.h"
#include "LoadWindow.h"
//指针初始化
WindowsManager* WindowsManager::instance = nullptr;

void WindowsManager::Close()
{
}

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
	Window = new LoadWindow();
}

void WindowsManager::Run()
{
}
