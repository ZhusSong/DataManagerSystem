#include "UIManager.h"


//指针初始化
UIManager* UIManager::instance = nullptr;

UIManager::UIManager()
{
  
}

UIManager::~UIManager()
{
    delete instance;
}

void UIManager::ShowFileInfo()
{
    settextstyle(30, 0, _T("宋体"));   
    int textX = 50;
    int textY = 590;
    settextcolor(RGB(rgb[COLORS::TextColor].r, rgb[COLORS::TextColor].g, rgb[COLORS::TextColor].b));
    wstring text = L"FileName: ";
    text +=DataManager::Instance()->GetSelectedData(nowProcessData).filename;

    wstring text2 = L"Mean is: ";
    text2 += to_wstring(DataManager::Instance()->GetSelectedData(nowProcessData).Nmean);

    wstring text3 = L"Variance is: ";
    text3 += to_wstring(DataManager::Instance()->GetSelectedData(nowProcessData).Nvar);



    char* _text = SystemUtiliy::ChangeStringToChar(text);
    char* _text2 = SystemUtiliy::ChangeStringToChar(text2);
    char* _text3 = SystemUtiliy::ChangeStringToChar(text3);

    outtextxy(textX, textY, text.c_str());
     textX = 50;
     textY = 630;
    outtextxy(textX, textY, text2.c_str());
     textX = 50;
     textY = 670;
    outtextxy(textX, textY, text3.c_str());

    delete(_text);
    delete(_text2);
    delete(_text3);
}
void UIManager::SetNewTable(WindowsKind kind)
{
    //两个列表，一个用于初始化表头并结合成总数据，一个用于接收自DataManager获取的数据
    vector<vector<wstring>> newList;
    vector<vector<wstring>> newList2;
    for (auto iter = tables.begin(); iter != tables.end(); iter++)
    {
        if (iter->kind == mainWindow)
        {
            //为图表添加表头
            newList.push_back({ L"文件名",L"行数",L"均值" ,L"方差" });
            
            newList2 = DataManager::Instance()->GetInitialData();
            for (const auto& innerVector : newList2)
            {
                newList.push_back(innerVector);
            }
            iter->table->SetData(newList);
            //重置图表
            iter->table->ResetTable();
            newList.clear();
            newList2.clear();
        }
        if (iter->kind == showProcessWindow)
        {
            //为图表添加表头
            newList.push_back({ L"文件名",L"行数",L"均值" ,L"方差",L"最大拟合阶数" });
            newList2 = DataManager::Instance()->GetPolyfitData();
            for (const auto& innerVector : newList2)
            {
                newList.push_back(innerVector);
            }
            iter->table->SetData(newList);
            iter->table->ResetTable();

            newList.clear();
            newList2.clear();

        }
    }
}


UIManager* UIManager::Instance()
{
    return instance;
}

void UIManager::CreatePage()
{

}

void UIManager::CreateButton(WindowsKind index, int x, int y, int width, int height, const wstring& text, const function<void()>& onClick,int number)
{
    Button* button = new Button(x, y, width, height, text,onClick,number);
    AddButton(index, button);
}

void UIManager::CreateTextBox(WindowsKind index, int x, int y, int width, int height, int maxWord, int number)
{
    TextBox* textBox = new TextBox(x, y, width, height, maxWord, number);
    AddTextBox(index, textBox);
}

void UIManager::ClearTextBox()
{
    for (auto iter = textBoxs.begin(); iter != textBoxs.end(); iter++)
    {
        iter->textBox->Clear();
    }
}

void UIManager::CreateLabel(WindowsKind index, int x, int y, int width, int height, const std::wstring& text)
{
    Label* label = new Label(x, y, width, height, text);
    AddLabel(index,label);
}

