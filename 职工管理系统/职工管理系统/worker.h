#pragma once
#include <iostream>
using namespace std;

class Worker
{ 
public:
	virtual void showInfo() = 0;       //��ȡԱ��������Ϣ
	virtual string getDepartment() = 0;//��ȡ���Ż�����Ϣ
	int m_Id;
	string m_Name;
	int m_DepartmentId;

};