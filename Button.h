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
    float scale;
    int index ;
    bool isMouseOver;
    bool isMouseClick;
    wstring text;
    function<void()> onClick;

public:
    Button(int x, int y, int width, int height, const wstring& text, const function<void()>& onClick,int index)
        : x(x), y(y), width(width), height(height), text(text), onClick(onClick), scale(1.0f), isMouseOver(false), isMouseClick(false),index(-1)
    {
    }

    void CheckMouseOver(int mouseX, int mouseY);

    bool CheckClick(int mouseX, int mouseY);

    void Draw();
};