#include <iostream>
#include "speechManager.h"
using namespace std;


int main()
{

	SpeechManager sm;
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		cout << "ѡ�ֱ��:" << (*it).first << "ѡ������:" << (*it).second.getName() << "ѡ�ֵ÷�:" << (*it).second.getScore(0) << endl;
	}*/
	int select = 0;

	while (true)
	{
		sm.showMenu();
		cout << "������������:";
		cin >> select;
		switch (select)
		{
		case 1://��ʼ�ݽ�����
			sm.startSpeech();
			break;
		case 2://�鿴������¼
			sm.loadRecoder();
			break;
		case 3://��ձ�����¼
			sm.clearFile();
			break;
		case 0://�˳�������¼
			sm.existSystem();
			break;
		default:
			cout << "������������������!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}