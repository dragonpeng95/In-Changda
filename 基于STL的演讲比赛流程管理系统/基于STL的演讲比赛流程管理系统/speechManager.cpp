#include "speechManager.h"
SpeechManager::SpeechManager()
{
	//初始化属性
	this->initSpeech();
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		//cout << "文件打开失败!" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "记录为空!" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}
	this->FileIsEmpty = false;
}

//菜单显示
void SpeechManager::showMenu()
{
	cout << "**********************************************************" << endl;
	cout << "*******************  欢迎参加演讲比赛  *******************" << endl;
	cout << "********************  1.开始演讲比赛   *******************" << endl;
	cout << "********************  2.查看往届记录  ********************" << endl;
	cout << "********************  3.清空比赛记录  ********************" << endl;
	cout << "********************  0.退出比赛程序  ********************" << endl;
	cout << "**********************************************************" << endl;
}

//退出系统
void SpeechManager::existSystem()
{
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);
}

//初始化属性
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_index = 1;
}

//创建选手
void SpeechManager::CreateSpeaker()
{
	string seedSpeaker = "ABCDEFGHIJKL";
	for (int i = 0; i < seedSpeaker.size(); i++)
	{
		string name = "选手";
		name += seedSpeaker[i];

		Speaker sp;
		sp.setName(name);
		for (int i = 0; i < 2; i++)
		{
			sp.setScore(i, 0);
		}

		//将选手编号放进v1容器
		this->v1.push_back(i + 10001);

		//将选手编号和对应对象放进map容器
		this->m_Speaker.insert(pair<int, Speaker>(i + 10001, sp));
	}
}

void SpeechManager::speechDraw()
{
	cout << "第 << " << this->m_index << " >> 轮比赛选手正在抽签" << endl;
	cout << "-----------------------------------" << endl;
	cout << "抽签顺序如下:" << endl;
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

//比赛
void SpeechManager::speechContest()
{
	cout << "———————————————第 << " << this->m_index << " >> 轮比赛开始:———————————————" << endl;
	//给每个选手10个分数(第一组)
	multimap<double, int,greater<double>> mulmap1;//第一个参数存放平均分，第二个参数存放编号
	//存放两个组的前三名
	multimap<double, int, greater<double>> mulmap3;
	for (vector<int>::iterator it = this->v1.begin(); it != this->v1.begin()+6; it++)
	{
		vector<double> v;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600)/10.f;
			v.push_back(score);

		}
		sort(v.begin(), v.end());//对10个评委的打分排序
		v.erase(v.begin());//去除最高分
		v.erase(--v.end());//去除最低分
		double scoreTotal = accumulate(v.begin(), v.end(), 0.0f);
		double scoreAvg = scoreTotal / (double)v.size();
		mulmap1.insert(pair<double, int>(scoreAvg, *it));
	}
	cout << "-------第 << " << this->m_index << " >> 轮比赛结果如下:-------" << endl;
	cout << "第一个小组：" << endl;
	int num = 0;
	for (multimap<double, int, greater<double>>::iterator it = mulmap1.begin(); it != mulmap1.end(); it++)
	{
		num++;
		this->m_Speaker[(*it).second].setScore(this->m_index - 1, (*it).first);//分数存进去
		cout << "编号: " << (*it).second << " 最终得分:" << (*it).first << endl;
		if (num <= 3)
		{
			this->v2.push_back((*it).second);
			mulmap3.insert(*it);
			
		}
	}

	//第二组
	multimap<double, int, greater<double>> mulmap2;//第一个参数存放平均分，第二个参数存放编号
	for (vector<int>::iterator it = this->v1.begin()+6; it != this->v1.end(); it++)
	{
		vector<double> v;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			v.push_back(score);

		}
		sort(v.begin(), v.end());//对10个评委的打分排序
		v.erase(v.begin());//去除最高分
		v.erase(--v.end());//去除最低分
		double scoreTotal = accumulate(v.begin(), v.end(), 0.0f);
		double scoreAvg = scoreTotal / (double)v.size();
		mulmap2.insert(pair<double, int>(scoreAvg, *it));
	}
	cout << "第二个小组：" << endl;
	num = 0;
	for (multimap<double, int, greater<double>>::iterator it = mulmap2.begin(); it != mulmap2.end(); it++)
	{
		num++;
		cout << "编号: " << (*it).second << " 最终得分:" << (*it).first << endl;
		this->m_Speaker[(*it).second].setScore(this->m_index - 1, (*it).first);
		if (num <= 3)
		{
			this->v2.push_back((*it).second);
			mulmap3.insert(*it);

		}	
		
	}


	cout << "-------第一轮获胜名单:-------" << endl;
	for (multimap<double, int, greater<double>>::iterator it = mulmap3.begin(); it != mulmap3.end(); it++)
	{
		cout << "编号: " << (*it).second << " 最终得分:" << (*it).first << endl;
	}

	cout << "--------------第 <<" << this->m_index << ">> 轮比赛结束--------------" << endl;

}

