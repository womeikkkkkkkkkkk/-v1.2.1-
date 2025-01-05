#include "Identity.h"

Identity::Identity() {
	this->name = LOGIN_INIT_ID;
	this->passward = LOGIN_INIT_NAME;
	this->status = LOGIN_INIT_STATUS;
}

Identity::Identity(int id, std::string name, std::string passward) {
	this->SetName(name);
	this->SetPasswards(passward);
}

void Identity::SetName(const std::string& name)//
{
	this->name = name;
}

void Identity::SetPasswards(const std::string& passward) {
	this->passward = passward;
}

std::string Identity::GetName()const {
	return this->name;
}

std::string Identity::GetPassward() const {
	return this->passward;
}