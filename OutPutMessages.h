#pragma once
#include <iostream>
#include <vector>
#include "ComputerRoom.h"

//菜单类
///一级菜单显示
void printMainMenu();
void printExitMainMenu();
///管理员菜单显示
void printManagerSecondMenu();
void printManagerThirst1Menu();
void printManagerThirst2Menu();
void printManagerThirst3Menu();
///教师菜单显示
void printTeacherSecondMenu();
void printTeacherThirst1Menu();
void printTeacherThirst2Menu();
///学生菜单显示
void printStudentSecondMenu();
void printStudentThirst1Mneu();
void printStudentThirst2Menu();
void printRegisterMenu();
//异常类
void printInputError();
void printFileNotFound();

//登录类
void printInputStudentId();
void printInputTeacherId();
void printInputManagerId();
void printInputPassword();
void printPasswardError();
void printIdError();
void printLoginStudentSuccess();
void printLoginTeacherSuccess();
void printLoginManagerSuccess();
void printLoginStudentFailed();
void printLoginTeacherFailed();
void printLoginManagerFailed();
void printIllegalLogin();
void printRegisterSuccess();
void printRegisterFailed();
void printRegisterError();

//功能类
void LOG();
void TMP();
void CLEAR();

//提示类
///二级菜单功能
///管理员二级菜单功能

void printAddAccount();
void printStudentIdDuplicate();
void printTeacherIdDuplicate();
void printAddSuccess();
void printRemovePerson();
void printFindPerson();
void printInputName();
void printViewAccount();
void printAllTeacherInfo();
void printAllStudentInfo();
void printCurrentStudentNumber(int studentnums);
void printCurrentTeacherNumber(int teachernums);

void printViewComputerRoom();
void printAllComputerInfo();
void printCurrentComputerNumber(int computernums);

void printClearReservation();
void printAllClearSucces();
void printResetName();
void printResetPassward();
void printResetPasswardSuccess();
void printResetPasswardFalied();
void printResetNameSuccess();
void printResetNameFalied();
///教师二级菜单功能
void printViewAllOrder();

void printValidOrder();
void printMemoryOrder1();
void printMemoryOrder2();
void printMemoryOrder3();
void printMemoryOrder4();

///学生二级菜单功能
void printApplyOrder1();
void printApplyOrder2();
void printApplyOrder3(std::vector<ComputerRoom>& vCom);
void printApplySuccess();

void printMyOrderError();

void printAllOrderError();

void printDeleteOrder1();
void printDeleteOrder2();
//共用类
void printLogoutSuccess();
