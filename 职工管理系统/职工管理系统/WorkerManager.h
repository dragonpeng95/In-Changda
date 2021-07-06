#pragma once
#include <iostream>
#include <fstream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#define FILENAME "Employee.txt"
using namespace std;

class WorkerManager
{
public:
	WorkerManager();

	void showMenu();//显示菜单

	int m_EmployeeNum;//记录员工人数

	Worker** m_EmployeeArray;//员工数组的指针

	void AddEmployee();//添加功能

	void saveFile();//将信息保存到文件

	bool m_fileIsNull;//用来判断文件是否为空

	int get_EmployeeNum();//当文件存在时，统计出文件中员工数

	void init_Employee();//读取文件信息

	void show_Employee();//展示员工信息

	int IsExist(int find_Num);//判断要找的职工是否存在，存在则返回职工编号，不存在则返回-1

	void delEmployee();//删除找到的员工

	void modify_Employee();//修改员工

	void find_Employee();//查找员工

	void Sort_Employee();//排序

	void Clean_File();//清空文件

	void ExitSystem();//退出系统功能

	~WorkerManager();
};