#include "stdafx.h"
#include <iostream>  
#include "allInfo.h"
//#include <afx.h>                                                            //CString
#include <fstream>   
#include <io.h>																//包含_access

using namespace std;
//判断自启，在网上参考过来的。。。
int self_start(CString mu_url)                                            //为什么不能设置为int？？？
{
	char pathDocu[MAX_PATH] = {0};
	lstrcat(pathDocu, mu_url);
	lstrcat(pathDocu, "workLog");
	char path_copy[MAX_PATH] ;
	lstrcpy(path_copy, pathDocu);
	if(_access(pathDocu, NULL) == 0)                                       //判断文件夹是否存在，不创建
		return 0;
	CreateDirectory(pathDocu, NULL);

	//首次使用.exe提示本程序功能和使用方法
	cout << "/***************************************************************/" << endl;
	cout << "/*****************本程序将记录您所提供的************************/" << endl;
	cout << "/*******************有关生日的一些信息**************************/" << endl;
	cout << "/*****************具体为:姓名，生日月，日***********************/" << endl;
	cout << "/****************我将为您提示距离今天的天数*********************/" << endl;
	cout << "/**********请尽量使用英文而非汉字，接下来，请享用!**************/" << endl;
	system("pause");
	system("cls");
	//创建生日信息
	ofstream AD;                                                  
	lstrcat(pathDocu, "\\birthday.txt");  
	AD.open(pathDocu);
	AD.close();

	char flag;
	cout << "And then I will make the exe self_start , yes or no(input: y/n)" << endl;
	cout << "This will show only once unless you delete the directory which called 'worklog'" << endl;
	cin >> flag;
	if(flag == 'n')
		return 1;
	
	char pathtofile[MAX_PATH];                     //当前文件路径
	HMODULE GetModH = GetModuleHandle(NULL);

	GetModuleFileName(NULL, pathtofile, MAX_PATH);
	cout << pathtofile << endl;
	if(CreatLinkToStartMenu(pathtofile))
	{
		cout << "Succeed to self_start" << endl;
		system("cls");
		return 1;
	}
	else
	{
		cout << "Fail to self_start" << endl;
		system("cls");
		return 0;
	}

} 

