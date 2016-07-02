#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "allInfo.h"
#include "workLogCorrect.h"

using namespace std;

namespace workLogCorrect
{
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
	
	struct CDNum
	{
		int delNum = 0;
		int corNum = 0;
	};
	
	// 全局变量
	int now_year, now_month, now_day;
	char name[N], old_name[N];
	del delNo[N1];
	correct corNo[N1];
	
	// 函数声明
	void getCurrTime();
	void recAddenLog(ostream &out);
	void recAdjustLog();
	void funcAddInfo(CDNum &cdNum, ofstream &mu_out);
	void funcCorrectInfo(CDNum &cdNum, ofstream &copy_mu, ifstream &mu_in);
	
	void workLogCorrect(TCHAR muPath[], TCHAR copy_muPath[])
	{
		getCurrTime(); // 获得当前日期信息
		
		ofstream mu_out(muPath, ios::out | ios::app); //打开生日信息文件流以及其副本
		ofstream copy_mu(copy_muPath);
		ifstream mu_in(muPath);
		
		if ((!mu_out) || (!copy_mu)) /*打开成功返回值为1*/ {
			cout << "??? Fail to open!!!" << endl;
			return;
		}
		
		CDNum cdNum;
		
		funcAddInfo(cdNum, mu_out);
		funcCorrectInfo(cdNum, copy_mu, mu_in);
		
		mu_out.close();
		mu_in.close();
		copy_mu.close();
		remove(muPath);
		rename(copy_muPath, muPath);
	}
	
	void getCurrTime()
	{
		SYSTEMTIME t;                                  
		GetLocalTime(&t);
		now_year = t.wYear;
		now_month = t.wMonth;
		now_day = t.wDay;
	}

	void recAddenLog(ostream &out)
	{
		int month, day, rest;
		cout << "Name(no space)    Month   Day (once a man/woman一次一人):" << endl;
		cin >> name >> month >> day;
		
		rest = abs(daysGap(now_year, now_month, now_day);
		
		if (now_month < month || (now_month == month && now_day <= day)) {
			rest -= daysGap(now_year, month, day));
		}
		else {
			rest -= daysGap(now_year + 1, month, day));
		}
		
		out << name << "    " << month << "    " << day << "    " << rest <<'\n';
	}
	void recAdjustLog()
	{
		int &month = corNo[corNum].month;
		int &day = corNo[corNum].day;
		int &rest = corNo[corNum].rest;
		
		cout << "input the name,correct name(no space) , correct month and correct day:" << endl;
		cin >> old_name;
		cin >> corNo[corNum].name;
		cin >> month >> day;
		
		rest = abs(daysGap(now_year, now_month, now_day);
		
		if (now_month < month || (now_month == month && now_day <= day)) {
			rest -= daysGap(now_year, month, day));
		}
		else {
			rest -= daysGap(now_year + 1, month, day));
		}
		
		cout << rest << endl;
	}

	void funcAddInfo(CDNum &cdNum, ofstream &mu_out)
	{
		int &delNum = cdNum.delNum;
		int &corNum = cdNum.corNum;
		cout << "Will you want to add(1)/correct(2)/delete(3) info or no(0):" << endl;        //界面优化,让用户进行选择
		int num = 0;
		cin >> num;
		while (num) //先将需要的修正，增加，删除的信息保存到程序里
		{
			if (num == 1) {
				recAddenLog(mu_out);
			}
			else if (num == 2) {
				recAdjustLog();
				corNum++;
			}
			else {
				cout << "input the name(no space)" << endl;
				cin >> delNo[delNum++].name;
			}
			cout << "continue?...(input num)" << endl;
			cin >> num;
		}
	}
	void funcCorrectInfo(CDNum &cdNum, ofstream &copy_mu, ifstream &mu_in)
	{
		int &delNum = cdNum.delNum;
		int &corNum = cdNum.corNum;
		while (!mu_in.eof())                              //将程序中保存的信息结合原txt输入到副本txt中
		{
			int i = 0;
			int month, day, rest;
			mu_in>>name;
			mu_in >> month >> day >> rest ;
			if( month > 12 || month < 1 || day > 31 || day < 1 || !strcmp(name, "")) /*""得到回车*/ {
				break;
			}
			for (i = 0; i < delNum; i++) {
				if (!strcmp(name, delNo[i].name))
					break;
			}
			if (i < delNum) {
				continue;
			}

			for (i = 0; i < corNum; i++) {
				if (!strcmp(name, old_name)) {
					copy_mu << corNo[i].name << "    " << corNo[i].month << "    " << corNo[i].day << "    " << corNo[i].rest << '\n';
					break;
				}
			}
			if (i < corNum)
				continue;
			copy_mu << name << "    " << month << "    " << day << "    " << rest <<'\n';
		}
	}
}
