#include "TextBox.h"

void TextBox::SetText(const std::wstring& newText)
{
    text = newText;
}

void TextBox::Draw()
{
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(height * 0.8, 0, _T("‘v‘Ì"));
    int textX = x + (width - textwidth(*text.c_str())) / 2;
    int textY = y + (height - textheight(_T("‘v‘Ì"))) / 2;
    outtextxy(textX, textY, *text.c_str());
}