#include "Student.h"

Student::Student() {
	this->id = NULLID;
}

Student::Student(int id, std::string name, std::string passward) {
	this->id = id;
	this->SetName(name);
	this->SetPasswards(passward);

	std::ifstream ifs;
	ifs.open(COMPUTER_FILE, std::ios::in);

	ComputerRoom c;
	while (ifs >> c) {
		vCom.insert(c);
	}
	ifs.close();
}

void Student::operMenu() {
	printStudentSecondMenu();
}

std::istream& operator>>(std::istream& is, Student& s) {
	int id;
	std::string name;
	std::string passward;
	is >> id;
	is >> name;
	is >> passward;
	s.SetId(id);
	s.SetName(name);
	s.SetPassward(passward);
	return is;
}

void Student::ReSetName(Identity& person, const std::string name) {
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		// 打开文件读取内容
		std::ifstream fileIn(STUDENT_FILE);
		if (!fileIn.is_open()) {
			std::cerr << "无法打开文件进行读取操作！" << std::endl;
			return;
		}

		// 读取文件中的每一行
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(fileIn, line)) {
			lines.push_back(line);  // 将每行存储到lines向量中
		}
		fileIn.close();  // 关闭读取流

		bool found = false;
		// 遍历文件中的每一行，查找用户名匹配的记录
		for (auto& l : lines) {
			// 使用 stringstream 分割每行内容
			std::istringstream ss(l);
			std::string index, username, password;
			ss >> index >> username >> password;  // 提取编号、用户名和密码

			// 如果找到了该用户名
			if (username == person.GetName()) {
				found = true;
				// 修改该行的用户名
				l = index + " " + name + " " + password;  // 更新用户名
				person.SetName(name);  // 更新对象的名字
				break;
			}
		}

		// 如果找到了目标用户名，覆盖文件内容
		if (found) {
			// 打开文件以进行写入
			std::ofstream fileOut(STUDENT_FILE, std::ios::trunc);  // 清空文件并覆盖写入
			if (!fileOut.is_open()) {
				std::cerr << "无法打开文件进行写入操作！" << std::endl;
				return;
			}

			// 将修改后的内容写入文件
			for (const auto& l : lines) {
				fileOut << l << std::endl;  // 将每行数据写入文件
			}
			fileOut.close();  // 关闭写入流

			// 打印成功信息并记录日志
			printResetNameSuccess();
			logMsg = Utils::GetCurrentTimes(RESETNAME_SUCCESS);
			exceptionLog.LogException(logMsg);
		}
		else {
			std::cerr << "未找到指定的用户名！" << std::endl;
		}
	}
	catch (...) {
		// 捕获所有异常并记录日志
		logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
		logMsg += Utils::GetCurrentTimes(RESETNAME_FALIED);
		exceptionLog.LogException(logMsg);
		return;
	}
}

#include <sstream>  // 包含 istringstream 库

void Student::ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward) {
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		// 检查旧密码是否正确
		if (person.GetPassward() == oldpassward) {
			// 修改密码
			person.SetPasswards(passward);

			// 读取文件内容
			std::ifstream fileIn(STUDENT_FILE);
			if (fileIn.is_open()) {
				std::vector<std::string> lines;
				std::string line;
				while (std::getline(fileIn, line)) {
					lines.push_back(line);  // 将每行存储到lines向量中
				}
				fileIn.close();  // 关闭文件读取流

				bool found = false;
				for (auto& l : lines) {
					// 使用 stringstream 分割每行内容
					std::istringstream ss(l);
					std::string index, username, password;
					ss >> index >> username >> password;  // 提取编号、用户名和密码
					if (username == person.GetName()) {
						found = true;
						// 修改该行的密码
						l = index + " " + username + " " + passward;  // 用新密码替换旧密码
						break;
					}
				}

				// 如果找到了用户，覆盖文件内容
				if (found) {
					std::ofstream fileOut(STUDENT_FILE, std::ios::trunc);  // 清空文件并覆盖写入
					if (fileOut.is_open()) {
						for (const auto& l : lines) {
							fileOut << l << std::endl;  // 将修改后的内容写入文件
						}
						printResetPasswardSuccess();
						logMsg = Utils::GetCurrentTimes(RESETPASSWARD_SUCCESS);
						exceptionLog.LogException(logMsg);
					}
					else {
						std::cerr << "无法打开文件进行写入操作！" << std::endl;
					}
				}
				else {
					std::cerr << "未找到指定的用户名！" << std::endl;
				}
			}
			else {
				std::cerr << "无法打开文件进行读取操作！" << std::endl;
			}
		}
		else {
			printResetPasswardFalied();
			logMsg = Utils::GetCurrentTimes(RESETPASSWARD_FALIED);
			exceptionLog.LogException(logMsg);
		}
	}
	catch (...) {
		logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
		exceptionLog.LogException(logMsg);
	}
}

