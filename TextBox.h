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
    //是否被选中
    bool isSelected;
    //显示闪动条
    bool showCursor;
    int cursorPos;
    //此输入框在界面中的索引
    int index;

public:
    //初始化
    TextBox(int x, int y, int width, int height, int maxWord,int _index)
        : x(x), y(y), width(width), height(height), maxWord(maxWord), isSelected(false), showCursor(false), cursorPos(0),index(_index)
    {
    }
    //返回框中的文字
    const wstring& GetText();

    //返回此输入框的索引
    int GetInedx()
    { 
        return index;
    }

    //返回此输入框是否被选中
    bool GetSelect()
    {
        return isSelected;
    }

    //返回此输入框是否为空
    bool IsEmpty()
    {
        return text.empty();
    }

    //重置输入框
    void Clear()
    {
        SetText(L"");
    }

    //设置文字
    void SetText(const wstring& newText)
    {
        text = newText;
        cursorPos = text.length();
    }
    //绘制
    void Draw();

    //判断是否被选中
    bool CheckClick(int mouseX, int mouseY);

    //键盘输入事件
    void KeyInput(wchar_t ch);

    //更新闪动条
    void UpdateCursor();
};