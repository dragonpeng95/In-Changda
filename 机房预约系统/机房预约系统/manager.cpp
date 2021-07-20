#include "manager.h"

//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string password)
{
	this->m_Name = name;
	this->m_Password = password;

	//初始化容器 获取到所有文件中 学生、老师的信息
	this->initVector();

	//初始化机房信息
	this->initComputerRoom();
}

//选择菜单
void Manager::openMenu()
{
	cout << "欢迎管理员：" << this->m_Name << "登陆!" << endl;
	cout << "\t\t --------------------------------------\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             1.添加账号              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             2.查看账号              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             3.查看机房              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             4.清空预约              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             0.注销登陆              |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t --------------------------------------\n";
	cout << "请输入您的操作:" << endl;
}

//添加账号
void Manager::addPerson()
{
	system("cls");
	this->initVector();
	this->openMenu();
	string fileName;//操作的文件名
	string tips;//提示
	int select;
	while (true)
	{
		cout << "请输入添加的类型" << endl;
		cout << "1.学生" << endl;
		cout << "2.教师" << endl;	
		cin >> select;
		if (select == 1)
		{
			fileName = STUDENT_FILE;
			tips = "请输入学生学号:";
			break;
		}
		else if(select == 2)
		{
			fileName = TEACHER_FILE;
			tips = "请输入教师编号:";
			break;
		}
		cout << "输入有误,请重新输入！" << endl;
		system("pause");
		system("cls");
		this->openMenu();
	}
	ofstream ofs;
	ofs.open(fileName, ios::out | ios::app);//追加方式

	int id;
	while (true)
	{
		cout << tips;		
		cin >> id;
		bool ret = this->checkRepeat(id, select);//重复返回true，不重复返回false
		if (ret == false)//不重复
		{
			break;
		}
	}
	
	cout << "请输入用户名:";
	string username;
	cin >> username;

	cout << "请输入密码:";
	string password;
	cin >> password;

	ofs << id << " " << username << " " << password << endl;
	cout << "添加成功!" << endl;
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();
	
}

//学生全局仿函数 给for_each使用
class MyPrintStu
{
public:
	void operator()(Student& s)
	{
		cout << "学号:" << s.m_Id << " 姓名:" << s.m_Name << " 密码:" << s.m_Password << endl;
	}
};

//老师全局仿函数 给for_each使用
class MyPrintTea
{
public:
	void operator()(Teacher& t)
	{
		cout << "学号:" << t.m_Name << " 姓名:" << t.m_TeacherId << " 密码:" << t.m_Password << endl;
	}
};

//查看账号
void Manager::showPerson()
{
	int select;
	while (true)
	{
		cout << "请输入查看的类型:" << endl;
		cout << "1.学生账号" << endl;
		cout << "2.老师账号" << endl;
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
		cout << "输入有误，请重新输入!" << endl;
	}
	system("pause");
	system("cls");
}

//查看机房信息
void Manager::showComputer()
{
	for (vector<ComputerRoom>::iterator it = this->vCom.begin(); it != this->vCom.end(); it++)
	{
		cout << "机房编号:" << it->roomId << "   机房最大容量:" << it->roomSize << endl;
	}
	system("pause");
	system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
	cout << "确认清空所有预约吗?" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;
	int select;
	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			ofstream ofs;
			ofs.open(ORDER_FILE, ios::out | ios::trunc);
			ofs.close();
			cout << "清空成功!" << endl;
			break;
		}
		else if (select == 2)
		{
			break;
		}
		cout << "输入有误，请重新输入:" << endl;
		cout << "1.确认" << endl;
		cout << "2.返回" << endl;

	}
	system("pause");
	system("cls");
}

//初始化容器
void Manager::initVector()
{
	//确保容器为空
	this->vStu.clear();
	this->vTea.clear();

	//读取信息
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "学生文件读取信息失败,请先添加信息!" << endl;
		return;
	}

	Student s;
	while (ifs>>s.m_Id && ifs>>s.m_Name && ifs>>s.m_Password)
	{
		this->vStu.push_back(s);
	}
	cout << "当前学生人数:" << this->vStu.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	/*if (!ifs.is_open())
	{
		cout << "教师信息读取失败,请先添加教师信息!" << endl;
		return;
	}*/
	Teacher t;
	while (ifs>>t.m_TeacherId && ifs>>t.m_Name && ifs>>t.m_Password)
	{
		this->vTea.push_back(t);
	}
	cout << "当前教师人数:" << this->vTea.size() << endl;

	ifs.close();
}


//检测重复 id是输入的id(学号，教师编号)，type是添加的类型
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)//检测学生
	{
		for (vector<Student>::iterator it = this->vStu.begin(); it != this->vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				cout << "学号已存在，请重新输入!" << endl;
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
				cout << "教师编号已存在，请重新输入!" << endl;
				return true;
			}
		}
	}
	return false;
}

//初始化机房信息
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
	cout << "机房数量为:" << this->vCom.size() << endl;
	ifs.close();

}