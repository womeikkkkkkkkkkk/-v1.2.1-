#pragma once
#include <string>

#define ADMIN_FILE "admin.txt"//管理员表
#define STUDENT_FILE "student.txt"//学生表
#define TEACHER_FILE "teacher.txt"//教师表
#define COMPUTER_FILE "computerroom.txt"//机房表
#define ORDER_FILE "order.txt"//预约表
#define EXCEPTIONLOG "exceptionlog.txt"//日志
//#define KEY "Key.txt"//密钥文件
const int TABLE_SIZE = 100;
const int  NULLID = -1;//初始化ID
const int NULLCONTAINER = -1;//初始化容量

const std::string LOGIN_INIT_ID = "";
const std::string LOGIN_INIT_NAME = "";
const bool LOGIN_INIT_STATUS = false;

// 0 取消的预约   1 审核中   2 已预约 - 1 预约失败
const std::string CANCELLED_APPOINEDMENT = "0";
const std::string UNDER_REVIEW = "1";
const std::string APPOINTMENT = "2";
const std::string APPOINTMENT_FALIED = "-1";
const std::string MORNING = "上午";
const std::string AFTERNOON = "下午";
const std::string APPOINTMENT_DATE_WEEK = "预约日期： 周";
const std::string TIME_SLOT = "时段：";
const std::string STUDENT_ID = "学号：";
const std::string TEACHER_ID = "职工号：";
const std::string NAME = "姓名：";
const std::string COMPUTER_ROOM = "机房：";
const std::string STATE = "状态：";
const std::string UNDER_VIEW = "审核中";
const std::string APPOINTMENT_SUCCESSFUL = "预约成功";
const std::string REVIEW_DISAPPROVED_APPOINTMENT_FAILED = "审核未通过，预约失败";
const std::string APPOINTMENT_CANCELLED = "预约已取消";
const std::string COMPUTER_ROOM_NUMBER = "机房编号：";
const std::string MAXIMUM_CAPACITY_OF_COMPUTER_ROOM = "机房最大容量：";
const std::string PASSWARD = "密码为：";
const std::string MANAGER_LOGIN_SUCCESS = "管理员的ID正确、密码正确";
const std::string STUDENT_LOGIN_SUCCESS = "学生的ID正确、密码正确";
const std::string TEACHER_LOGIN_SUCCESS = "教师的ID正确、密码正确";
const std::string CREATER_MANAGER_FALIED = "内存分配失败，无法创建管理员对象";
const std::string CREATER_STUDENT_FALIED = "内存分配失败，无法创建学生对象";
const std::string CREATER_TEACHER_FALIED = "内存分配失败，无法创建教师对象";
const std::string CREATER_MANAGER_SUCCESS = "创建管理员成功";
const std::string CREATER_STUDENT_SUCCESS = "创建学生成功";
const std::string CREATER_TEACHER_SUCCESS = "创建教师成功";
const std::string PASSWARD_ERROR = "密码错误";
const std::string ID_NO_EXIST = "Id不存在";
const std::string ILLEGAL_LOGIN = "非法登录";

const std::string OPERATE_ABNORMALLY = "运行异常";
const std::string UNKNOWN_EXCEPTION_OCCURRED = "出现未知异常";
const std::string LOAD_FILE_ERROR = "文件读取出现异常";

const std::string DATA_SIZE_FILL_MARCH_CORRECT = "数据长度符合,填充值合理,填充数据一致";
const std::string DATA_SIZE_ERROR = "数据长度不符合";
const std::string DATA_FILL_ERROR = "填充值不合理";
const std::string DATA_MARCH_ERROR = "填充数据不一致";

const std::string KEY_NO_EXIST = "密钥不存在";

const std::string RESETPASSWARD_SUCCESS = "修改密码成功";
const std::string RESETPASSWARD_FALIED = "修改密码失败";
const std::string RESETNAME_SUCCESS = "修改用户名成功";
const std::string RESETNAME_FALIED = "修改用户名失败";

const std::string ADD_STUDENT_SUCCESS = "学生添加成功";
const std::string ADD_STUDENT_FALIED = "学生添加失败";

const std::string SHOW_ALL_PERSON_SUCCESS = "显示所有信息成功";
const std::string SHOW_ALL_PERSON_FALIED = "显示所有信息失败";

const std::string STUDENT_NO_EXIST = "该学生不存在，请确认后查找";
const std::string STUDENT_EXIST = "查找学生成功";
const std::string TEACHER_NO_EXIST = "该教师不存在，请确认后查找";
const std::string TEACHER_EXIST = "查找教师成功";
const std::string FIND_FALIED = "查找失败";

const std::string CIN_ERROR = "输入错误";
const std::string TIME_STYLE_ERROR = "日期时间格式错误！";
enum {
	// 0学生  1教师  2 管理员
	STUDENTID,
	TEACHERID,
	MANAGERID
};
enum {
	//0有效  1 无效
	VALIDNUMS,
	UNVALIDNUMS
};
