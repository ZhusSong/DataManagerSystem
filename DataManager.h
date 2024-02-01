#pragma once
//****************
//信息管理系统头文件，负责数据处理
//****************
#include <iostream>
#include <stdlib.h>
#include <string>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>
#include<map>
#include "SystemConstant.h"
using namespace std;
namespace fs = std::filesystem;


class DataManager
{
public:
	//原始数据结构体
	typedef struct
	{
		wstring filename;
		//数据条数
		int row;
		//数据值
		vector<double> data;

		//噪声均值
		double Nmean;
		//噪声方差
		double Nvar;

	}InitialData;

	//已处理数据结构体
	typedef struct 
	{
		//文件名
		wstring filename;
		//数据条数
		int row;
		//最高拟合阶数
		int MaxOrder;
		//噪声均值
		double Nmean;
		//噪声方差
		double Nvar;
	}PolyfitInfo;
	//账号
	typedef struct
	{
		char name[20];
		char password[20];
	}Account;

	//显示区域
	typedef struct
	{
		int x0, y0, x1, y1;  // top left point and the bottom right point
	}PlotArea;
	PlotArea  parea = { 400,400,824,700 }; // 直方图显示区域，
	PlotArea dataarea = { 50,10,900,300 }; // 数据曲线显示区域

private:
	//单例
	static  DataManager* instance;
	//原始数据列表
	vector<InitialData> Datas;
	//已处理的数据列表
	vector<PolyfitInfo> PolyDatas;
	//账户数据列表
	vector<Account> AccountDatas;


	int Colour[16] = { BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE };


	//文件个数s
	 int FileCount = 0;

	 PolyfitInfo thisData;

	 //对X坐标从小到大排序
	 vector<double> SortByX(vector<double> datas);

public:
	DataManager();
	~DataManager();
	void Init();
	static DataManager* Instance();
	//创建随机原始文件,数据数大于1小于1000
	wstring CreateRandomData(int count);

	//获取数据文件夹中的文件个数
	int GetDataCount();

	//加载已处理过的数据
	bool InitPolyData();

	//加载已有的原始数据
	int InitData();


	//保存已处理数据
	bool SaveProcessData();

	//删除选中的原始数据
	//index:被选中的数据索引
	bool DeleteData(int index);

	//返回选中的数据
	//index:被选中的数据索引
	InitialData GetSelectedData(int index);

	//分析选中数据
	void ProcessData(int index,int maxorder);


	//返回原始数据列表
	const vector<vector<wstring>> GetInitialData();



	//返回已处理数据列表
	const vector<vector<wstring>> GetPolyfitData();

	//读取用户数据
	bool LoadAccount();

	//寻找用户是否存在
	bool FindAccount(char* name);

	//验证用户密码
	bool CheckPassWord(char* name, char* password);

	//创建新用户
	bool CreateAccount(char* name, char* password);


	//创建新用户
	void SortDatas(WindowsKind  dkind, SortKind skind);

	//根据数据条数进行排序
	void SortDataByRow();
	//计算均值
	double mean(vector<double> data);
	//计算方差
	double variance(vector<double> data);
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


	void showhisto(double result[], int n, PlotArea area);
	void showdata(double dataX[], double dataY[], int n, long color, PlotArea p);
};