#include "teacher.h"

//Ĭ�Ϲ���
Teacher::Teacher()
{

}

//�вι���
Teacher::Teacher(int id, string username, string password)
{
	this->m_TeacherId = id;
	this->m_Name = username;
	this->m_Password = password;
}

//��д�˵����飬ʵ�ֶ�̬
void Teacher::openMenu()
{
	cout << "��ӭ��ʦ: " << this->m_Name << "��½��" << endl;
	cout << "\t\t --------------------------------------\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             1.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             2.���ԤԼ              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             0.ע����½              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t --------------------------------------\n";
}

//�鿴����ԤԼ
void Teacher::showAllOrder()
{
	OrderFile orderFile;
	if (orderFile.m_Size == 0)
	{
		cout << "��ǰ��ԤԼ!" << endl;
		system("pause");
		system("cls");
		return;
	}
	int index = 1;
	for (map<int, map<string, string>>::iterator it = orderFile.m_Map.begin(); it != orderFile.m_Map.end(); it++)
	{
		cout << index << "��";
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			cout << mit->first << ":" << mit->second << " ";
		}
		cout << endl;
		index++;
	}
}

//���ԤԼ
void Teacher::validOrder()
{
	OrderFile orderFile;
	if (orderFile.m_Size == 0)
	{
		cout << "��ǰ��ԤԼ��¼!" << endl;
		system("pause");
		system("cls");
		return;
	}
	/*for (map<int, map<string, string>>::iterator it = orderFile.m_Map.begin(); it != orderFile.m_Map.end(); it++)
	{
		cout << it->first << "��";
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			cout << mit->first << ":" << mit->second << " ";
		}
		cout << endl;
	}*/

	//�ҳ����������״̬��ԤԼ��Ϣ
	map<int, map<string, string>> mapProcessing;//int���ԤԼ����
	vector<int> vProcessing;//������״̬��ԤԼ��m_Map�е�����
	int indexAll = 1;
	int index = 0; 
	string status = "�����";
	for (map<int, map<string, string>>::iterator it = orderFile.m_Map.begin(); it != orderFile.m_Map.end(); it++)
	{
		bool flag = false;
		map<string, string> m_temp;
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			m_temp.insert(pair<string,string>(mit->first, mit->second));
			if (mit->second == status)
			{
				flag = true;
			}
		}

		if (flag == true)
		{
			mapProcessing.insert(pair<int, map<string, string>>(indexAll, m_temp));
			indexAll++; 
			
			vProcessing.push_back(index);
		}
		
		index++;
	}

	//������������е�ԤԼ
	if (mapProcessing.size() == 0)
	{
		cout << "��ǰ������е�ԤԼ!" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (map<int, map<string, string>>::iterator it = mapProcessing.begin(); it != mapProcessing.end(); it++)
	{
		cout << it->first << "��";
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			cout << mit->first << ":" << mit->second << " ";
		}
		cout << endl;
	}

	//����vProcessing����
	/*for (vector<int>::iterator it = vProcessing.begin(); it != vProcessing.end(); it++)
	{
		cout << *it << endl;
	}*/

	while (true)
	{
		cout << "��������Ҫ��˵�ԤԼ���:";
		int select;
		cin >> select;
		if (select >= 1 && select <= vProcessing.size())
		{
			//�ҵ���m_Map�е�����
			int index = vProcessing[select-1];
			//cout << orderFile.m_Map[index+1]["״̬"] << endl;
			while (true)
			{
				cout << "��������Ҫ��Ϊ��״̬:" << endl;
				cout << "1.ԤԼ�ɹ�" << endl;
				cout << "2.ԤԼʧ��" << endl;
				int selectStatus;
				cin >> selectStatus;
				if (selectStatus == 1)
				{
					orderFile.m_Map[index + 1]["״̬"] = "ԤԼ�ɹ�";
					orderFile.updateOrder();
					break;
				}
				if (selectStatus == 2)
				{
					orderFile.m_Map[index + 1]["״̬"] = "ԤԼʧ��";
					orderFile.updateOrder();
					break;
				}
				cout << "������������������!" << endl;
			}
			cout << "���ԤԼ�ɹ�!" << endl;
			system("pause");
			break;
		}
		cout << "������������������!" << endl;
	}

}