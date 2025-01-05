#pragma once
#include <ctime>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "GlobalFile.h"

class Utils {
public:
	static std::string GetCurrentTimes();
	static std::string GetCurrentTimes(std::string s);
	static bool TimeCmp(const std::string& timeStr1, const std::string& timeStr2);//比较时间差是否大于三分钟
};
