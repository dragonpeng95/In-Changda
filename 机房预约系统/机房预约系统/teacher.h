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
	//默认构造
	Teacher();

	//有参构造
	Teacher(int id, string username, string password);

	//重写菜单纯虚，实现多态
	virtual void openMenu();

	//查看所有预约
	void  showAllOrder();

	//审核预约
	void validOrder();

	int m_TeacherId;
};