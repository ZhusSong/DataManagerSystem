#pragma once
#include <graphics.h>
#include "DataManager.h"
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include "SystemConstant.h"
#include "Button.h"
#include "TextBox.h"
#include "TableWidget.h"
#include "Label.h"

using namespace std;


//UI组件管理
class UIManager
{
	


private:
    typedef struct {
        WindowsKind kind;
        Button* button;
    } Buttons;
    typedef struct  {
        WindowsKind kind;
        Label* label;
    }Labels;
    typedef struct {
        WindowsKind kind;
        TextBox* textBox;
    }TextBoxs;

    //单例
    static  UIManager* instance;
    WindowsKind thisKind=loadWindow;
    vector<IMAGE*> pages;
    vector<Buttons> buttons;
    vector<TextBoxs>textBoxs;
    vector<vector<TableWidget*>> tables;
    vector<Labels> labels;
    //当前点击的按钮索引
    int NowClickButton = -1;

    void AddPage(IMAGE* page);

    void AddButton(WindowsKind index, Button* button);

    void AddTextBox(WindowsKind index, TextBox* inputBox);

    void AddLabel(WindowsKind index, Label* label);

    void AddTable(WindowsKind index, TableWidget* table);
public:
    static UIManager* Instance();

    void CreatePage();

    void CreateButton(WindowsKind index, int x, int y, int width, int height, const wstring& text, const function<void()>& onClick,int number);

    void CreateTextBox(WindowsKind index, int x, int y, int width, int height, int maxWord,int number);

    void CreateLabel(WindowsKind index, int x, int y, int width, int height, const std::wstring& text);

    void CreateTable(WindowsKind index, TableWidget* table);
    void GetNowWindowKind(WindowsKind index);

    //从输入框处得到输入值
    wstring GetTextFromTextBox(int index) const;


    void MouseClick(int mouseX, int mouseY);

    void MouseMove(int mouseX, int mouseY);

    void MouseWheel(int mouseX, int mouseY, int wheel);

    void KeyInput(wchar_t ch);

    void Init();
    void Run();
	UIManager();
	virtual ~UIManager();
};