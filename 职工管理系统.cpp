#include <iostream>
#include "workerManager.h"
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
int main()
{

	// ʵ���������߶���
	WorkerManager wm;
	int choice = 0;

	while(true)
	{
		wm.Show_Menu();

		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0: // �˳�ϵͳ
			wm.exitSystem();
			break;
		case 1: // ����ְ��
			wm.addEmp();
			break;
		case 2: // ��ʾְ��
			wm.show_Emp();
			break;
		case 3: // ɾ��ְ��
			wm.del_Emp();
			break; 
		case 4: // �޸�ְ��
			wm.mod_Emp();
			break;
		case 5: // ����ְ��
			break;
		case 6: // ����ְ��
			break;
		case 7: // ����ĵ�
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}