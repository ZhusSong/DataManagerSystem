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
    //按钮结构体
    //kind:应用此按钮的界面
    //button:按钮指针
    typedef struct {
        WindowsKind kind;
        Button* button;
    } Buttons;
    //标题结构体
    //kind:应用此标题的界面
    //label:标题指针
    typedef struct  {
        WindowsKind kind;
        Label* label;
    }Labels;
    //输入框结构体
    //kind:应用此输入框的界面
    //textBox:输入框指针
    typedef struct {
        WindowsKind kind;
        TextBox* textBox;
    }TextBoxs;

    //图表结构体
    //kind:应用此输入框的界面
    //textBox:输入框指针
    typedef struct {
        WindowsKind kind;
        TableWidget* table;
    }TableWidgets;
    //单例
    static  UIManager* instance;

    //图片列表，保存所有的图片对象
    vector<IMAGE*> pages;

    //按钮列表，保存所有的按钮对象
    vector<Buttons> buttons;

    //输入框列表，保存所有的输入框对象
    vector<TextBoxs> textBoxs;

    //图表列表，保存所有的图表对象
    vector<TableWidgets> tables;

    //标题列表，保存所有的标题对象
    vector<Labels> labels;
    //当前点击的按钮索引
    int NowClickButton = -1;

    //添加图片
    void AddPage(IMAGE* page);

    //向列表中添加一个新按钮
    //index:应用此按钮的界面索引
    //button:按钮对象
    void AddButton(WindowsKind index, Button* button);

    //向列表中添加一个新输入框
    //index:应用此输入框的界面索引
    //inputBox:输入框对象
    void AddTextBox(WindowsKind index, TextBox* inputBox);

    //向列表中添加一个新按钮
    //index:应用此标题的界面索引
    //labeln:标题对象
    void AddLabel(WindowsKind index, Label* label);

    //向列表中添加一个新按钮
    //index:应用此图表的界面索引
    //table:图表对象
    void AddTable(WindowsKind index, TableWidget* _table);
public:
    static UIManager* Instance();

    void CreatePage();

    void CreateButton(WindowsKind index, int x, int y, int width, int height, const wstring& text, const function<void()>& onClick,int number);

    void CreateTextBox(WindowsKind index, int x, int y, int width, int height, int maxWord,int number);
    //清空输入框
    void ClearTextBox();
    void CreateLabel(WindowsKind index, int x, int y, int width, int height, const std::wstring& text);

    void CreateTable(WindowsKind index, int x, int y, int width, int height, int visibleRowCount);

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