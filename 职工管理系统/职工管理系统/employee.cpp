#include "employee.h"
Employee::Employee(int id, string name, int departmentId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DepartmentId = departmentId;
}

void Employee::showInfo()
{
	cout << "职工编号:" << this->m_Id << "\t职工姓名:" << this->m_Name << "\t职工岗位:" << this->getDepartment()
		<< "\t岗位职责:完成经理交给的任务" << endl;
}

string Employee::getDepartment()
{
	return "员工";
}
