#include "boss.h"

Boss::Boss(int id, string name, int departmentId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DepartmentId = departmentId;
}
void Boss::showInfo()
{
	cout << "ְ�����:" << this->m_Id << "\tְ������:" << this->m_Name << "\tְ����λ:" << this->getDepartment()
		<< "\t��λְ��:��ɹ�˾��������" << endl;
}
string Boss::getDepartment()
{
	return (string)"�ϰ�";
}