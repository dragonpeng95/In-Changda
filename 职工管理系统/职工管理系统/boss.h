#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

//¿œ∞Â¿‡
class Boss:public Worker
{
public:
	Boss(int id,string name,int departmentId);
	virtual void showInfo();
	virtual string getDepartment();
};
