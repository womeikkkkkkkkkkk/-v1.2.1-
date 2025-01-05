#pragma once
#include "GlobalFile.h"
#include "MyUnorderedMap.h"
#include <iostream>
#include <fstream>

class ComputerRoom {
private:
	int CRID;//�������
	int MAXC;//�������
	int bookedcount;//��ԤԼ����
public:
	ComputerRoom();
	void SetId(int& id);//����ID
	void SetMax(int& max);//�����������
	void SetBookedCount(int count);//���ÿ�ԤԼ����
	int getId()const;//��ȡID
	int GetMax()const;//��ȡ�������
	int GetBookedCount()const;//��ȡ��ԤԼ����

	friend std::istream& operator>>(std::istream& is, ComputerRoom& s);//����>>���������ڶ�д����
	// ʵ�� operator==������ȥ��
	bool operator==(const ComputerRoom& other) const {
		return this->getId() == other.getId();
	}

	// ʵ�� operator<����������
	bool operator<(const ComputerRoom& other) const {
		return this->getId() < other.getId();
	}
};