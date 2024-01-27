#include "UIManager.h"


//指针初始化
UIManager* UIManager::instance = nullptr;

UIManager::UIManager()
{
  
}

UIManager::~UIManager()
{
}

void UIManager::SetNewTable(WindowsKind kind)
{
    for (auto iter = tables.begin(); iter != tables.end(); iter++)
    {
        if (iter->kind == kind)
        {
            //两个列表，一个用于初始化表头并结合成总数据，一个用于接收自DataManager获取的数据
            vector<vector<wstring>> newList;
            vector<vector<wstring>> newList2;
            //为图表添加表头
            newList.push_back({ L"name",L"rowCount",L"mean" ,L"variance" });
            
            newList2 = DataManager::Instance()->GetInitialData();
            for (const auto& innerVector : newList2)
            {
                newList.push_back(innerVector);
            }
            iter->table->SetData(newList);
            //重置图表
            iter->table->ResetTable();
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
        newList.push_back({ L"name",L"rowCount",L"mean" ,L"variance" });
        newList2 = DataManager::Instance()->GetInitialData();
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
        MessageBox(GetHWnd(), "Input Error!","error",MB_OK);
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
                newList.push_back({ L"name",L"rowCount",L"mean" ,L"variance" });
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
        MessageBox(GetHWnd(), "Failed!", "DELETE", MB_OK);
    }
}
void UIManager::Init()
{
    instance = new UIManager();
}

//
void UIManager::Run()
{
    //easyX鼠标事件
    ExMessage msg;
    if (peekmessage(&msg))
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
            cleardevice();
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
            cleardevice();
            for (auto iter = labels.begin(); iter != labels.end(); iter++)
            {
                if (iter->kind == mainWindow)
                {
                    iter->label->Draw();
                }
            }
            for (auto iter = textBoxs.begin(); iter != textBoxs.end(); iter++)
            {
                if (iter->kind == mainWindow)
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
                cleardevice();
                for (auto iter = labels.begin(); iter != labels.end(); iter++)
                {
                    if (iter->kind == mainWindow)
                    {
                        iter->label->Draw();
                    }
                }
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
        case showProcessWindow:
                break;
        default:
            break;
    }
}
