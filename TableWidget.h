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
    //数据值，需注意在初始化时在最初给与表头要显示的数据
    vector<vector<wstring>> data;
    //列宽度
    vector<int> columnWidths;
    //被选中的行
    int selectedRow;
    //滑块属性
    int scrollbarWidth;
    int handleHeight;
    int handleY;
    bool canBeSelected;

public:
    //初始化
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

    //返回选中的行序号
    int GetSelectedRow() const
    {
        return selectedRow;
    }
    //返回选中的数据值
    wstring GetSelectedInfo(int col) const
    {
        return data[selectedRow][col];
    }
    //设置图表显示的数据，可用于重置图表
    void SetData(const vector<vector<wstring>> newData)
    {
        data = newData;
        CalculateColumnWidths();
    }

    //计算宽度
    void CalculateColumnWidths();

    //向上滚动
    void ScrollUp();

    //向下滚动
    void ScrollDown();

    //滑动事件
    void Scroll(int mouseX, int mouseY, int wheel);

    //鼠标点击事件
    void HandleMouseClick(int mouseX, int mouseY);

    void Draw();
    //重置图表状态
    void ResetTable();
};
