#include "OrderFile.h"
#include <sstream>
#include <fstream>
OrderFile::OrderFile() {
	std::ifstream ifs;
	ifs.open(ORDER_FILE, std::ios::in);
	std::string date;
	std::string interval;
	std::string studentid;
	std::string studentname;
	std::string roomid;
	std::string status;
	this->OrderSize = 0;
	while (ifs >> date && ifs >> interval && ifs >> studentid && ifs >> studentname && ifs >> roomid && ifs >> status) {
		std::string key;
		std::string value;
		std::map<std::string, std::string> m;

		//¸üÐÂ×´Ì¬
		size_t pos = date.find(":");
		if (pos != -1) {
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = interval.find(":");
		if (pos != -1) {
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = studentid.find(":");
		if (pos != -1) {
			key = studentid.substr(0, pos);
			value = studentid.substr(pos + 1, studentid.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = studentname.find(":");
		if (pos != -1) {
			key = studentname.substr(0, pos);
			value = studentname.substr(pos + 1, studentname.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = roomid.find(":");
		if (pos != -1) {
			key = roomid.substr(0, pos);
			value = roomid.substr(pos + 1, roomid.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		pos = status.find(":");
		if (pos != -1) {
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		this->OrderData.insert(make_pair(this->GetSize(), m));
		this->OrderSize++;
	}
	ifs.close();
}

int const OrderFile::GetSize() const {
	return this->OrderSize;
}

void OrderFile::UpdateOrder() {
	if (this->GetSize() == 0) {
		return;
	}

	std::ofstream ofs(ORDER_FILE, std::ios::out | std::ios::trunc);
	for (int i = 0; i < this->GetSize(); i++) {
		ofs << "date:" << this->OrderData[i]["date"] << " ";
		ofs << "interval:" << this->OrderData[i]["interval"] << " ";
		ofs << "studentid:" << this->OrderData[i]["studentid"] << " ";
		ofs << "studentname:" << this->OrderData[i]["studentname"] << " ";
		ofs << "roomId:" << this->OrderData[i]["roomId"] << " ";
		ofs << "status:" << this->OrderData[i]["status"] << std::endl;
	}
	ofs.close();
}