#include "speaker.h"

//设置姓名
void Speaker::setName(string name)
{
	this->m_Name = name;
}

//设置分数
void Speaker::setScore(int i, double score)
{
	this->m_Score[i] = score;
}

//得到姓名
string Speaker::getName()
{
	return this->m_Name;
}

//得到分数
double Speaker::getScore(int i)
{
	return this->m_Score[i];
}