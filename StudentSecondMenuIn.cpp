#include "StudentSecondMenuIn.h"

void StudentMenu(Identity*& student) {
	while (true) {
		student->operMenu();
		Student* stu = (Student*)student;
		int select = 0;
		std::cin >> select;
		if (select == 1) {
			stu->ApplyOrder();
		}
		else if (select == 2) {
			stu->ShowMyOrder();
		}
		else if (select == 3) {
			stu->ShowAllOrder();
		}
		else if (select == 4) {
			stu->CancelOrder();
		}
		else if (select == 5) {
			printResetName();
			std::string s;  std::cin >> s;
			stu->ReSetName(*stu, s);
		}
		else if (select == 6) {
			printResetPassward();
			std::string s, ss;  std::cin >> s >> ss;
			stu->ReSetPasswards(*stu, ss, s);
		}
		else if (select == 0) {
			delete student;
			printLogoutSuccess();
			LOG();
			return;
		}
	}
}