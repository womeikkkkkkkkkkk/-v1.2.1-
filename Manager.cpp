#include "Manager.h"

std::istream& operator>>(std::istream& is, Manager& s) {
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

bool Manager::TextIdCmp(int fid, std::string text) {
	std::string ftext = std::to_string(fid);
	size_t len_valid_id = ftext.size();
	for (int i = 0; i < text.size(); i++) {
		if (ftext[i] != text[i] || len_valid_id != text.size()) {
			return false;
		}
	}
	return true;
}

Manager::Manager() {
	this->id = NULLID;
}

Manager::Manager(std::string name, std::string password) {
	this->SetName(name);
	this->SetPassward(password);
	this->InitVector();  // ��ʼ������
}

void Manager::operMenu() {
	printManagerSecondMenu();
}

void Manager::ReSetName(Identity& person, const std::string name) {
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

void Manager::ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward) {
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		// ���������Ƿ���ȷ
		if (person.GetPassward() == oldpassward) {
			// ��������
			person.SetPasswards(passward);

			// ��ȡ�ļ�����
			std::ifstream fileIn(ADMIN_FILE);
			if (fileIn.is_open()) {
				std::vector<std::string> lines;
				std::string line;
				while (std::getline(fileIn, line)) {
					lines.push_back(line);  // ���ļ����ݴ洢��lines������
				}
				fileIn.close();  // �رն�ȡ�ļ���

				bool found = false;
				for (auto& l : lines) {
					// ʹ�� istringstream �ָ�ÿ������
					std::istringstream ss(l);
					std::string username, password;
					ss >> username >> password;  // �ָ����е��û���������
					if (username == person.GetName()) {
						found = true;
						// �ҵ��û����������
						l = username + " " + passward;  // ���������滻������
						break;
					}
				}

				if (found) {
					// �ҵ��û����޸����룬����д���ļ�
					std::ofstream fileOut(ADMIN_FILE, std::ios::trunc);  // ����ļ�������д��
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

void Manager::RegisterUser(const int& id, const std::string& name, const std::string& passward) {
}

void Manager::SetId(const int& id) {
	this->id = id;
}

void Manager::SetName(const std::string& name) {
	this->Identity::SetName(name);
}

void Manager::SetPassward(const std::string& passward) {
	this->Identity::SetPasswards(passward);
}

int Manager::getId() const {
	return this->id;
}

std::string Manager::GetName() const {
	return this->Identity::GetName();
}

std::string Manager::GetPassward() const {
	return this->Identity::GetPassward();
}

void Manager::InitVector() {
	std::ifstream ifs;
	ifs.open(STUDENT_FILE, std::ios::in);
	Student s;
	while (ifs >> s) {
		vStu.insert(s);  // ���뵽ѧ����ϣ��
	}
	ifs.close();

	ifs.open(TEACHER_FILE, std::ios::in);
	Teacher t;
	while (ifs >> t) {
		vTea.insert(t);  // ���뵽��ʦ��ϣ��
	}
	ifs.close();

	ifs.open(COMPUTER_FILE, std::ios::in);
	ComputerRoom c;
	while (ifs >> c) {
		vCom.insert(c);  // ���뵽������ϣ��
	}
	ifs.close();
}

bool Manager::CheckRepeat(const int id, const int type) {
	if (type == STUDENTID) {
		return vStu.find(id);  // ��ѧ�����в���
	}
	else if (type == TEACHERID) {
		return vTea.find(id);  // �ڽ�ʦ���в���
	}
	return false;
}

void Manager::AddPerson() {
	InitVector();
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		printManagerThirst1Menu();
		std::string FileName;
		int flag = -1;
		std::ofstream ofs;
		int select = 0;
		/// �ж�����û�����
		while (true) {
			std::cin >> select;
			if (select == 1) {
				FileName = STUDENT_FILE;
				flag = STUDENTID;
				break;
			}
			else if (select == 2) {
				FileName = TEACHER_FILE;
				flag = TEACHERID;
				break;
			}
			else if (select == 0) {
				return;
			}
			else {
				printInputError();
				continue;
			}
		}
		/// ����û�
		ofs.open(FileName, std::ios::out | std::ios::app);
		int id;
		std::string name;
		std::string passward;

		flag == STUDENTID ? printInputStudentId() : printInputTeacherId();
		while (true) {
			std::cin >> id;
			bool isValid = this->CheckRepeat(id, flag);
			if (isValid) {
				flag == STUDENTID ? printStudentIdDuplicate() : printTeacherIdDuplicate();
			}
			else {
				break;
			}
		}
		printInputName();
		std::cin >> name;
		printInputPassword();
		std::cin >> passward;
		// �������������ݵ���ϣ��
		if (flag == STUDENTID) {
			Student student(id, name, passward);
			vStu.insert(student);  // ��ӵ�ѧ����ϣ��
		}
		else if (flag == TEACHERID) {
			Teacher teacher(id, name, passward);
			vTea.insert(teacher);  // ��ӵ���ʦ��ϣ��
		}
		ofs << id << " " << name << " " << passward << " " << std::endl;
		printAddSuccess();
		logMsg = Utils::GetCurrentTimes(ADD_STUDENT_SUCCESS);
		exceptionLog.LogException(logMsg);
		LOG();
		ofs.close();
		this->InitVector();
	}
	catch (...) {
		logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
		logMsg += Utils::GetCurrentTimes(ADD_STUDENT_FALIED);
		exceptionLog.LogException(logMsg);
		return;
	}
}

void Manager::RemovePerson() {
	InitVector();
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		printManagerThirst2Menu();
		int id;
		int flag = -1;
		std::string FileName;
		int select = 0;

		// �ж�ɾ���û�����
		while (true) {
			std::cin >> select;
			if (select == 1) {
				FileName = STUDENT_FILE;
				flag = STUDENTID;
				break;
			}
			else if (select == 2) {
				FileName = TEACHER_FILE;
				flag = TEACHERID;
				break;
			}
			else if (select == 0) {
				return;
			}
			else {
				printInputError();
				continue;
			}
		}

		// ��ȡ��ɾ�����û�ID
		flag == STUDENTID ? printInputStudentId() : printInputTeacherId();
		std::cin >> id;

		// ����ϣ�����Ƿ���ڸ�ID
		if (!this->CheckRepeat(id, flag)) {
			flag == STUDENTID ? printStudentIdDuplicate() : printTeacherIdDuplicate();
			return;
		}

		// �ӹ�ϣ����ɾ������
		if (flag == STUDENTID) {
			vStu.remove(id);  // ��ѧ����ϣ����ɾ��
		}
		else if (flag == TEACHERID) {
			vTea.remove(id);  // �ӽ�ʦ��ϣ����ɾ��
		}

		// ��ȡ�ļ�������д�룬ɾ��ָ��ID����Ŀ
		std::ifstream ifs(FileName);
		std::ofstream ofs("temp.txt");  // ������ʱ�ļ����洢�µ�����

		if (!ifs.is_open() || !ofs.is_open()) {
			throw std::runtime_error("�ļ���ʧ��");
		}

		int fileId;
		std::string name, passward;

		// ���ж�ȡ�ļ����ݲ�д����ʱ�ļ�������Ҫɾ����ID
		while (ifs >> fileId >> name >> passward) {
			if (fileId != id) {
				ofs << fileId << " " << name << " " << passward << " " << std::endl;
			}
		}

		// �ر��ļ���
		ifs.close();
		ofs.close();

		// ɾ��ԭ�ļ�������ʱ�ļ�������Ϊԭ�ļ���
		std::remove(FileName.c_str());
		std::rename("temp.txt", FileName.c_str());

		// ���ɾ���ɹ�����Ϣ
		std::cout << "ɾ���ɹ�" << std::endl;
		logMsg = Utils::GetCurrentTimes("ɾ���ɹ�");
		exceptionLog.LogException(logMsg);
		LOG();
	}
	catch (...) {
		logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
		logMsg += Utils::GetCurrentTimes(FIND_FALIED);
		exceptionLog.LogException(logMsg);
		return;
	}
}

void Manager::FindPerson(const std::string& text) {
	InitVector();
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		int select = 0;
		while (1) {
			printManagerThirst3Menu();
			std::cin >> select;
			if (select == 1) {
				std::cout << "������Ҫ���ҵ�id" << std::endl;
				int s; std::cin >> s;
				bool found = false;  // ���һ����־λ���ж��Ƿ��ҵ�ѧ��
				// ��������ѧ��Ͱ��ʹ�� find ����
				for (int i = 0; i < TABLE_SIZE; ++i) {
					auto& student = vStu.table[i];
					for (auto& students : student) {  // ���ѧ�������ҵ�ѧ��
						if (s == students.getId()) {
							logMsg = Utils::GetCurrentTimes(STUDENT_EXIST);
							exceptionLog.LogException(logMsg);
							std::cout << STUDENT_ID << students.getId() << NAME << students.GetName() << PASSWARD << students.GetPassward() << std::endl;
							found = true;
							break;
						}
					}
					if (found) break;  // �ҵ�������ѭ��
				}
			}
			else if (select == 2) {
				std::cout << "������Ҫ���ҵ�id" << std::endl;
				int s; std::cin >> s;
				for (int i = 0; i < TABLE_SIZE; ++i) {
					auto& teacher = vTea.table[i];
					for (auto& teachers : teacher) {
						if (s == teachers.getId()) {
							logMsg = Utils::GetCurrentTimes(TEACHER_EXIST);
							exceptionLog.LogException(logMsg);
							std::cout << TEACHER_ID << teachers.getId() << NAME << teachers.GetName() << PASSWARD << teachers.GetPassward() << std::endl;
							return;
						}
					}
				}
			}
			else if (select == 0) {
				return;
			}
			else {
				printInputError();
				logMsg = Utils::GetCurrentTimes(CIN_ERROR);
				exceptionLog.LogException(logMsg);
			}
		}
		LOG();
	}
	catch (...) {
		logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
		logMsg += Utils::GetCurrentTimes(FIND_FALIED);
		exceptionLog.LogException(logMsg);
		return;
	}
}

void Manager::ShowPerson() {
	InitVector();
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		int select = 0;
		while (1) {
			printManagerThirst3Menu();
			std::cin >> select;
			if (select == 1) {
				printAllStudentInfo();
				std::cout << "����" << std::endl;
				std::vector<Student>vRes = vStu.getAllElements_asc();
				for (auto& i : vRes) {
					std::cout << TEACHER_ID << i.getId() << " " << NAME << i.GetName() << " " << PASSWARD << i.GetPassward() << std::endl;
				}
				std::cout << "����" << std::endl;
				std::vector<Student>vRes_ = vStu.getAllElements_des();
				for (auto& i : vRes_) {
					std::cout << TEACHER_ID << i.getId() << " " << NAME << i.GetName() << " " << PASSWARD << i.GetPassward() << std::endl;
				}
			}
			else if (select == 2) {
				printAllTeacherInfo();
				std::cout << "����" << std::endl;
				std::vector<Teacher>vRes = vTea.getAllElements_asc();
				for (auto& i : vRes) {
					std::cout << TEACHER_ID << i.getId() << " " << NAME << i.GetName() << " " << PASSWARD << i.GetPassward() << std::endl;
				}
				std::cout << "����" << std::endl;
				std::vector<Teacher>vRes_ = vTea.getAllElements_des();
				for (auto& i : vRes_) {
					std::cout << TEACHER_ID << i.getId() << " " << NAME << i.GetName() << " " << PASSWARD << i.GetPassward() << std::endl;
				}
			}
			else if (select == 0) {
				return;
			}
			else {
				printInputError();
				continue;
			}
			break;
		}
		LOG();
	}
	catch (...) {
		logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
		logMsg += Utils::GetCurrentTimes(SHOW_ALL_PERSON_FALIED);
		exceptionLog.LogException(logMsg);
		return;
	}
}

void Manager::ShowComputer() {
	InitVector();
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		printAllComputerInfo();
		std::cout << "����" << std::endl;
		std::vector<ComputerRoom>vRes = vCom.getAllElements_asc();
		for (auto& i : vRes) {
			std::cout << COMPUTER_ROOM_NUMBER << i.getId() << " " << MAXIMUM_CAPACITY_OF_COMPUTER_ROOM << i.GetMax() << std::endl;
		}
		std::cout << "����" << std::endl;
		std::vector<ComputerRoom>vRes_ = vCom.getAllElements_des();
		for (auto& i : vRes_) {
			std::cout << COMPUTER_ROOM_NUMBER << i.getId() << " " << MAXIMUM_CAPACITY_OF_COMPUTER_ROOM << i.GetMax() << std::endl;
		}
		LOG();
	}
	catch (...) {
		logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
		logMsg += Utils::GetCurrentTimes(SHOW_ALL_PERSON_FALIED);
		exceptionLog.LogException(logMsg);
		return;
	}
}

void Manager::CleanFile() {
	InitVector();
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		std::ofstream ofs(ORDER_FILE, std::ios::trunc);
		ofs.close();
	}
	catch (...) {
		logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
		logMsg += Utils::GetCurrentTimes(SHOW_ALL_PERSON_FALIED);
		exceptionLog.LogException(logMsg);
		return;
	}
}