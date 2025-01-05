#pragma once
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

class ExceptionLog//日志类
{
private:
	std::ofstream LogFile;
public:
	ExceptionLog(const std::string& LogFilePath);//构造
	~ExceptionLog();//析构
	void LogException(const std::string& ExceptionMessage);//写日志
};