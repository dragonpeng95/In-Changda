#include "speechManager.h"
SpeechManager::SpeechManager()
{
	//��ʼ������
	this->initSpeech();
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		//cout << "�ļ���ʧ��!" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "��¼Ϊ��!" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}
	this->FileIsEmpty = false;
}

//�˵���ʾ
void SpeechManager::showMenu()
{
	cout << "**********************************************************" << endl;
	cout << "*******************  ��ӭ�μ��ݽ�����  *******************" << endl;
	cout << "********************  1.��ʼ�ݽ�����   *******************" << endl;
	cout << "********************  2.�鿴�����¼  ********************" << endl;
	cout << "********************  3.��ձ�����¼  ********************" << endl;
	cout << "********************  0.�˳���������  ********************" << endl;
	cout << "**********************************************************" << endl;
}

//�˳�ϵͳ
void SpeechManager::existSystem()
{
	cout << "��ӭ�´�ʹ��!" << endl;
	system("pause");
	exit(0);
}

//��ʼ������
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_index = 1;
}

//����ѡ��
void SpeechManager::CreateSpeaker()
{
	string seedSpeaker = "ABCDEFGHIJKL";
	for (int i = 0; i < seedSpeaker.size(); i++)
	{
		string name = "ѡ��";
		name += seedSpeaker[i];

		Speaker sp;
		sp.setName(name);
		for (int i = 0; i < 2; i++)
		{
			sp.setScore(i, 0);
		}

		//��ѡ�ֱ�ŷŽ�v1����
		this->v1.push_back(i + 10001);

		//��ѡ�ֱ�źͶ�Ӧ����Ž�map����
		this->m_Speaker.insert(pair<int, Speaker>(i + 10001, sp));
	}
}

void SpeechManager::speechDraw()
{
	cout << "�� << " << this->m_index << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------------------" << endl;
	cout << "��ǩ˳������:" << endl;
	if (this->m_index == 1)
	{
		random_shuffle(this->v1.begin(), this->v1.end());
		for (vector<int>::iterator it = this->v1.begin(); it != this->v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(this->v2.begin(), this->v2.end());
		for (vector<int>::iterator it = this->v2.begin(); it != this->v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-----------------------------------" << endl;
	system("pause");
	
}

//����
void SpeechManager::speechContest()
{
	cout << "�������������������������������� << " << this->m_index << " >> �ֱ�����ʼ:������������������������������" << endl;
	//��ÿ��ѡ��10������(��һ��)
	multimap<double, int,greater<double>> mulmap1;//��һ���������ƽ���֣��ڶ���������ű��
	//����������ǰ����
	multimap<double, int, greater<double>> mulmap3;
	for (vector<int>::iterator it = this->v1.begin(); it != this->v1.begin()+6; it++)
	{
		vector<double> v;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600)/10.f;
			v.push_back(score);

		}
		sort(v.begin(), v.end());//��10����ί�Ĵ������
		v.erase(v.begin());//ȥ����߷�
		v.erase(--v.end());//ȥ����ͷ�
		double scoreTotal = accumulate(v.begin(), v.end(), 0.0f);
		double scoreAvg = scoreTotal / (double)v.size();
		mulmap1.insert(pair<double, int>(scoreAvg, *it));
	}
	cout << "-------�� << " << this->m_index << " >> �ֱ����������:-------" << endl;
	cout << "��һ��С�飺" << endl;
	int num = 0;
	for (multimap<double, int, greater<double>>::iterator it = mulmap1.begin(); it != mulmap1.end(); it++)
	{
		num++;
		this->m_Speaker[(*it).second].setScore(this->m_index - 1, (*it).first);//�������ȥ
		cout << "���: " << (*it).second << " ���յ÷�:" << (*it).first << endl;
		if (num <= 3)
		{
			this->v2.push_back((*it).second);
			mulmap3.insert(*it);
			
		}
	}

	//�ڶ���
	multimap<double, int, greater<double>> mulmap2;//��һ���������ƽ���֣��ڶ���������ű��
	for (vector<int>::iterator it = this->v1.begin()+6; it != this->v1.end(); it++)
	{
		vector<double> v;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			v.push_back(score);

		}
		sort(v.begin(), v.end());//��10����ί�Ĵ������
		v.erase(v.begin());//ȥ����߷�
		v.erase(--v.end());//ȥ����ͷ�
		double scoreTotal = accumulate(v.begin(), v.end(), 0.0f);
		double scoreAvg = scoreTotal / (double)v.size();
		mulmap2.insert(pair<double, int>(scoreAvg, *it));
	}
	cout << "�ڶ���С�飺" << endl;
	num = 0;
	for (multimap<double, int, greater<double>>::iterator it = mulmap2.begin(); it != mulmap2.end(); it++)
	{
		num++;
		cout << "���: " << (*it).second << " ���յ÷�:" << (*it).first << endl;
		this->m_Speaker[(*it).second].setScore(this->m_index - 1, (*it).first);
		if (num <= 3)
		{
			this->v2.push_back((*it).second);
			mulmap3.insert(*it);

		}	
		
	}


	cout << "-------��һ�ֻ�ʤ����:-------" << endl;
	for (multimap<double, int, greater<double>>::iterator it = mulmap3.begin(); it != mulmap3.end(); it++)
	{
		cout << "���: " << (*it).second << " ���յ÷�:" << (*it).first << endl;
	}

	cout << "--------------�� <<" << this->m_index << ">> �ֱ�������--------------" << endl;

}

