#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <math.h>

#define N 999   // number of points

int COLOR[]={BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE};

typedef struct 
{
  char filename[20];
  int col;
  int row;
  float mean;
  float variance;
  char status;
}FILEINFO;

typedef struct 
{ 
	int x0,y0,x1,y1;  // the coordinates of  top left point and the bottom right point
}PLOTAREA;

void rowscale(float a[], int n) //scale the time series between 0 and 1;
{
  float max,min,scale;
  int i;
  // find the max and min of the series
  max=min=a[0];
  for(i=1;i<n;i++)
  {
	if(max<a[i]) max=a[i];
	if(min>a[i]) min=a[i];
  }
  // Scale the time series to between 0 and 1
  scale=max-min;
  for(i=0;i<n;i++)
  {
	a[i]=(a[i]-min)/(scale+0.00001);
  }
}

float mean(float a[], int n)
{
	float sum=0;
	int i;
	for(i=0;i<n;i++)
		sum=sum+a[i];
	return sum/n;
}

float variance(float a[], int n)
{
	float M,sum=0;
	int i;
	M=mean(a,n);
	for(i=0;i<100;i++)
		sum=sum+(a[i]-M)*(a[i]-M);
	return sum/n;
}

void histogram(float a[],int n,int result[])
{
	int i;
	for(i=0;i<10;i++)  // generate 10 intervals
		result[i]=0;
	for(i=0;i<n;i++)
		result[(int)(a[i]*9.999)]++;
}


void showhisto(int result[],int n, PLOTAREA area)
{
	int i,max;
	float xscale,yscale;
	max=result[0];
	for(i=1;i<n;i++)
		if(max<result[i]) max=result[i];
	xscale=(area.x1-area.x0)/(float)n;
	yscale=(area.y1-area.y0)/(float)max;
	for(i=0;i<n;i++)
	{ 
		setfillcolor(COLOR[i+1]);
		solidrectangle(area.x0+i*xscale,area.y1,area.x0+(i+1)*xscale,area.y1-result[i]*yscale);
	}
}

void showfinfo(FILEINFO finfo,PLOTAREA farea)
{
// need to set the project properties to MBCS	
 char s[50];
 sprintf(s,"Filename: %s",strupr(finfo.filename));
 outtextxy(farea.x0,farea.y0,s);
 sprintf(s,"Mean is %f",finfo.mean);
 outtextxy(farea.x0,farea.y0+30,s);
 sprintf(s,"Variance is %f",finfo.variance);
 outtextxy(farea.x0,farea.y0+60,s);
}

// 主函数
int main()
{
	FILE *fp;
	int i,result[10];
	char ch[80], *filename="randn.txt";
	float a[N];
	float M,VAR;
	FILEINFO finfo;
	PLOTAREA parea={200,400,824,700},farea={10,600,80,700}; // set the plot area 
	if((fp=fopen(filename,"r+"))==NULL)
	{
		printf("Can not open file\n");
		exit(0);
	}
	for(i=0;i<N;i++)
	{
		fscanf(fp,"%f",&a[i]);
	}
	fclose(fp);
	

	// scale the time series between 0 and 1.
    rowscale(a,N);	
	M=mean(a,N);
	VAR=variance(a,N);
	histogram(a,N,result);
	printf("The mean and the variance of the data series are %f and %f\n",M,VAR);
	printf("The number within each interval is :");
	for(i=0;i<10;i++)
		printf("%4d",result[i]);
	// time series info 
	strcpy(finfo.filename,filename);
	finfo.col=1;
	finfo.row=N;
	finfo.mean=M;
	finfo.variance=VAR;
	finfo.status='Y';
	
	//display data in the graphics window 
	initgraph(1024, 768, EX_SHOWCONSOLE);			// 创建绘图窗口
	// plot the scale time series.
	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	for(i=0;i<N-1;i++)
	{
		line(5*i,a[i]*300,5*(i+1),a[i+1]*300 );
	}
	showhisto(result,10,parea);
	showfinfo(finfo,farea);

	// end of graphics
	
	printf("\nPress any key to exit...");
	fflush(stdin);
	getchar();
	closegraph();					// 关闭绘图窗口
	return 0;
}