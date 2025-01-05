#pragma once
#include <map>
#include <string>
#include <fstream>
#include "GlobalFile.h"
#include <iostream>

class OrderFile//预约类
{
private:
	int OrderSize;//表容量

public:
	std::map<int, std::map<std::string, std::string>> OrderData;//表数据

	OrderFile();//构造

	int const GetSize() const;//获取表容量
	void UpdateOrder();//更新表
};