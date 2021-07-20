#include "orderFile.h"


OrderFile::OrderFile()//����
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		ofstream ofs;
		ofs.open(ORDER_FILE, ios::out);
		ofs.close();
		ifs.close();
		ifs.open(ORDER_FILE, ios::out);
	}

	string m_Data;//����
	string m_Interval;//ʱ���
	string m_Id;//ѧ��
	string m_Name;//����
	string m_Room;//������
	string m_Status;//ԤԼ״̬

	while (ifs>>m_Data && ifs>>m_Interval && ifs>>m_Id && ifs>>m_Name && ifs>>m_Room && ifs>>m_Status)
	{
		/*cout << m_Data << endl;
		cout << m_Interval << endl;
		cout << m_Id << endl;
		cout << m_Name << endl;
		cout << m_Room << endl;
		cout << m_Status << endl;*/
		map<string, string> m;
		string key;
		string value;
		int position = m_Data.find(":");//����:��һ
		if (position != -1)
		{
			key = m_Data.substr(0, position);
			value = m_Data.substr(position + 1, m_Data.size() - position - 1);
			m.insert(pair<string, string>(key, value));
		}

		position = m_Interval.find(":");
		if (position != -1)
		{
			key = m_Interval.substr(0, position);
			value = m_Interval.substr(position + 1, m_Interval.size() - position - 1);
			m.insert(pair<string, string>(key, value));
		}

		position = m_Id.find(":");
		if (position != -1)
		{
			key = m_Id.substr(0, position);
			value = m_Id.substr(position + 1, m_Id.size() - position - 1);
			m.insert(pair<string, string>(key, value));
		}

		position = m_Name.find(":");
		if (position != -1)
		{
			key = m_Name.substr(0, position);
			value = m_Name.substr(position + 1, m_Name.size() - position - 1);
			m.insert(pair<string, string>(key, value));
		}

		position = m_Room.find(":");
		if (position != -1)
		{
			key = m_Room.substr(0, position);
			value = m_Room.substr(position + 1, m_Room.size() - position - 1);
			m.insert(pair<string, string>(key, value));
		}

		position = m_Status.find(":");
		if (position != -1)
		{
			key = m_Status.substr(0, position);
			value = m_Status.substr(position + 1, m_Status.size() - position - 1);
			m.insert(pair<string, string>(key, value));
		}

		this->m_Size++;
		this->m_Map.insert(pair<int, map<string, string>>(this->m_Size, m));

	}
	//���Դ���
	/*for (map<int,map<string,string>>::iterator it = this->m_Map.begin();it != this->m_Map.end(); it++)
	{
		cout << "��" << it->first << "����¼:" << endl;
		for (map<string, string>::iterator itm = (*it).second.begin(); itm != (*it).second.end(); itm++)
		{
			cout << (*itm).first << ":" << (*itm).second << endl;
		}
	}*/
	ifs.close();

}

//����ԤԼ
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return;
	}

	ofstream ofs;
	ofs.open(ORDER_FILE,ios::trunc);
	for (map<int, map<string, string>>::iterator it = this->m_Map.begin(); it != this->m_Map.end(); it++)
	{
		for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
		{
			ofs << (*mit).first << ":" << (*mit).second << " ";
		}
		ofs << endl;
	}

	ofs.close();
}

