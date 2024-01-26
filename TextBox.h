#pragma once
#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include "SystemConstant.h"
#include <windows.h>
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
    int index;

public:
    TextBox(int x, int y, int width, int height, int maxWord,int _index)
        : x(x), y(y), width(width), height(height), maxWord(maxWord), isSelected(false), showCursor(false), cursorPos(0),index(_index)
    {
    }

    const wstring& GetText();
    int GetInedx()
    { 
        return index;
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