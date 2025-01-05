#pragma once
#include "Identity.h"
#include "OutPutMessages.h"
#include "GlobalFile.h"
#include "ComputerRoom.h"
#include "OrderFile.h"
#include "Utils.h"
#include "ExceptionLog.h"
#include "MyUnorderedMap.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

class Student : public Identity // ѧ����
{
private:
	int id;//ѧ��

public:
	MyUnorderedMap<ComputerRoom> vCom;//������

	Student();//����
	Student(int id, std::string name, std::string passward);//����

	virtual void operMenu()override;//��д�˵�
	virtual void ReSetName(Identity& person, const std::string name)override;
	virtual void ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward)override;
	virtual void RegisterUser(const int& id, const std::string& name, const std::string& passward)override;//ע���û�

	friend std::istream& operator>>(std::istream& is, Student& s);//����>>ѧ��
	// ʵ�� operator==������ȥ��
	bool operator==(const Student& other) const {
		return this->getId() == other.getId();
	}

	// ʵ�� operator<����������
	bool operator<(const Student& other) const {
		return this->getId() < other.getId();
	}
	void SetId(const int& id);//����ID
	void SetName(const std::string& name);//��������
	void SetPassward(const std::string& passward);//��������

	int getId()const;//��ȡID
	std::string GetName()const;//��ȡ����
	std::string GetPassward()const;//��ȡ����

	void ApplyOrder();   // ����ԤԼ
	void ShowMyOrder();  // �鿴�ҵ�ԤԼ
	void ShowAllOrder(); // �鿴����ԤԼ
	void CancelOrder();  // ȡ��ԤԼ
};