#include "DataManager.h"

//指针初始化
DataManager* DataManager::instance = nullptr;
//类的初始化
DataManager::DataManager()
{
	char a[20] = "user02";
	char b[20] = "1234";

	FileCount = InitData();
//	AccountDatas.push_back({ "user","123" });
//	CreateAccount(a, b);
}

//内存释放 
DataManager::~DataManager()
{
    delete instance;
}
void DataManager::Init()
{
	instance = new DataManager();
}
//由外部函数调用，返回此类的单例
DataManager* DataManager::Instance()
{
    return instance;
}

bool DataManager::CreateRandomData(int count)
{
	return false;
}


int DataManager::GetDataCount()
{
	return FileCount;
}

int DataManager::InitData()
{
	int fileCount=0;
	const string FolderPath = "./Datas";
	std::vector<double> numericalData;
	int row;
	string s ;
	for (const auto& entry :filesystem::directory_iterator(FolderPath))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".txt")
		{
			ifstream inputFile(entry.path());
			if (inputFile.is_open()) {
				double value;
				while (inputFile >> value) {
					s = entry.path().filename().string();
					numericalData.push_back(value);
				}
				row = numericalData.size();
				PolyDatas.push_back({ s,row,numericalData,NULL,NULL,NULL,NULL,NULL,NULL,false });
				inputFile.close();
			}
			else {
				std::cerr << "Error opening file: " << entry.path() << std::endl;
			}
		}
		fileCount+=1;
	}
	return fileCount;
}

bool DataManager::FindAccount(char* name)
{
	for (const auto& account : AccountDatas)
	{
		if (strcmp(account.name,name)==0)
		{
			return true;
		}
	}
	return false;
}

bool DataManager::LoadAccount()
{
	ifstream infile("./Accounts/account.dat", ios::binary);
	if (!infile.is_open()) 
	{
		MessageBox(GetHWnd(), "无法打开文件！", "error", MB_OK);
		return false;
	}
	else
	{
		Account ac;
		while (infile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
			AccountDatas.push_back(ac);
		}
		infile.close();
		return true;
	}
}

