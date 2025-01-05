#pragma once
#include "Identity.h"
#include "GlobalFile.h"
#include "OutPutMessages.h"
#include "OrderFile.h"
#include "Utils.h"
#include "ExceptionLog.h"
#include <vector>
#include <string>
#include <iostream>

class Teacher : public Identity // ��ʦ��
{
private:
	int id;

public:
	Teacher();//����
	Teacher(int id, std::string name, std::string passward);//����

	virtual void operMenu()override;//��д�˵�
	virtual void ReSetName(Identity& person, const std::string name)override;
	virtual void ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward)override;
	virtual void RegisterUser(const int& id, const std::string& name, const std::string& passward)override;//ע���û�

	friend std::istream& operator>>(std::istream& is, Teacher& s);//����>>��ʦ
	// ʵ�� operator==������ȥ��
	bool operator==(const Teacher& other) const {
		return this->getId() == other.getId();
	}

	// ʵ�� operator<����������
	bool operator<(const Teacher& other) const {
		return this->getId() < other.getId();
	}
	void SetId(const int& id);//����ID
	void SetName(const std::string& name);//��������
	void SetPassward(const std::string& passward);//��������

	int getId()const;//��ȡID
	std::string GetName()const;//��ȡ����
	std::string GetPassward()const;//��ȡ����

	void ShowAllOrder();//��ʾ����ԤԼ
	void ValidOrder();//���ԤԼ
};