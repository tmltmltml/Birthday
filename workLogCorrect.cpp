#include "stdafx.h"
#include <iostream>
//#include <afx.h>
#include <fstream>
#include "allInfo.h"

using namespace std;
//实现该功能的思路是：创建副本
struct del                                          //删除信息的时候，通过指定名字来区分
{
	char name[N];
};

struct correct                                       //保存要修正的正确信息
{
	char name[N];
	int month;
	int day;
	int rest;
};

void workLogCorrect(TCHAR muPath[], TCHAR copy_muPath[])
{
	int now_year, now_month, now_day;                                                  
	SYSTEMTIME t;                                                                      //获得当前日期信息                                        
	GetLocalTime(&t);
	now_year = t.wYear;
	now_month = t.wMonth;
	now_day = t.wDay;

	ofstream mu_out(muPath, ios::out | ios::app);                                       //打开生日信息文件流以及其副本
	ofstream copy_mu(copy_muPath);
	if((!mu_out) || (!copy_mu))                                                         //打开成功返回值为1
	{
		cout << "??? Fail to open!!!" << endl;
		return;
	}
	mu_out.close();

	del delNo[N1]; correct corNo[N1];
	int delNum = 0, corNum = 0;
	char name[N], old_name[N];
	int month, day, rest;
	cout << "Will you want to add(1)/correct(2)/delete(3) info or no(0):" << endl;        //界面优化,让用户进行选择
	int num = 0;
	cin >> num;
	while(num) //先将需要的修正，增加，删除的信息保存到程序里
	{
		if(num == 1)
		{
			cout << "Name(no space)    Month   Day (once a man/woman一次一人):" << endl;
			cin >> name >> month >> day;
			if(now_month < month || (now_month == month && now_day <= day))
			{
				rest = abs(daysGap(now_year, now_month, now_day) - daysGap(now_year, month, day));
			}
			else
			{
				rest = abs(daysGap(now_year, now_month, now_day) - daysGap(now_year + 1, month, day));
			}
			mu_out.open(muPath, ios::out | ios::app);
			mu_out << name << "    " << month << "    " << day << "    " << rest <<'\n';
			mu_out.close();
		}
		else if(num == 2)
		{
			cout << "input the name,correct name(no space) , correct month and correct day:" << endl;
			cin >> old_name;
			cin >> corNo[corNum].name;
			cin >> corNo[corNum].month >> corNo[corNum].day;
			if(now_month < corNo[corNum].month || (now_month == corNo[corNum].month && now_day <= corNo[corNum].day))
			{
				cout << (corNo[corNum].rest = abs(daysGap(now_year, now_month, now_day) - daysGap(now_year, corNo[corNum].month, corNo[corNum].day))) << endl;
			}
			else
			{
				cout << (corNo[corNum].rest = abs(daysGap(now_year, now_month, now_day) - daysGap(now_year + 1, corNo[corNum].month, corNo[corNum].day))) << endl;
			}
			corNum++;
		}
		else
		{
			cout << "input the name(no space)" << endl;
			cin >> delNo[delNum++].name;
		}
		cout << "continue?...(input num)" << endl;
		cin >> num;
	}

	ifstream mu_in(muPath);
	while(!mu_in.eof())                              //将程序中保存的信息结合原txt输入到副本txt中
	{
		int i = 0;
		mu_in>>name;
		mu_in >> month >> day >> rest ;
		if( month > 12 || month < 1 || day > 31 || day < 1 || !strcmp(name, "")) //""得到回车
		{
			break;
		}
		for(i = 0; i < delNum; i++)
		{
			if(!strcmp(name, delNo[i].name))
				break;
		}
		if(i < delNum)
			continue;

		for(i = 0; i < corNum; i++)
		{
			if(!strcmp(name, old_name))
			{
				copy_mu << corNo[i].name << "    " << corNo[i].month << "    " << corNo[i].day << "    " << corNo[i].rest << '\n';
				break;
			}
		}
		if(i < corNum)
			continue;
		copy_mu << name << "    " << month << "    " << day << "    " << rest <<'\n';
	}
	
	mu_in.close();
	copy_mu.close();
	remove(muPath);
	rename(copy_muPath, muPath);
	return;
}