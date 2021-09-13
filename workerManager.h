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
	// ���캯��
	WorkerManager();
	// ��ʼ��������
	void InitEmptyData(ifstream*  ifs);
	// չʾ�˵�
	void Show_Menu();
	// �˳�ϵͳ
	void exitSystem();

	// ��¼ְ������
	int m_EmpNum;

	// ְ������ָ��
	Worker** m_EmpArr;

	// ���ְ��
	void addEmp();

	// �����ļ�
	void save();

	// �ж��ļ��Ƿ�Ϊ�ձ�־
	bool m_FileIsEmpty;

	// ͳ���ļ�������
	int get_EmpNum();

	// ��ʼ��ְ��
	void init_Emp();

	// ��ʾְ��
	void show_Emp();

	// �ж�ְ���Ƿ����
	int IsExist(int id);

	// ɾ��ְ��
	void del_Emp();

	// �޸�ְ��
	void mod_Emp();

	// ��������
	~WorkerManager();
};