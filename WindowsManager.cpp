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
	while (true)
	{
		BeginBatchDraw();
		switch (NowWindow)
		{
		case loadWindow:

			cleardevice();
			LoadWindow::Instance()->Run();
			UIManager::Instance()->Run();

			break;
		case loginWindow:
			UIManager::Instance()->Run();
			LoginWindow::Instance()->Run();
			break;
		case mainWindow:
			break;
		default:
			break;
		}
		EndBatchDraw();
	}
}
