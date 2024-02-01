#include "MainWindow.h"

//指针初始化
MainWindow* MainWindow::instance = nullptr;
void MainWindow::AddNewData()
{
	wchar_t s[10];
	InputBox(s,10, L"请输入数据条数，最大1000:");
	const char* s2=SystemUtiliy::ChangeWcharToChar(s);
	if (sizeof(s) != 0 && SystemUtiliy::JudgementNumber(s2))
	{
		int count = atoi(s2);
		if (count > 1000)
		{
			count = 1000;
		}
		if (count > 0)
		{
			//创建messageBox显示文字
			wstring n=L"Create ";
			n+= DataManager::Instance()->CreateRandomData(count);
			n += L" successful!";

			MessageBox(GetHWnd(), n.c_str(), L"CREATE", MB_OK);
			//刷新图表
			UIManager::Instance()->SetNewTable(mainWindow);
		}
	}
	else
	{
		UINT yesno = MessageBox(GetHWnd(), L"请输入数字!", L"ERROR", MB_YESNO);
		if (yesno == IDYES)
		{
			AddNewData();
		}
		else
		{
			return;
		}
	}
	delete s2;
}



void MainWindow::DeleteData()
{
	UINT yesno = MessageBox(GetHWnd(),L"确定删除此数据?",L"DELETE",MB_YESNO);
	if (yesno == IDYES)
	{
		UIManager::Instance()->DeleteSelectedData(mainWindow);
	}
}
void MainWindow::ProcessData() 
{
	UINT yesno = MessageBox(GetHWnd(), L"确定分析此数据?", L"CONFIRM", MB_YESNO);
	if (yesno == IDYES)
	{
		int	count = 7;
		NowWindow = processWindow;
		UIManager::Instance()->ProcessSelectedData(mainWindow, count);
	}

}
void MainWindow::ShowProcessData()
{
	NowWindow = showProcessWindow;
	//刷新图表
	UIManager::Instance()->SetNewTable(showProcessWindow);
}
void MainWindow::Return()
{
	NowWindow = loginWindow;
}
void MainWindow::SortByMean()
{
	DataManager::Instance()->SortDatas(mainWindow, ByMean);
	//刷新图表
	UIManager::Instance()->SetNewTable(mainWindow);
}
void MainWindow::SortByVar()
{

	DataManager::Instance()->SortDatas(mainWindow, ByVar);
	//刷新图表
	UIManager::Instance()->SetNewTable(mainWindow);
}
void MainWindow::SortByRow()
{

	DataManager::Instance()->SortDatas(mainWindow, ByRow);
	//刷新图表
	UIManager::Instance()->SetNewTable(mainWindow);
}
MainWindow* MainWindow::Instance()
{
	return nullptr;
}

void MainWindow::Init()
{
	instance = new MainWindow();
	//创建分析按钮
	UIManager::Instance()->CreateButton(WindowsKind::mainWindow,
		50, 100, 200, 80, L"处理数据", [&]() {
			ProcessData();
		}, 0);
	//创建按均值排序按钮
	UIManager::Instance()->CreateButton(WindowsKind::mainWindow,
		260, 100, 200, 80, L"均值小到大排序", [&]() {
			SortByMean();
		}, 1);
	//创建按方差排序按钮
	UIManager::Instance()->CreateButton(WindowsKind::mainWindow,
		470, 100, 200, 80, L"方差小到大排序", [&]() {
			SortByVar();
		}, 2);
	//创建按行数排序按钮
	UIManager::Instance()->CreateButton(WindowsKind::mainWindow,
		680, 100, 200, 80, L"行数小到大排序", [&]() {
			SortByRow();
		}, 3);
	//创建添加新数据按钮
	UIManager::Instance()->CreateButton(WindowsKind::mainWindow,
		750, 200, 250, 80, L"添加新数据", [&]() {
			AddNewData();
		}, 4);
	//创建删除数据按钮
	UIManager::Instance()->CreateButton(WindowsKind::mainWindow,
		750, 300, 250, 80, L"删除选中数据", [&]() {
			DeleteData();
		}, 5);
	//创建显示已处理数据按钮
	UIManager::Instance()->CreateButton(WindowsKind::mainWindow,
		750, 400, 250, 80, L"显示已处理数据", [&]() {
			ShowProcessData();
		}, 6);
	//创建返回按钮
	UIManager::Instance()->CreateButton(WindowsKind::mainWindow,
		750, 500, 250, 80, L"返回", [&]() {
			Return();
		}, 7);

	//创建待处理的数据图表
	UIManager::Instance()->CreateTable(mainWindow, 50,200,620,500,8);
}

