#pragma once
//****************
//数据管理框架与数据操作函数
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

//最大可处理数据条数
#define N 999 

//可显示颜色
int COLOR[] = { BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE };

class DataManager
{
	typedef struct 
	{
		//数据文件名
		char filename[20];
		//数据条数
		int row;
		//不同阶次多项式拟合
		double polyCoeff[10][10];
		//不同阶次多项式拟合误差
		double fitError[10];
		//最高拟合阶数——用户输入
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
	//单例
	static  DataManager* instance;
public:
	DataManager();
	~DataManager();

	static DataManager* Instance();
	// 函数声明

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