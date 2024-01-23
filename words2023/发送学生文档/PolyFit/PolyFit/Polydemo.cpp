#include "Polyhead.h"

#define N 1000   // number of points max 1000
int COLOR[16]={BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE};
//定义窗口分辨率为1024*768
#define WIDTH  1024;
#define HEIGHT  768;
// ﾖｯﾊ
int main()
{
	FILE *fp;
	int i,datacount=0;
	char ch[80], *filename="002.txt"; //ｶﾁﾈ・ﾄﾊｾﾝﾎﾄｼﾃ﨤ﾆ
	double datax[N],datay[N],fity[N]; 
	double fiterror;		// ﾄ篌ﾏﾎ・
	int order,MaxOrder=7; // ｶ猾鑅ｽｵﾄｽﾗｴﾎ
	
	POLYFITINFO pinfo;

	PLOTAREA  parea={200,400,824,700}; // ﾖｱｷｽﾍｼﾏﾔﾊｾﾇｬ
	PLOTAREA  farea={10,600,80,700};   // ﾎﾄﾗﾖﾏﾔﾊｾﾇ・
	PLOTAREA dataarea={50,10,950,300}; // ﾊｾﾝﾇ昕ﾟﾏﾔﾊｾﾇ・
	
	// ｴﾓﾊｾﾝﾎﾄｼｶﾁﾈ・ｭﾊｼﾊｾﾝ｣ｬﾔｭﾊｼﾊｾﾝｵﾄﾐﾐﾊｲｻﾄﾜｳｬｹN
	if((fp=fopen(filename,"r+"))==NULL)
	{
		printf("Can not open file\n");
		exit(0);
	}
	for(i=0;i<N;i++)
	{
		fscanf(fp,"%lf %lf",&datax[i],&datay[i]);
		if(feof(fp)!=0) // ﾈ郢鋐ﾑｾｭｶﾁｵｽﾎﾄｼﾄｩﾎｲ｣ｬﾍ｣ﾖｹｶﾁﾎﾄｼ｡｣
			break;
	}
	datacount=i; // ﾊｾﾝｵﾄﾐﾐﾊ｡｣
	fclose(fp);
	
	strcpy(pinfo.filename,filename);
	pinfo.row=datacount;
	pinfo.MaxOrder=MaxOrder;

	//display data in the graphics window 
	initgraph(1024, 768, EX_SHOWCONSOLE);			// ｴｴｽｨｻ賚ｼｴｰｿﾚ
	// ｻｭｳｭﾊｼﾊｾﾝ.
	showdata(datax,datay,datacount,RED,dataarea);
	
	// ﾀ﨧ﾃﾗ隯｡ｶｳﾋﾈｷｶｨｶ猾鑅ｽﾄ篌ﾏｵﾄﾏｵﾊ
	for(order=1;order<=MaxOrder;order++)
	{
		polyfit(datacount,datax,datay,order,pinfo.polyCoeff[order]);
	}

	// ｼﾆﾋ羇｢ｼﾇﾂｼﾄ篌ﾏﾎ釤ｬｻｭｳ篌ﾏﾇ昕ﾟ｡｣
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

	// ﾓﾃﾖｱｷｽﾍｼｱ桄ｾｲｻﾍｬｽﾗｴﾎｵﾄﾄ篌ﾏﾎ釭｣
	showhisto(pinfo.fitError,MaxOrder,parea); // ﾔﾚparea ﾏﾔﾊｾﾖｱｷｽﾍｼ

	// ﾊ菠・錡ﾑｵﾄｶ猾鑅ｽﾄ篌ﾏｽﾗｴﾎ｡｣
	printf("\nPress enter the best order of polynormial:");
	fflush(stdin);
	scanf("%d",&pinfo.OptiOrder);

	// ｽｫｴｦﾀ昉ﾄｹｳﾌｽﾐﾗﾜｽ癸｣
	showpinfo(pinfo,farea);  // ﾔﾚfarea ﾏﾔﾊｾﾊｾﾝﾎﾄｼﾐﾅﾏ｢
	printf("\nPress any key to exit...");
	fflush(stdin);
	getchar();
	closegraph();					// ｹﾘｱﾕｻ賚ｼｴｰｿﾚ
	return 0;
}