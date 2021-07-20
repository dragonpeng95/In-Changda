#pragma once
#include "student.h"

//Ĭ�Ϲ���
Student::Student() 
{

}

//�вι���
Student::Student(int id, string username, string password)
{
	this->m_Id = id;
	this->m_Name = username;
	this->m_Password = password;

	//��ʼ��������Ϣ
	this->initComputerRoom();
}

//�˵�����
void Student::openMenu()
{
	cout << "��ӭѧ������:" << this->m_Name << "��½��" << endl;
	cout << "\t\t --------------------------------------\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             1.����ԤԼ              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             2.�鿴�ҵ�ԤԼ          |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             3.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             4.ȡ��ԤԼ              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             0.ע����½              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t --------------------------------------\n";

}

//����ԤԼ
void Student::applyOrder()
{
	cout << "��������ʱ��Ϊ��һ������!" << endl;
	cout << "����������ԤԼʱ��:" << endl;
	cout << "1.��һ" << endl;
	cout << "2.�ܶ�" << endl;
	cout << "3.����" << endl;
	cout << "4.����" << endl;
	cout << "5.����" << endl;
	int data;//����
	while (true)
	{
		cin >> data;
		if (data == 1 || data == 2 || data == 3 || data == 4 || data == 5)
		{
			break;
		}
		cout << "������������������:";
	}

	cout << "����������ʱ���:" << endl;
	cout << "1.����" << endl;
	cout << "2.����" << endl;
	int interval;
	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		cout << "��������,����������:";
	}

	cout << "��ѡ�����:" << endl;
	cout << this->vCom[0].roomId << "�Ż���������:" << this->vCom[0].roomSize << endl;
	cout << this->vCom[1].roomId << "�Ż���������:" << this->vCom[1].roomSize << endl;
	cout << this->vCom[2].roomId << "�Ż���������:" << this->vCom[2].roomSize << endl;
	int room;
	while (true)
	{
		cin >> room;
		if (room == 1 || room == 2 || room == 3)
		{
			break;
		}
		cout << "��������,����������:";
	}

	cout << "ԤԼ�ɹ�,�����!" << endl;
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::app);
	string m_data;//�����洢����
	switch (data)
	{
	case 1:
		m_data = "��һ";
		break;
	case 2:
		m_data = "�ܶ�";
		break;
	case 3:
		m_data = "����";
		break;
	case 4:
		m_data = "����";
		break;
	case 5:
		m_data = "����";
		break;
	default:
		break;
	}
	string m_interval;//�����洢ʱ���
	switch (interval)
	{
	case 1:
		m_interval = "����";
		break;
	case 2:
		m_interval = "����";
		break;
	default:
		break;
	}

	string m_room;//�洢����Ļ�����
	switch (room)
	{
	case 1:
		m_room = "1�Ż���";
		break;
	case 2:
		m_room = "2�Ż���";
		break;
	case 3:
		m_room = "3�Ż���";
		break;
	default:
		break;
	}

	ofs << "����:" << m_data
		<< " ʱ���:" << m_interval
		<< " ѧ��ѧ��:" << this->m_Id
		<< " ѧ������:" << this->m_Name
		<< " ������:" << m_room
		<< " ״̬:" << "�����" << endl;
	ofs.close();
	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::showMyOrder()
{
	OrderFile orderFile;
	if (orderFile.m_Size == 0)
	{
		cout << "��ǰ��ԤԼ!" << endl;
		return;
	}
	//cout << orderFile.m_Map.size() << "����¼" << endl;
	multimap<bool,map<string, string>> m_tempGlobal;
	for (map<int,map<string,string>>::iterator it = orderFile.m_Map.begin();it!=orderFile.m_Map.end();it++)
	{
		bool flag = false;//�������ԤԼ�е����У���flag��Ϊtrue
		map<string, string> m_temp;
		for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
		{
			m_temp.insert(pair<string,string>(mit->first, (*mit).second));
			if ((*mit).second == this->m_Name)
			{
				flag = true;
			}
		}
		//���������¼bool��Ϊtrue����ֻ�ܲ���һ�����������ظ�,����multimap����
		m_tempGlobal.insert(pair<bool,map<string,string>>(flag, m_temp));
	}
	for (map<bool, map<string, string>>::iterator it = m_tempGlobal.begin(); it != m_tempGlobal.end(); it++)
	{
		if ((*it).first == true)
		{
			for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
			{
				cout << (*mit).first << ":" << (*mit).second << " ";
			}
			cout << endl;
		}
	}
	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::showAllOrder()
{
	OrderFile orderFile;
	if (orderFile.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (map<int, map<string, string>>::iterator it = orderFile.m_Map.begin(); it != orderFile.m_Map.end(); it++)
	{
		for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
		{
			cout << (*mit).first << ":" << (*mit).second << " ";
		}
		cout << endl;
	}
	system("pause");
	system("cls");
}

//ȡ��ԤԼ
void Student::cancelMyOrder()
{
	OrderFile orderFile;
	if (orderFile.m_Size == 0)
	{
		cout << "ԤԼ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	//��ѧ���ҳ��Լ���ԤԼ
	map<int, map<string,string>> m_selfMap;//��һ��int����Լ��ļ�¼���ڶ���int����Լ���¼�����м�¼�еĵڼ���
	int indexSelf = 1;
	int indexAll = 0;
	vector<int> v;//��������м�¼�е�����
	for (map<int, map<string, string>>::iterator it = orderFile.m_Map.begin(); it != orderFile.m_Map.end(); it++)
	{
		bool flag = false;
		map<string, string> m_temp;
		//map<string, string> m_temp2;
		for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
		{
			
			m_temp.insert(pair<string,string>(mit->first, mit->second));
			if (this->m_Id == atoi((mit->second).c_str()))//�ļ���ȡ���ַ���תint
			{
				flag = true;
			}

		}
		if (flag == true)
		{
			m_selfMap.insert(pair<int,map<string,string>>(indexSelf,m_temp));
			v.push_back(indexAll);
			indexSelf++;
		}
		indexAll++;
	}

	cout << "����ǰԤԼ:" << endl;
	for (map<int,map<string,string>>::iterator it = m_selfMap.begin(); it != m_selfMap.end(); it++)
	{
		cout << it->first << " ";
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			cout << mit->first << ":" << mit->second << " ";
		}
		cout << endl;
	
	}
	//����vector�Ƿ��õ���m_Map�е�λ��
	/*for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "******" << *it << "******" << endl;
	}*/

	cout << "������Ҫȡ��ԤԼ�����:" << endl;
	int select;
	int index;
	while (true)
	{
		cin >> select;
		if (select >= 1 && select <= v.size())
		{
			index = v[select - 1];//�õ���m_Map�е�����
			break;
		}
		cout << "������������������:";
	}
	int cancel;
	while (true)
	{
		cout << "�Ƿ�ȷ��ȡ��:" << endl;
		cout << "1.ȷ��" << endl;
		cout << "2.����" << endl;
		cin >> cancel;
		if (cancel == 1)
		{
			string status = "ȡ��ԤԼ";
			orderFile.m_Map[index+1]["״̬"] = status;
			orderFile.updateOrder();
			system("pause");
			return;
		}
		else if (cancel == 2)
		{
			system("pause");
			return;
		}
		cout << "������������������!" << endl;
	}
}

//��ʼ����������
void Student::initComputerRoom()
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
	while (ifs>>computerRoom.roomId && ifs>>computerRoom.roomSize)
	{
		this->vCom.push_back(computerRoom);
	}
	ifs.close();
	cout << "��������:" << this->vCom.size() << endl;
}