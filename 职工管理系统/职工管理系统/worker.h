#pragma once
#include <iostream>
using namespace std;

class Worker
{ 
public:
	virtual void showInfo() = 0;       //获取员工基本信息
	virtual string getDepartment() = 0;//获取部门基本信息
	int m_Id;
	string m_Name;
	int m_DepartmentId;

};