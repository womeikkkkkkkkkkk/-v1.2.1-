#include "ExceptionLog.h"

ExceptionLog::ExceptionLog(const std::string& LogFilePath) {
	LogFile.open(LogFilePath, std::ios::app);
	if (!LogFile) {
		throw std::runtime_error("日志无法打开");
	}
}

ExceptionLog::~ExceptionLog() {
	if (LogFile.is_open()) {
		LogFile.close();
	}
}

void ExceptionLog::LogException(const std::string& ExceptionMessage) {
	LogFile << ExceptionMessage << std::endl;
}