#include "WorkerManager.h"

WorkerManager::WorkerManager()
{
	//1.文件不存在的初始化
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "文件不存在!" << endl;
		this->m_EmployeeNum = 0;
		this->m_EmployeeArray = NULL;
		this->m_fileIsNull = true;
		ifs.close();
		return;
	}
	else
	{
		//2.文件存在，但是为空
		char ch;
		ifs >> ch;
		if (ifs.eof())
		{
			//cout << "文件存在，但是为空!" << endl;
			this->m_EmployeeNum = 0;
			this->m_EmployeeArray = NULL;
			this->m_fileIsNull = true;
			ifs.close();
			return;
		}
		//文件存在，读取员工个数
		else
		{
			int num = this->get_EmployeeNum();
			//cout << "职工人数为:" << num << endl;
			this->m_EmployeeNum = num;
			this->m_EmployeeArray = new Worker * [num];
			this->init_Employee();
			this->m_fileIsNull = false;

			//测试
			/*for (int i = 0; i < num; i++)
			{
				cout << "职工编号:" << this->m_EmployeeArray[i]->m_Id
					 << "职工姓名:" << this->m_EmployeeArray[i]->m_Name
					 << "职工部门编号:" << this->m_EmployeeArray[i]->m_DepartmentId << endl;
			}*/
		}
		
		
	}
	////初始化人数
	//this->m_EmployeeNum = 0;
	////初始化数组指针
	//this->m_EmployeeArray = NULL;
}

void WorkerManager::showMenu()
{
	cout << "**************************************************" << endl;
	cout << "*************  欢迎使用职工管理系统  *************" << endl;
	cout << "******            0.退出管理程序            ******" << endl;
	cout << "******            1.增加职工信息            ******" << endl;
	cout << "******            2.显示职工信息            ******" << endl;
	cout << "******            3.删除离职员工            ******" << endl;
	cout << "******            4.修改职工信息            ******" << endl;
	cout << "******            5.查找职工信息            ******" << endl;
	cout << "******            6.按照编号排序            ******" << endl;
	cout << "******            7.清空所有文档            ******" << endl;
	cout << "**************************************************" << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用!" << endl;
	exit(0);
}


void WorkerManager::AddEmployee()
{
	cout << "请输入你需要添加的人数:";
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) 
	{
		//计算新的空间大小
		int newSize = this->m_EmployeeNum + addNum;

		//开辟新的空间
		Worker** newSpace = new Worker * [newSize];//定义指向Worker*类型的指针数组

		if (this->m_EmployeeArray != NULL)
		{
			for (int i = 0; i < this->m_EmployeeNum; i++)
			{
				newSpace[i] = this->m_EmployeeArray[i];
			}
		}
		//添加新的数据
		for (int i = 0; i < addNum; i++)
		{
			cout << "请输入添加的第" << i+1 << "个人信息" << endl;
			int id;
			string name;
			int departmentId;
			cout << "输入员工编号:";
			cin >> id;
			cout << "输入员工姓名:";
			cin >> name;
			cout << "输入员工部门序号:" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> departmentId;
			Worker* worker = NULL;
			switch (departmentId)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmployeeNum + i] = worker;
		}
		//释放原有空间
		delete[] this->m_EmployeeArray;
		//更改空间指向
		this->m_EmployeeArray = newSpace;

		//更新新的个数
		this->m_EmployeeNum = newSize;

		//更新信息不为空的标志
		this->m_fileIsNull = false;

		//提示信息
		cout << "成功添加" << addNum << "名新职工" << endl;

		this->saveFile();

	}
	else
	{
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::saveFile()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmployeeNum; i++)
	{
		ofs << this->m_EmployeeArray[i]->m_Id << " "
			<< this->m_EmployeeArray[i]->m_Name << " "
			<< this->m_EmployeeArray[i]->m_DepartmentId << endl;
	}
	ofs.close();
}

int WorkerManager::get_EmployeeNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int departmentId;
	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> departmentId)
	{
		num++;
	}
	return num;
	
}

void WorkerManager::init_Employee()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int departmentId;

	Worker* worker = NULL;
	int index = 0;
	while (ifs>>id && ifs>>name && ifs>>departmentId)
	{
		
		if (departmentId == 1)
		{
			worker = new Employee(id,name,departmentId);
		}
		else if (departmentId == 2)
		{
			worker = new Manager(id,name,departmentId);
		}
		else if (departmentId == 3)
		{
			worker = new Boss(id, name, departmentId);
		}
		this->m_EmployeeArray[index] = worker;
		index++;
	}
	ifs.close();
} 

