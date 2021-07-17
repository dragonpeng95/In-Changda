#include <iostream>
#include "speechManager.h"
using namespace std;


int main()
{

	SpeechManager sm;
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		cout << "选手编号:" << (*it).first << "选手姓名:" << (*it).second.getName() << "选手得分:" << (*it).second.getScore(0) << endl;
	}*/
	int select = 0;

	while (true)
	{
		sm.showMenu();
		cout << "请输入操作序号:";
		cin >> select;
		switch (select)
		{
		case 1://开始演讲比赛
			sm.startSpeech();
			break;
		case 2://查看比赛记录
			sm.loadRecoder();
			break;
		case 3://清空比赛记录
			sm.clearFile();
			break;
		case 0://退出比赛记录
			sm.existSystem();
			break;
		default:
			cout << "输入有误，请重新输入!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}