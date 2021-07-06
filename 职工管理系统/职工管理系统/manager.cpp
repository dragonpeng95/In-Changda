#include "manager.h"

Manager::Manager(int id,string name,int departmentId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DepartmentId = departmentId;
}

void Manager::showInfo()
{
	cout << "职工编号:" << this->m_Id << "\t职工姓名:" << this->m_Name << "\t职工岗位:" << this->getDepartment()
		<< "\t岗位职责:完成老板交给的任务，将任务分发给下属" << endl;
}

string Manager::getDepartment()
{
	return (string)"经理";
}