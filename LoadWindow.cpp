#include "LoadWindow.h"

//指针初始化
LoadWindow* LoadWindow::instance = nullptr;
LoadWindow::LoadWindow()
{
}

LoadWindow::~LoadWindow()
{
	delete instance;
}

void LoadWindow::DrawProgressBar()
{
	// Clear the screen
	cleardevice();
	int barWidth = 800;
	int barHeight = 150;

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
	settextstyle(40, 0, _T("Arial"));
	TCHAR progressText[20];
	_stprintf_s(progressText, _T("Loading: %d%%"), Progress);
	//
	outtextxy(barX + barWidth / 2 - textwidth(progressText) / 2, barY + barHeight / 2 - textheight(progressText) / 2 + barHeight+20, progressText);

//	outtextxy(barX + barWidth / 2 - textwidth(progressText) / 2, barY + barHeight / 2 - textheight(progressText) / 2, progressText);

	// Render the graphics
	FlushBatchDraw();


	EndBatchDraw();
}

LoadWindow* LoadWindow::Instance()
{
	return instance;
}
void LoadWindow::Init()
{
	instance = new LoadWindow();
}

void LoadWindow::Run()
{
	while (Progress <= 100) {
		DrawProgressBar();
		Sleep(200); // Optional delay to slow down the progress for demonstration purposes
		Progress += 5; // You can adjust the increment to control the speed of progress
	}
		
}