void WorkerManager::show_Employee()
{
	if (this->m_fileIsNull)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmployeeNum; i++)
		{
			this->m_EmployeeArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

int WorkerManager::IsExist(int findNum)
{
	int index = -1;
	for (int i = 0; i < this->m_EmployeeNum; i++)
	{
		if (findNum == this->m_EmployeeArray[i]->m_Id)
			index = i;
	}
	return index;
}

void WorkerManager::delEmployee()
{
	if (this->m_fileIsNull)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		cout << "请输入要删除的职工编号:";
		int findNum;
		cin >> findNum;
		int index = this->IsExist(findNum);
		if (index != -1)
		{
			for (int i = index; i < this->m_EmployeeNum - 1; i++)
			{
				this->m_EmployeeArray[i] = this->m_EmployeeArray[i + 1];
			}
			this->m_EmployeeNum--;
			//保存进文件
			this->saveFile();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该员工!" << endl;
		}
	}
	
	
	system("pause");
	system("cls");
	
}

void WorkerManager::modify_Employee()
{
	if (this->m_fileIsNull)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		cout << "请输入要修改的职工编号:";
		int findNum;
		cin >> findNum;
		int index = this->IsExist(findNum);
		if (index != -1)
		{
			//释放原来的空间
			delete this->m_EmployeeArray[index];
			Worker* worker = NULL;
			int id;
			string name;
			int department;
			cout << "请输入新的职工编号:";
			cin >> id;
			cout << "请输入新的职工姓名:";
			cin >> name;
			cout << "请输入新的职工所属部门编号:" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> department;
			if (department == 1)
			{
				worker = new Employee(id, name, department);
			}
			else if(department == 2)
			{
				worker = new Manager(id, name, department);
			}
			else if(department == 3)
			{
				worker = new Boss(id, name, department);
			}
			this->m_EmployeeArray[index] = worker;

			cout << "修改成功!" << endl;
			this->saveFile(); 
		}
		else
		{
			cout << "修改失败，未找到该员工!" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::find_Employee()
{
	if (this->m_fileIsNull)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		cout << "请输入查找的方式:" << endl;
		cout << "1.按编号查找" << endl;
		cout << "2.按姓名查找" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			cout << "请输入需要查找员工的编号:";
			int id;
			cin >> id;
			int index = this->IsExist(id);
			if (index != -1)
			{
				cout << "查找成功!员工信息如下:" << endl;
				this->m_EmployeeArray[index]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人!" << endl;
			}
		}
		else if (select == 2)
		{
			cout << "请输入需要查找员工的姓名:";
			string name;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmployeeNum; i++)
			{
				if (this->m_EmployeeArray[i]->m_Name == name)
				{
					this->m_EmployeeArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == true)
			{
				cout << "查找成功！" << endl;
			}
			else
			{
				cout << "查找失败，查无此人!" << endl;
			}
		}
		else
		{
			cout << "输入有误!" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Employee()
{
	if (this->m_fileIsNull)
	{
		cout << "文件不存在或记录为空!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请输入需要排序的方式:" << endl;
		cout << "1.升序" << endl;
		cout << "2.降序" << endl;
		int select;
		cin >> select;
		//这里排序算法用的选择排序
		for (int i = 0; i < this->m_EmployeeNum; i++)
		{
			int MinOrMax = i;
			for (int j = i+1; j < this->m_EmployeeNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmployeeArray[MinOrMax]->m_Id > this->m_EmployeeArray[j]->m_Id)
					{
						MinOrMax = j;
					}
				}
				else if (select == 2)//降序
				{
					if (this->m_EmployeeArray[MinOrMax]->m_Id < this->m_EmployeeArray[j]->m_Id)
					{
						MinOrMax = j;
					}
				}
				
			}
			if (MinOrMax != i)
			{
				Worker* worker = this->m_EmployeeArray[i];
				this->m_EmployeeArray[i] = this->m_EmployeeArray[MinOrMax];
				this->m_EmployeeArray[MinOrMax] = worker;
			}
		}
		cout << "排序后的信息如下:" << endl;
		this->show_Employee();
	}
	
}

void WorkerManager::Clean_File()
{
	if (this->m_fileIsNull)
	{
		cout << "文件不存在或文件为空!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请确认是否清空文件:" << endl;
		cout << "1.确认" << endl;
		cout << "2.返回" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			ofstream ofs(FILENAME, ios::trunc);//删除文件，并创建
			ofs.close();

			if (this->m_EmployeeArray != NULL)
			{
				for (int i = 0; i < this->m_EmployeeNum; i++)
				{
					delete this->m_EmployeeArray[i];
					this->m_EmployeeArray[i] = NULL;
				}
				delete[] this->m_EmployeeArray;
				this->m_EmployeeArray = NULL;
				this->m_EmployeeNum = 0;
				this->m_fileIsNull = true;
 			}
			cout << "清空文件成功!" << endl;
			system("pause");
			system("cls");
		}
		else if(select == 2)
		{
			system("pause");
			system("cls");
		}
		else
		{
			system("pause");
			system("cls");
		}
		

	}
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmployeeArray != NULL)
	{
		for (int i = 0; i < this->m_EmployeeNum; i++)
		{
			if (this->m_EmployeeArray[i] != NULL)
				delete this->m_EmployeeArray[i];

		}
		delete[] this->m_EmployeeArray;
		this->m_EmployeeArray = NULL;
	}
}
