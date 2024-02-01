#pragma once
#include <graphics.h>
#include <easyx.h>
#include <string>
#include "SystemConstant.h"
#include <vector>

class Label {
private:
    int x;
    int y;
    int width;
    int height;
    std::wstring text;

public:
    Label(int x, int y, int width, int height, const std::wstring& text)
        : x(x), y(y), width(width), height(height), text(text) {
}

    void SetText(const std::wstring& newText);

    void Draw();
};