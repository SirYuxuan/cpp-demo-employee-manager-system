#include "workerManager.h"

WorkerManager::WorkerManager()
{
	// 文件不存在
	ifstream ifs(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		this->InitEmptyData(&ifs);
		return;
	}

	// 文件存在 数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->InitEmptyData(&ifs);
		return;
	}
	// 文件存在，并且有数据
	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	// 开辟空间
	this->m_EmpArr = new Worker * [this->m_EmpNum];
	// 将文件中的数据，存到数组中
	this->init_Emp();

	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号：" << this->m_EmpArr[i]->m_Id
			<< "\t职工姓名：" << this->m_EmpArr[i]->m_Name
			<< "\t职工部门：" << this->m_EmpArr[i]->getDeptName() << endl;
	}*/

}

void WorkerManager::InitEmptyData(ifstream* ifs)
{
	// 初始化属性
	this->m_EmpNum = 0;
	this->m_EmpArr = NULL;
	this->m_FileIsEmpty = true;
	(*ifs).close();
}



WorkerManager::~WorkerManager()
{
	if (this->m_EmpArr != NULL)
	{
		delete[] this->m_EmpArr;
		this->m_EmpArr = NULL;
	}
}
// 展示菜单
void WorkerManager::Show_Menu()
{
	cout << "*******************************************" << endl;
	cout << "********** 欢迎使用职工管理系统! **********" << endl;
	cout << "************  0. 退出管理程序 *************" << endl;
	cout << "************  1. 增加职工信息 *************" << endl;
	cout << "************  2. 显示职工信息 *************" << endl;
	cout << "************  3. 删除离职职工 *************" << endl;
	cout << "************  4. 修改职工信息 *************" << endl;
	cout << "************  5. 查找职工信息 *************" << endl;
	cout << "************  6. 按照编号排序 *************" << endl;
	cout << "************  7. 清空所有文档 *************" << endl;
	cout << "*******************************************" << endl;
}
// 退出系统
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
// 添加职工
void WorkerManager::addEmp()
{
	cout << "请输入添加职工数量：" << endl;
	int addNum = 0; // 保存用户的输入数量
	cin >> addNum;
	if (addNum > 0)
	{
		// 计算空间大小
		int newSize = this->m_EmpNum + addNum;

		// 开辟新空间
		Worker** newSpace = new Worker * [newSize];
		if (this->m_EmpArr != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArr[i];
			}
		}

		// 批量添加新数量
		for (int i = 0; i < addNum; i++)
		{
			int id; // 职工编号
			string name; // 职工姓名
			int dSelect; // 部门选择
			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
			cin >> name;
			cout << "请选择该职工岗位" << endl;
			cout << "1. 普通职工" << endl;
			cout << "2. 经理" << endl;
			cout << "3. 老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			default:
				break;
			}
			// 将创建职工指针，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		// 释放原有空间
		delete[] this->m_EmpArr;
		// 更改新空间的指向
		this->m_EmpArr = newSpace;
		// 更新一下职工人数
		this->m_EmpNum = newSize;
		// 更新职工标志不为空
		this->m_FileIsEmpty = false;
		cout << "成功添加" << addNum << "名新职工" << endl;

		// 保存数据到文件
		this->save();
	}
	else
	{
		cout << "输入的数量有误" << endl;
	}
	// 按任意键后清屏回到上级目录
	system("pause");
	system("cls");
}

// 保存文件
void WorkerManager::save()
{
	ofstream ofs(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArr[i]->m_Id << " "
			<< this->m_EmpArr[i]->m_Name << " "
			<< this->m_EmpArr[i]->m_DeptId << endl;
	}
	ofs.close();

}

// 统计文件中人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs(FILENAME, ios::in);
	int num = 0;
	int id;
	string name;
	int dId;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		num++;
	}

	return num;
}
// 初始化职工
void WorkerManager::init_Emp()
{
	ifstream ifs(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	Worker* worker = NULL;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		switch (dId)
		{
		case 1:
			worker = new Employee(id, name, dId);
			break;
		case 2:
			worker = new Manager(id, name, dId);
			break;
		case 3:
			worker = new Boss(id, name, dId);
			break;
		default:
			break;
		}
		this->m_EmpArr[index] = worker;
		index++;
	}
	// 关闭文件
	ifs.close();
}
// 显示职工
void WorkerManager::show_Emp()
{
	if (this->m_FileIsEmpty) 
	{
		cout << "当前没有职工" << endl;
		return;
	}else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArr[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
// 判断职工是否存在，如果存在返回位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArr[i]->m_Id == id) 
		{
			index = i;
			break;
		}
	}
	return index;
}
// 删除职工
void WorkerManager::del_Emp()
{
	if (this->m_FileIsEmpty) 
	{
		cout << "当前没有职工" << endl;
		return;
	}

	cout << "请输入要删除的职工编号" << endl;
	int id;
	cin >> id;
	int index = this->IsExist(id);
	if(index !=-1)
	{
		// 职工存在
		for (int i = index; i < this->m_EmpNum - 1; i++)
		{
			this->m_EmpArr[i] = this->m_EmpArr[i + 1];
		}
		// 更新一下人员个数
		this->m_EmpNum--;
		// 同步更新到文件中
		this->save();
		cout << "删除成功" << endl;
		system("pause");
		system("cls");
	}
	else 
	{
		cout << "编号为:" << id << "的职工不存在" << endl;
	}
}
// 修改职工
void WorkerManager::mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "当前没有职工" << endl;
		return;
	}

	cout << "请输入要修改的职工编号" << endl;
	int id;
	cin >> id;
	int index = this->IsExist(id);
	if (index != -1)
	{
		delete this->m_EmpArr[index];
		int newId;
		string newName;
		int newDSelect;
		cout << "查到：" << id << "号职工，请输入新的职工号：" << endl;
		cin >> newId;
		cout << "请输入新的姓名" << endl;
		cin >> newName;
		cout << "请选择新的岗位" << endl;
		cout << "1. 普通职工" << endl;
		cout << "2. 经理" << endl;
		cout << "3. 老板" << endl;
		cin >> newDSelect;
		Worker* worker = NULL;
		switch (newDSelect)
		{
		case 1:
			worker = new Employee(newId, newName, newDSelect);
			break;
		case 2:
			worker = new Manager(newId, newName, newDSelect);
			break;
		case 3:
			worker = new Boss(newId, newName, newDSelect);
			break;
		default:
			break;
		}
		this->m_EmpArr[index] = worker;
		cout << "修改成功" << endl;
		this->save();
		system("pause");
		system("cls");
	}
	else
	{
		cout << "编号为:" << id << "的职工不存在" << endl;
	}
}
