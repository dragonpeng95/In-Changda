#include "manager.h"

Manager::Manager(int id,string name,int departmentId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DepartmentId = departmentId;
}

void Manager::showInfo()
{
	cout << "ְ�����:" << this->m_Id << "\tְ������:" << this->m_Name << "\tְ����λ:" << this->getDepartment()
		<< "\t��λְ��:����ϰ彻�������񣬽�����ַ�������" << endl;
}

string Manager::getDepartment()
{
	return (string)"����";
}