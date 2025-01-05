#include "ManagerSecondMenuIn.h"

void ManagerSecondMenu(Identity* manager) {
	while (true) {
		manager->operMenu();
		Manager* man = (Manager*)manager;
		int select = 0;
		std::cin >> select;
		if (select == 1) {
			printAddAccount();
			man->AddPerson();
		}
		else if (select == 2) {
			printRemovePerson();
			man->RemovePerson();
		}
		else if (select == 3) {
			printFindPerson();
			man->FindPerson(manager->GetName());
		}
		else if (select == 4) {
			printViewComputerRoom();
			man->ShowComputer();
		}
		else if (select == 5) {
			printViewAccount();
			man->ShowPerson();
		}
		else if (select == 6) {
			printClearReservation();
			man->CleanFile();
		}
		else if (select == 7) {
			printResetName();
			std::string s;  std::cin >> s;
			man->ReSetName(*man, s);
		}
		else if (select == 8) {
			printResetPassward();
			std::string s, ss;  std::cin >> s >> ss;
			man->ReSetPasswards(*man, ss, s);
		}
		else if (select == 0) {
			delete manager;
			printLogoutSuccess();
			LOG();
			return;
		}
	}
}