void UIManager::CreateTable(WindowsKind index, int x, int y, int width, int height, int visibleRowCount)
{
    TableWidget* table = new TableWidget(x, y, width, height, visibleRowCount);

    vector<vector<wstring>> newList;
    vector<vector<wstring>> newList2;

    switch (index)
    {
    case mainWindow:
        //为主界面的图表设置表头
        newList.push_back({ L"文件名",L"行数",L"均值" ,L"方差" });
        newList2 = DataManager::Instance()->GetInitialData();
        for (const auto& innerVector : newList2)
        {
            newList.push_back(innerVector);
        }
        table->SetData(newList);
        newList.clear();
        newList2.clear();
        break;
    case showProcessWindow:
        //为主界面的图表设置表头
        newList.push_back({ L"文件名",L"行数",L"均值" ,L"方差",L"最大拟合阶数" });
        newList2 = DataManager::Instance()->GetPolyfitData();
        for (const auto& innerVector : newList2)
        {
            newList.push_back(innerVector);
        }
        table->SetData(newList);
        break;
    default:
        break;
    }
    AddTable(index, table);
}

 wstring UIManager::GetTextFromTextBox(int index) const
{
    for (auto iter = textBoxs.begin(); iter != textBoxs.end(); iter++)
    {
        if (iter->kind == NowWindow&& iter->textBox->GetInedx()== index)
        {
            return iter->textBox->GetText();
        }
    }

}

void UIManager::AddPage(IMAGE* page)
{
    pages.push_back(page);
   
}

void UIManager::AddButton(WindowsKind index, Button* button)
{
        buttons.push_back({ index, button });
}

void UIManager::AddTextBox(WindowsKind index, TextBox* textBox)
{
        textBoxs.push_back({index, textBox });
}

void UIManager::AddLabel(WindowsKind index, Label* label)
{

    labels.push_back({index, label});
    
}

void UIManager::AddTable(WindowsKind index, TableWidget* _table)
{
    tables.push_back({index,_table});
}


//事件处理，向每一个有对应事件的成员进行广播，并由其单独处理事件
void UIManager::MouseClick(int mouseX, int mouseY)
{
    for (auto iter = textBoxs.begin(); iter != textBoxs.end(); iter++)
    {
        if (iter->kind == NowWindow)
        {
            iter->textBox->CheckClick(mouseX, mouseY);
        }
    }
    for (auto iter = buttons.begin(); iter != buttons.end(); iter++)
    {
        if (iter->kind == NowWindow)
        {
            iter->button->CheckClick(mouseX, mouseY);
        }
    }
    for (auto iter = tables.begin(); iter != tables.end(); iter++)
    {
        if (iter->kind == NowWindow)
        {
            iter->table->HandleMouseClick(mouseX, mouseY);
        }
    }
}

void UIManager::MouseMove(int mouseX, int mouseY)
{
    for (auto iter = buttons.begin(); iter != buttons.end(); iter++)
    {
        if (iter->kind == NowWindow)
        {
            iter->button->CheckMouseOver(mouseX,mouseY);
        }
    }
}

void UIManager::MouseWheel(int mouseX, int mouseY, int wheel)
{
    for (auto iter = tables.begin(); iter != tables.end(); iter++)
    {
        if (iter->kind == NowWindow)
        {
            iter->table->Scroll(mouseX, mouseY,wheel);
        }
    }
}

