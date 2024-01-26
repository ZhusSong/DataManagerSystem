#include "TableWidget.h"

void TableWidget::CalculateColumnWidths()
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

void TableWidget::ScrollUp()
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

void TableWidget::ScrollDown()
{
    int maxScrollOffset = data.size() - visibleRowCount;
    if (scrollOffset < maxScrollOffset)
    {
        scrollOffset++;
    }
}

void TableWidget::Scroll(int mouseX, int mouseY, int wheel)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height && canBeSelected)
    {
        if (wheel > 0)
        {
            ScrollUp();
        }
        else if (wheel < 0) {
            ScrollDown();
        }
    }
}

void TableWidget::HandleMouseClick(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height&&canBeSelected)
    {
        int clickedRow = (mouseY - y) / rowHeight + scrollOffset;

        if (clickedRow > 0 && clickedRow < static_cast<int>(data.size()))
        {
            selectedRow = clickedRow;
        }
        else
        {
            selectedRow = -1;
        }
    }
}

void TableWidget::Draw()
{
    canBeSelected = true;
    const char* _text = nullptr;
    size_t bufferSize = 0;
    setbkmode(1);

    setfillcolor(WHITE);
    solidrectangle(x, y, x + width, y + height);

    setlinecolor(BLACK);
    settextstyle(14, 0, _T("Arial"));
    //计算需要绘制的行数
    int rowCount = min(visibleRowCount, static_cast<int>(data.size()));
    //绘制表头
    int headerY = y;
    int columnX = x;
    for (int j = 0; j < data[0].size(); ++j) {
        int columnWidth = columnWidths[j];

        //将参数中的wstring类型转换为const char*类型
        wcstombs_s(&bufferSize, nullptr, 0, data[0][j].c_str(), 0);
        std::vector<char> buffer(bufferSize + 1);
        if (wcstombs_s(&bufferSize, buffer.data(), bufferSize + 1, data[0][j].c_str(), bufferSize) == 0)
        {
            _text = buffer.data();
        }

        rectangle(columnX, headerY, columnX + columnWidth, headerY + rowHeight);
        int textX = columnX + (columnWidth - textwidth(_text)) / 2;
        int textY = headerY + (rowHeight - textheight(_T("Arial"))) / 2;
        settextcolor(BLACK);
        outtextxy(textX, textY, _text);
        columnX += columnWidth;
    }
    //绘制表格内容
    for (int i = 1; i < rowCount; ++i) {
        int rowY = y + i * rowHeight;
        int dataIndex = i + scrollOffset;
        columnX = x;
        for (int j = 0; dataIndex < data.size() && j < data[dataIndex].size(); ++j)
        {
            int columnWidth = columnWidths[j];
            bool isSelectedRow = (dataIndex == selectedRow);
            if (isSelectedRow) 
            {
                setfillcolor(LIGHTBLUE);
                settextcolor(RED);
            }
            else 
            {
                setfillcolor(WHITE);
                settextcolor(BLACK);
            }
            //将参数中的wstring类型转换为const char*类型
            wcstombs_s(&bufferSize, nullptr, 0, data[dataIndex][j].c_str(), 0);
            std::vector<char> buffer(bufferSize + 1);
            if (wcstombs_s(&bufferSize, buffer.data(), bufferSize + 1, data[dataIndex][j].c_str(), bufferSize) == 0)
            {
                _text = buffer.data();
            }

            fillrectangle(columnX, rowY, columnX + columnWidth, rowY + rowHeight);
            int textX = columnX + (columnWidth - textwidth(_text)) / 2;
            int textY = rowY + (rowHeight - textheight(_T("Arial"))) / 2;
            outtextxy(textX, textY, _text);
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

void TableWidget::DrawNewTable()
{

}
