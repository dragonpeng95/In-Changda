#include <iostream>
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "globalFile.h"
#include "Identity.h"
#include <fstream>
using namespace std;

//进入管理员界面
//指针引用,什么意思呢?传入的指针，加了引用而已
//因为使用new开辟的空间，所以返回的是指针(Identity* person = new Manager(username,password))
//父类指针指向子类对象，引用
void managerMenu(Identity*& manager)
{
	while (true)
	{
		//显示管理员界面
		//(*manager).openMenu();也可以
		manager->openMenu();//现在还是父类指针，只能调用父类的变量和函数
		
		//但是传入的父类指针指向子类对象
		Manager * man = (Manager*)manager;//强转为子类指针

		int select = 0;
		cout << "请输入选择:" << endl;
		cin >> select;

		//1.添加账号
		if (select == 1)
		{
			man->addPerson();
		}

		//2.查看账号
		else if(select == 2)
		{
			man->showPerson();
		}

		//3.查看机房
		else if(select == 3)
		{
			man->showComputer();
		}

		//4.清空预约
		else if(select == 4)
		{
			man->cleanFile();
		}

		//注销
		else
		{
			delete manager;
			cout << "注销成功!" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//教师菜单
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		teacher->openMenu();

		Teacher* tea = (Teacher*)teacher;//强转为教师指针

		cout << "请输入操作序号:" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			tea->showAllOrder();
			system("pause");
			system("cls");
		}
		else if(select == 2)
		{
			tea->validOrder();
			system("cls");
		}
		else if(select == 0)
		{
			delete teacher;
			cout << "注销成功!" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "输入有误，请重新输入!" << endl;
			system("pause");
			system("cls");
		}
		
	}
	

}

//学生菜单
void studentMenu(Identity*& student)
{
	while (true)
	{
		//展示学生菜单
		student->openMenu();

		//强转为student指针
		Student* stu = (Student*)student;

		cout << "请输入操作序号:" << endl;
		int select;

		cin >> select;
		if (select == 1)
		{
			//申请预约
			stu->applyOrder();
		}
		else if(select == 2)
		{
			//查看自身预约
			stu->showMyOrder();
		}
		else if(select == 3)
		{
			//查看所有预约
			stu->showAllOrder();
		}
		else if(select == 4)
		{
			//取消预约
			stu->cancelMyOrder();
		}
		else
		{
			delete student;
			cout << "注销成功!" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void LoginIn(string filename, int type)//filename表示即将操作的文件夹，type表示身份
{
	Identity* person = NULL;
	ifstream ifs;//读文件流
	ifs.open(filename, ios::in);
	if (!ifs.is_open())
	{
		ofstream ofs;
		cout << "文件打开失败!" << endl;
		ofs.open(filename, ios::out);//写文件没有就会创建，读文件流不会，这里利用写文件流创建文件
		cout << "--------------------------------" << endl;
		cout << "文件创建成功!" << endl;
		ofs.close();
	}
	int id;
	if (type == 1)
	{
		cout << "请输入学号:";
		cin >> id;
	}
	else if(type == 2)
	{
		cout << "请输入教师编号:";
		cin >> id;
	}
	cout << "请输入用户名:";
	string name;
	cin >> name;

	cout << "请输入密码:";
	string password;
	cin >> password;

	if (type == 1)
	{
		//对学生进行操作
		int studentId;
		string studentUserName;
		string studentPassword;
		while (ifs >> studentId && ifs >> studentUserName && ifs >> studentPassword)//一行一行读，空格分开
		{
			if (studentId == id && studentUserName == name && studentPassword == password)
			{
				//如果读取的id，用户名，密码和输入的id，用户名，密码一致，则登陆成功
				cout << "学生"<< studentUserName <<"登陆成功!" << endl;
				system("pause");
				system("cls");
				//指针依然是父类类型，只能使用父类方法或变量(但是能调用父类和子类都有的纯虚函数，实现多态)
				person = new Student(id,name,password);
				//跳到学生界面
				studentMenu(person);

				return;
			}
		}
	}
	else if(type == 2)
	{
		//对老师进行操作
		int teacherId;
		string teacherUserName;
		string teacherPassword;
		while (ifs>>teacherId && ifs>>teacherUserName && ifs>>teacherPassword)
		{
			if (teacherId == id && teacherUserName == name && teacherPassword == password)
			{
				cout << "教师" << teacherUserName << "登陆成功!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id,name,password);
				//进入教师界面
				teacherMenu(person);
				return;
			}
		}
	}
	else if(type == 3)
	{
		//对管理员进行操作
		string managerName;
		string managerPassword;
		while (ifs>>managerName && ifs >> managerPassword)
		{
			if (name == managerName && password == managerPassword)
			{
				cout << "管理员" << managerName << "登陆成功!" << endl;
				system("pause");
				system("cls");
				person = new Manager(managerName, managerPassword);
				//跳转到管理员界面
				managerMenu(person);
				return;
			}
		}
	}

	cout << "登陆失败!" << endl;
	system("pause");
	system("cls");
}

int main()
{
	while (true)
	{
		cout << "==========================  长江大学机房预约系统  ==========================" << endl;
		cout << "                                                                            " << endl;
		cout << "                                                                            " << endl;
		cout << "                         --------------------------                         " << endl;
		cout << "                         |                        |                         " << endl;
		cout << "                         |        1.学生代表      |                         " << endl;
		cout << "                         |                        |                         " << endl;
		cout << "                         |        2.老    师      |                         " << endl;
		cout << "                         |                        |                         " << endl;
		cout << "                         |        3.管 理 员      |                         " << endl;
		cout << "                         |                        |                         " << endl;
		cout << "                         |        0.退    出      |                         " << endl;
		cout << "                         |                        |                         " << endl;
		cout << "                         --------------------------                         " << endl;
		cout << "请输出您的选择:";
		int select;
		cin >> select;
		switch (select)
		{
		case 1:
			LoginIn(STUDENT_FILE,select);
			break;
		case 2:
			LoginIn(TEACHER_FILE, select);
			break;
		case 3:
			LoginIn(ADMIN_FILE, select);
			break;
		case 0:
			cout << "欢迎下次使用！" << endl;
			system("pause");
			exit(0);
			break;
		default:
			cout << "输入有误,请重新选择!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}