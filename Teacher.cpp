#include "Teacher.h"

Teacher::Teacher() {
	this->id = NULLID;
}

Teacher::Teacher(int id, std::string name, std::string passward) {
	this->id = id;
	this->SetName(name);
	this->SetPasswards(passward);
}

void Teacher::operMenu() {
	printTeacherSecondMenu();
}

void Teacher::ReSetName(Identity& person, const std::string name) {
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		// ���ļ���ȡ����
		std::ifstream fileIn(TEACHER_FILE);
		if (!fileIn.is_open()) {
			std::cerr << "�޷����ļ����ж�ȡ������" << std::endl;
			return;
		}

		// ��ȡ�ļ��е�ÿһ��
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(fileIn, line)) {
			lines.push_back(line);  // ��ÿ�д洢��lines������
		}
		fileIn.close();  // �رն�ȡ��

		bool found = false;
		// �����ļ��е�ÿһ�У������û���ƥ��ļ�¼
		for (auto& l : lines) {
			// ʹ�� stringstream �ָ�ÿ������
			std::istringstream ss(l);
			std::string index, username, password;
			ss >> index >> username >> password;  // ��ȡ��š��û���������

			// ����ҵ��˸��û���
			if (username == person.GetName()) {
				found = true;
				// �޸ĸ��е��û���
				l = index + " " + name + " " + password;  // �����û���
				person.SetName(name);  // ���¶��������
				break;
			}
		}

		// ����ҵ���Ŀ���û����������ļ�����
		if (found) {
			// ���ļ��Խ���д��
			std::ofstream fileOut(TEACHER_FILE, std::ios::trunc);  // ����ļ�������д��
			if (!fileOut.is_open()) {
				std::cerr << "�޷����ļ�����д�������" << std::endl;
				return;
			}

			// ���޸ĺ������д���ļ�
			for (const auto& l : lines) {
				fileOut << l << std::endl;  // ��ÿ������д���ļ�
			}
			fileOut.close();  // �ر�д����

			// ��ӡ�ɹ���Ϣ����¼��־
			printResetNameSuccess();
			logMsg = Utils::GetCurrentTimes(RESETNAME_SUCCESS);
			exceptionLog.LogException(logMsg);
		}
		else {
			std::cerr << "δ�ҵ�ָ�����û�����" << std::endl;
		}
	}
	catch (...) {
		// ���������쳣����¼��־
		logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
		logMsg += Utils::GetCurrentTimes(RESETNAME_FALIED);
		exceptionLog.LogException(logMsg);
		return;
	}
}

