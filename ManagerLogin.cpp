#include "ManagerSecondMenuIn.h"
#include "Utils.h"
#include "ExceptionLog.h"

void ManagerLogin(std::string FileName) {
	// 数据初始化
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	try {
		std::ifstream ifs;
		ifs.open(FileName, std::ios::in);
		if (!ifs.is_open()) {
			printFileNotFound();
			ifs.close();
			return;
		}
		// 输入账号密码
		Identity* person = nullptr;

		std::string name;
		std::string passward;
		printInputManagerId();
		std::cin >> name;
		printInputPassword();
		std::cin >> passward;
		// 验证
		std::string fname;
		std::string encryptedFpassward;
		std::string logMsg;

		bool flag = false;
		while (ifs >> fname && ifs >> encryptedFpassward) {
			if (name == fname) {
				flag = true;
				if (passward == encryptedFpassward) {
					// 验证通过
					logMsg = Utils::GetCurrentTimes(MANAGER_LOGIN_SUCCESS);
					printLoginManagerSuccess();
					exceptionLog.LogException(logMsg); // 验证通过信息

					person = new Manager(name, passward);
					if (person == nullptr) { // 内存是否分配成功
						printLoginManagerFailed();
						logMsg = Utils::GetCurrentTimes(CREATER_MANAGER_FALIED);
						exceptionLog.LogException(logMsg); // 分配失败
					}
					else {
						logMsg = Utils::GetCurrentTimes(CREATER_MANAGER_SUCCESS);
						exceptionLog.LogException(logMsg); // 分配成功
						ManagerSecondMenu(person);         // 进入管理员二级菜单
						return;
					}
				}
				else {
					printPasswardError(); // 密码错误
					logMsg = Utils::GetCurrentTimes(PASSWARD_ERROR);
					exceptionLog.LogException(logMsg);
					return;
				}
			}
		}
		if (flag == false) { // ID不存在
			printIdError();
			logMsg = Utils::GetCurrentTimes(ID_NO_EXIST);
			exceptionLog.LogException(logMsg);
		}
		else { // 非法登录
			printIllegalLogin();
			logMsg = Utils::GetCurrentTimes(ILLEGAL_LOGIN);
			exceptionLog.LogException(logMsg);
		}
	}
	catch (...) {
		std::string logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
		exceptionLog.LogException(logMsg);
		return;
	}
}