#pragma once
#include <iostream>
#include <fstream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#define FILENAME "empFile.txt"

class WorkerManager {
public:
	// 构造函数
	WorkerManager();
	// 初始化空数据
	void InitEmptyData(ifstream*  ifs);
	// 展示菜单
	void Show_Menu();
	// 退出系统
	void exitSystem();

	// 记录职工人数
	int m_EmpNum;

	// 职工数组指针
	Worker** m_EmpArr;

	// 添加职工
	void addEmp();

	// 保存文件
	void save();

	// 判断文件是否为空标志
	bool m_FileIsEmpty;

	// 统计文件中人数
	int get_EmpNum();

	// 初始化职工
	void init_Emp();

	// 显示职工
	void show_Emp();

	// 判断职工是否存在
	int IsExist(int id);

	// 删除职工
	void del_Emp();

	// 修改职工
	void mod_Emp();

	// 析构函数
	~WorkerManager();
};