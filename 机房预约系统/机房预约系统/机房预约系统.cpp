#include <iostream>
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "globalFile.h"
#include "Identity.h"
#include <fstream>
using namespace std;

//�������Ա����
//ָ������,ʲô��˼��?�����ָ�룬�������ö���
//��Ϊʹ��new���ٵĿռ䣬���Է��ص���ָ��(Identity* person = new Manager(username,password))
//����ָ��ָ�������������
void managerMenu(Identity*& manager)
{
	while (true)
	{
		//��ʾ����Ա����
		//(*manager).openMenu();Ҳ����
		manager->openMenu();//���ڻ��Ǹ���ָ�룬ֻ�ܵ��ø���ı����ͺ���
		
		//���Ǵ���ĸ���ָ��ָ���������
		Manager * man = (Manager*)manager;//ǿתΪ����ָ��

		int select = 0;
		cout << "������ѡ��:" << endl;
		cin >> select;

		//1.����˺�
		if (select == 1)
		{
			man->addPerson();
		}

		//2.�鿴�˺�
		else if(select == 2)
		{
			man->showPerson();
		}

		//3.�鿴����
		else if(select == 3)
		{
			man->showComputer();
		}

		//4.���ԤԼ
		else if(select == 4)
		{
			man->cleanFile();
		}

		//ע��
		else
		{
			delete manager;
			cout << "ע���ɹ�!" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//��ʦ�˵�
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		teacher->openMenu();

		Teacher* tea = (Teacher*)teacher;//ǿתΪ��ʦָ��

		cout << "������������:" << endl;
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
			cout << "ע���ɹ�!" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "������������������!" << endl;
			system("pause");
			system("cls");
		}
		
	}
	

}

//ѧ���˵�
void studentMenu(Identity*& student)
{
	while (true)
	{
		//չʾѧ���˵�
		student->openMenu();

		//ǿתΪstudentָ��
		Student* stu = (Student*)student;

		cout << "������������:" << endl;
		int select;

		cin >> select;
		if (select == 1)
		{
			//����ԤԼ
			stu->applyOrder();
		}
		else if(select == 2)
		{
			//�鿴����ԤԼ
			stu->showMyOrder();
		}
		else if(select == 3)
		{
			//�鿴����ԤԼ
			stu->showAllOrder();
		}
		else if(select == 4)
		{
			//ȡ��ԤԼ
			stu->cancelMyOrder();
		}
		else
		{
			delete student;
			cout << "ע���ɹ�!" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void LoginIn(string filename, int type)//filename��ʾ�����������ļ��У�type��ʾ���
{
	Identity* person = NULL;
	ifstream ifs;//���ļ���
	ifs.open(filename, ios::in);
	if (!ifs.is_open())
	{
		ofstream ofs;
		cout << "�ļ���ʧ��!" << endl;
		ofs.open(filename, ios::out);//д�ļ�û�оͻᴴ�������ļ������ᣬ��������д�ļ��������ļ�
		cout << "--------------------------------" << endl;
		cout << "�ļ������ɹ�!" << endl;
		ofs.close();
	}
	int id;
	if (type == 1)
	{
		cout << "������ѧ��:";
		cin >> id;
	}
	else if(type == 2)
	{
		cout << "�������ʦ���:";
		cin >> id;
	}
	cout << "�������û���:";
	string name;
	cin >> name;

	cout << "����������:";
	string password;
	cin >> password;

	if (type == 1)
	{
		//��ѧ�����в���
		int studentId;
		string studentUserName;
		string studentPassword;
		while (ifs >> studentId && ifs >> studentUserName && ifs >> studentPassword)//һ��һ�ж����ո�ֿ�
		{
			if (studentId == id && studentUserName == name && studentPassword == password)
			{
				//�����ȡ��id���û���������������id���û���������һ�£����½�ɹ�
				cout << "ѧ��"<< studentUserName <<"��½�ɹ�!" << endl;
				system("pause");
				system("cls");
				//ָ����Ȼ�Ǹ������ͣ�ֻ��ʹ�ø��෽�������(�����ܵ��ø�������඼�еĴ��麯����ʵ�ֶ�̬)
				person = new Student(id,name,password);
				//����ѧ������
				studentMenu(person);

				return;
			}
		}
	}
	else if(type == 2)
	{
		//����ʦ���в���
		int teacherId;
		string teacherUserName;
		string teacherPassword;
		while (ifs>>teacherId && ifs>>teacherUserName && ifs>>teacherPassword)
		{
			if (teacherId == id && teacherUserName == name && teacherPassword == password)
			{
				cout << "��ʦ" << teacherUserName << "��½�ɹ�!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id,name,password);
				//�����ʦ����
				teacherMenu(person);
				return;
			}
		}
	}
	else if(type == 3)
	{
		//�Թ���Ա���в���
		string managerName;
		string managerPassword;
		while (ifs>>managerName && ifs >> managerPassword)
		{
			if (name == managerName && password == managerPassword)
			{
				cout << "����Ա" << managerName << "��½�ɹ�!" << endl;
				system("pause");
				system("cls");
				person = new Manager(managerName, managerPassword);
				//��ת������Ա����
				managerMenu(person);
				return;
			}
		}
	}

	cout << "��½ʧ��!" << endl;
	system("pause");
	system("cls");
}

int main()
{
	while (true)
	{
		cout << "==========================  ������ѧ����ԤԼϵͳ  ==========================" << endl;
		cout << "                                                                            " << endl;
		cout << "                                                                            " << endl;
		cout << "                         --------------------------                         " << endl;
		cout << "                         |                        |                         " << endl;
		cout << "                         |        1.ѧ������      |                         " << endl;
		cout << "                         |                        |                         " << endl;
		cout << "                         |        2.��    ʦ      |                         " << endl;
		cout << "                         |                        |                         " << endl;
		cout << "                         |        3.�� �� Ա      |                         " << endl;
		cout << "                         |                        |                         " << endl;
		cout << "                         |        0.��    ��      |                         " << endl;
		cout << "                         |                        |                         " << endl;
		cout << "                         --------------------------                         " << endl;
		cout << "���������ѡ��:";
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
			cout << "��ӭ�´�ʹ�ã�" << endl;
			system("pause");
			exit(0);
			break;
		default:
			cout << "��������,������ѡ��!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}