#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <map>
#include <numeric>
#include <functional>
using namespace std;
#include <fstream>

class SpeechManager
{
public:
	SpeechManager();

	//�˵���ʾ
	void showMenu();

	//�˳�ϵͳ
	void existSystem();

	//����ѡ�ֱ������->  ʹ12�˱��ϴ��(��һ��)
	vector<int> v1;

	//����ѡ�ֱ������->  ʹ6�˱��ϴ��(�ڶ���)
	vector<int> v2;

	//ʤ��ǰ��������->    ����ǰ����
	vector<int> vVictory;

	//��ű���Լ���Ӧ�ľ���ѡ������
	map<int, Speaker> m_Speaker;

	//����
	int m_index;

	//����ѡ��
	void CreateSpeaker();

	//��ʼ������
	void initSpeech();

	//��ʼ����
	void startSpeech();

	//��ǩ
	void speechDraw();

	//��һ�ֱ���
	void speechContest();

	//�ڶ��ֱ���
	void speechContest2();

	//������ļ�
	void saveFile();

	//�ļ����ڱ�־
	bool FileIsEmpty;

	//�鿴������¼
	void loadRecoder();

	//��ȡ�ļ���¼
	map<int, vector<string>> m_Recode;

	//��ձ�����¼
	void clearFile();

	~SpeechManager();
};