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
        if (iter->first == kind)
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
            iter->second->SetData(newList);
            //重置图表
            iter->second->ResetTable();
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

void UIManager::CreateButton(int index, int x, int y, int width, int height, const wstring& text, const function<void()>& onClick,int number)
{
    Button* button = new Button(x, y, width, height, text,onClick,number);
    AddButton(index, button);
}

void UIManager::CreateTextBox(int index, int x, int y, int width, int height, int maxWord, int number)
{
    TextBox* textBox = new TextBox(x, y, width, height, maxWord, number);
    AddTextBox(index, textBox);
}

void UIManager::ClearTextBox()
{
    textBoxs[0]->Clear();
    textBoxs[1]->Clear();
  /*  for (auto iter = textBoxs.begin(); iter != textBoxs.end(); iter++)
    {
        iter->second->Clear();
    }*/
}

void UIManager::CreateLabel(int index, int x, int y, int width, int height, const std::wstring& text)
{
    Label* label = new Label(x, y, width, height, text);
    AddLabel(index,label);
}

void UIManager::CreateTable(int index, int x, int y, int width, int height, int visibleRowCount)
{
    TableWidget* table = new TableWidget(x, y, width, height, visibleRowCount);

    vector<vector<wstring>> newList;
    vector<vector<wstring>> newList2;

    switch (index)
    {
    case 0:
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

 wstring UIManager::GetTextFromTextBox(int index) 
{
     return textBoxs[index]->GetText();

}

void UIManager::AddPage(IMAGE* page)
{
    pages.push_back(page);
   
}

void UIManager::AddButton(int index, Button* button)
{
    buttons[index]=button;
}

void UIManager::AddTextBox(int index, TextBox* textBox)
{
    textBoxs[index] = textBox;
}

void UIManager::AddLabel(int index, Label* label)
{

    labels[index] = label;
    
}

void UIManager::AddTable(int index, TableWidget* _table)
{
    tables[index] = _table;
}


//事件处理，向每一个有对应事件的成员进行广播，并由其单独处理事件
void UIManager::MouseClick(int mouseX, int mouseY)
{
    switch (NowWindow)
    {
    case loginWindow:
        buttons[0]->CheckClick(mouseX,  mouseY);
        buttons[1]->CheckClick(mouseX, mouseY);
        buttons[2]->CheckClick(mouseX, mouseY);

        textBoxs[0]->CheckClick(mouseX, mouseY);
        textBoxs[1]->CheckClick(mouseX, mouseY);
        break;
    case mainWindow:
        buttons[3]->CheckClick(mouseX, mouseY);
        buttons[4]->CheckClick(mouseX, mouseY);
        buttons[5]->CheckClick(mouseX, mouseY);
        buttons[6]->CheckClick(mouseX, mouseY);
        buttons[7]->CheckClick(mouseX, mouseY);
        tables[0]->HandleMouseClick(mouseX, mouseY);

        break;
    case processWindow:

        break;
    }
  /*  for (auto iter = textBoxs.begin(); iter != textBoxs.end(); iter++)
    {
        if (iter->kind == NowWindow)
        {
            iter->textBox->CheckClick(mouseX, mouseY);
        }
    }
    for (auto iter = buttons.begin(); iter != buttons.end(); iter++)
    {
        iter->second->CheckClick(mouseX, mouseY);
    }
    for (auto iter = tables.begin(); iter != tables.end(); iter++)
    {
        if (iter->kind == NowWindow)
        {
            iter->table->HandleMouseClick(mouseX, mouseY);
        }
    }*/
}

void UIManager::MouseMove(int mouseX, int mouseY)
{
    switch (NowWindow)
    {
    case loginWindow:
        buttons[0]->CheckMouseOver(mouseX, mouseY);
        buttons[1]->CheckMouseOver(mouseX, mouseY);
        buttons[2]->CheckMouseOver(mouseX, mouseY);
        break;
    case mainWindow:
        buttons[3]->CheckMouseOver(mouseX, mouseY);
        buttons[4]->CheckMouseOver(mouseX, mouseY);
        buttons[5]->CheckMouseOver(mouseX, mouseY);
        buttons[6]->CheckMouseOver(mouseX, mouseY);
        buttons[7]->CheckMouseOver(mouseX, mouseY);

        break;
    case processWindow:

        break;
    }
   /* for (auto iter = buttons.begin(); iter != buttons.end(); iter++)
    {
        if (iter->kind == NowWindow)
        {
            iter->button->CheckMouseOver(mouseX,mouseY);
        }
    }*/
}

void UIManager::MouseWheel(int mouseX, int mouseY, int wheel)
{
    tables[0]->Scroll(mouseX,mouseY, wheel);
  /*  for (auto iter = tables.begin(); iter != tables.end(); iter++)
    {
        if (iter->kind == NowWindow)
        {
            iter->table->Scroll(mouseX, mouseY,wheel);
        }
    }*/
}

void UIManager::KeyInput(wchar_t ch)
{
    //判断输入字符是否是英文字母或数字或操作符，若不是，则弹出错误提示框
    if (iswalpha(ch) || iswdigit(ch)|| ch == L'\n' || ch == L'\b' || ch == '\r')
    {
        if (textBoxs[0]->GetSelect())
        textBoxs[0]->KeyInput(ch);
        else if(textBoxs[1]->GetSelect())
            textBoxs[1]->KeyInput(ch);
    }
    else
    {
        MessageBox(GetHWnd(), "Input Error!","error",MB_OK);
    }
}
void UIManager::DeleteSelectedData(int kind)
{
    int nowData = -1;
    nowData = tables[kind]->GetSelectedRow();
    //若成功删除数据，则重置图表
    if (DataManager::Instance()->DeleteData(nowData))
    {
                vector<vector<wstring>> newList;
                vector<vector<wstring>> newList2;
                newList.push_back({ L"name",L"rowCount",L"mean" ,L"variance" });
                newList2 = DataManager::Instance()->GetInitialData();
                for (const auto& innerVector : newList2)
                {
                    newList.push_back(innerVector);
                }
                tables[kind]->SetData(newList);
                tables[kind]->ResetTable();
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
            labels[10]->Draw();
            break;
        case loginWindow:
            cleardevice();
            labels[0]->Draw();
            labels[1]->Draw();
         
            if (textBoxs[0]->GetSelect())
            {
                textBoxs[0]->UpdateCursor();
            }
            textBoxs[0]->Draw();

            if (textBoxs[1]->GetSelect())
            {
                textBoxs[1]->UpdateCursor();
            }
            textBoxs[1]->Draw();
          /*  for (auto iter = textBoxs.begin(); iter != textBoxs.end(); iter++)
            {
                if (iter->kind == loginWindow)
                {
                    if (iter->textBox->GetSelect())
                    {
                        iter->textBox->UpdateCursor();
                    }
                    iter->textBox->Draw();
                }
            }*/
            buttons[0]->Draw();
            buttons[1]->Draw();
            buttons[2]->Draw();
            break;
        case mainWindow:
            cleardevice();
           /* for (auto iter = labels.begin(); iter != labels.end(); iter++)
            {
                if (iter->kind == mainWindow)
                {
                    iter->label->Draw();
                }
            }*/
          /*  for (auto iter = textBoxs.begin(); iter != textBoxs.end(); iter++)
            {
                if (iter->kind == mainWindow)
                {
                    if (iter->textBox->GetSelect())
                    {
                        iter->textBox->UpdateCursor();
                    }
                    iter->textBox->Draw();
                }
            }*/

            buttons[3]->Draw();
            buttons[4]->Draw();
            buttons[5]->Draw();
            buttons[6]->Draw();
            buttons[7]->Draw();

            tables[0]->Draw();
          /*  for (auto iter = tables.begin(); iter != tables.end(); iter++)
            {
                if (iter->kind == mainWindow)
                {
                    iter->table->Draw();
                }
            }*/
            break;  
        case processWindow:
                cleardevice();
             /*   for (auto iter = labels.begin(); iter != labels.end(); iter++)
                {
                    if (iter->kind == mainWindow)
                    {
                        iter->label->Draw();
                    }
                }*/

              /*  for (auto iter = tables.begin(); iter != tables.end(); iter++)
                {
                    if (iter->kind == mainWindow)
                    {
                        iter->table->Draw();
                    }
                }*/
                break;
        case showProcessWindow:
                break;
        default:
            break;
    }
}
