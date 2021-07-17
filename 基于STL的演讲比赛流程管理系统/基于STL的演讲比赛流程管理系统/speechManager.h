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

	//菜单显示
	void showMenu();

	//退出系统
	void existSystem();

	//比赛选手编号容器->  使12人编号洗牌(第一轮)
	vector<int> v1;

	//比赛选手编号容器->  使6人编号洗牌(第二轮)
	vector<int> v2;

	//胜利前三名容器->    保存前三名
	vector<int> vVictory;

	//存放编号以及对应的具体选手容器
	map<int, Speaker> m_Speaker;

	//轮数
	int m_index;

	//创建选手
	void CreateSpeaker();

	//初始化属性
	void initSpeech();

	//开始比赛
	void startSpeech();

	//抽签
	void speechDraw();

	//第一轮比赛
	void speechContest();

	//第二轮比赛
	void speechContest2();

	//保存进文件
	void saveFile();

	//文件存在标志
	bool FileIsEmpty;

	//查看比赛记录
	void loadRecoder();

	//读取文件记录
	map<int, vector<string>> m_Recode;

	//清空比赛记录
	void clearFile();

	~SpeechManager();
};