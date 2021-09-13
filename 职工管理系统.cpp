#include <iostream>
#include "workerManager.h"
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
int main()
{

	// 实例化管理者对象
	WorkerManager wm;
	int choice = 0;

	while(true)
	{
		wm.Show_Menu();

		cout << "请输入您的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0: // 退出系统
			wm.exitSystem();
			break;
		case 1: // 增加职工
			wm.addEmp();
			break;
		case 2: // 显示职工
			wm.show_Emp();
			break;
		case 3: // 删除职工
			wm.del_Emp();
			break; 
		case 4: // 修改职工
			wm.mod_Emp();
			break;
		case 5: // 查找职工
			break;
		case 6: // 排序职工
			break;
		case 7: // 清空文档
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}