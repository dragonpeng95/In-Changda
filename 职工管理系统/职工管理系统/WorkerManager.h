#pragma once
#include <iostream>
#include <fstream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#define FILENAME "Employee.txt"
using namespace std;

class WorkerManager
{
public:
	WorkerManager();

	void showMenu();//��ʾ�˵�

	int m_EmployeeNum;//��¼Ա������

	Worker** m_EmployeeArray;//Ա�������ָ��

	void AddEmployee();//��ӹ���

	void saveFile();//����Ϣ���浽�ļ�

	bool m_fileIsNull;//�����ж��ļ��Ƿ�Ϊ��

	int get_EmployeeNum();//���ļ�����ʱ��ͳ�Ƴ��ļ���Ա����

	void init_Employee();//��ȡ�ļ���Ϣ

	void show_Employee();//չʾԱ����Ϣ

	int IsExist(int find_Num);//�ж�Ҫ�ҵ�ְ���Ƿ���ڣ������򷵻�ְ����ţ��������򷵻�-1

	void delEmployee();//ɾ���ҵ���Ա��

	void modify_Employee();//�޸�Ա��

	void find_Employee();//����Ա��

	void Sort_Employee();//����

	void Clean_File();//����ļ�

	void ExitSystem();//�˳�ϵͳ����

	~WorkerManager();
};