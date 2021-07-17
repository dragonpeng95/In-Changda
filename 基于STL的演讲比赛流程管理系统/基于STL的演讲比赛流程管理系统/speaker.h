#pragma once
#include <iostream>
using namespace std;

class Speaker
{
public:
	//设置姓名
	void setName(string name);

	//设置分数
	void setScore(int i, double score);

	//得到姓名
	string getName();

	//得到分数
	double getScore(int i);
private:
	string m_Name;
	double m_Score[2];//数组用来存放两轮分数
};