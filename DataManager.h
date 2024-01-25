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
using namespace std;
namespace fs = std::filesystem;


class DataManager
{
public:
	//数据结构体
	typedef struct 
	{
		//文件名
		string filename;
		//数据条数
		int row;
		//数据值
		vector<double> data;
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
	//账号
	typedef struct
	{
		char name[20];
		char password[20];
	}Account;

	//
	typedef struct
	{
		int x0, y0, x1, y1;  // top left point and the bottom right point
	}PlotArea;

	int COLOR[16];
private:
	//单例
	static  DataManager* instance;

	vector<PolyfitInfo> PolyDatas;

	vector<Account> AccountDatas;


	//文件个数s
	 int FileCount = 0;

public:
	DataManager();
	~DataManager();
	void Init();
	static DataManager* Instance();
	//创建随机数文件,数据数大于1小于1000
	bool CreateRandomData(int count);
	//获取数据文件夹中的文件个数
	int GetDataCount();
	//加载已有数据
	int InitData();
	//读取用户数据
	bool LoadAccount();
	//寻找用户是否存在
	bool FindAccount(char* name);
	//验证用户密码
	bool CheckPassWord(char* name, char* password);
	//创建新用户
	bool CreateAccount(char* name, char* password);
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