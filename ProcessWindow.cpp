#include "ProcessWindow.h"

ProcessWindow* ProcessWindow::instance = nullptr;
//void ProcessWindow::SetMaxOrder()
//{
//	char s[10];
//	InputBox(s, 10, "Please input the max order");
//	if (sizeof(s) != 0 && SystemUtiliy::JudgementNumber(s))
//	{
//		int count = atoi(s);
//		UIManager::Instance()->ProcessSelectedData(processWindow,count);
//	}
//}
void ProcessWindow::Return()
{
	//重置选中数据
	UIManager::Instance()->SetNowProcessData();
	NowWindow = mainWindow;
	Sleep(50);
}
//void ProcessWindow::SmoothnessData()
//{
//
//}
//void ProcessWindow::RemovalData()
//{
//
//}
//void ProcessWindow::Cancel()
//{
//
//}
//void ProcessWindow::ShowDifferent()
//{
//
//}
void ProcessWindow::Save()
{
	bool s = false;
	UINT yesno = MessageBox(GetHWnd(), L"保存此数据?", L"SAVE", MB_YESNO);
	if (yesno == IDYES)
	{
		s =DataManager::Instance()->SaveProcessData();
	}
	if (s)
	{
		MessageBox(GetHWnd(), L"保存成功!", L"SAVE", MB_OK);
	}
	else
	{
		MessageBox(GetHWnd(), L"保存失败！", L"SAVE", MB_OK);
	}
}
ProcessWindow* ProcessWindow::Instance()
{
	return instance;
}

ProcessWindow::ProcessWindow()
{

}

ProcessWindow::~ProcessWindow()
{

	delete instance;
}

void ProcessWindow::Init()
{
	instance = new ProcessWindow();

	

	//UIManager::Instance()->CreateButton(WindowsKind::processWindow,
	//	50, 410, 350, 50, L"SetMaxOrder", [&]() {
	//		SetMaxOrder();
	//	}, 0);
	//创建保存按钮
	UIManager::Instance()->CreateButton(WindowsKind::processWindow,
		50, 470, 350, 50, L"保存", [&]() {
			Save();
		}, 1);

	//创建平滑按钮
	//UIManager::Instance()->CreateButton(WindowsKind::processWindow,
	//	10, 410, 400, 50, L"SmoothnessData", [&]() {
	//		SmoothnessData();
	//	}, 1);

	////添加去除离散值按钮
	//UIManager::Instance()->CreateButton(WindowsKind::processWindow,
	//	10, 470, 400, 50, L"RemovalData", [&]() {
	//		RemovalData();
	//	}, 2);

	////添加撤销
	//UIManager::Instance()->CreateButton(WindowsKind::processWindow,
	//	10, 530, 400, 50, L"Cancel", [&]() {
	//		Cancel();
	//	}, 3);

	//创建返回按钮
	UIManager::Instance()->CreateButton(WindowsKind::processWindow,
		50, 530, 350, 50, L"返回", [&]() {
			Return();
		}, 2);






}

