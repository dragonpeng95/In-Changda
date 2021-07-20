#pragma once
#include <iostream>
#include "Identity.h"
#include "globalFile.h"
#include <fstream>
#include <vector>
#include "student.h"
#include "teacher.h"
#include <algorithm>
#include "computerRoom.h"
using namespace std;

class Manager :public Identity
{
public:
	//默认构造
	Manager();

	//有参构造
	Manager(string name, string password);

	//选择菜单
	virtual void openMenu();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	void cleanFile();

	//初始化容器
	void initVector();

	//检测重复 id是输入的id(学号，教师编号)，type是添加的类型
	bool checkRepeat(int id,int type);

	//学生容器
	vector<Student> vStu;

	//教师容器
	vector<Teacher> vTea;

	//机房容器
	vector<ComputerRoom> vCom;

	//初始化机房信息
	void initComputerRoom();
};