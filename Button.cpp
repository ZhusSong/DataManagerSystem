#include "Button.h"
void Button::CheckMouseOver(int mouseX, int mouseY)
{
    //判断鼠标位置是否在此按钮范围内
    isMouseOver = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);

    if (isMouseOver) 
    {
        scale = 0.95f;
    }
    else 
    {
        isMouseClick =false;
        scale = 1.0f;
    }
}

bool Button::CheckClick(int mouseX, int mouseY)
{
    //判断鼠标的点击是否在此按钮内
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        isMouseClick = true;
        onClick();
        isMouseOver = false;
        scale = 0.9f;
        return true;
    }
    return false;
}

void Button::Draw()
{
    //计算此按钮的大小
    int scaledWidth = width * scale;
    int scaledHeight = height * scale;
    int scaledX = x + (width - scaledWidth) / 2;
    int scaledY = y + (height - scaledHeight) / 2;

    //根据是否有鼠标事件绘制颜色
    if (isMouseOver)
    {
        setlinecolor(BLUE);
        setfillcolor(RGB(rgb[COLORS::EnterColor_1].r, rgb[COLORS::EnterColor_1].g, rgb[COLORS::EnterColor_1].b));
    }
    else if(isMouseClick)
    {
        setlinecolor(YELLOW);
        setfillcolor(RGB(rgb[COLORS::ClickColor_1].r, rgb[COLORS::ClickColor_1].g, rgb[COLORS::ClickColor_1].b));

    }
    else 
    {
        setlinecolor(BLACK);
        setfillcolor(RGB(rgb[COLORS::NormalColor_1].r, rgb[COLORS::NormalColor_1].g, rgb[COLORS::NormalColor_1].b));

    }

    //将参数中的wstring类型转换为const char*类型，以便easyX的函数使用
    const char* _text = nullptr;
    size_t bufferSize = 0;
    wcstombs_s(&bufferSize, nullptr, 0, text.c_str(), 0);
    std::vector<char> buffer(bufferSize + 1);
    if (wcstombs_s(&bufferSize, buffer.data(), bufferSize + 1, text.c_str(), bufferSize) == 0)
    {
        _text = buffer.data();
    }

    //绘制按钮
    fillroundrect(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight,50,50);
    settextcolor(RGB(rgb[COLORS::TextColor].r, rgb[COLORS::TextColor].g, rgb[COLORS::TextColor].b));
    setbkmode(TRANSPARENT);
    settextstyle(30 * scale, 0, _T("Arial"));
    int textX = scaledX + (scaledWidth - textwidth(_text)) / 2;
    int textY = scaledY + (scaledHeight - textheight(_T("Arial"))) / 2;
    outtextxy(textX, textY, _text);
}

