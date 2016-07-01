#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;
#define N 20

void listAll(TCHAR muPath[])                                                   //show all birthday info
{
	ifstream mu_in(muPath);
	if(!mu_in)                                                                 //打开成功返回值为1
	{
		cout << "???Fail to open!" << endl;
	}

	char name[N];
	int month, day, rest;
	//cout << mu_in.eof() << endl;                                             //空文件为什么不认为结束
	mu_in >> name;
	if( !strcmp(name, ""))
	{
		cout << "???暂无信息" << endl;
		return;
	}
	while(!mu_in.eof())
	{
		mu_in >> month >> day >> rest; 
		if( month > 12 || month < 1 || day > 31 || day < 1 || !strcmp(name, "")) //""得到回车
		{
			break;
		}	        
		cout << name << '\t' << month << '\t' << day << '\t' << rest << endl;
		mu_in >> name;  
	}
	mu_in.close();
	return;
}