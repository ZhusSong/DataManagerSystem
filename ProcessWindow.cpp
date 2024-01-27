#include "ProcessWindow.h"

ProcessWindow* ProcessWindow::instance = nullptr;
ProcessWindow* ProcessWindow::Instance()
{
	return instance;
}

ProcessWindow::ProcessWindow()
{

}

ProcessWindow::~ProcessWindow()
{

}

void ProcessWindow::Init()
{
	instance = new ProcessWindow();

}

void ProcessWindow::Run()
{
}
