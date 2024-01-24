#include "Label.h"

void Label::SetText(const std::wstring& newText)
{
    text = newText;

}

void Label::Draw()
{
    settextcolor(RGB(rgb[COLORS::TextColor].r, rgb[COLORS::TextColor].g, rgb[COLORS::TextColor].b));
    setbkmode(TRANSPARENT);

    //将参数中的wstring类型转换为const char*类型
    const char* _text=nullptr;
    size_t bufferSize = 0;
    wcstombs_s(&bufferSize, nullptr, 0, text.c_str(), 0);
    std::vector<char> buffer(bufferSize + 1);
    if (wcstombs_s(&bufferSize, buffer.data(), bufferSize + 1, text.c_str(), bufferSize) == 0)
    {
        _text = buffer.data();
    }

    settextstyle(height * 0.8, 0, _T("宋体"));
    int textX = x + (width - textwidth(_text)) / 2;
    int textY = y + (height - textheight(_T("宋体"))) / 2;
    outtextxy(textX, textY, _text);
}