//�ڶ��ֱ���
void SpeechManager::speechContest2()
{
	cout << "�������������������������������� << " << this->m_index << " >> �ֱ�����ʼ:������������������������������" << endl;
	multimap<double, int, greater<double>> mulmap1;//��һ���������ƽ���֣��ڶ���������ű��
	cout << "------------�ڶ��ֳɼ�����:--------------" << endl;
	for (vector<int>::iterator it = this->v2.begin(); it != this->v2.end(); it++)
	{
		vector<double> v;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			v.push_back(score);

		}
		sort(v.begin(), v.end());//��10����ί�Ĵ������
		v.erase(v.begin());//ȥ����߷�
		v.erase(--v.end());//ȥ����ͷ�
		double scoreTotal = accumulate(v.begin(), v.end(), 0.0f);
		double scoreAvg = scoreTotal / (double)v.size();
		mulmap1.insert(pair<double, int>(scoreAvg, *it));
	}
	for (multimap<double, int, greater<double>>::iterator it = mulmap1.begin(); it != mulmap1.end(); it++)
	{
		this->m_Speaker[(*it).second].setScore(this->m_index-1, (*it).first);//�������ȥ
		cout << "���: " << (*it).second << " ���յ÷�:" << (*it).first << endl;
	}
	cout << "-------�ڶ��ֻ�ʤ����:-------" << endl;
	int num = 0;
	for (multimap<double, int, greater<double>>::iterator it = mulmap1.begin(); it != mulmap1.end(),num<3; it++)
	{
		num++;
		cout << "���: " << (*it).second << " ���յ÷�:" << (*it).first << endl;
		this->vVictory.push_back((*it).second);
	}

	cout << "--------------�� <<" << this->m_index << ">> �ֱ�������--------------" << endl;

}

void SpeechManager::saveFile()
{
	//��Ϣ��vVictory��(���)
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].getScore(1) << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "��¼����ɹ�!" << endl;
}
//��ʼ����
void SpeechManager::startSpeech()
{
	//����ѡ��
	this->CreateSpeaker();

	//��һ�ֱ���
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	
	//�ڶ��ֱ���
	this->m_index++;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest2();

	//������Ϣ
	this->saveFile();
	this->initSpeech();
	system("pause");
	system("cls");
}

//�鿴������¼
void SpeechManager::loadRecoder()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ��!" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "��¼Ϊ��!" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}
	this->FileIsEmpty = false;
	//�Ѹոն�ȡ���ַ��Ž�ȥ
	ifs.putback(ch);

	string data;
	int index = 0;
	while (ifs>>data)
	{
		vector<string> v;
		//cout << data << endl;
		int start = 0;
		while (true)
		{
			int position = data.find(",", start);
			if (position == -1)
			{
				break;
			}
			string temp = data.substr(start, position - start);//����ҵ����ִ�
			v.push_back(temp);
			//cout << temp << endl;
			start = position + 1;
		}
		index++;
		this->m_Recode.insert(pair<int, vector<string>>(index, v));
		

	}
	ifs.close();
	//չʾ��¼
	for (map<int, vector<string>>::iterator itm = this->m_Recode.begin(); itm != this->m_Recode.end(); itm++)
	{
	
		cout << "   ��" << (*itm).first << "�����������:     " << endl;
		cout << " �ھ����:" << (*itm).second.front()
			//<< " ����:" << this->m_Speaker[atoi((*itm).second[0].c_str())].getName()//�޷���ȡ����Ϊ�ļ�û�д�
			//<< " �÷�:" << this->m_Speaker[atoi((*itm).second[0].c_str())].getScore(1)
			<< "\t�÷�"<<(*itm).second[1]
			<< " \t�Ǿ����:" << (*itm).second[2]
			//<< " ����:" << this->m_Speaker[atoi((*itm).second[2].c_str())].getName()
			//<< " �÷�:" << this->m_Speaker[atoi((*itm).second[2].c_str())].getScore(1)
			<< " \t�÷�" << (*itm).second[3]
			<< " \t�������:" << (*itm).second[4]
			//<< " ����:" << this->m_Speaker[atoi((*itm).second[4].c_str())].getName()
			//<< " �÷�:" << this->m_Speaker[atoi((*itm).second[4].c_str())].getScore(1) 
			<< " \t�÷�" << (*itm).second[5]
			<< endl;
		
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearFile()
{
	if (this->FileIsEmpty == true)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "ȷ�����?" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc);

		//��ʼ������
		this->initSpeech();

		this->loadRecoder();

		cout << "��ճɹ�!" << endl;

		ofs.close();
	}
	system("pause");
	system("cls");


}

//û���ڶ������ٿռ�
//SpeechManager::~SpeechManager()
//{
//	
//}

