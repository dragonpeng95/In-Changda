#include "employee.h"
Employee::Employee(int id, string name, int departmentId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DepartmentId = departmentId;
}

void Employee::showInfo()
{
	cout << "ְ�����:" << this->m_Id << "\tְ������:" << this->m_Name << "\tְ����λ:" << this->getDepartment()
		<< "\t��λְ��:��ɾ�����������" << endl;
}

string Employee::getDepartment()
{
	return "Ա��";
}
