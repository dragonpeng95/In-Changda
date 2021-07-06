#include <iostream>
#include <string>
#include "WorkerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;



int main()
{ 
	//测试代码
	/*Worker* worker = new Employee(1,"彭章龙",1);
	worker->showInfo();
	delete worker;

	worker = new Manager(2, "张三", 1);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "李四", 1);
	worker->showInfo();
	delete worker;*/

	WorkerManager wm;
	int select = 0;
	while (true)
	{
		wm.showMenu();

		cout << "请输入您需要的操作序号:";
		cin >> select;
		switch (select)
		{
		case 0:    //退出系统
			wm.ExitSystem();
			break;
		case 1:    //增加职工信息
			wm.AddEmployee();
			break;
		case 2:	   //显示职工信息
			wm.show_Employee();
			break;
		case 3:	   //删除职工信息
			wm.delEmployee();			
			break;
		case 4:	   //修改职工信息
			wm.modify_Employee();
			break;
		case 5:    //查找职工信息
			wm.find_Employee();
			break;
		case 6:	   //按照编号排序
			wm.Sort_Employee();
			break;
		case 7:    //清空所有文档
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;

			
		}
	}
	system("pause");
	return 0;
}