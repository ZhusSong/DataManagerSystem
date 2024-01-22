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

//加载各种界面
void WindowsManager::Init()
{
	LoadWindow::Instance()->Init();
}

void WindowsManager::Run()
{
	initgraph(WIDTH, HEIGHT);
	//设置背景颜色
	setbkcolor(RGB(rgb[COLORS::BackGround].r, rgb[COLORS::BackGround].g, rgb[COLORS::BackGround].b));

	while (true)
	{

		LoadWindow::Instance()->Run();
	}
}
