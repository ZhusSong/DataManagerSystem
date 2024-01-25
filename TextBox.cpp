#include "TextBox.h"
void TextBox::Draw()
{
    if (isSelected)
    {
        setfillcolor(RGB(rgb[COLORS::ClickColor_1].r, rgb[COLORS::ClickColor_1].g, rgb[COLORS::ClickColor_1].b));
        setlinecolor(BLUE);
        fillrectangle(x, y, x + width, y + height);
    }
    else
    {
        setfillcolor(RGB(rgb[COLORS::NormalColor_1].r, rgb[COLORS::NormalColor_1].g, rgb[COLORS::NormalColor_1].b));
        setlinecolor(BLACK);
        fillrectangle(x, y, x + width, y + height);
    }

    //将参数中的wstring类型转换为const char*类型
    const char* _text = nullptr;
    const char* _text02 = nullptr;
    size_t bufferSize = 0;
    size_t bufferSize2 = 0;
    wcstombs_s(&bufferSize, nullptr, 0, text.c_str(), 0);
    wcstombs_s(&bufferSize2, nullptr, 0, text.substr(0, cursorPos).c_str(), 0);
    std::vector<char> buffer(bufferSize + 1);
    std::vector<char> buffer2(bufferSize2 + 1);
    if (wcstombs_s(&bufferSize, buffer.data(), bufferSize + 1, text.c_str(), bufferSize) == 0)
    {
        _text = buffer.data();
    }
    if (wcstombs_s(&bufferSize2, buffer2.data(), bufferSize2 + 1, text.substr(0, cursorPos).c_str(), bufferSize2) == 0)
    {
        _text02 = buffer.data();
    }
    settextcolor(RGB(rgb[COLORS::TextColor].r, rgb[COLORS::TextColor].g, rgb[COLORS::TextColor].b));
    setbkmode(TRANSPARENT);
    settextstyle(height * 3 / 4, 0, _T("Arial"));

    outtextxy(x + 5, y + (height - textheight(_T("Arial"))) / 2, _text);

    setlinecolor(BLACK);
    if (isSelected && showCursor)
    {
        int cursorX = x + 5 + textwidth(_text02);
        line(cursorX, y + 2 + height / 8, cursorX, y + height * 7 / 8 - 2);
    }
}

bool TextBox::CheckClick(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        isSelected = true;
        return true;
    }
    else
    {
        isSelected = false;
        cursorPos = text.length();
        return false;
    }
}

void TextBox::KeyInput(wchar_t ch)
{
    if (isSelected)
    {
       switch (ch)
        {
        case '\b':
            if (!text.empty() && cursorPos > 0) {
                text.erase(cursorPos - 1, 1);
                cursorPos--;
            }
            break;
        case '\r':
        case '\n':
            cursorPos = text.length();
            isSelected = false;
            break;
        default:
            if (text.length() < maxWord) {
                text.insert(cursorPos, 1, ch);
                cursorPos++;
            }
        }
    }
}

void TextBox::UpdateCursor()
{
    static DWORD lastTick = GetTickCount();
    DWORD currentTick = GetTickCount();
    if (currentTick - lastTick >= 500)
    {
        showCursor = !showCursor;
        lastTick = currentTick;
    }
}