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
}

void ShowProcessWindow::Init()
{
	instance = new ShowProcessWindow();
}

void ShowProcessWindow::Run()
{
}