bool DataManager::CreateAccount(char* name, char* password)
{
	if (!FindAccount(name)||AccountDatas.size()==0)
	{
		//处理字符串存储时的空占位符
		Account ac;
		strncpy_s(ac.name, name, sizeof(ac.name) - 1);
		strncpy_s(ac.password, password, sizeof(ac.password) - 1);
		ac.name[sizeof(ac.name) - 1] = '\0'; // Ensure null-terminated strings
		ac.password[sizeof(ac.password) - 1] = '\0';

		AccountDatas.push_back(ac);

		ofstream outfile("./Accounts/account.dat", ios::binary);
		// Check if the file is opened successfully
		if (!outfile.is_open()) 
		{
			return false;
		}
		else
		{
			outfile.write(reinterpret_cast<const char*>(AccountDatas.data()), AccountDatas.size() * sizeof(Account));
			if (outfile.fail())
			{
				std::cerr << "Error!" << std::endl;
				outfile.close();
				return false;
			}
		}
		outfile.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool DataManager::AddData()
{
	return false;
}

bool DataManager::DeleteData()
{

	return false;
}

bool DataManager::SaveData()
{
	return false;
}

void DataManager::SortDataByRow()
{
}

double DataManager::arrayscale(double a[], int n)
{
    return arraymax(a, n) - arraymin(a, n);
}

double DataManager::arraymin(double a[], int n)
{
    double min;
    int i;
    min = a[0];
    for (i = 1; i < n; i++)
    {
        if (min > a[i]) min = a[i];
    }
    return min;
}

double DataManager::arraymax(double a[], int n)
{
    double max;
    int i;
    max = a[0];
    for (i = 1; i < n; i++)
    {
        if (max < a[i]) max = a[i];
    }
    return max;
}

void DataManager::arraycopy(double target[], double source[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        target[i] = source[i];
}

void DataManager::arraysub(double x[], double y[], double z[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        z[i] = x[i] - y[i];
}

void DataManager::polyfit(int n, double x[], double y[], int poly_n, double p[])
{
	int i, j;
	double* tempx, * tempy, * sumxx, * sumxy, * ata;

	tempx = (double*)calloc(n, sizeof(double));
	sumxx = (double*)calloc((poly_n * 2 + 1), sizeof(double));
	tempy = (double*)calloc(n, sizeof(double));
	sumxy = (double*)calloc((poly_n + 1), sizeof(double));
	ata = (double*)calloc((poly_n + 1) * (poly_n + 1), sizeof(double));

	for (i = 0; i < n; i++)
	{
		tempx[i] = 1;
		tempy[i] = y[i];
	}


	for (i = 0; i < 2 * poly_n + 1; i++)
	{
		for (sumxx[i] = 0, j = 0; j < n; j++)
		{
			sumxx[i] += tempx[j];
			tempx[j] *= x[j];
		}
	}


	for (i = 0; i < poly_n + 1; i++)
	{
		for (sumxy[i] = 0, j = 0; j < n; j++)
		{
			sumxy[i] += tempy[j];
			tempy[j] *= x[j];
		}
	}



	for (i = 0; i < poly_n + 1; i++)
	{
		for (j = 0; j < poly_n + 1; j++)
		{
			ata[i * (poly_n + 1) + j] = sumxx[i + j];
		}
	}

	gauss_solve(poly_n + 1, ata, p, sumxy);
	reverseP(p, poly_n);

	//ﾊﾍｷﾅｶｯﾌｬｷﾖﾅ莊ﾄﾄﾚｴ譯｣	
	free(tempx);
	free(sumxx);
	free(tempy);
	free(sumxy);
	free(ata);
}

void DataManager::gauss_solve(int n, double A[], double x[], double b[])
{
	int i, j, k, r;
	double max;
	for (k = 0; k < n - 1; k++)
	{
		max = fabs(A[k * n + k]);					// find maxmum 
		r = k;
		for (i = k + 1; i < n - 1; i++)
		{
			if (max < fabs(A[i * n + i]))
			{
				max = fabs(A[i * n + i]);
				r = i;
			}
		}
		if (r != k)
		{
			for (i = 0; i < n; i++)		//change array:A[k]&A[r]
			{
				max = A[k * n + i];
				A[k * n + i] = A[r * n + i];
				A[r * n + i] = max;
			}

			max = b[k];                    //change array:b[k]&b[r]
			b[k] = b[r];
			b[r] = max;
		}                                  //ﾎｪﾁﾋﾊｹﾓﾃﾁﾐﾖｪﾏ鉙･ｷｨ｣ｬﾔﾚｵﾚkｲｽﾏ鋕ｪﾇｰ｣ｬﾏﾈﾕﾒｳﾐﾐﾏﾂﾋﾐｵﾚkﾁﾐﾔｪﾋﾘﾗ鋗ﾄｷﾇﾁ耿ｪﾋﾘar,k｣ｬｽｫｵﾚrﾐﾐﾓ・ﾚkﾐﾐｽﾐﾕ鋗ﾐｽｻｻｻ

		for (i = k + 1; i < n; i++)
		{
			for (j = k + 1; j < n; j++)
				A[i * n + j] -= A[i * n + k] * A[k * n + j] / A[k * n + k];
			b[i] -= A[i * n + k] * b[k] / A[k * n + k];
		}
	}


	for (i = n - 1; i >= 0; x[i] /= A[i * n + i], i--)
	{
		for (j = i + 1, x[i] = b[i]; j < n; j++)
			x[i] -= A[i * n + j] * x[j];
	}
}

void DataManager::reverseP(double arr[], int size)
{
	double temp;
	int i;
	for (i = 0; i <= size / 2; i++)
	{
		temp = arr[i]; arr[i] = arr[size - i]; arr[size - i] = temp;
	}
}

double DataManager::fx(double x, double coeffs[], int degree)
{
	double result = 0;
	int i;
	for (i = 0; i <= degree; ++i) {
		result += coeffs[i] * pow(x, degree - i);
	}
	return result;
}

void DataManager::showhisto(double result[], int n, PlotArea area)
{
	int i;
	double max;
	float xscale, yscale;
	max = result[1];
	for (i = 1; i < n; i++)
		if (max < result[i]) max = result[i];
	xscale = (area.x1 - area.x0) / (float)n;
	yscale = (area.y1 - area.y0) / (float)max;
	for (i = 1; i <= n; i++)
	{
		setfillcolor(COLOR[i + 1]);
		solidrectangle(area.x0 + i * xscale, area.y1, area.x0 + (i + 1) * xscale, area.y1 - result[i] * yscale);
	}
}

void DataManager::showpinfo(PolyfitInfo pinfo, PlotArea farea)
{
	// need to set the project properties to MBCS	
	char s[50];
	//printf_s(s, "Filename: %s", _strupr_s(pinfo.filename));
	outtextxy(farea.x0, farea.y0, s);
	printf_s(s, "Row of Data %d", pinfo.row);
	outtextxy(farea.x0, farea.y0 + 30, s);
	printf_s(s, "OptiOrder is %d", pinfo.OptiOrder);
	outtextxy(farea.x0, farea.y0 + 60, s);
	printf_s(s, "Overall fiterrror is %.2lf", pinfo.fitError[pinfo.OptiOrder]);
	outtextxy(farea.x0, farea.y0 + 90, s);
}

void DataManager::showdata(double dataX[], double dataY[], int n, long color, PlotArea p)
{
	int i;
	int x0, y1, height, width;
	double minX, scaleX, minY, scaleY;

	//  find the min and scale of the input array
	minX = arraymin(dataX, n);
	scaleX = arrayscale(dataX, n);

	minY = arraymin(dataY, n);
	scaleY = arrayscale(dataY, n);

	// Set the plot area;
	x0 = p.x0;
	y1 = p.y1;
	height = p.y1 - p.y0;
	width = p.x1 - p.x0;

	// Plot the graph
	setlinecolor(color);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	for (i = 0; i < n - 1; i++)
	{
		line(x0 + (dataX[i] - minX) / scaleX * width, y1 - (dataY[i] - minY) / scaleY * height, x0 + (dataX[i + 1] - minX) / scaleX * width, y1 - (dataY[i + 1] - minY) / scaleY * height);
	}
}
