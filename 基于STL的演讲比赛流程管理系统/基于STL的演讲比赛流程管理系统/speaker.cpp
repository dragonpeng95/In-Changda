#include "speaker.h"

//��������
void Speaker::setName(string name)
{
	this->m_Name = name;
}

//���÷���
void Speaker::setScore(int i, double score)
{
	this->m_Score[i] = score;
}

//�õ�����
string Speaker::getName()
{
	return this->m_Name;
}

//�õ�����
double Speaker::getScore(int i)
{
	return this->m_Score[i];
}