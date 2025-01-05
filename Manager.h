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

class Manager : public Identity // 管理员类
{
private:
	int id;
	MyUnorderedMap<Student> vStu;//学生表
	MyUnorderedMap<Teacher> vTea;//教师表
	MyUnorderedMap<ComputerRoom> vCom;//机房表

public:

	Manager();//构造
	Manager(std::string name, std::string passward);//构造

	virtual void operMenu();//重写菜单
	virtual void ReSetName(Identity& person, const std::string name);//重写修改名字
	virtual void ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward);//重写修改密码
	virtual void RegisterUser(const int& id, const std::string& name, const std::string& passward);//注册用户

	friend std::istream& operator>>(std::istream& is, Manager& s);//重载>>管理员，用于读写数据
	// 实现 operator==，用于去重
	bool operator==(const Manager& other) const {
		return this->getId() == other.getId();
	}

	// 实现 operator<，用于排序
	bool operator<(const Manager& other) const {
		return this->getId() < other.getId();
	}
	bool TextIdCmp(int fid, std::string text); // 比较ID和文本是否相等

	void SetId(const int& id);//设置ID
	void SetName(const std::string& name);//设置名字
	void SetPassward(const std::string& passward);//设置密码

	int getId()const;//获取ID
	std::string GetName()const;//获取名字
	std::string GetPassward()const;//获取密码

	void InitVector();//载入数据
	bool CheckRepeat(const int id, const int type);//去重

	void AddPerson();//添加用户
	void RemovePerson();//删除用户（待实现）
	void FindPerson(const std::string& text);//查找用户
	void ShowPerson();//显示所有用户
	void ShowComputer();//显示机房信息
	void CleanFile();//清空数据
};