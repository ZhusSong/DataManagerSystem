#include "Button.h"
void Button::CheckMouseOver(int mouseX, int mouseY)
{
    isMouseOver = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);

    if (isMouseOver) {
        scale = 0.9f;
    }
    else {
        scale = 1.0f;
    }
}

bool Button::CheckClick(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        onClick();
        isMouseOver = false;
        scale = 1.0f;
        return true;
    }
    return false;
}

void Button::Draw()
{
    int scaledWidth = width * scale;
    int scaledHeight = height * scale;
    int scaledX = x + (width - scaledWidth) / 2;
    int scaledY = y + (height - scaledHeight) / 2;

    if (isMouseOver)
    {
        setlinecolor(RGB(0, 120, 215));
        setfillcolor(RGB(229, 241, 251));

    }
    else
    {
        setlinecolor(RGB(173, 173, 173));
        setfillcolor(RGB(225, 225, 225));
    }

    //将参数中的wstring类型转换为const char*类型
    const char* _text = nullptr;
    size_t bufferSize = 0;
    wcstombs_s(&bufferSize, nullptr, 0, text.c_str(), 0);
    std::vector<char> buffer(bufferSize + 1);
    if (wcstombs_s(&bufferSize, buffer.data(), bufferSize + 1, text.c_str(), bufferSize) == 0)
    {
        _text = buffer.data();
    }

    fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight);
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(20 * scale, 0, _T("宋体"));
    int textX = scaledX + (scaledWidth - textwidth(_text)) / 2;
    int textY = scaledY + (scaledHeight - textheight(_T("宋体"))) / 2;
    outtextxy(textX, textY, _text);
}

