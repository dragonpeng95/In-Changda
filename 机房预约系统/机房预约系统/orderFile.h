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

	//更新预约
	void updateOrder();

	//记录预约的容器  int存放第几条   
	map<int, map<string, string>> m_Map;

	//预约记录条数
	int m_Size;

};