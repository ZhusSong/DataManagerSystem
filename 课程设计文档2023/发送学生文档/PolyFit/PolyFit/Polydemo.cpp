#include "Polyhead.h"

#define N 1000   // number of points max 1000
int COLOR[16]={BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE};

// 主函数
int main()
{
	FILE *fp;
	int i,datacount=0;
	char ch[80], *filename="002.txt"; //读入的数据文件名称
	double datax[N],datay[N],fity[N]; 
	double fiterror;		// 拟合误差
	int order,MaxOrder=7; // 多项式的阶次
	
	POLYFITINFO pinfo;

	PLOTAREA  parea={200,400,824,700}; // 直方图显示区域，
	PLOTAREA  farea={10,600,80,700};   // 文字显示区域 
	PLOTAREA dataarea={50,10,950,300}; // 数据曲线显示区域
	
	// 从数据文件读入原始数据，原始数据的行数不能超过N
	if((fp=fopen(filename,"r+"))==NULL)
	{
		printf("Can not open file\n");
		exit(0);
	}
	for(i=0;i<N;i++)
	{
		fscanf(fp,"%lf %lf",&datax[i],&datay[i]);
		if(feof(fp)!=0) // 如果已经读到文件末尾，停止读文件。
			break;
	}
	datacount=i; // 数据的行数。
	fclose(fp);
	
	strcpy(pinfo.filename,filename);
	pinfo.row=datacount;
	pinfo.MaxOrder=MaxOrder;

	//display data in the graphics window 
	initgraph(1024, 768, EX_SHOWCONSOLE);			// 创建绘图窗口
	// 画出原始数据.
	showdata(datax,datay,datacount,RED,dataarea);
	
	// 利用最小二乘确定多项式拟合的系数
	for(order=1;order<=MaxOrder;order++)
	{
		polyfit(datacount,datax,datay,order,pinfo.polyCoeff[order]);
	}

	// 计算并记录拟合误差，画出拟合曲线。
	for(order=1;order<=MaxOrder;order++)
	{
		fiterror=0;
		for(i=0;i<datacount;i++)
		{
			fity[i]=fx(datax[i],pinfo.polyCoeff[order],order);
			fiterror+=(fity[i]-datay[i])*(fity[i]-datay[i]);
		}
		pinfo.fitError[order]=fiterror;
		showdata(datax,fity,datacount,COLOR[order],dataarea);
	}

	// 用直方图表示不同阶次的拟合误差。
	showhisto(pinfo.fitError,MaxOrder,parea); // 在parea 显示直方图

	// 输入最佳的多项式拟合阶次。
	printf("\nPress enter the best order of polynormial:");
	fflush(stdin);
	scanf("%d",&pinfo.OptiOrder);

	// 将处理的过程进行总结。
	showpinfo(pinfo,farea);  // 在farea 显示数据文件信息
	printf("\nPress any key to exit...");
	fflush(stdin);
	getchar();
	closegraph();					// 关闭绘图窗口
	return 0;
}