void UIManager::KeyInput(wchar_t ch)
{
    //判断输入字符是否是英文字母或数字或操作符，若不是，则弹出错误提示框
    if (iswalpha(ch) || iswdigit(ch)|| ch == L'\n' || ch == L'\b' || ch == '\r')
    {
        for (auto iter = textBoxs.begin(); iter != textBoxs.end(); iter++)
        {
            if (iter->textBox->GetSelect())
            {
                iter->textBox->KeyInput(ch);
            }
        }
    }
    else
    {
        MessageBox(GetHWnd(), L"输入格式错误!",L"ERROR",MB_OK);
    }
}
void UIManager::DeleteSelectedData(WindowsKind kind)
{
    int nowData = -1;
    //得到选中数据
    for (auto iter = tables.begin(); iter != tables.end(); iter++)
    {
        if (iter->kind == kind)
        {
            nowData = iter->table->GetSelectedRow();
        }
    }
    //若成功删除数据，则重置图表
    if (DataManager::Instance()->DeleteData(nowData))
    {
        for (auto iter = tables.begin(); iter != tables.end(); iter++)
        {
            if (iter->kind == kind)
            {
                vector<vector<wstring>> newList;
                vector<vector<wstring>> newList2;
                newList.push_back({ L"文件名",L"行数",L"均值" ,L"方差" });
                newList2 = DataManager::Instance()->GetInitialData();
                for (const auto& innerVector : newList2)
                {
                    newList.push_back(innerVector);
                }
                iter->table->SetData(newList);
                iter->table->ResetTable();
            }
        }
    }
    else
    {
        MessageBox(GetHWnd(), L"删除失败!", L"DELETE", MB_OK);
    }
}
void UIManager::ProcessSelectedData(WindowsKind kind,int maxorder)
{   
    maxOrder = maxorder;
    if (nowProcessData == -1)
    {
        //得到选中数据
        for (auto iter = tables.begin(); iter != tables.end(); iter++)
        {
            if (iter->kind == kind)
            {
                nowProcessData = iter->table->GetSelectedRow();
                if (nowProcessData == -1)
                {
                    MessageBox(GetHWnd(), L"请选择数据!", L"ERROR", MB_OK);
                }
            }
        }
    }
    DataManager::Instance()->ProcessData(nowProcessData, maxOrder);

}
void UIManager::SetNowProcessData()
{
    nowProcessData = -1;
}

void UIManager::Init()
{
    instance = new UIManager();
}

void UIManager::Run()
{

    //easyX鼠标事件
    ExMessage msg;
    if (peekmessage(&msg)&& NowWindow!= loadWindow)
    {
        switch (msg.message)
        {
        case WM_LBUTTONDOWN:
            UIManager::Instance()->MouseClick(msg.x, msg.y);
            break;
        case WM_MOUSEMOVE:
            UIManager::Instance()->MouseMove(msg.x, msg.y);
            break;
        case WM_MOUSEWHEEL:
            UIManager::Instance()->MouseWheel(msg.x, msg.y, msg.wheel);
            break;
        case WM_CHAR:
            UIManager::Instance()->KeyInput(msg.ch);
            break;
        }
    }

         //根据当前界面判断运行哪一处的UI控件事件
        switch (NowWindow)
        {
        case loadWindow:
            for (auto iter = labels.begin(); iter != labels.end(); iter++)
            {
                if (iter->kind == loadWindow)
                {
                    iter->label->Draw();
                }
            }
            break;
        case loginWindow:
            for (auto iter = labels.begin(); iter != labels.end(); iter++)
            {
                if (iter->kind == loginWindow)
                {
                    iter->label->Draw();
                }
            }
            for (auto iter = textBoxs.begin(); iter != textBoxs.end(); iter++)
            {
                if (iter->kind == loginWindow)
                {
                    if (iter->textBox->GetSelect())
                    {
                        iter->textBox->UpdateCursor();
                    }
                    iter->textBox->Draw();
                }
            }
            for (auto iter = buttons.begin(); iter != buttons.end(); iter++)
            {
                if (iter->kind == loginWindow)
                {
                    iter->button->Draw();
                }
            }
            break;
        case mainWindow:
            for (auto iter = buttons.begin(); iter != buttons.end(); iter++)
            {
                if (iter->kind == mainWindow)
                {
                    iter->button->Draw();
                }
            }
            for (auto iter = tables.begin(); iter != tables.end(); iter++)
            {
                if (iter->kind == mainWindow)
                {
                    iter->table->Draw();
                }
            }
            break;  
        case processWindow:
             clearrectangle(50, 400, 440, 800);
             ShowFileInfo();
             for (auto iter = buttons.begin(); iter != buttons.end(); iter++)
             {
                if (iter->kind == processWindow)
                {
                   iter->button->Draw();
                 }
             }
             break;
        case showProcessWindow:
            for (auto iter = tables.begin(); iter != tables.end(); iter++)
            {
                if (iter->kind == showProcessWindow)
                {
                    iter->table->Draw();
                }
            }
            for (auto iter = buttons.begin(); iter != buttons.end(); iter++)
            {
                if (iter->kind == showProcessWindow)
                {
                    iter->button->Draw();
                }
            }
                break;
        default:
            break;
    }

}


