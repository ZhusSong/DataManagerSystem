#pragma once
//******************
//处理信息界面，负责对选中的信息进行处理界面中的按钮进行事件响应，以及返回主界面
//******************
#include "UIManager.h"
class ProcessWindow
{
private:
	////设置最大拟合阶数
	//void SetMaxOrder();
	//返回主界面
	void Return();
	////平滑一次
	//void SmoothnessData();
	////去除离散值
	//void RemovalData();
	////撤销全部操作
	//void Cancel();
	////显示前后差别
	//void ShowDifferent();

	//保存此数据
	void Save();
	//单例
	static ProcessWindow* instance;

public:
	static ProcessWindow* Instance();
	ProcessWindow();
	~ProcessWindow();
	//初始化
	void Init();
};