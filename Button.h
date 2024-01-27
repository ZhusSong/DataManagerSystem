#pragma once
#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include "SystemConstant.h"
using namespace std;
class Button
{
private:
    int x;
    int y;
    int width;
    int height;
    //按钮大小
    float scale;
    //按钮在界面中的索引
    int index ;
    //是否被鼠标覆盖
    bool isMouseOver;
    //是否被点击
    bool isMouseClick;
    //显示的文字
    wstring text;
    //点击事件
    function<void()> onClick;

public:
    //初始化，同时赋予参数初值
    Button(int x, int y, int width, int height, const wstring& text, const function<void()>& onClick,int index)
        : x(x), y(y), width(width), height(height), text(text), onClick(onClick), scale(1.0f), isMouseOver(false), isMouseClick(false),index(-1)
    {
    }

    //判断是否被鼠标覆盖
    void CheckMouseOver(int mouseX, int mouseY);

    //判断是否被鼠标点击
    bool CheckClick(int mouseX, int mouseY);

    void Draw();
};