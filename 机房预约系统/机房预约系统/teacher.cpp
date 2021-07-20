#include "teacher.h"

//默认构造
Teacher::Teacher()
{

}

//有参构造
Teacher::Teacher(int id, string username, string password)
{
	this->m_TeacherId = id;
	this->m_Name = username;
	this->m_Password = password;
}

//重写菜单纯虚，实现多态
void Teacher::openMenu()
{
	cout << "欢迎教师: " << this->m_Name << "登陆！" << endl;
	cout << "\t\t --------------------------------------\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             1.查看所有预约          |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             2.审核预约              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             0.注销登陆              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t --------------------------------------\n";
}

//查看所有预约
void Teacher::showAllOrder()
{
	OrderFile orderFile;
	if (orderFile.m_Size == 0)
	{
		cout << "当前无预约!" << endl;
		system("pause");
		system("cls");
		return;
	}
	int index = 1;
	for (map<int, map<string, string>>::iterator it = orderFile.m_Map.begin(); it != orderFile.m_Map.end(); it++)
	{
		cout << index << "、";
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			cout << mit->first << ":" << mit->second << " ";
		}
		cout << endl;
		index++;
	}
}

//审核预约
void Teacher::validOrder()
{
	OrderFile orderFile;
	if (orderFile.m_Size == 0)
	{
		cout << "当前无预约记录!" << endl;
		system("pause");
		system("cls");
		return;
	}
	/*for (map<int, map<string, string>>::iterator it = orderFile.m_Map.begin(); it != orderFile.m_Map.end(); it++)
	{
		cout << it->first << "、";
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			cout << mit->first << ":" << mit->second << " ";
		}
		cout << endl;
	}*/

	//找出所有在审核状态的预约信息
	map<int, map<string, string>> mapProcessing;//int存放预约条数
	vector<int> vProcessing;//存放审核状态的预约在m_Map中的索引
	int indexAll = 1;
	int index = 0; 
	string status = "审核中";
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

	//遍历所有审核中的预约
	if (mapProcessing.size() == 0)
	{
		cout << "当前无审核中的预约!" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (map<int, map<string, string>>::iterator it = mapProcessing.begin(); it != mapProcessing.end(); it++)
	{
		cout << it->first << "、";
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			cout << mit->first << ":" << mit->second << " ";
		}
		cout << endl;
	}

	//测试vProcessing容器
	/*for (vector<int>::iterator it = vProcessing.begin(); it != vProcessing.end(); it++)
	{
		cout << *it << endl;
	}*/

	while (true)
	{
		cout << "请输入需要审核的预约序号:";
		int select;
		cin >> select;
		if (select >= 1 && select <= vProcessing.size())
		{
			//找到在m_Map中的索引
			int index = vProcessing[select-1];
			//cout << orderFile.m_Map[index+1]["状态"] << endl;
			while (true)
			{
				cout << "请输入需要改为的状态:" << endl;
				cout << "1.预约成功" << endl;
				cout << "2.预约失败" << endl;
				int selectStatus;
				cin >> selectStatus;
				if (selectStatus == 1)
				{
					orderFile.m_Map[index + 1]["状态"] = "预约成功";
					orderFile.updateOrder();
					break;
				}
				if (selectStatus == 2)
				{
					orderFile.m_Map[index + 1]["状态"] = "预约失败";
					orderFile.updateOrder();
					break;
				}
				cout << "输入有误，请重新输入!" << endl;
			}
			cout << "审核预约成功!" << endl;
			system("pause");
			break;
		}
		cout << "输入有误，请重新输入!" << endl;
	}

}