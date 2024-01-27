#pragma once
//******************
//UI组件，包括标题、按钮、图标等的管理，同时负责处理鼠标事件
//******************
#include <graphics.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include "DataManager.h"
#include "SystemConstant.h"
#include "Button.h"
#include "TextBox.h"
#include "TableWidget.h"
#include "Label.h"

using namespace std;


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
    //创建按钮
    /*index:创建此按钮的界面索引
    * x,y,width,height:按钮左上角点的xy值，以及此按钮的宽度与高度值
    * text:按钮上显示的文字
    * onClick:点击事件，在创建此按钮的界面中进行事件的注册
    * number:按钮在界面中对应的索引，管理函数根据此索引判断点击的是哪一个按钮
    */
    void CreateButton(WindowsKind index, int x, int y, int width, int height, const wstring& text, const function<void()>& onClick,int number);

    //创建输入框
    /*index:创建此输入框的界面索引
    * x,y,width,height:输入框左上角点的xy值，以及此输入框的宽度与高度值
    * maxWord:最大可输入文字数
    * number:输入框在界面中对应的索引，管理函数根据此索引判断应用哪一个输入框
    */
    void CreateTextBox(WindowsKind index, int x, int y, int width, int height, int maxWord,int number);
    
    //清空所有输入框
    void ClearTextBox();

    //创建标题
    //参数意义同按钮
    void CreateLabel(WindowsKind index, int x, int y, int width, int height, const std::wstring& text);

    //创建图表
    //visibleRowCount:最大显示行数，其余参数同上
    void CreateTable(WindowsKind index, int x, int y, int width, int height, int visibleRowCount);

    //从输入框处得到输入值
    //index:输入框的索引值，管理函数根据此索引值判断想要得到数据的是哪一个输入框
    wstring GetTextFromTextBox(int index) const;

    //刷新图表，设计中一个界面只会拥有一个图表，因此无需索引值
    void SetNewTable(WindowsKind kind);

    //鼠标点击事件
    void MouseClick(int mouseX, int mouseY);

    //鼠标移动事件
    void MouseMove(int mouseX, int mouseY);

    //鼠标中键滚动事件
    void MouseWheel(int mouseX, int mouseY, int wheel);

    //键盘输入事件
    void KeyInput(wchar_t ch);

    //删除选中数据
    void DeleteSelectedData(WindowsKind kind);

    //初始化
    void Init();

    //运行
    void Run();
	UIManager();
	virtual ~UIManager();
};