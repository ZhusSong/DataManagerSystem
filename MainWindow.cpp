#include "MainWindow.h"

//指针初始化
MainWindow* MainWindow::instance = nullptr;
MainWindow* MainWindow::Instance()
{
	return nullptr;
}

void MainWindow::Init()
{
	instance = new MainWindow();

	UIManager::Instance()->CreateTable(mainWindow,100,100,500,500,10);
}

void MainWindow::Run()
{

}
