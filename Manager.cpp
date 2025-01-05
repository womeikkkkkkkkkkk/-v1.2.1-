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
	this->InitVector();  // 初始化数据
}

void Manager::operMenu() {
	printManagerSecondMenu();
}

void Manager::ReSetName(Identity& person, const std::string name) {
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

void Manager::ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward) {
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	std::string logMsg;
	try {
		// 检查旧密码是否正确
		if (person.GetPassward() == oldpassward) {
			// 更新密码
			person.SetPasswards(passward);

			// 读取文件内容
			std::ifstream fileIn(ADMIN_FILE);
			if (fileIn.is_open()) {
				std::vector<std::string> lines;
				std::string line;
				while (std::getline(fileIn, line)) {
					lines.push_back(line);  // 将文件内容存储到lines向量中
				}
				fileIn.close();  // 关闭读取文件流

				bool found = false;
				for (auto& l : lines) {
					// 使用 istringstream 分割每行内容
					std::istringstream ss(l);
					std::string username, password;
					ss >> username >> password;  // 分割行中的用户名和密码
					if (username == person.GetName()) {
						found = true;
						// 找到用户后更新密码
						l = username + " " + passward;  // 用新密码替换旧密码
						break;
					}
				}

				if (found) {
					// 找到用户并修改密码，重新写入文件
					std::ofstream fileOut(ADMIN_FILE, std::ios::trunc);  // 清空文件并覆盖写入
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
		vStu.insert(s);  // 插入到学生哈希表
	}
	ifs.close();

	ifs.open(TEACHER_FILE, std::ios::in);
	Teacher t;
	while (ifs >> t) {
		vTea.insert(t);  // 插入到教师哈希表
	}
	ifs.close();

	ifs.open(COMPUTER_FILE, std::ios::in);
	ComputerRoom c;
	while (ifs >> c) {
		vCom.insert(c);  // 插入到机房哈希表
	}
	ifs.close();
}

bool Manager::CheckRepeat(const int id, const int type) {
	if (type == STUDENTID) {
		return vStu.find(id);  // 在学生表中查找
	}
	else if (type == TEACHERID) {
		return vTea.find(id);  // 在教师表中查找
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
		/// 判断添加用户类型
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
		/// 添加用户
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
		// 创建并插入数据到哈希表
		if (flag == STUDENTID) {
			Student student(id, name, passward);
			vStu.insert(student);  // 添加到学生哈希表
		}
		else if (flag == TEACHERID) {
			Teacher teacher(id, name, passward);
			vTea.insert(teacher);  // 添加到教师哈希表
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

		// 判断删除用户类型
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

		// 获取待删除的用户ID
		flag == STUDENTID ? printInputStudentId() : printInputTeacherId();
		std::cin >> id;

		// 检查哈希表中是否存在该ID
		if (!this->CheckRepeat(id, flag)) {
			flag == STUDENTID ? printStudentIdDuplicate() : printTeacherIdDuplicate();
			return;
		}

		// 从哈希表中删除数据
		if (flag == STUDENTID) {
			vStu.remove(id);  // 从学生哈希表中删除
		}
		else if (flag == TEACHERID) {
			vTea.remove(id);  // 从教师哈希表中删除
		}

		// 读取文件并重新写入，删除指定ID的条目
		std::ifstream ifs(FileName);
		std::ofstream ofs("temp.txt");  // 创建临时文件来存储新的数据

		if (!ifs.is_open() || !ofs.is_open()) {
			throw std::runtime_error("文件打开失败");
		}

		int fileId;
		std::string name, passward;

		// 逐行读取文件内容并写入临时文件，跳过要删除的ID
		while (ifs >> fileId >> name >> passward) {
			if (fileId != id) {
				ofs << fileId << " " << name << " " << passward << " " << std::endl;
			}
		}

		// 关闭文件流
		ifs.close();
		ofs.close();

		// 删除原文件并将临时文件重命名为原文件名
		std::remove(FileName.c_str());
		std::rename("temp.txt", FileName.c_str());

		// 输出删除成功的信息
		std::cout << "删除成功" << std::endl;
		logMsg = Utils::GetCurrentTimes("删除成功");
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
				std::cout << "请输入要查找的id" << std::endl;
				int s; std::cin >> s;
				bool found = false;  // 添加一个标志位，判断是否找到学生
				// 遍历所有学生桶，使用 find 查找
				for (int i = 0; i < TABLE_SIZE; ++i) {
					auto& student = vStu.table[i];
					for (auto& students : student) {  // 如果学生表中找到学生
						if (s == students.getId()) {
							logMsg = Utils::GetCurrentTimes(STUDENT_EXIST);
							exceptionLog.LogException(logMsg);
							std::cout << STUDENT_ID << students.getId() << NAME << students.GetName() << PASSWARD << students.GetPassward() << std::endl;
							found = true;
							break;
						}
					}
					if (found) break;  // 找到后跳出循环
				}
			}
			else if (select == 2) {
				std::cout << "请输入要查找的id" << std::endl;
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
				std::cout << "升序" << std::endl;
				std::vector<Student>vRes = vStu.getAllElements_asc();
				for (auto& i : vRes) {
					std::cout << TEACHER_ID << i.getId() << " " << NAME << i.GetName() << " " << PASSWARD << i.GetPassward() << std::endl;
				}
				std::cout << "降序" << std::endl;
				std::vector<Student>vRes_ = vStu.getAllElements_des();
				for (auto& i : vRes_) {
					std::cout << TEACHER_ID << i.getId() << " " << NAME << i.GetName() << " " << PASSWARD << i.GetPassward() << std::endl;
				}
			}
			else if (select == 2) {
				printAllTeacherInfo();
				std::cout << "升序" << std::endl;
				std::vector<Teacher>vRes = vTea.getAllElements_asc();
				for (auto& i : vRes) {
					std::cout << TEACHER_ID << i.getId() << " " << NAME << i.GetName() << " " << PASSWARD << i.GetPassward() << std::endl;
				}
				std::cout << "降序" << std::endl;
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
		std::cout << "升序" << std::endl;
		std::vector<ComputerRoom>vRes = vCom.getAllElements_asc();
		for (auto& i : vRes) {
			std::cout << COMPUTER_ROOM_NUMBER << i.getId() << " " << MAXIMUM_CAPACITY_OF_COMPUTER_ROOM << i.GetMax() << std::endl;
		}
		std::cout << "降序" << std::endl;
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