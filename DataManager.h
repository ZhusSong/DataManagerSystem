#pragma once
//****************
//信息管理系统头文件，负责数据处理
//****************
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
using namespace std;

//最大文件条数
#define N 999 
//定义窗口分辨率为1024*768
#define WIDTH  1024
#define HEIGHT  768
//所需颜色定义
enum Colors
{
	//背景色
	BackGround = 0,
	//边线颜色
	LineColor = 1,
	//文字颜色
	TextColor = 2,
	//颜色组01:灰色系
	//常态颜色
	NormalColor_1 = 3,
	//鼠标进入时的颜色
	EnterColor_1 = 4,
	//鼠标点击时的颜色
	ClickColor_1 = 5,

	//颜色组02:黄色系
	//常态颜色
	NormalColor_2 = 6,
	//鼠标进入时的颜色
	EnterColor_2 = 7,
	//鼠标点击时的颜色
	ClickColor_2 = 8,

	//颜色组03:蓝色系
	//常态颜色
	NormalColor_3 = 9,
	//鼠标进入时的颜色
	EnterColor_3 = 10,
	//鼠标点击时的颜色
	ClickColor_3 = 11,
};

//颜色rgb结构体
//初始化颜色RGB值，与枚举Colors一一对应
typedef struct {
	BYTE r, g, b;
}RGBs[12];
RGBs rgb= { {0,0,0},
	{163,148,128},
	{245,245,245},

	{128,138,135},
	{192,192,192},
	{41,36,33},

	{218,165,105},
	{255,227,132},
	{237,145,33},

	{61,89,171},
	{30,144,255},
	{25,25,112}
};


class DataManager
{
	typedef struct 
	{
		//文件名
		char filename[20];
		//数据条数
		int row;
		//不同阶次多项式拟合
		double polyCoeff[10][10];
		//不同阶次多项式拟合误差
		double fitError[10];
		//最高拟合阶数_用户输入
		int MaxOrder;
		//最佳拟合阶数
		int OptiOrder;
		//噪声均值
		char Nmean;
		//噪声方差
		char Nvar;
		//是否已存入信息管理系统
		bool status;
	}PolyfitInfo;

	typedef struct
	{
		int x0, y0, x1, y1;  // top left point and the bottom right point
	}PlotArea;

	int COLOR[16];
private:

	//单例
	static  DataManager* instance;

public:
	DataManager();
	~DataManager();

	static DataManager* Instance();

	//加载已有数据
	bool InitData();
	//添加新数据
	bool AddData();
	//删除数据
	bool DeleteData();
	//保存数据
	bool SaveData();
	//根据数据条数进行排序
	void SortDataByRow();

	// 数组基本操作 文件：arrayop.cpp
	double arrayscale(double a[], int n);
	double arraymin(double a[], int n);
	double arraymax(double a[], int n);
	void arraycopy(double target[], double source[], int n);
	void arraysub(double x[], double y[], double z[], int n);// z=x-y;

	// 多项式拟合函数
	void polyfit(int n, double x[], double y[], int poly_n, double p[]);
	void gauss_solve(int n, double A[], double x[], double b[]);
	void reverseP(double arr[], int size);


	// 多项式函数处理
	double fx(double x, double coeffs[], int degree);

	// 图形显示  文件： datagraph.cpp
	void showhisto(double result[], int n, PlotArea area);
	void showpinfo(PolyfitInfo pinfo, PlotArea farea);
	void showdata(double dataX[], double dataY[], int n, long color, PlotArea p);
};