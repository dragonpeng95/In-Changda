#pragma once
#include <iostream>
using namespace std;

class Speaker
{
public:
	//��������
	void setName(string name);

	//���÷���
	void setScore(int i, double score);

	//�õ�����
	string getName();

	//�õ�����
	double getScore(int i);
private:
	string m_Name;
	double m_Score[2];//��������������ַ���
};