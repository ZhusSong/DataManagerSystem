#pragma once
#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class TextBox
{
private:
    int x;
    int y;
    int width;
    int height;
    int maxWord;
    wstring text;
    bool isSelected;
    bool showCursor;
    int cursorPos;

public:
    TextBox(int x, int y, int width, int height, int maxWord)
        : x(x), y(y), width(width), height(height), maxWord(maxWord), isSelected(false), showCursor(false), cursorPos(0)
    {
    }

    const wstring& GetText() const
    {
        return text;
    }

    bool GetSelect() const
    {
        return isSelected;
    }

    bool IsEmpty() const
    {
        return text.empty();
    }

    void Clear()
    {
        SetText(L"");
    }

    void SetText(const wstring& newText)
    {
        text = newText;
        cursorPos = text.length();
    }

    void Draw();

    bool CheckClick(int mouseX, int mouseY);

    void KeyInput(wchar_t ch);

    void UpdateCursor();
};