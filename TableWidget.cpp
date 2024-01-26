#include "TableWidget.h"

void TableWidget::calculateColumnWidths()
{
    columnWidths.clear();
    if (!data.empty())
    {
        columnWidths.resize(data[0].size(), 0);
        for (const auto& row : data)
        {
            for (size_t j = 0; j < row.size(); ++j)
            {
                int width = textwidth(*row[j].c_str());
                if (width > columnWidths[j])
                {
                    columnWidths[j] = width;
                }
            }
        }
    }
    int sumWidth = 0;
    for (auto it : columnWidths)
        sumWidth += it;
    for (auto& it : columnWidths)
        it = (float)it / sumWidth * width;
}

void TableWidget::scrollUp()
{
    if (scrollOffset > 0)
    {
        scrollOffset--;
    }
    if (scrollOffset < 0)
    {
        scrollOffset = 0;
    }
}

void TableWidget::scrollDown()
{
    int maxScrollOffset = data.size() - visibleRowCount;
    if (scrollOffset < maxScrollOffset)
    {
        scrollOffset++;
    }
}

void TableWidget::scroll(int mouseX, int mouseY, int wheel)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        if (wheel > 0)
        {
            scrollUp();
        }
        else if (wheel < 0) {
            scrollDown();
        }
    }
}

void TableWidget::handleMouseClick(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        int clickedRow = (mouseY - y) / rowHeight + scrollOffset;

        if (clickedRow >= 0 && clickedRow < static_cast<int>(data.size()))
        {
            selectedRow = clickedRow;
        }
        else
        {
            selectedRow = -1;
        }
    }
}

void TableWidget::draw()
{
    setbkmode(1);

    setfillcolor(WHITE);
    solidrectangle(x, y, x + width, y + height);

    setlinecolor(BLACK);
    settextstyle(12, 0, _T("Arial"));
    //计算需要绘制的行数
    int rowCount = min(visibleRowCount, static_cast<int>(data.size()));
    //绘制表头
    int headerY = y;
    int columnX = x;
    for (int j = 0; j < data[0].size(); ++j) {
        int columnWidth = columnWidths[j];
        rectangle(columnX, headerY, columnX + columnWidth, headerY + rowHeight);
        int textX = columnX + (columnWidth - textwidth(*data[0][j].c_str())) / 2;
        int textY = headerY + (rowHeight - textheight(_T("Arial"))) / 2;
        outtextxy(textX, textY, *data[0][j].c_str());
        columnX += columnWidth;
    }
    //绘制表格内容
    for (int i = 1; i < rowCount; ++i) {
        int rowY = y + i * rowHeight;
        int dataIndex = i + scrollOffset;
        columnX = x;
        for (int j = 0; dataIndex < data.size() && j < data[dataIndex].size(); ++j) {
            int columnWidth = columnWidths[j];
            bool isSelectedRow = (dataIndex == selectedRow);
            if (isSelectedRow) {
                setfillcolor(LIGHTBLUE);
                settextcolor(RED);
            }
            else {
                setfillcolor(WHITE);
                settextcolor(BLACK);
            }
            fillrectangle(columnX, rowY, columnX + columnWidth, rowY + rowHeight);
            int textX = columnX + (columnWidth - textwidth(*data[dataIndex][j].c_str())) / 2;
            int textY = rowY + (rowHeight - textheight(_T("Arial"))) / 2;
            outtextxy(textX, textY, *data[dataIndex][j].c_str());
            columnX += columnWidth;
        }
    }
    //绘制滚动条背景
    int scrollbarX = x + width;
    setfillcolor(LIGHTGRAY);
    solidrectangle(scrollbarX, y, scrollbarX + scrollbarWidth, y + height);
    //计算滑块位置和大小
    int handleX = scrollbarX;
    int handleWidth = scrollbarWidth;
    int maxHandleY = height - handleHeight;
    handleY = maxHandleY * double(scrollOffset) / (data.size() - visibleRowCount);
    //绘制滑块
    setfillcolor(DARKGRAY);
    solidrectangle(handleX, y + handleY, handleX + handleWidth, y + handleY + handleHeight);
}