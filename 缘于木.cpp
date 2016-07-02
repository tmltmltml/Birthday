// 缘于木.cpp : 定义控制台应用程序的入口点。
//程序功能:用户输入生日信息，并进而计算距离当天剩余的日子，支持添加，修改，删除。
#pragma once
#include "stdafx.h"
#include <iostream>
//#include <afx.h>                                                                    //有对CString,GetModuleFileName,MAX_PATH,Sleep,lstrcat的声明
#include "allInfo.h"                                                                 //内含afx.h,包含自定义函数的头文件
#include "workLogCorrect.h"

using namespace std;
void listAll(TCHAR muPath[]);                                                           //显示所有信息

int main()
{
	//程序初始化控制背景
	system("color 0C");
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle("Birthday");

	//获得程序运行路径
	TCHAR muPath[MAX_PATH], copy_muPath[MAX_PATH];                                   //TCHAR字节够大
	GetModuleFileName(NULL, muPath, MAX_PATH);
	(_tcsrchr(muPath, _T('\\')))[1] = 0;
	CString mu_url = muPath;                                                         //必须CString???

	//检查启动信息,主要是检测有无指定文件夹的创建，文件夹中的txt记录用户输入的信息
	self_start(muPath);

	//将文件路径修改为“生日信息”路径,即txt路径
	lstrcat(muPath,"workLog");                            
	lstrcat(muPath,"\\birthday.txt");         

	//创建副本
	lstrcpy(copy_muPath, muPath);
	(_tcsrchr(copy_muPath, _T('\\')))[1] = 0;
	lstrcat(copy_muPath, "\\copy_birthday.txt");

	//扫描进而修正已有的“生日信息”rest,rest指的是距离剩余的天数
	scanfAd(muPath, copy_muPath);

	//是否列出全部信息
	char choice;
	cout << "Would you want to list all infomation?(y/n)" << endl;
	cin >> choice;
	if(choice == 'y')
	{
		listAll(muPath);
	}


	//进入workLog文件夹,对信息进行修正
	workLogCorrect::workLogCorrect(muPath, copy_muPath);		

	//30s后关闭程序
	cout << "The program will close after 5s ......" << endl;               
	Sleep(5000);   
	return 0;
}

