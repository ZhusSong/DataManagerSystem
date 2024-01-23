#include "WindowsManager.h"
//指针初始化
WindowsManager* WindowsManager::instance = nullptr;

void WindowsManager::Close()
{
}

WindowsManager::WindowsManager()
{
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
	instance = new WindowsManager();
	LoadWindow::Instance()->Init();
	LoginWindow::Instance()->Init();
}

void WindowsManager::Run()
{
	initgraph(WIDTH, HEIGHT);
	//设置背景颜色
	setbkcolor(RGB(rgb[COLORS::BackGround].r, rgb[COLORS::BackGround].g, rgb[COLORS::BackGround].b));

	while (true)
	{
		switch (NowWindow)
		{
		case loadWindow:
			LoadWindow::Instance()->Run();
			break;
		case loginWindow:
			LoginWindow::Instance()->Run();
			break;
		case mainWindow:
			break;
		default:
			break;
		}

	}
}
