#include "MainWindow.h"

//指针初始化
MainWindow* MainWindow::instance = nullptr;
void MainWindow::AddNewData()
{
	char s[10];
	InputBox(s,10, "Please input the data count");
	if (sizeof(s) != 0 && JudgementNumber(s))
	{
		int count = atoi(s);
		if (count > 2000)
		{
			count = 2000;
		}
		if (count > 0)
		{
			/*UINT yesno = MessageBox(GetHWnd(), "If you want to create random data?", "CREATE", MB_YESNO);
			if (yesno == IDYES)
			{
				char n[20];
				InputBox(n, 20, "Please input data's name,use english,numbers or _");
				DataManager::Instance()->CreateRandomData(n,count);
			}*/
			//创建messageBox显示文字
			wstring n=L"Create ";
			n+= DataManager::Instance()->CreateRandomData(count);
			n += L".txt successful!";
			int size = WideCharToMultiByte(CP_UTF8, 0, n.c_str(), -1, NULL, 0, NULL, NULL);
			char* buffer = new char[size];
			WideCharToMultiByte(CP_UTF8, 0, n.c_str(), -1, buffer, size, NULL, NULL);
			LPCSTR lpcstr = buffer;
			UINT yesno = MessageBox(GetHWnd(), lpcstr, "CREATE", MB_OK);
			//刷新图表
			UIManager::Instance()->SetNewTable(mainWindow);
		}
	}
	else
	{
		UINT yesno = MessageBox(GetHWnd(), "Please input numbers!", "ERROR", MB_YESNO);
		if (yesno == IDYES)
		{
			AddNewData();
		}
		else
		{
			return;
		}
	}

}

bool MainWindow::JudgementNumber(char* s)
{
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(s[i]))
			return false;
	}
	return true;

}

void MainWindow::DeleteData()
{
	UINT yesno = MessageBox(GetHWnd(),"Sure to delete this data?","DELETE",MB_YESNO);
	if (yesno == IDYES)
	{
		UIManager::Instance()->DeleteSelectedData(0);
	}
}
void MainWindow::ProcessData() 
{

}
void MainWindow::ShowProcessData()
{

}
void MainWindow::Return()
{
	NowWindow = loginWindow;
	cleardevice();
}
MainWindow* MainWindow::Instance()
{
	return nullptr;
}

void MainWindow::Init()
{
	instance = new MainWindow();
	//创建分析按钮
	UIManager::Instance()->CreateButton(3,
		200, 100, 200, 80, L"Process", [&]() {
			ProcessData();
		}, 3);
	//创建添加新数据按钮
	UIManager::Instance()->CreateButton(4,
		750, 200, 250, 80, L"AddNewData", [&]() {
			AddNewData();
		}, 4);
	//创建删除数据按钮
	UIManager::Instance()->CreateButton(5,
		750, 300, 250, 80, L"DeleteData", [&]() {
			DeleteData();
		}, 5);
	//创建显示已处理数据按钮
	UIManager::Instance()->CreateButton(6,
		750, 400, 250, 80, L"ShowProcessData", [&]() {
			ShowProcessData();
		}, 6);
	//创建返回按钮
	UIManager::Instance()->CreateButton(7,
		750, 500, 250, 80, L"Return", [&]() {
			Return();
		}, 7);

	//创建待处理的数据图表
	UIManager::Instance()->CreateTable(0,150,200,500,500,8);
}

void MainWindow::Run()
{

}
