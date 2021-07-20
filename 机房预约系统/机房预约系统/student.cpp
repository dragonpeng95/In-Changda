#pragma once
#include "student.h"

//默认构造
Student::Student() 
{

}

//有参构造
Student::Student(int id, string username, string password)
{
	this->m_Id = id;
	this->m_Name = username;
	this->m_Password = password;

	//初始化机房信息
	this->initComputerRoom();
}

//菜单界面
void Student::openMenu()
{
	cout << "欢迎学生代表:" << this->m_Name << "登陆！" << endl;
	cout << "\t\t --------------------------------------\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             1.申请预约              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             2.查看我的预约          |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             3.查看所有预约          |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             4.取消预约              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             0.注销登陆              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t --------------------------------------\n";

}

//申请预约
void Student::applyOrder()
{
	cout << "机房开放时间为周一至周五!" << endl;
	cout << "请输入申请预约时间:" << endl;
	cout << "1.周一" << endl;
	cout << "2.周二" << endl;
	cout << "3.周三" << endl;
	cout << "4.周四" << endl;
	cout << "5.周五" << endl;
	int data;//日期
	while (true)
	{
		cin >> data;
		if (data == 1 || data == 2 || data == 3 || data == 4 || data == 5)
		{
			break;
		}
		cout << "输入有误，请重新输入:";
	}

	cout << "请输入申请时间段:" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;
	int interval;
	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		cout << "输入有误,请重新输入:";
	}

	cout << "请选择机房:" << endl;
	cout << this->vCom[0].roomId << "号机房的容量:" << this->vCom[0].roomSize << endl;
	cout << this->vCom[1].roomId << "号机房的容量:" << this->vCom[1].roomSize << endl;
	cout << this->vCom[2].roomId << "号机房的容量:" << this->vCom[2].roomSize << endl;
	int room;
	while (true)
	{
		cin >> room;
		if (room == 1 || room == 2 || room == 3)
		{
			break;
		}
		cout << "输入有误,请重新输入:";
	}

	cout << "预约成功,审核中!" << endl;
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::app);
	string m_data;//用来存储日期
	switch (data)
	{
	case 1:
		m_data = "周一";
		break;
	case 2:
		m_data = "周二";
		break;
	case 3:
		m_data = "周三";
		break;
	case 4:
		m_data = "周四";
		break;
	case 5:
		m_data = "周五";
		break;
	default:
		break;
	}
	string m_interval;//用来存储时间段
	switch (interval)
	{
	case 1:
		m_interval = "上午";
		break;
	case 2:
		m_interval = "下午";
		break;
	default:
		break;
	}

	string m_room;//存储申请的机房号
	switch (room)
	{
	case 1:
		m_room = "1号机房";
		break;
	case 2:
		m_room = "2号机房";
		break;
	case 3:
		m_room = "3号机房";
		break;
	default:
		break;
	}

	ofs << "日期:" << m_data
		<< " 时间段:" << m_interval
		<< " 学生学号:" << this->m_Id
		<< " 学生姓名:" << this->m_Name
		<< " 机房号:" << m_room
		<< " 状态:" << "审核中" << endl;
	ofs.close();
	system("pause");
	system("cls");
}

//查看自身预约
void Student::showMyOrder()
{
	OrderFile orderFile;
	if (orderFile.m_Size == 0)
	{
		cout << "当前无预约!" << endl;
		return;
	}
	//cout << orderFile.m_Map.size() << "条记录" << endl;
	multimap<bool,map<string, string>> m_tempGlobal;
	for (map<int,map<string,string>>::iterator it = orderFile.m_Map.begin();it!=orderFile.m_Map.end();it++)
	{
		bool flag = false;//如果发现预约中的人有，则flag变为true
		map<string, string> m_temp;
		for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
		{
			m_temp.insert(pair<string,string>(mit->first, (*mit).second));
			if ((*mit).second == this->m_Name)
			{
				flag = true;
			}
		}
		//如果两条记录bool都为true，则只能插入一条，键不能重复,改用multimap容器
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

//查看所有预约
void Student::showAllOrder()
{
	OrderFile orderFile;
	if (orderFile.m_Size == 0)
	{
		cout << "无预约记录" << endl;
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

//取消预约
void Student::cancelMyOrder()
{
	OrderFile orderFile;
	if (orderFile.m_Size == 0)
	{
		cout << "预约记录为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	//用学号找出自己的预约
	map<int, map<string,string>> m_selfMap;//第一个int存放自己的记录，第二个int存放自己记录在所有记录中的第几条
	int indexSelf = 1;
	int indexAll = 0;
	vector<int> v;//存放在所有记录中的索引
	for (map<int, map<string, string>>::iterator it = orderFile.m_Map.begin(); it != orderFile.m_Map.end(); it++)
	{
		bool flag = false;
		map<string, string> m_temp;
		//map<string, string> m_temp2;
		for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
		{
			
			m_temp.insert(pair<string,string>(mit->first, mit->second));
			if (this->m_Id == atoi((mit->second).c_str()))//文件读取的字符串转int
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

	cout << "您当前预约:" << endl;
	for (map<int,map<string,string>>::iterator it = m_selfMap.begin(); it != m_selfMap.end(); it++)
	{
		cout << it->first << " ";
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			cout << mit->first << ":" << mit->second << " ";
		}
		cout << endl;
	
	}
	//测试vector是否拿到在m_Map中的位置
	/*for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "******" << *it << "******" << endl;
	}*/

	cout << "请输入要取消预约的序号:" << endl;
	int select;
	int index;
	while (true)
	{
		cin >> select;
		if (select >= 1 && select <= v.size())
		{
			index = v[select - 1];//拿到在m_Map中的索引
			break;
		}
		cout << "输入有误，请重新输入:";
	}
	int cancel;
	while (true)
	{
		cout << "是否确认取消:" << endl;
		cout << "1.确定" << endl;
		cout << "2.返回" << endl;
		cin >> cancel;
		if (cancel == 1)
		{
			string status = "取消预约";
			orderFile.m_Map[index+1]["状态"] = status;
			orderFile.updateOrder();
			system("pause");
			return;
		}
		else if (cancel == 2)
		{
			system("pause");
			return;
		}
		cout << "输入有误，请重新输入!" << endl;
	}
}

//初始化机房容器
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
	cout << "机房数量:" << this->vCom.size() << endl;
}