void Student::RegisterUser(const int& id, const std::string& name, const std::string& passward) {
	std::ofstream ofs;
	ofs.open(STUDENT_FILE, std::ios::out | std::ios::app);
	ofs << id << " " << name << " " << passward << std::endl;
	ofs.close();
	printRegisterSuccess();
	LOG();
}

void Student::SetId(const int& id) {
	this->id = id;
}

void Student::SetName(const std::string& name) {
	this->Identity::SetName(name);
}

void Student::SetPassward(const std::string& passward) {
	this->SetPasswards(passward);
}

int Student::getId() const {
	return this->id;
}

std::string Student::GetName() const {
	return this->Identity::GetName();
}

std::string Student::GetPassward() const {
	return this->Identity::GetPassward();
}

void Student::ApplyOrder() {
	printApplyOrder1();
	int date = 0;
	int interval = 0;
	int room = 0;
	while (true) {
		std::cin >> date;
		if (1 <= date && date <= 5) {
			break;
		}
		printInputError();
	}
	printApplyOrder2();
	while (true) {
		std::cin >> interval;
		if (interval == 1 || interval == 2 || interval == 3 || interval == 4 || interval == 5 || interval == 6 || interval == 7 || interval == 8 || interval == 9 || interval == 10) {
			break;
		}
		printInputError();
	}
	std::vector<ComputerRoom> Res = vCom.getAllElements_asc(); // 机房容量
	for (auto& c : Res) {
		std::cout << COMPUTER_ROOM_NUMBER << c.getId() << " " << MAXIMUM_CAPACITY_OF_COMPUTER_ROOM << c.GetMax() << std::endl;
	}
	while (true) {
		std::cin >> room;
		if (room == 1 || room == 2 || room == 3 || room == 4 || room == 5 || room == 6 || room == 7 || room == 8 || room == 9 || room == 10) {
			break;
		}
		else {
			std::cout << "输入错误" << std::endl;
			return;
		}
		printInputError();
	}
	printApplySuccess();

	std::ofstream ofs(ORDER_FILE, std::ios::app);

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "studentid:" << this->getId() << " ";
	ofs << "studentname:" << this->GetName() << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << std::endl;

	ofs.close();
	LOG();
}

void Student::ShowMyOrder() {
	OrderFile of;

	if (of.GetSize() == 0) {
		printMyOrderError();
		LOG();
		return;
	}
	for (int i = 0; i < of.GetSize(); i++) {
		if (atoi(of.OrderData[i]["studentid"].c_str()) == this->getId()) { // ID匹配，只要自己的记录
			std::cout << APPOINTMENT_DATE_WEEK << of.OrderData[i]["date"];
			// 显示时段对应的课节信息
			std::cout << TIME_SLOT;
			int interval = atoi(of.OrderData[i]["interval"].c_str());  // 获取时段
			std::cout << "第";
			switch (interval) {
			case 1:
				std::cout << "一节课";
				break;
			case 2:
				std::cout << "二节课";
				break;
			case 3:
				std::cout << "三节课";
				break;
			case 4:
				std::cout << "四节课";
				break;
			case 5:
				std::cout << "五节课";
				break;
			case 6:
				std::cout << "六节课";
				break;
			case 7:
				std::cout << "七节课";
				break;
			case 8:
				std::cout << "八节课";
				break;
			case 9:
				std::cout << "九节课";
				break;
			case 10:
				std::cout << "十节课";
				break;
			default:
				std::cout << "数据错误";
				break;
			}
			std::cout << COMPUTER_ROOM << of.OrderData[i]["roomId"];

			std::string status = STATE; // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
			if (of.OrderData[i]["status"] == UNDER_REVIEW) {
				status += UNDER_VIEW;
			}
			else if (of.OrderData[i]["status"] == APPOINTMENT) {
				status += APPOINTMENT_SUCCESSFUL;
			}
			else if (of.OrderData[i]["status"] == APPOINTMENT_FALIED) {
				status += REVIEW_DISAPPROVED_APPOINTMENT_FAILED;
			}
			else if (of.OrderData[i]["status"] == CANCELLED_APPOINEDMENT) {
				status += APPOINTMENT_CANCELLED;
			}
			std::cout << status << std::endl;
		}
	}
	LOG();
}

