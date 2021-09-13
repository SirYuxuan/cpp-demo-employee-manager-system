#include "workerManager.h"

WorkerManager::WorkerManager()
{
	// �ļ�������
	ifstream ifs(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		this->InitEmptyData(&ifs);
		return;
	}

	// �ļ����� ����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->InitEmptyData(&ifs);
		return;
	}
	// �ļ����ڣ�����������
	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	// ���ٿռ�
	this->m_EmpArr = new Worker * [this->m_EmpNum];
	// ���ļ��е����ݣ��浽������
	this->init_Emp();

	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "ְ����ţ�" << this->m_EmpArr[i]->m_Id
			<< "\tְ��������" << this->m_EmpArr[i]->m_Name
			<< "\tְ�����ţ�" << this->m_EmpArr[i]->getDeptName() << endl;
	}*/

}

void WorkerManager::InitEmptyData(ifstream* ifs)
{
	// ��ʼ������
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
// չʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "*******************************************" << endl;
	cout << "********** ��ӭʹ��ְ������ϵͳ! **********" << endl;
	cout << "************  0. �˳�������� *************" << endl;
	cout << "************  1. ����ְ����Ϣ *************" << endl;
	cout << "************  2. ��ʾְ����Ϣ *************" << endl;
	cout << "************  3. ɾ����ְְ�� *************" << endl;
	cout << "************  4. �޸�ְ����Ϣ *************" << endl;
	cout << "************  5. ����ְ����Ϣ *************" << endl;
	cout << "************  6. ���ձ������ *************" << endl;
	cout << "************  7. ��������ĵ� *************" << endl;
	cout << "*******************************************" << endl;
}
// �˳�ϵͳ
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
// ���ְ��
void WorkerManager::addEmp()
{
	cout << "���������ְ��������" << endl;
	int addNum = 0; // �����û�����������
	cin >> addNum;
	if (addNum > 0)
	{
		// ����ռ��С
		int newSize = this->m_EmpNum + addNum;

		// �����¿ռ�
		Worker** newSpace = new Worker * [newSize];
		if (this->m_EmpArr != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArr[i];
			}
		}

		// �������������
		for (int i = 0; i < addNum; i++)
		{
			int id; // ְ�����
			string name; // ְ������
			int dSelect; // ����ѡ��
			cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;
			cout << "��ѡ���ְ����λ" << endl;
			cout << "1. ��ְͨ��" << endl;
			cout << "2. ����" << endl;
			cout << "3. �ϰ�" << endl;
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
			// ������ְ��ָ�룬���浽������
			newSpace[this->m_EmpNum + i] = worker;
		}
		// �ͷ�ԭ�пռ�
		delete[] this->m_EmpArr;
		// �����¿ռ��ָ��
		this->m_EmpArr = newSpace;
		// ����һ��ְ������
		this->m_EmpNum = newSize;
		// ����ְ����־��Ϊ��
		this->m_FileIsEmpty = false;
		cout << "�ɹ����" << addNum << "����ְ��" << endl;

		// �������ݵ��ļ�
		this->save();
	}
	else
	{
		cout << "�������������" << endl;
	}
	// ��������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

// �����ļ�
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

// ͳ���ļ�������
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
// ��ʼ��ְ��
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
	// �ر��ļ�
	ifs.close();
}
// ��ʾְ��
void WorkerManager::show_Emp()
{
	if (this->m_FileIsEmpty) 
	{
		cout << "��ǰû��ְ��" << endl;
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
// �ж�ְ���Ƿ���ڣ�������ڷ���λ�ã������ڷ���-1
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
// ɾ��ְ��
void WorkerManager::del_Emp()
{
	if (this->m_FileIsEmpty) 
	{
		cout << "��ǰû��ְ��" << endl;
		return;
	}

	cout << "������Ҫɾ����ְ�����" << endl;
	int id;
	cin >> id;
	int index = this->IsExist(id);
	if(index !=-1)
	{
		// ְ������
		for (int i = index; i < this->m_EmpNum - 1; i++)
		{
			this->m_EmpArr[i] = this->m_EmpArr[i + 1];
		}
		// ����һ����Ա����
		this->m_EmpNum--;
		// ͬ�����µ��ļ���
		this->save();
		cout << "ɾ���ɹ�" << endl;
		system("pause");
		system("cls");
	}
	else 
	{
		cout << "���Ϊ:" << id << "��ְ��������" << endl;
	}
}
// �޸�ְ��
void WorkerManager::mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "��ǰû��ְ��" << endl;
		return;
	}

	cout << "������Ҫ�޸ĵ�ְ�����" << endl;
	int id;
	cin >> id;
	int index = this->IsExist(id);
	if (index != -1)
	{
		delete this->m_EmpArr[index];
		int newId;
		string newName;
		int newDSelect;
		cout << "�鵽��" << id << "��ְ�����������µ�ְ���ţ�" << endl;
		cin >> newId;
		cout << "�������µ�����" << endl;
		cin >> newName;
		cout << "��ѡ���µĸ�λ" << endl;
		cout << "1. ��ְͨ��" << endl;
		cout << "2. ����" << endl;
		cout << "3. �ϰ�" << endl;
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
		cout << "�޸ĳɹ�" << endl;
		this->save();
		system("pause");
		system("cls");
	}
	else
	{
		cout << "���Ϊ:" << id << "��ְ��������" << endl;
	}
}
