#include "DataManager.h"

//指针初始化
DataManager* DataManager::instance = nullptr;
//类的初始化
DataManager::DataManager()
{
	FileCount = InitData();
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

wstring DataManager::CreateRandomData(int count)
{
	//为新文件命名，命名格式为newData_N,后缀N为当前以此方法创建的文件的总数
	wstring s=L"newData_";
	//后缀N
	int newCount = 0;
	//为新文件的后缀做判断，若已存在拥有此后缀的文件，则后缀N加1
	string::size_type idx;
	vector<wstring> names;
	for (auto iter = Datas.begin(); iter != Datas.end(); iter++)
	{
		idx = iter->filename.find(s);
		if (idx != string::npos)
		{
			names.push_back(iter->filename);
		}
	}
	for (int i = 0; i < names.size(); i++)
	{
		idx = names[i].find(to_wstring(newCount));
		if (idx != string::npos)
		{
			newCount++;
			i = 0;
		}

	}
	s += to_wstring(newCount);

	//创建数据，为-100~100的随机双浮点数，保留10位小数
	vector<double> newDatas;
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < count; i++)
	{
		double random_double = -100 + static_cast<double>(rand()) / (RAND_MAX / 200.0);
	//	random_double = trunc(random_double * 1e10) / 1e10;
		newDatas.push_back(random_double);
	}
	double m=mean(newDatas);
	double v=variance(newDatas);
	//将新创建的数据存入Datas
	Datas.push_back({s,count,newDatas,m,v});

	//在文件夹中创建文件,保留8位有效数字
	wstring folders = L"./InitialDatas/"+s+L".txt";
	ofstream file(folders);
	for(int i=0;i<newDatas.size();i++)
	{
		file << std::setprecision(8)<< newDatas[i]<<std::endl;
	}

	return s;
}


int DataManager::GetDataCount()
{
	return FileCount;
}

bool DataManager::InitPolyData()
{
	return false;
}

int DataManager::InitData()
{
	int fileCount=0;
	const string FolderPath = "./InitialDatas";
	//数据列表
	std::vector<double> numericalData;
	int row;
	//噪声均值
	double Nmean;
	//噪声方差
	double Nvar;
	//获取文件
	wstring s ;
	for (const auto& entry :filesystem::directory_iterator(FolderPath))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".txt")
		{
			ifstream inputFile(entry.path());
			if (inputFile.is_open())
			{
				double value=0;
				while (inputFile >> value)
				{
					//获取每一个数据
					s = entry.path().filename().wstring();
					numericalData.push_back(value);
				}
			}
			else 
			{
				std::cerr << "Error opening file: " << entry.path() << std::endl;
			}
			row = numericalData.size();
			//获取均值
			Nmean = mean(numericalData);
			//获取方差
			Nvar = variance(numericalData);
			//存入数据信息
			Datas.push_back({ s,row,numericalData,Nmean,Nvar});
			//清空缓存
			numericalData.clear();
			inputFile.close();
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

bool DataManager::CheckPassWord(char* name, char* password)
{
	for (const auto& account : AccountDatas)
	{
		if (strcmp(account.name, name) == 0)
		{
				if (strcmp(account.password, password) == 0)
				{
					return true;
				}
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
		//读取用户数据
		while (infile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) 
		{
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
		ac.name[sizeof(ac.name) - 1] = '\0'; 
		ac.password[sizeof(ac.password) - 1] = '\0';

		AccountDatas.push_back(ac);

		ofstream outfile("./Accounts/account.dat", ios::binary);
		if (!outfile.is_open()) 
		{
			return false;
		}
		else
		{
			//写入数据
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


bool DataManager::AddData(string& name, vector<double>& data)
{
	return false;
}

bool DataManager::DeleteData(int index)
{
	//得到数据名
	wstring oldFileName= Datas[index - 1].filename;
	//在Datas中删除此数据
	Datas.erase(Datas.begin()+(index)-1); 
	//文件操作，判断此文件是否有后缀名txt，若没有则为其添加
	wstring folder = L"./InitialDatas/";
	string::size_type idx= oldFileName.find(L".txt");
	if (idx == string::npos)
	{
		oldFileName += L".txt";
	}
	wstring filename = folder + oldFileName;
	string narrowFilename(filename.begin(), filename.end());
	//删除操作
	if (std::remove(narrowFilename.c_str()) != 0)
	{
	//	MessageBox(GetHWnd(), "Fail to delete!", "DELETE", MB_OK);
		return false;
	}
	else
	{
		MessageBox(GetHWnd(), "Successfully!", "DELETE", MB_OK);
		return true;
	}
}




const vector<vector<wstring>> DataManager::GetInitialData()
{
	
	wstring name,row,mean,variance;
	vector<vector<wstring>> newList;
	for (auto iter = Datas.begin(); iter != Datas.end(); iter++)
	{
		name = iter->filename;
		row =  to_wstring(iter->row);
		mean = to_wstring(iter->Nmean);
		variance = to_wstring(iter->Nvar);
		newList.push_back({ name,row,mean,variance });
	}
	return newList;
}

void DataManager::SortDataByRow()
{
}

double DataManager::mean(vector<double> data)
{
	double sum = 0;
	int s = data.size();
	for (int i=0;i<data.size();i++)
	{
		sum += data[i];
	}
	return sum/s;
}

double DataManager::variance(vector<double> data)
{
	double M, sum = 0;
	int s = data.size();
	int i;
	M = mean(data);
	for (i = 0; i < data.size(); i++)
		sum = sum + (data[i] - M) * (data[i] - M);
	return sum / s;
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
