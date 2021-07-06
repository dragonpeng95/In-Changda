#include "boss.h"

Boss::Boss(int id, string name, int departmentId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DepartmentId = departmentId;
}
void Boss::showInfo()
{
	cout << "职工编号:" << this->m_Id << "\t职工姓名:" << this->m_Name << "\t职工岗位:" << this->getDepartment()
		<< "\t岗位职责:完成公司所有事务" << endl;
}
string Boss::getDepartment()
{
	return (string)"老板";
}