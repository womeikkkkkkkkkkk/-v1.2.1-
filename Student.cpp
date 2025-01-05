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
		// ���ļ���ȡ����
		std::ifstream fileIn(STUDENT_FILE);
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
			std::ofstream fileOut(STUDENT_FILE, std::ios::trunc);  // ����ļ�������д��
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

#include <sstream>  // ���� istringstream ��

void Student::ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward) {
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		// ���������Ƿ���ȷ
		if (person.GetPassward() == oldpassward) {
			// �޸�����
			person.SetPasswards(passward);

			// ��ȡ�ļ�����
			std::ifstream fileIn(STUDENT_FILE);
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
					std::ofstream fileOut(STUDENT_FILE, std::ios::trunc);  // ����ļ�������д��
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
	std::vector<ComputerRoom> Res = vCom.getAllElements_asc(); // ��������
	for (auto& c : Res) {
		std::cout << COMPUTER_ROOM_NUMBER << c.getId() << " " << MAXIMUM_CAPACITY_OF_COMPUTER_ROOM << c.GetMax() << std::endl;
	}
	while (true) {
		std::cin >> room;
		if (room == 1 || room == 2 || room == 3 || room == 4 || room == 5 || room == 6 || room == 7 || room == 8 || room == 9 || room == 10) {
			break;
		}
		else {
			std::cout << "�������" << std::endl;
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
		if (atoi(of.OrderData[i]["studentid"].c_str()) == this->getId()) { // IDƥ�䣬ֻҪ�Լ��ļ�¼
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
				std::cout << index++ << "�� ";
				std::cout << APPOINTMENT_DATE_WEEK << of.OrderData[i]["date"];
				// ��ʾʱ�ζ�Ӧ�Ŀν���Ϣ
				std::cout << TIME_SLOT;
				int interval = atoi(of.OrderData[i]["interval"].c_str());  // ��ȡʱ��
				std::cout << " ��";
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
				std::string status = STATE; // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ  -1 ԤԼʧ��
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
				std::cout << "ȡ��ԤԼ�ɹ�" << std::endl;
			}
		}
	}
	LOG();
}