//第二轮比赛
void SpeechManager::speechContest2()
{
	cout << "———————————————第 << " << this->m_index << " >> 轮比赛开始:———————————————" << endl;
	multimap<double, int, greater<double>> mulmap1;//第一个参数存放平均分，第二个参数存放编号
	cout << "------------第二轮成绩如下:--------------" << endl;
	for (vector<int>::iterator it = this->v2.begin(); it != this->v2.end(); it++)
	{
		vector<double> v;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			v.push_back(score);

		}
		sort(v.begin(), v.end());//对10个评委的打分排序
		v.erase(v.begin());//去除最高分
		v.erase(--v.end());//去除最低分
		double scoreTotal = accumulate(v.begin(), v.end(), 0.0f);
		double scoreAvg = scoreTotal / (double)v.size();
		mulmap1.insert(pair<double, int>(scoreAvg, *it));
	}
	for (multimap<double, int, greater<double>>::iterator it = mulmap1.begin(); it != mulmap1.end(); it++)
	{
		this->m_Speaker[(*it).second].setScore(this->m_index-1, (*it).first);//分数存进去
		cout << "编号: " << (*it).second << " 最终得分:" << (*it).first << endl;
	}
	cout << "-------第二轮获胜名单:-------" << endl;
	int num = 0;
	for (multimap<double, int, greater<double>>::iterator it = mulmap1.begin(); it != mulmap1.end(),num<3; it++)
	{
		num++;
		cout << "编号: " << (*it).second << " 最终得分:" << (*it).first << endl;
		this->vVictory.push_back((*it).second);
	}

	cout << "--------------第 <<" << this->m_index << ">> 轮比赛结束--------------" << endl;

}

void SpeechManager::saveFile()
{
	//信息在vVictory中(编号)
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].getScore(1) << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "记录保存成功!" << endl;
}
//开始比赛
void SpeechManager::startSpeech()
{
	//创建选手
	this->CreateSpeaker();

	//第一轮比赛
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	
	//第二轮比赛
	this->m_index++;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest2();

	//保存信息
	this->saveFile();
	this->initSpeech();
	system("pause");
	system("cls");
}

//查看比赛记录
void SpeechManager::loadRecoder()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败!" << endl;
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
		cout << "记录为空!" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}
	this->FileIsEmpty = false;
	//把刚刚读取的字符放进去
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
			string temp = data.substr(start, position - start);//存放找到的字串
			v.push_back(temp);
			//cout << temp << endl;
			start = position + 1;
		}
		index++;
		this->m_Recode.insert(pair<int, vector<string>>(index, v));
		

	}
	ifs.close();
	//展示记录
	for (map<int, vector<string>>::iterator itm = this->m_Recode.begin(); itm != this->m_Recode.end(); itm++)
	{
	
		cout << "   第" << (*itm).first << "届获奖名单如下:     " << endl;
		cout << " 冠军编号:" << (*itm).second.front()
			//<< " 姓名:" << this->m_Speaker[atoi((*itm).second[0].c_str())].getName()//无法获取，因为文件没有存
			//<< " 得分:" << this->m_Speaker[atoi((*itm).second[0].c_str())].getScore(1)
			<< "\t得分"<<(*itm).second[1]
			<< " \t亚军编号:" << (*itm).second[2]
			//<< " 姓名:" << this->m_Speaker[atoi((*itm).second[2].c_str())].getName()
			//<< " 得分:" << this->m_Speaker[atoi((*itm).second[2].c_str())].getScore(1)
			<< " \t得分" << (*itm).second[3]
			<< " \t季军编号:" << (*itm).second[4]
			//<< " 姓名:" << this->m_Speaker[atoi((*itm).second[4].c_str())].getName()
			//<< " 得分:" << this->m_Speaker[atoi((*itm).second[4].c_str())].getScore(1) 
			<< " \t得分" << (*itm).second[5]
			<< endl;
		
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearFile()
{
	if (this->FileIsEmpty == true)
	{
		cout << "文件不存在或记录为空!" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "确认清空?" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc);

		//初始化属性
		this->initSpeech();

		this->loadRecoder();

		cout << "清空成功!" << endl;

		ofs.close();
	}
	system("pause");
	system("cls");


}

//没有在堆区开辟空间
//SpeechManager::~SpeechManager()
//{
//	
//}

