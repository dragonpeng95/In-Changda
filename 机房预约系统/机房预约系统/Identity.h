#pragma once
#include <iostream>
using namespace std;

class Identity
{
public:

	virtual void openMenu() = 0;//纯虚，给子类来重写，实现多态

	string m_Name;//用户名
	string m_Password;//密码
};