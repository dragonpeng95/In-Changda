#include <iostream>
#include <string>
#include "WorkerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;



int main()
{ 
	//���Դ���
	/*Worker* worker = new Employee(1,"������",1);
	worker->showInfo();
	delete worker;

	worker = new Manager(2, "����", 1);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "����", 1);
	worker->showInfo();
	delete worker;*/

	WorkerManager wm;
	int select = 0;
	while (true)
	{
		wm.showMenu();

		cout << "����������Ҫ�Ĳ������:";
		cin >> select;
		switch (select)
		{
		case 0:    //�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1:    //����ְ����Ϣ
			wm.AddEmployee();
			break;
		case 2:	   //��ʾְ����Ϣ
			wm.show_Employee();
			break;
		case 3:	   //ɾ��ְ����Ϣ
			wm.delEmployee();			
			break;
		case 4:	   //�޸�ְ����Ϣ
			wm.modify_Employee();
			break;
		case 5:    //����ְ����Ϣ
			wm.find_Employee();
			break;
		case 6:	   //���ձ������
			wm.Sort_Employee();
			break;
		case 7:    //��������ĵ�
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