void Student::ShowAllOrder() {
	OrderFile of;

	if (of.GetSize() == 0) {
		printMyOrderError();
		LOG();
		return;
	}

	for (int i = 0; i < of.GetSize(); i++) {
		std::cout << i + 1 << "、 ";
		std::cout << APPOINTMENT_DATE_WEEK << of.OrderData[i]["date"];
		// 显示时段对应的课节信息
		std::cout << TIME_SLOT;
		int interval = atoi(of.OrderData[i]["interval"].c_str());  // 获取时段
		std::cout << "第";
		switch (interval) {
		case 1:
			std::cout << "一节课";
			break;
		case 2:
			std::cout << "二节课";
			break;
		case 3:
			std::cout << "三节课";
			break;
		case 4:
			std::cout << "四节课";
			break;
		case 5:
			std::cout << "五节课";
			break;
		case 6:
			std::cout << "六节课";
			break;
		case 7:
			std::cout << "七节课";
			break;
		case 8:
			std::cout << "八节课";
			break;
		case 9:
			std::cout << "九节课";
			break;
		case 10:
			std::cout << "十节课";
			break;
		default:
			std::cout << "数据错误";
			break;
		}
		std::cout << STUDENT_ID << of.OrderData[i]["studentid"];
		std::cout << NAME << of.OrderData[i]["studentname"];
		std::cout << COMPUTER_ROOM << of.OrderData[i]["roomId"];
		std::string status = STATE; // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
		if (of.OrderData[i]["status"] == UNDER_REVIEW) {
			status += UNDER_VIEW;
		}
		else if (of.OrderData[i]["status"] == APPOINTMENT) {
			status += APPOINTMENT_SUCCESSFUL;
		}
		else if (of.OrderData[i]["status"] == APPOINTMENT_FALIED) {
			status += REVIEW_DISAPPROVED_APPOINTMENT_FAILED;
		}
		else if (of.OrderData[i]["status"] == CANCELLED_APPOINEDMENT) {
			status += APPOINTMENT_CANCELLED;
		}
		std::cout << status << std::endl;
	}
	LOG();
}

void Student::CancelOrder() {
	OrderFile of;

	if (of.GetSize() == 0) {
		printMyOrderError();
		LOG();
		return;
	}
	printDeleteOrder1();

	std::vector<int> v;
	int index = 1;

	for (int i = 0; i < of.GetSize(); i++) {
		if (atoi(of.OrderData[i]["studentid"].c_str()) == this->getId()) {
			if (of.OrderData[i]["status"] == UNDER_REVIEW || of.OrderData[i]["status"] == APPOINTMENT) {
				v.push_back(i);
				std::cout << index++ << "、 ";
				std::cout << APPOINTMENT_DATE_WEEK << of.OrderData[i]["date"];
				// 显示时段对应的课节信息
				std::cout << TIME_SLOT;
				int interval = atoi(of.OrderData[i]["interval"].c_str());  // 获取时段
				std::cout << " 第";
				switch (interval) {
				case 1:
					std::cout << "一节课";
					break;
				case 2:
					std::cout << "二节课";
					break;
				case 3:
					std::cout << "三节课";
					break;
				case 4:
					std::cout << "四节课";
					break;
				case 5:
					std::cout << "五节课";
					break;
				case 6:
					std::cout << "六节课";
					break;
				case 7:
					std::cout << "七节课";
					break;
				case 8:
					std::cout << "八节课";
					break;
				case 9:
					std::cout << "九节课";
					break;
				case 10:
					std::cout << "十节课";
					break;
				default:
					std::cout << "数据错误";
					break;
				}
				std::cout << COMPUTER_ROOM << of.OrderData[i]["roomId"];
				std::string status = STATE; // 0 取消的预约   1 审核中   2 已预约  -1 预约失败
				if (of.OrderData[i]["status"] == UNDER_REVIEW) {
					status += UNDER_VIEW;
				}
				else if (of.OrderData[i]["status"] == APPOINTMENT) {
					status += APPOINTMENT_SUCCESSFUL;
				}
				std::cout << status << std::endl;
			}
		}
	}

	printDeleteOrder2();
	int select = 0;
	while (true) {
		std::cin >> select;
		if (0 <= select && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				of.OrderData[v[select - 1]]["status"] = CANCELLED_APPOINEDMENT;
				of.UpdateOrder();
				break;
				std::cout << "取消预约成功" << std::endl;
			}
		}
	}
	LOG();
}