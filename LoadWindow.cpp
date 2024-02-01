#include "LoadWindow.h"
#include "WindowsManager.h"
//指针初始化
LoadWindow* LoadWindow::instance = nullptr;
LoadWindow::LoadWindow()
{
}

LoadWindow::~LoadWindow()
{
}

void LoadWindow::DrawProgressBar()
{
	//外部进度条长度与宽度
	int barWidth = 800;
	int barHeight = 150;

	//内部进度条位置
	int barX = (getmaxx() - barWidth) / 2;
	int barY = (getmaxy() - barHeight) / 2;

	setfillcolor(RGB(rgb[COLORS::EnterColor_1].r, rgb[COLORS::EnterColor_1].g, rgb[COLORS::EnterColor_1].b)); // Set the border color to light gray
	fillroundrect(barX, barY, barX + barWidth, barY + barHeight,100,100);
	//setfillcolor();

	int filledWidth = static_cast<int>(static_cast<double>(Progress) / 100 * (barWidth ))+100;
	if (barX + filledWidth >= barX + barWidth)
	{
		filledWidth = barWidth;
	}
	
	setfillcolor(RGB(rgb[COLORS::NormalColor_1].r, rgb[COLORS::NormalColor_1].g, rgb[COLORS::NormalColor_1].b)); 
	solidroundrect(barX, barY , barX  + filledWidth, barY + barHeight ,100,100);

	settextcolor(RGB(rgb[COLORS::TextColor].r, rgb[COLORS::TextColor].g, rgb[COLORS::TextColor].b));
	settextstyle(40, 0, _T("宋体"));
	TCHAR progressText[20];
	_stprintf_s(progressText, _T("加载中: %d%%"), Progress);
	
	outtextxy(barX + barWidth / 2 - textwidth(progressText) / 2, barY + barHeight / 2 - textheight(progressText) / 2 + barHeight+20, progressText);


}

LoadWindow* LoadWindow::Instance()
{
	return instance;
}
void LoadWindow::Init()
{
	instance = new LoadWindow();
	instance ->DataCount = DataManager::Instance()->GetDataCount();

	UIManager::Instance()->CreateLabel(WindowsKind::loadWindow,
		300, 100, 400, 80, L"数据处理系统");
}

void LoadWindow::UnInit()
{
	delete instance;
}

void LoadWindow::Run()
{
	if (Progress == 100)
	{
		Sleep(300);
		NowWindow = loginWindow;
		UnInit();
		return;
	}
		DrawProgressBar();
		Progress += 100/ DataCount;
		if (Progress >= 100)
		{
			Progress = 100;
		}
		Sleep(200);

		
}
