#include "TextBox.h"
void TextBox::Draw()
{
    setfillcolor(WHITE);
    if (isSelected)
    {
        setlinecolor(RGB(0, 120, 215));
        fillrectangle(x, y, x + width, y + height);
    }
    else
    {
        setlinecolor(RGB(122, 122, 122));
        fillrectangle(x, y, x + width, y + height);
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

    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(height * 3 / 4, 0, _T("宋体"));

    outtextxy(x + 5, y + (height - textheight(_T("宋体"))) / 2,  *text.c_str());

    setlinecolor(BLACK);
    if (isSelected && showCursor)
    {
        int cursorX = x + 5 + textwidth(*text.substr(0, cursorPos).c_str());
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