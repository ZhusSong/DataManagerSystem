#include "ShowProcessWindow.h"

ShowProcessWindow* ShowProcessWindow::instance = nullptr;
ShowProcessWindow* ShowProcessWindow::Instance()
{
	return instance;
}

ShowProcessWindow::ShowProcessWindow()
{
}

ShowProcessWindow::~ShowProcessWindow()
{
	delete instance;
}
void ShowProcessWindow::Return()
{
	NowWindow = mainWindow;
	Sleep(50);
}
void ShowProcessWindow::SortByMean()
{
	DataManager::Instance()->SortDatas(showProcessWindow,ByMean);
	//刷新图表
	UIManager::Instance()->SetNewTable(showProcessWindow);
}

void ShowProcessWindow::SortByVar()
{
	DataManager::Instance()->SortDatas(showProcessWindow, ByVar);
	//刷新图表
	UIManager::Instance()->SetNewTable(showProcessWindow);
}

void ShowProcessWindow::SortByRow()
{
	DataManager::Instance()->SortDatas(showProcessWindow, ByRow);
	//刷新图表
	UIManager::Instance()->SetNewTable(showProcessWindow);
}
void ShowProcessWindow::Init()
{
	instance = new ShowProcessWindow();

	//创建返回按钮
	UIManager::Instance()->CreateButton(WindowsKind::showProcessWindow,
		50, 100, 200, 80, L"返回", [&]() {
			Return();
		}, 0);
	//创建按均值排序按钮
	UIManager::Instance()->CreateButton(WindowsKind::showProcessWindow,
		260, 100, 200, 80, L"均值小到大排序", [&]() {
			SortByMean();
		}, 1);
	//创建按方差排序按钮
	UIManager::Instance()->CreateButton(WindowsKind::showProcessWindow,
		470, 100, 200, 80, L"方差小到大排序", [&]() {
			SortByVar();
		}, 2);
	//创建按行数排序按钮
	UIManager::Instance()->CreateButton(WindowsKind::showProcessWindow,
		680, 100, 200, 80, L"行数小到大排序", [&]() {
			SortByRow();
		}, 3);
	//创建显示已处理信息的图表
	UIManager::Instance()->CreateTable(showProcessWindow, 50, 200, 800, 500, 5);
}

