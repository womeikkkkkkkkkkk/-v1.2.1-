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

class Teacher : public Identity // 教师类
{
private:
	int id;

public:
	Teacher();//构造
	Teacher(int id, std::string name, std::string passward);//构造

	virtual void operMenu()override;//重写菜单
	virtual void ReSetName(Identity& person, const std::string name)override;
	virtual void ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward)override;
	virtual void RegisterUser(const int& id, const std::string& name, const std::string& passward)override;//注册用户

	friend std::istream& operator>>(std::istream& is, Teacher& s);//重载>>教师
	// 实现 operator==，用于去重
	bool operator==(const Teacher& other) const {
		return this->getId() == other.getId();
	}

	// 实现 operator<，用于排序
	bool operator<(const Teacher& other) const {
		return this->getId() < other.getId();
	}
	void SetId(const int& id);//设置ID
	void SetName(const std::string& name);//设置名字
	void SetPassward(const std::string& passward);//设置密码

	int getId()const;//获取ID
	std::string GetName()const;//获取名字
	std::string GetPassward()const;//获取密码

	void ShowAllOrder();//显示所有预约
	void ValidOrder();//审核预约
};