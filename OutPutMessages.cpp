#include "OutPutMessages.h"
using namespace std;

//菜单类
void printMainMenu() {
	cout << "======================  机房预约系统  =====================" << endl;
	cout << endl << "请输入您的身份" << endl;
	cout << "\t\t -------------------------------\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          1.学生代表           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          2.老    师           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          3.管 理 员           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          4.注册用户           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          0.退    出           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t -------------------------------\n";
	cout << "输入您的选择: ";
}

void printExitMainMenu() {
	cout << "欢迎下一次使用!!!" << endl;
}

void printManagerSecondMenu() {
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.删除账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查找账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          5.显示用户            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          6.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          7.修改用户名          |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          8.修改密码            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void printManagerThirst1Menu() {
	cout << "请输入添加账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;
	cout << "0、退出" << endl;
}

void printManagerThirst2Menu() {
	cout << "请输入删除账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;
	cout << "0、退出" << endl;
}

void printManagerThirst3Menu() {
	cout << "请选择查看账号的类型：" << endl;
	cout << "1、查看学生" << endl;
	cout << "2、查看老师" << endl;
	cout << "0、退出" << endl;
}

void printTeacherSecondMenu() {
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.审核预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.修改用户名            |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.修改密码              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void printTeacherThirst1Menu() {
}

void printTeacherThirst2Menu() {
}

void printStudentSecondMenu() {
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1.申请预约             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2.查看我的预约         |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3.查看所有预约         |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          4.取消预约             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          5.修改用户名           |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          6.修改密码             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.注销登录             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void printStudentThirst1Mneu() {
}

void printStudentThirst2Menu() {
}

void printRegisterMenu() {
	cout << "请选择注册类型：" << endl;
	cout << "1、学生" << endl;
	cout << "2、老师" << endl;
	cout << "0、退出" << endl;
}

//异常类
void printInputError() {
	cout << "输入有误，请重新选择！" << endl;
}

void printFileNotFound() {
	cout << "No File" << endl;
}

//登陆类
void printInputStudentId() {
	cout << "请输入学号：" << endl;
}

void printInputTeacherId() {
	cout << "请输入职工号：" << endl;
}

void printInputManagerId() {
	cout << "请输入管理员账号：" << endl;
}

void printInputPassword() {
	cout << "请输入密码：" << endl;
}

void printPasswardError() {
	cout << "密码错误！" << endl;
}

void printIdError() {
	cout << "ID不存在" << endl;
}

void printLoginStudentSuccess() {
	cout << "学生登录成功" << endl;
}

void printLoginTeacherSuccess() {
	cout << "教师登录成功" << endl;
}

void printLoginManagerSuccess() {
	cout << "管理员登录成功" << endl;
}

void printLoginStudentFailed() {
	cout << "学生登录失败" << endl;
}

void printLoginTeacherFailed() {
	cout << "教师登录失败" << endl;
}

void printLoginManagerFailed() {
	cout << "管理员登录失败" << endl;
}

void printIllegalLogin() {
	cout << "非法登录" << endl;
}

void printRegisterSuccess() {
	cout << "注册成功" << endl;
}

void printRegisterFailed() {
	cout << "注册失败" << endl;
}

void printRegisterError() {
	cout << "注册错误" << endl;
}
//功能类
void LOG() {
	system("pause");
	system("cls");
}
void TMP() {
	system("pause");
}
void CLEAR() {
	system("cls");
}

//提示类
///管理员二级菜单功能
void printAddAccount() {
	cout << "添加账号" << endl;
}

void printStudentIdDuplicate() {
	cout << "学号重复，请重新输入" << endl;
}

void printTeacherIdDuplicate() {
	cout << "职工号重复，请重新输入" << endl;
}

void printCurrentStudentNumber(int studentnums) {
	cout << "当前学生数量为：" << studentnums << endl;
}

void printCurrentTeacherNumber(int teachernums) {
	cout << "当前教师数量为：" << teachernums << endl;
}

void printAddSuccess() {
	cout << "添加成功" << endl;
}

void printRemovePerson() {
	cout << "删除账号" << endl;
}

void printFindPerson() {
	cout << "查找账号" << endl;
}

void printViewAccount() {
	cout << "查看账号" << endl;
}

void printAllTeacherInfo() {
	cout << "所有老师信息如下：" << endl;
}

void printAllStudentInfo() {
	cout << "所有学生信息如下：" << endl;
}

void printViewComputerRoom() {
	cout << "查看机房" << endl;
}

void printCurrentComputerNumber(int computernums) {
	cout << "当前机房数量为：" << computernums << endl;
}

void printAllComputerInfo() {
	cout << "机房信息如下：" << endl;
}

void printClearReservation() {
	cout << "清空预约" << endl;
}

void printAllClearSucces() {
	cout << "清空成功！" << endl;
}

void printResetName() {
	cout << "修改名字" << endl;
}

void printResetPassward() {
	cout << "修改密码，请输入原密码和新密码！" << endl;
}
void printResetPasswardSuccess() {
	cout << "修改密码成功！" << endl;
}
void printResetPasswardFalied() {
	cout << "修改密码失败，请检查原密码是否正确！" << endl;
}

void printResetNameSuccess() {
	cout << "修改用户名成功" << endl;
}

void printResetNameFalied() {
	cout << "修改用户名失败，请稍后重试" << endl;
}

//
///教师二级菜单功能
void printViewAllOrder() {
	cout << "查看所有预约" << endl;
}

void printValidOrder() {
	cout << "审核预约" << endl;
}

void printMemoryOrder1() {
	cout << "待审核的预约记录如下：" << endl;
}

void printMemoryOrder2() {
	cout << "请输入审核的预约记录,0代表返回" << endl;
}

void printMemoryOrder3() {
	cout << "请输入审核结果" << endl;
	cout << "1、通过" << endl;
	cout << "2、不通过" << endl;
}
void printMemoryOrder4() {
	cout << "审核完毕！" << endl;
}
//
///学生二级菜单功能
void printApplyOrder1() {
	cout << "机房开放时间为周一至周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
}

void printApplyOrder2() {
	cout << "请输入申请预约的时间段：" << endl;
	cout << "1、第一节课" << endl;
	cout << "2、第二节课" << endl;
	cout << "3、第三节课" << endl;
	cout << "4、第四节课" << endl;
	cout << "5、第五节课" << endl;
	cout << "6、第六节课" << endl;
	cout << "7、第七节课" << endl;
	cout << "8、第八节课" << endl;
	cout << "9、第九节课" << endl;
	cout << "10、第十节课" << endl;
}

void printApplyOrder3(std::vector<ComputerRoom>& vCom) {
}

void printApplySuccess() {
	cout << "预约成功！审核中" << endl;
}

void printMyOrderError() {
	cout << "无预约记录" << endl;
}

void printAllOrderError() {
	cout << "无预约记录" << endl;
}

void printDeleteOrder1() {
	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
}

void printDeleteOrder2() {
	cout << "请输入取消的记录,0代表返回" << endl;
}

///共用二级菜单功能
void printLogoutSuccess() {
	cout << "注销成功" << endl;
}

void printInputName() {
	cout << "请输入姓名：" << endl;
}