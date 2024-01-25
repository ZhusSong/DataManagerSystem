#include "UIManager.h"


//指针初始化
UIManager* UIManager::instance = nullptr;

UIManager::UIManager()
{
  
}

UIManager::~UIManager()
{
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

void UIManager::CreateLabel(WindowsKind index, int x, int y, int width, int height, const std::wstring& text)
{
    Label* label = new Label(x, y, width, height, text);
    AddLabel(index,label);
}

void UIManager::CreateTable(WindowsKind index, TableWidget* table)
{
}

void UIManager::GetNowWindowKind(WindowsKind index)
{
    thisKind = index;
}

wstring UIManager::GetTextFromTextBox(int index)
{
    for (auto iter = textBoxs.begin(); iter != textBoxs.end(); iter++)
    {
        if (iter->kind == NowWindow)
        {
           return iter->textBox->GetText(index);
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

void UIManager::AddTable(WindowsKind index, TableWidget* table)
{
    if (index >= 0 && index < tables.size())
    {
        tables[index].push_back(table);
    }
}



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

}

void UIManager::KeyInput(wchar_t ch)
{
    //判断输入字符是否是英文字母或数字或操作符
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

void UIManager::Init()
{
    instance = new UIManager();
}

void UIManager::Run()
{
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
            break;
    }
}
