#pragma once
#include "GlobalFile.h"
#include "MyUnorderedMap.h"
#include <iostream>
#include <fstream>

class ComputerRoom {
private:
	int CRID;//机房编号
	int MAXC;//最大容量
	int bookedcount;//可预约人数
public:
	ComputerRoom();
	void SetId(int& id);//设置ID
	void SetMax(int& max);//设置最大容量
	void SetBookedCount(int count);//设置可预约人数
	int getId()const;//获取ID
	int GetMax()const;//获取最大容量
	int GetBookedCount()const;//获取可预约人数

	friend std::istream& operator>>(std::istream& is, ComputerRoom& s);//重载>>机房，用于读写数据
	// 实现 operator==，用于去重
	bool operator==(const ComputerRoom& other) const {
		return this->getId() == other.getId();
	}

	// 实现 operator<，用于排序
	bool operator<(const ComputerRoom& other) const {
		return this->getId() < other.getId();
	}
};