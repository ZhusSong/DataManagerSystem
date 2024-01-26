#pragma once
#include <graphics.h>
#include <string>
#include <vector>
using namespace std;

class TableWidget {
private:
    int x;
    int y;
    int width;
    int height;
    //最大可见行数
    int visibleRowCount;
    //行高度
    int rowHeight;
    int scrollOffset;
    vector<vector<wstring>> data;
    //列宽度
    vector<int> columnWidths;
    //被选中的行
    int selectedRow;
    int scrollbarWidth;
    int handleHeight;
    int handleY;
    bool canBeSelected;

public:
    TableWidget(int x, int y, int width, int height, int visibleRowCount)
        : x(x), y(y), width(width), height(height), visibleRowCount(visibleRowCount) {
        data = { {} };
        rowHeight = height / visibleRowCount;
        selectedRow = -1;
        scrollOffset = 0;
        scrollbarWidth = 20;
        handleHeight = 30;
        handleY = 0; 
        canBeSelected = false;
    }

    int GetSelectedRow() const
    {
        return selectedRow;
    }

    wstring GetSelectedInfo(int col) const
    {
        return data[selectedRow][col];
    }

    void SetData(const vector<vector<wstring>> newData)
    {
        data = newData;
        CalculateColumnWidths();
    }

    void CalculateColumnWidths();

    void ScrollUp();

    void ScrollDown();

    void Scroll(int mouseX, int mouseY, int wheel);

    void HandleMouseClick(int mouseX, int mouseY);

    void Draw();
    //重新绘制
    void DrawNewTable();
};
