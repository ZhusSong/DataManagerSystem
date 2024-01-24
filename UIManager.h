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

    void AddPage(IMAGE* page);

    void AddButton(WindowsKind index, Button* button);

    void AddTextBox(WindowsKind index, TextBox* inputBox);

    void AddLabel(WindowsKind index, Label* label);

    void AddTable(WindowsKind index, TableWidget* table);
public:
    static UIManager* Instance();

    void CreatePage();

    void CreateButton(WindowsKind index, Button* button);

    void CreateTextBox(WindowsKind index, TextBox* inputBox);

    void CreateLabel(WindowsKind index, int x, int y, int width, int height, const std::wstring& text);

    void CreateTable(WindowsKind index, TableWidget* table);
    void GetNowWindowKind(WindowsKind index);

  


    void MouseClick(int mouseX, int mouseY);

    void MouseMove(int mouseX, int mouseY);

    void MouseWheel(int mouseX, int mouseY, int wheel);

    void Init();
    void Run();
	UIManager();
	virtual ~UIManager();
};