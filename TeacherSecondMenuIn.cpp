#include "TeacherSecondMenuIn.h"

void TeacherSecondMenu(Identity*& teacher) {
	while (true) {
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		std::cin >> select;
		if (select == 1) {
			tea->ShowAllOrder();
		}
		else if (select == 2) {
			tea->ValidOrder();
		}
		else if (select == 3) {
			printResetName();
			std::string s;  std::cin >> s;
			tea->ReSetName(*tea, s);
		}
		else if (select == 4) {
			printResetPassward();
			std::string s, ss;  std::cin >> s >> ss;
			tea->ReSetPasswards(*tea, ss, s);
		}
		else if (select == 0) {
			delete teacher;
			printLogoutSuccess();
			LOG();
			return;
		}
	}
}