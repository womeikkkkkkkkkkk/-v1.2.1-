#include "GlobalFile.h"
#include "OutPutMessages.h"
#include "OrderFile.h"
#include "ComputerRoom.h"
#include "Identity.h"
#include "Student.h"
#include "Manager.h"
#include "Teacher.h"
#include "ManagerLogin.h"
#include "StudentLogin.h"
#include "TeacherLogin.h"
#include "TeacherSecondMenuIn.h"
#include "StudentSecondMenuIn.h"
#include "ManagerSecondMenuIn.h"
using namespace std;

int main() {
	int select = 0;

	while (true) {
		printMainMenu();
		cin >> select; //接受用户选择
		switch (select) {
		case 1:  //学生身份
			StudentLogin(STUDENT_FILE);
			break;
		case 2:  //老师身份
			TeacherLogin(TEACHER_FILE);
			break;
		case 3:  //管理员身份
			ManagerLogin(ADMIN_FILE);
			break;
		case 4: //注册
			printRegisterMenu();
			int a; std::cin >> a;
			if (a == 1) {
				Student s;
				std::cout << "请输入ID、用户名" << std::endl;
				std::string name, passward;
				int id;
				std::cin >> id >> name;
				std::cout << "请输入密码" << std::endl;
				std::cin >> passward;
				s.RegisterUser(id, name, passward);
			}
			else if (a == 2) {
				Teacher t;
				std::cout << "请输入ID、用户名" << std::endl;
				std::string name, passward;
				int id;
				std::cin >> id >> name;
				std::cout << "请输入密码" << std::endl;
				std::cin >> passward;
				t.RegisterUser(id, name, passward);
			}
			else {
				printInputError();
			}
			break;
		case 0:  //退出系统
			printExitMainMenu();
			TMP();
			return 0;
			break;
		default:
			printInputError();
			LOG();
			break;
		}
	}
	TMP();
	return 0;
}