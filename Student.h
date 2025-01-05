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

class Student : public Identity // 学生类
{
private:
	int id;//学号

public:
	MyUnorderedMap<ComputerRoom> vCom;//机房表

	Student();//构造
	Student(int id, std::string name, std::string passward);//构造

	virtual void operMenu()override;//重写菜单
	virtual void ReSetName(Identity& person, const std::string name)override;
	virtual void ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward)override;
	virtual void RegisterUser(const int& id, const std::string& name, const std::string& passward)override;//注册用户

	friend std::istream& operator>>(std::istream& is, Student& s);//重载>>学生
	// 实现 operator==，用于去重
	bool operator==(const Student& other) const {
		return this->getId() == other.getId();
	}

	// 实现 operator<，用于排序
	bool operator<(const Student& other) const {
		return this->getId() < other.getId();
	}
	void SetId(const int& id);//设置ID
	void SetName(const std::string& name);//设置名字
	void SetPassward(const std::string& passward);//设置密码

	int getId()const;//获取ID
	std::string GetName()const;//获取名字
	std::string GetPassward()const;//获取密码

	void ApplyOrder();   // 申请预约
	void ShowMyOrder();  // 查看我的预约
	void ShowAllOrder(); // 查看所有预约
	void CancelOrder();  // 取消预约
};