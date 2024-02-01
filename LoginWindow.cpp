#include "LoginWindow.h"
//****************
//登录界面，负责用户的登录，注册以及退出
//****************

//指针初始化
LoginWindow* LoginWindow::instance = nullptr;
void LoginWindow::Login()
{
	wstring text = UIManager::Instance()->GetTextFromTextBox(0);
	wstring text02 = UIManager::Instance()->GetTextFromTextBox(1);
	char* userName = nullptr;
	char* userPassword = nullptr;
	if (text.size() > 0 && text.size() <= 20&& text02.size() > 0 && text02.size() <= 20)
	{
	/*	size_t bufferSize = 0;
		wcstombs_s(&bufferSize, nullptr, 0, text.c_str(), 0);
		std::vector<char> buffer(bufferSize + 1);
		if (wcstombs_s(&bufferSize, buffer.data(), bufferSize + 1, text.c_str(), bufferSize) == 0)
		{
			userName = buffer.data();
		}*/
		userName = SystemUtiliy::ChangeStringToChar(text);

		if (DataManager::Instance()->FindAccount(userName))
		{
			userPassword = SystemUtiliy::ChangeStringToChar(text02);

			/*size_t bufferSize = 0;
			wcstombs_s(&bufferSize, nullptr, 0, text02.c_str(), 0);
			std::vector<char> buffer(bufferSize + 1);
			if (wcstombs_s(&bufferSize, buffer.data(), bufferSize + 1, text02.c_str(), bufferSize) == 0)
			{
				userPassword = buffer.data();
			}*/

			if (DataManager::Instance()->CheckPassWord(userName, userPassword))
			{
				UIManager::Instance()->ClearTextBox();
				MessageBox(GetHWnd(), L"登录成功!", L"login", MB_OK);
				Sleep(100);
				NowWindow = mainWindow;
			}
			else
			{
				UIManager::Instance()->ClearTextBox();
				MessageBox(GetHWnd(), L"密码错误!", L"ERROR", MB_OK);
			}
		}
		else
		{
			UIManager::Instance()->ClearTextBox();
			MessageBox(GetHWnd(), L"用户名错误!", L"ERROR", MB_OK);
		}
	}
	else
	{
		UIManager::Instance()->ClearTextBox();
		MessageBox(GetHWnd(), L"输入格式错误!", L"ERROR", MB_OK);
	}
}
void LoginWindow::Register()
{
	wstring text = UIManager::Instance()->GetTextFromTextBox(0);
	wstring text02 = UIManager::Instance()->GetTextFromTextBox(1);
	if (text.size() > 0 && text.size() <= 20 && text02.size() > 0 && text02.size() <= 20)
	{
		char* userName = nullptr;
		size_t bufferSize = 0;
		wcstombs_s(&bufferSize, nullptr, 0, text.c_str(), 0);
		std::vector<char> buffer(bufferSize + 1);
		if (wcstombs_s(&bufferSize, buffer.data(), bufferSize + 1, text.c_str(), bufferSize) == 0)
		{
			userName = buffer.data();
		}
		if (DataManager::Instance()->FindAccount(userName))
		{
			UIManager::Instance()->ClearTextBox();
			MessageBox(GetHWnd(), L"用户已存在!", L"ERROR", MB_OK);
		}
		else
		{
			char* userPassword = nullptr;
			size_t bufferSize = 0;
			wcstombs_s(&bufferSize, nullptr, 0, text02.c_str(), 0);
			std::vector<char> buffer(bufferSize + 1);
			if (wcstombs_s(&bufferSize, buffer.data(), bufferSize + 1, text02.c_str(), bufferSize) == 0)
			{
				userPassword = buffer.data();
			}
			DataManager::Instance()->CreateAccount(userName,userPassword);
			UIManager::Instance()->ClearTextBox();
			MessageBox(GetHWnd(), L"注册成功!", L"REGISTER", MB_OK);
		}
	}
	else
	{
		UIManager::Instance()->ClearTextBox();
		MessageBox(GetHWnd(), L"输入错误!", L"ERROR", MB_OK);
	}

}
void LoginWindow::Exit()
{
	UINT yesno = MessageBox(GetHWnd(), L"确定退出?", L"EXIT", MB_YESNO);
	UIManager::Instance()->ClearTextBox();
	if (yesno == IDYES)
	{
		exit(0);
	}
}
LoginWindow* LoginWindow::Instance()
{
	return instance;
}

LoginWindow::LoginWindow()
{

}

LoginWindow::~LoginWindow()
{
	delete instance;
}

void LoginWindow::Init()
{
	instance = new LoginWindow();

	DataManager::Instance()->LoadAccount();
	//添加用户名输入框
	UIManager::Instance()->CreateLabel(WindowsKind::loginWindow,
		300, 100, 400, 60, L"请输入用户名");
	UIManager::Instance()->CreateTextBox(WindowsKind::loginWindow,
		300, 170, 400, 60, 20,0);
	//添加密码输入框
	UIManager::Instance()->CreateLabel(WindowsKind::loginWindow,
		300, 240, 400, 60, L"请输入密码");
	UIManager::Instance()->CreateTextBox(WindowsKind::loginWindow,
		300, 310, 400, 60, 20,1);
	//添加登录按钮
	UIManager::Instance()->CreateButton(WindowsKind::loginWindow,
		350, 400, 300, 80, L"登录", [&]() {
			Login();
		},0);
	//添加注册按钮
	UIManager::Instance()->CreateButton(WindowsKind::loginWindow,
		350, 500, 300, 80, L"注册", [&]() {
			Register();
		},1);

	//添加退出按钮
	UIManager::Instance()->CreateButton(WindowsKind::loginWindow,
		350, 600, 300, 80, L"退出", [&]() {
			Exit();
		}, 2);
}

