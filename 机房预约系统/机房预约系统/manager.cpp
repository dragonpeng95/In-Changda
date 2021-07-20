#include "manager.h"

//Ĭ�Ϲ���
Manager::Manager()
{

}

//�вι���
Manager::Manager(string name, string password)
{
	this->m_Name = name;
	this->m_Password = password;

	//��ʼ������ ��ȡ�������ļ��� ѧ������ʦ����Ϣ
	this->initVector();

	//��ʼ��������Ϣ
	this->initComputerRoom();
}

//ѡ��˵�
void Manager::openMenu()
{
	cout << "��ӭ����Ա��" << this->m_Name << "��½!" << endl;
	cout << "\t\t --------------------------------------\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             1.����˺�              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             2.�鿴�˺�              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             3.�鿴����              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             4.���ԤԼ              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             0.ע����½              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t --------------------------------------\n";
	cout << "���������Ĳ���:" << endl;
}

//����˺�
void Manager::addPerson()
{
	system("cls");
	this->initVector();
	this->openMenu();
	string fileName;//�������ļ���
	string tips;//��ʾ
	int select;
	while (true)
	{
		cout << "��������ӵ�����" << endl;
		cout << "1.ѧ��" << endl;
		cout << "2.��ʦ" << endl;	
		cin >> select;
		if (select == 1)
		{
			fileName = STUDENT_FILE;
			tips = "������ѧ��ѧ��:";
			break;
		}
		else if(select == 2)
		{
			fileName = TEACHER_FILE;
			tips = "�������ʦ���:";
			break;
		}
		cout << "��������,���������룡" << endl;
		system("pause");
		system("cls");
		this->openMenu();
	}
	ofstream ofs;
	ofs.open(fileName, ios::out | ios::app);//׷�ӷ�ʽ

	int id;
	while (true)
	{
		cout << tips;		
		cin >> id;
		bool ret = this->checkRepeat(id, select);//�ظ�����true�����ظ�����false
		if (ret == false)//���ظ�
		{
			break;
		}
	}
	
	cout << "�������û���:";
	string username;
	cin >> username;

	cout << "����������:";
	string password;
	cin >> password;

	ofs << id << " " << username << " " << password << endl;
	cout << "��ӳɹ�!" << endl;
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();
	
}

//ѧ��ȫ�ַº��� ��for_eachʹ��
class MyPrintStu
{
public:
	void operator()(Student& s)
	{
		cout << "ѧ��:" << s.m_Id << " ����:" << s.m_Name << " ����:" << s.m_Password << endl;
	}
};

//��ʦȫ�ַº��� ��for_eachʹ��
class MyPrintTea
{
public:
	void operator()(Teacher& t)
	{
		cout << "ѧ��:" << t.m_Name << " ����:" << t.m_TeacherId << " ����:" << t.m_Password << endl;
	}
};

//�鿴�˺�
void Manager::showPerson()
{
	int select;
	while (true)
	{
		cout << "������鿴������:" << endl;
		cout << "1.ѧ���˺�" << endl;
		cout << "2.��ʦ�˺�" << endl;
		cin >> select;
		if (select == 1)
		{
			for_each(this->vStu.begin(), this->vStu.end(), MyPrintStu());
			break;
		}
		if (select == 2)
		{
			for_each(this->vTea.begin(), this->vTea.end(), MyPrintTea());
			break;
		}
		cout << "������������������!" << endl;
	}
	system("pause");
	system("cls");
}

//�鿴������Ϣ
void Manager::showComputer()
{
	for (vector<ComputerRoom>::iterator it = this->vCom.begin(); it != this->vCom.end(); it++)
	{
		cout << "�������:" << it->roomId << "   �����������:" << it->roomSize << endl;
	}
	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Manager::cleanFile()
{
	cout << "ȷ���������ԤԼ��?" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select;
	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			ofstream ofs;
			ofs.open(ORDER_FILE, ios::out | ios::trunc);
			ofs.close();
			cout << "��ճɹ�!" << endl;
			break;
		}
		else if (select == 2)
		{
			break;
		}
		cout << "������������������:" << endl;
		cout << "1.ȷ��" << endl;
		cout << "2.����" << endl;

	}
	system("pause");
	system("cls");
}

//��ʼ������
void Manager::initVector()
{
	//ȷ������Ϊ��
	this->vStu.clear();
	this->vTea.clear();

	//��ȡ��Ϣ
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "ѧ���ļ���ȡ��Ϣʧ��,���������Ϣ!" << endl;
		return;
	}

	Student s;
	while (ifs>>s.m_Id && ifs>>s.m_Name && ifs>>s.m_Password)
	{
		this->vStu.push_back(s);
	}
	cout << "��ǰѧ������:" << this->vStu.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	/*if (!ifs.is_open())
	{
		cout << "��ʦ��Ϣ��ȡʧ��,������ӽ�ʦ��Ϣ!" << endl;
		return;
	}*/
	Teacher t;
	while (ifs>>t.m_TeacherId && ifs>>t.m_Name && ifs>>t.m_Password)
	{
		this->vTea.push_back(t);
	}
	cout << "��ǰ��ʦ����:" << this->vTea.size() << endl;

	ifs.close();
}


//����ظ� id�������id(ѧ�ţ���ʦ���)��type����ӵ�����
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)//���ѧ��
	{
		for (vector<Student>::iterator it = this->vStu.begin(); it != this->vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				cout << "ѧ���Ѵ��ڣ�����������!" << endl;
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = this->vTea.begin(); it != this->vTea.end(); it++)
		{
			if (id == it->m_TeacherId)
			{
				cout << "��ʦ����Ѵ��ڣ�����������!" << endl;
				return true;
			}
		}
	}
	return false;
}

//��ʼ��������Ϣ
void Manager::initComputerRoom()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		ofstream ofs;
		ofs.open(COMPUTER_FILE, ios::out);
		ofs << 1 << " " << 20 << endl;
		ofs << 2 << " " << 50 << endl;
		ofs << 3 << " " << 100 << endl;
		ofs.close();
		ifs.close();
		ifs.open(COMPUTER_FILE, ios::in);
	}
	ComputerRoom computerRoom;
	while (ifs>> computerRoom.roomId && ifs>> computerRoom.roomSize)
	{
		this->vCom.push_back(computerRoom);
	}
	cout << "��������Ϊ:" << this->vCom.size() << endl;
	ifs.close();

}