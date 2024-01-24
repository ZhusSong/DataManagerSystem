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

void UIManager::CreateButton(WindowsKind index, Button* button)
{
}

void UIManager::CreateTextBox(WindowsKind index, TextBox* inputBox)
{
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
}

void UIManager::MouseMove(int mouseX, int mouseY)
{
}

void UIManager::MouseWheel(int mouseX, int mouseY, int wheel)
{

}

void UIManager::Init()
{
    instance = new UIManager();
}

void UIManager::Run()
{
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
            break;
        case mainWindow:
            break;
    }
}
