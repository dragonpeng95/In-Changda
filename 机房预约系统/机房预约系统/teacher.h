#pragma once
#include <iostream>
#include "Identity.h"
#include <fstream>
#include "globalFile.h"
#include "orderFile.h"
#include <vector>
using namespace std;

class Teacher:public Identity
{
public:
	//Ĭ�Ϲ���
	Teacher();

	//�вι���
	Teacher(int id, string username, string password);

	//��д�˵����飬ʵ�ֶ�̬
	virtual void openMenu();

	//�鿴����ԤԼ
	void  showAllOrder();

	//���ԤԼ
	void validOrder();

	int m_TeacherId;
};