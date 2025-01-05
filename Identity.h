#pragma once
#include <string>
#include <iostream>
#include "GlobalFile.h"

class Identity // 人员基类
{
private:
	std::string name;     // 用户名
	std::string passward; // 密码
	bool status;//登录状态
protected:

public:
	virtual void operMenu() = 0;//二级菜单入口，可通过叠加if，switch实现多级菜单
	virtual void ReSetName(Identity& person, const std::string name) = 0;//修改用户名
	virtual void ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward) = 0;//修改密码
	virtual void RegisterUser(const int& id, const std::string& name, const std::string& passward) = 0;//注册用户

	Identity();//默认构造
	Identity(int id, std::string name, std::string passward);//构造

	void SetName(const std::string& name);//设置名字
	void SetPasswards(const std::string& passward);//设置密码

	std::string GetName()const;//获取名字
	std::string GetPassward() const;//获取密码
};