void Teacher::ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward) {
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		// ���������Ƿ���ȷ
		if (person.GetPassward() == oldpassward) {
			// �޸�����
			person.SetPasswards(passward);

			// ��ȡ�ļ�����
			std::ifstream fileIn(TEACHER_FILE);
			if (fileIn.is_open()) {
				std::vector<std::string> lines;
				std::string line;
				while (std::getline(fileIn, line)) {
					lines.push_back(line);  // ��ÿ�д洢��lines������
				}
				fileIn.close();  // �ر��ļ���ȡ��

				bool found = false;
				for (auto& l : lines) {
					// ʹ�� stringstream �ָ�ÿ������
					std::istringstream ss(l);
					std::string index, username, password;
					ss >> index >> username >> password;  // ��ȡ��š��û���������
					if (username == person.GetName()) {
						found = true;
						// �޸ĸ��е�����
						l = index + " " + username + " " + passward;  // ���������滻������
						break;
					}
				}

				// ����ҵ����û��������ļ�����
				if (found) {
					std::ofstream fileOut(TEACHER_FILE, std::ios::trunc);  // ����ļ�������д��
					if (fileOut.is_open()) {
						for (const auto& l : lines) {
							fileOut << l << std::endl;  // ���޸ĺ������д���ļ�
						}
						printResetPasswardSuccess();
						logMsg = Utils::GetCurrentTimes(RESETPASSWARD_SUCCESS);
						exceptionLog.LogException(logMsg);
					}
					else {
						std::cerr << "�޷����ļ�����д�������" << std::endl;
					}
				}
				else {
					std::cerr << "δ�ҵ�ָ�����û�����" << std::endl;
				}
			}
			else {
				std::cerr << "�޷����ļ����ж�ȡ������" << std::endl;
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

void Teacher::RegisterUser(const int& id, const std::string& name, const std::string& passward) {
	std::ofstream ofs;
	ofs.open(TEACHER_FILE, std::ios::out | std::ios::app);
	ofs << id << " " << name << " " << passward << std::endl;
	ofs.close();
	printRegisterSuccess();
	LOG();
}

std::istream& operator>>(std::istream& is, Teacher& s) {
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

void Teacher::SetId(const int& id) {
	this->id = id;
}

void Teacher::SetName(const std::string& name) {
	this->Identity::SetName(name);
}

void Teacher::SetPassward(const std::string& passward) {
	this->Identity::SetPasswards(passward);
}

int Teacher::getId() const {
	return this->id;
}

std::string Teacher::GetName() const {
	return this->Identity::GetName();
}

std::string Teacher::GetPassward() const {
	return this->Identity::GetPassward();
}

void Teacher::ShowAllOrder() {
	OrderFile of;

	if (of.GetSize() == 0) {
		printMyOrderError();
		LOG();
		return;
	}

	for (int i = 0; i < of.GetSize(); i++) {
		std::cout << i + 1 << "�� ";

		std::cout << APPOINTMENT_DATE_WEEK << of.OrderData[i]["date"];
		// ��ʾʱ�ζ�Ӧ�Ŀν���Ϣ
		std::cout << TIME_SLOT;
		int interval = atoi(of.OrderData[i]["interval"].c_str());  // ��ȡʱ��
		std::cout << "��";
		switch (interval) {
		case 1:
			std::cout << "һ�ڿ�";
			break;
		case 2:
			std::cout << "���ڿ�";
			break;
		case 3:
			std::cout << "���ڿ�";
			break;
		case 4:
			std::cout << "�Ľڿ�";
			break;
		case 5:
			std::cout << "��ڿ�";
			break;
		case 6:
			std::cout << "���ڿ�";
			break;
		case 7:
			std::cout << "�߽ڿ�";
			break;
		case 8:
			std::cout << "�˽ڿ�";
			break;
		case 9:
			std::cout << "�Žڿ�";
			break;
		case 10:
			std::cout << "ʮ�ڿ�";
			break;
		default:
			std::cout << "���ݴ���";
			break;
		}
		std::cout << STUDENT_ID << of.OrderData[i]["studentid"];
		std::cout << NAME << of.OrderData[i]["studentname"];
		std::cout << COMPUTER_ROOM << of.OrderData[i]["roomId"];
		std::string status = STATE; // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
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

void Teacher::ValidOrder() {
	OrderFile of;

	if (of.GetSize() == 0) {
		printMyOrderError();
		LOG();
		return;
	}
	std::vector<int> v;
	int index = 0;
	for (int i = 0; i < of.GetSize(); i++) {
		if (of.OrderData[i]["status"] == UNDER_REVIEW) {
			v.push_back(i);
			std::cout << ++index << "�� ";
			std::cout << APPOINTMENT_DATE_WEEK << of.OrderData[i]["date"];
			// ��ʾʱ�ζ�Ӧ�Ŀν���Ϣ
			std::cout << TIME_SLOT;
			int interval = atoi(of.OrderData[i]["interval"].c_str());  // ��ȡʱ��
			std::cout << "��";
			switch (interval) {
			case 1:
				std::cout << "һ�ڿ�";
				break;
			case 2:
				std::cout << "���ڿ�";
				break;
			case 3:
				std::cout << "���ڿ�";
				break;
			case 4:
				std::cout << "�Ľڿ�";
				break;
			case 5:
				std::cout << "��ڿ�";
				break;
			case 6:
				std::cout << "���ڿ�";
				break;
			case 7:
				std::cout << "�߽ڿ�";
				break;
			case 8:
				std::cout << "�˽ڿ�";
				break;
			case 9:
				std::cout << "�Žڿ�";
				break;
			case 10:
				std::cout << "ʮ�ڿ�";
				break;
			default:
				std::cout << "���ݴ���";
				break;
			}
			std::cout << COMPUTER_ROOM << of.OrderData[i]["roomId"];
			std::string status = STATE; // 0ȡ����ԤԼ   1 �����   2 ��ԤԼ  -1 ԤԼʧ��
			if (of.OrderData[i]["status"] == UNDER_REVIEW) {
				status += UNDER_VIEW;
			}
			std::cout << status << std::endl;
		}
	}
	printMemoryOrder2();
	int select = 0;
	int ret = 0;
	while (true) {
		std::cin >> select;
		if (0 <= select && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				printMemoryOrder3();
				std::cin >> ret;
				if (ret == 1) {
					of.OrderData[v[select - 1]]["status"] = APPOINTMENT;
				}
				else {
					of.OrderData[v[select - 1]]["status"] = APPOINTMENT_FALIED;
				}
				of.UpdateOrder();
				printMemoryOrder4();
				break;
			}
		}
		printInputError();
	}
	LOG();
}