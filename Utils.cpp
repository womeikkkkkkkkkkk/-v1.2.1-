#include "Utils.h"
#pragma warning( disable : 4996 )

std::string Utils::GetCurrentTimes() {
	std::time_t CurrentTime = std::time(nullptr);
	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&CurrentTime));
	return std::string(buffer);
}

std::string Utils::GetCurrentTimes(std::string s) {
	std::time_t CurrentTime = std::time(nullptr);
	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%Y - %m - %d %H:%M:%S", std::localtime(&CurrentTime));
	return "[" + std::string(buffer) + "]" + s;
}

bool Utils::TimeCmp(const std::string& timeStr1, const std::string& timeStr2) {
	auto convertToSeconds = [](const std::string& datetimeStr) -> time_t {
		struct tm timeinfo = {};
		std::istringstream ss(datetimeStr);
		ss >> std::get_time(&timeinfo, "%Y - %m - %d %H:%M:%S");
		if (ss.fail()) {
			std::cerr << TIME_STYLE_ERROR << std::endl;
			return -1;
		}
		return mktime(&timeinfo);
		};

	time_t seconds1 = convertToSeconds(timeStr1);
	time_t seconds2 = convertToSeconds(timeStr2);

	if (seconds1 == -1 || seconds2 == -1) {
		return false;
	}

	const int threeMinutesInSeconds = 3 * 60;
	return (seconds2 - seconds2) <= threeMinutesInSeconds;
}