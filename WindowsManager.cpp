#include "WindowsManager.h"
//指针初始化
WindowsManager* WindowsManager::instance = nullptr;

void WindowsManager::Close()
{
}

WindowsManager::WindowsManager()
{
	//__int64 countsPerSec{};
	////QueryPerformanceFrequency：得到每个时钟周期的频率
	//QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	//SecondssPerCount = 1.0 / (double)countsPerSec;
}

WindowsManager::~WindowsManager()
{
	delete instance;
}



bool WindowsManager::SetFrame(int frame)
{
	float frameTime = 1.0f / frame;
	
	__int64 currTime{};
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	CurrTime = currTime;
	DeltaTime = (CurrTime - PrevTime) * SecondssPerCount;
	if (DeltaTime <= frameTime)
	{
		return false;
	}
	PrevTime = CurrTime;
	if (DeltaTime < 0)
	{
		DeltaTime = 0;
	}
	return true;
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
	MainWindow::Instance()->Init();
	ProcessWindow::Instance()->Init();
	ShowProcessWindow::Instance()->Init();


}

void WindowsManager::Run()
{

	/*__int64 startTime{};
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
	PrevTime = startTime;*/

	while (true)
	{

		BeginBatchDraw();
			switch (NowWindow)
			{
			case loadWindow:
				cleardevice();
				LoadWindow::Instance()->Run();
				UIManager::Instance()->Run();
				FlushBatchDraw();
				break;
			case loginWindow:
				cleardevice();
				UIManager::Instance()->Run();
				FlushBatchDraw();
				break;
			case mainWindow:
				cleardevice();
				UIManager::Instance()->Run();
				FlushBatchDraw();
				break;
			case processWindow:
				UIManager::Instance()->Run();
				FlushBatchDraw();
				break;
			case showProcessWindow:
				cleardevice();
				UIManager::Instance()->Run();
				FlushBatchDraw();
				break;
			default:
				break;
			}
	}
}
