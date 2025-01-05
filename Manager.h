#pragma once
#include "Identity.h"
#include "GlobalFile.h"
#include "OutPutMessages.h"
#include "ComputerRoom.h"
#include "Student.h"
#include "Teacher.h"
#include "MyUnorderedMap.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class Manager : public Identity // ����Ա��
{
private:
	int id;
	MyUnorderedMap<Student> vStu;//ѧ����
	MyUnorderedMap<Teacher> vTea;//��ʦ��
	MyUnorderedMap<ComputerRoom> vCom;//������

public:

	Manager();//����
	Manager(std::string name, std::string passward);//����

	virtual void operMenu();//��д�˵�
	virtual void ReSetName(Identity& person, const std::string name);//��д�޸�����
	virtual void ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward);//��д�޸�����
	virtual void RegisterUser(const int& id, const std::string& name, const std::string& passward);//ע���û�

	friend std::istream& operator>>(std::istream& is, Manager& s);//����>>����Ա�����ڶ�д����
	// ʵ�� operator==������ȥ��
	bool operator==(const Manager& other) const {
		return this->getId() == other.getId();
	}

	// ʵ�� operator<����������
	bool operator<(const Manager& other) const {
		return this->getId() < other.getId();
	}
	bool TextIdCmp(int fid, std::string text); // �Ƚ�ID���ı��Ƿ����

	void SetId(const int& id);//����ID
	void SetName(const std::string& name);//��������
	void SetPassward(const std::string& passward);//��������

	int getId()const;//��ȡID
	std::string GetName()const;//��ȡ����
	std::string GetPassward()const;//��ȡ����

	void InitVector();//��������
	bool CheckRepeat(const int id, const int type);//ȥ��

	void AddPerson();//����û�
	void RemovePerson();//ɾ���û�����ʵ�֣�
	void FindPerson(const std::string& text);//�����û�
	void ShowPerson();//��ʾ�����û�
	void ShowComputer();//��ʾ������Ϣ
	void CleanFile();//�������
};