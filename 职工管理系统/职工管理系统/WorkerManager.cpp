#include "WorkerManager.h"

WorkerManager::WorkerManager()
{
	//1.�ļ������ڵĳ�ʼ��
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "�ļ�������!" << endl;
		this->m_EmployeeNum = 0;
		this->m_EmployeeArray = NULL;
		this->m_fileIsNull = true;
		ifs.close();
		return;
	}
	else
	{
		//2.�ļ����ڣ�����Ϊ��
		char ch;
		ifs >> ch;
		if (ifs.eof())
		{
			//cout << "�ļ����ڣ�����Ϊ��!" << endl;
			this->m_EmployeeNum = 0;
			this->m_EmployeeArray = NULL;
			this->m_fileIsNull = true;
			ifs.close();
			return;
		}
		//�ļ����ڣ���ȡԱ������
		else
		{
			int num = this->get_EmployeeNum();
			//cout << "ְ������Ϊ:" << num << endl;
			this->m_EmployeeNum = num;
			this->m_EmployeeArray = new Worker * [num];
			this->init_Employee();
			this->m_fileIsNull = false;

			//����
			/*for (int i = 0; i < num; i++)
			{
				cout << "ְ�����:" << this->m_EmployeeArray[i]->m_Id
					 << "ְ������:" << this->m_EmployeeArray[i]->m_Name
					 << "ְ�����ű��:" << this->m_EmployeeArray[i]->m_DepartmentId << endl;
			}*/
		}
		
		
	}
	////��ʼ������
	//this->m_EmployeeNum = 0;
	////��ʼ������ָ��
	//this->m_EmployeeArray = NULL;
}

void WorkerManager::showMenu()
{
	cout << "**************************************************" << endl;
	cout << "*************  ��ӭʹ��ְ������ϵͳ  *************" << endl;
	cout << "******            0.�˳��������            ******" << endl;
	cout << "******            1.����ְ����Ϣ            ******" << endl;
	cout << "******            2.��ʾְ����Ϣ            ******" << endl;
	cout << "******            3.ɾ����ְԱ��            ******" << endl;
	cout << "******            4.�޸�ְ����Ϣ            ******" << endl;
	cout << "******            5.����ְ����Ϣ            ******" << endl;
	cout << "******            6.���ձ������            ******" << endl;
	cout << "******            7.��������ĵ�            ******" << endl;
	cout << "**************************************************" << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��!" << endl;
	exit(0);
}


void WorkerManager::AddEmployee()
{
	cout << "����������Ҫ��ӵ�����:";
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) 
	{
		//�����µĿռ��С
		int newSize = this->m_EmployeeNum + addNum;

		//�����µĿռ�
		Worker** newSpace = new Worker * [newSize];//����ָ��Worker*���͵�ָ������

		if (this->m_EmployeeArray != NULL)
		{
			for (int i = 0; i < this->m_EmployeeNum; i++)
			{
				newSpace[i] = this->m_EmployeeArray[i];
			}
		}
		//����µ�����
		for (int i = 0; i < addNum; i++)
		{
			cout << "��������ӵĵ�" << i+1 << "������Ϣ" << endl;
			int id;
			string name;
			int departmentId;
			cout << "����Ա�����:";
			cin >> id;
			cout << "����Ա������:";
			cin >> name;
			cout << "����Ա���������:" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmployeeArray;
		//���Ŀռ�ָ��
		this->m_EmployeeArray = newSpace;

		//�����µĸ���
		this->m_EmployeeNum = newSize;

		//������Ϣ��Ϊ�յı�־
		this->m_fileIsNull = false;

		//��ʾ��Ϣ
		cout << "�ɹ����" << addNum << "����ְ��" << endl;

		this->saveFile();

	}
	else
	{
		cout << "������������������" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		cout << "������Ҫɾ����ְ�����:";
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
			//������ļ�
			this->saveFile();
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���Ա��!" << endl;
		}
	}
	
	
	system("pause");
	system("cls");
	
}

void WorkerManager::modify_Employee()
{
	if (this->m_fileIsNull)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ�����:";
		int findNum;
		cin >> findNum;
		int index = this->IsExist(findNum);
		if (index != -1)
		{
			//�ͷ�ԭ���Ŀռ�
			delete this->m_EmployeeArray[index];
			Worker* worker = NULL;
			int id;
			string name;
			int department;
			cout << "�������µ�ְ�����:";
			cin >> id;
			cout << "�������µ�ְ������:";
			cin >> name;
			cout << "�������µ�ְ���������ű��:" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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

			cout << "�޸ĳɹ�!" << endl;
			this->saveFile(); 
		}
		else
		{
			cout << "�޸�ʧ�ܣ�δ�ҵ���Ա��!" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::find_Employee()
{
	if (this->m_fileIsNull)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ:" << endl;
		cout << "1.����Ų���" << endl;
		cout << "2.����������" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			cout << "��������Ҫ����Ա���ı��:";
			int id;
			cin >> id;
			int index = this->IsExist(id);
			if (index != -1)
			{
				cout << "���ҳɹ�!Ա����Ϣ����:" << endl;
				this->m_EmployeeArray[index]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���!" << endl;
			}
		}
		else if (select == 2)
		{
			cout << "��������Ҫ����Ա��������:";
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
				cout << "���ҳɹ���" << endl;
			}
			else
			{
				cout << "����ʧ�ܣ����޴���!" << endl;
			}
		}
		else
		{
			cout << "��������!" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Employee()
{
	if (this->m_fileIsNull)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��������Ҫ����ķ�ʽ:" << endl;
		cout << "1.����" << endl;
		cout << "2.����" << endl;
		int select;
		cin >> select;
		//���������㷨�õ�ѡ������
		for (int i = 0; i < this->m_EmployeeNum; i++)
		{
			int MinOrMax = i;
			for (int j = i+1; j < this->m_EmployeeNum; j++)
			{
				if (select == 1)//����
				{
					if (this->m_EmployeeArray[MinOrMax]->m_Id > this->m_EmployeeArray[j]->m_Id)
					{
						MinOrMax = j;
					}
				}
				else if (select == 2)//����
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
		cout << "��������Ϣ����:" << endl;
		this->show_Employee();
	}
	
}

void WorkerManager::Clean_File()
{
	if (this->m_fileIsNull)
	{
		cout << "�ļ������ڻ��ļ�Ϊ��!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ȷ���Ƿ�����ļ�:" << endl;
		cout << "1.ȷ��" << endl;
		cout << "2.����" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ���������
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
			cout << "����ļ��ɹ�!" << endl;
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
