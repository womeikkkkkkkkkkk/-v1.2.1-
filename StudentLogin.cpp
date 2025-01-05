#include "StudentLogin.h"
#include "ExceptionLog.h"
#include "Utils.h"

void StudentLogin(std::string FileName) {
	// ���ݳ�ʼ��
	ExceptionLog exceptionLog(EXCEPTIONLOG);
	try {
		std::ifstream ifs;
		ifs.open(FileName, std::ios::in);
		if (!ifs.is_open()) {
			printFileNotFound();
			ifs.close();
			return;
		}
		// �����˺�����
		Identity* person = nullptr;

		int id = 0;
		std::string passward;
		printInputStudentId();
		std::cin >> id;
		printInputPassword();
		std::cin >> passward;
		// ��֤
		int fid;
		std::string fname;
		std::string encryptedFpassward;
		std::string logMsg;

		bool flag = false;
		while (ifs >> fid && ifs >> fname && ifs >> encryptedFpassward) {
			if (id == fid) {
				flag = true;
				if (passward == encryptedFpassward) { // ��֤ͨ��
					logMsg = Utils::GetCurrentTimes(STUDENT_LOGIN_SUCCESS);
					printLoginStudentSuccess();
					exceptionLog.LogException(logMsg); // ��֤ͨ����Ϣ

					person = new Student(id, fname, passward);
					if (person == nullptr) { // �ڴ��Ƿ����ɹ�
						printLoginStudentFailed();
						logMsg = Utils::GetCurrentTimes(CREATER_STUDENT_FALIED);
						exceptionLog.LogException(logMsg); // ����ʧ��
					}
					else {
						logMsg = Utils::GetCurrentTimes(CREATER_STUDENT_SUCCESS);
						exceptionLog.LogException(logMsg); // ����ɹ�
						StudentMenu(person);               // ����ѧ�������˵�
						return;
					}
				}
				else {
					printPasswardError(); // �������
					logMsg = Utils::GetCurrentTimes(PASSWARD_ERROR);
					exceptionLog.LogException(logMsg);
					return;
				}
			}
		}
		if (flag == false) { // ID������
			printIdError();
			logMsg = Utils::GetCurrentTimes(ID_NO_EXIST);
			exceptionLog.LogException(logMsg);
		}
		else { // �Ƿ���¼
			printIllegalLogin();
			return;
		}
	}
	catch (...) {
		std::string logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
		exceptionLog.LogException(logMsg);
		return;
	}
}