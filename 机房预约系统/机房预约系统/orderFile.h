#pragma once
#include <iostream>
#include <fstream>
using namespace std;
#include "globalFile.h"
#include <map>
class OrderFile
{
public:

	OrderFile();

	//����ԤԼ
	void updateOrder();

	//��¼ԤԼ������  int��ŵڼ���   
	map<int, map<string, string>> m_Map;

	//ԤԼ��¼����
	int m_Size;

};