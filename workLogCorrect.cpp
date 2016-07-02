#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "allInfo.h"
using namespace std;

namespace workLogCorrect
{
	//实现该功能的思路是：创建副本
	struct del                                                                                 
	{
		char name[N];
	};

	struct correct                                                                          
	{
		char name[N];
		int month;
		int day;
		int rest;
	};

	struct CDNum                                                                        //Get
	{
		int delNum = 0;
		int corNum = 0;
	};

	//全局变量
	int now_year, now_month, now_day;
	char name[N], old_name[N];
	CDNum cdnum;                                                                     //将delNum和corNum封装到一个结构体的目标是什么？我这里写的是全局变量，哪个会更好一些？
	del delNo[N1];
	correct corNo[N1];

	//函数声明
	void getCurrentTime();
	void writeToPro(ofstream &mu_out, TCHAR muPath[]);       //不一样  
			//writeToPro内部使用
				void recAddLog(ostream &out);
				void recAdjustLog();
	void writeToCopy(istream &,  ostream &);

	void workLogCorrect(TCHAR muPath[], TCHAR copy_muPath[])
	{
		getCurrentTime();

		ofstream mu_out(muPath, ios::out | ios::app);                                      
		ofstream copy_mu(copy_muPath);
		if ((!mu_out) || (!copy_mu)) 
		{
			cout << "??? Fail to open!!!" << endl;
			return;
		}
		mu_out.close();                                                                    //和下面的recAddLog有一定关系，要删？

		writeToPro(mu_out, muPath);

		ifstream mu_in(muPath);
		writeToCopy(mu_in, copy_mu);

		mu_in.close();
		copy_mu.close();
		remove(muPath);
		rename(copy_muPath, muPath);
	}

	void getCurrentTime()
	{
		SYSTEMTIME t;                                                                                                              
		GetLocalTime(&t);
		now_year = t.wYear;
		now_month = t.wMonth;
		now_day = t.wDay;
	}

	void writeToPro(ofstream &mu_out, TCHAR muPath[] )
	{
		int &delNum = cdnum.delNum;
		int &corNum = cdnum.corNum;
		cout << "Will you want to add(1)/correct(2)/delete(3) info or no(0):" << endl;       

		int num = 0;
		cin >> num;
		while (num) 
		{
			if (num == 1)
			{
				mu_out.open(muPath, ios::out | ios::app);                   //打开文件    要删吗？
				recAddLog(mu_out);
				mu_out.close();                                                           //保证将信息保存并且关闭了文件流  要删吗？
			}
			else if (num == 2)
			{
				recAdjustLog();
				corNum++;
			}
			else
			{
				cout << "input the name(no space)" << endl;
				cin >> delNo[delNum].name;
			}
			cout << "continue?...(input num)" << endl;
			cin >> num;
		}
	}

	void recAddLog(ostream &mu_out)
	{
		int month, day, rest;
		cout << "Name(no space)    Month   Day (once a man/woman一次一人):" << endl;
		cin >> name >> month >> day;
		rest = daysGap(now_year, now_month, now_day);
		if (now_month < month || (now_month == month && now_day <= day))
		{
			rest -= daysGap(now_year, month, day);
		}
		else
		{
			rest -= daysGap(now_year + 1, month, day);
		}
		mu_out << name << "    " << month << "    " << day << "    " << rest << '\n';
	}

	void recAdjustLog()
	{
		int &month = corNo[cdnum.corNum].month;
		int &day = corNo[cdnum.corNum].day;
		int &rest = corNo[cdnum.corNum].rest;

		cout << "input the name,correct name(no space) , correct month and correct day:" << endl;
		cin >> old_name;
		cin >> corNo[cdnum.corNum].name;
		cin >> month >> day;
		if (now_month < month || (now_month == month && now_day <= day))
		{
			rest = abs(daysGap(now_year, now_month, now_day) - daysGap(now_year, month, day));
		}
		else
		{
			rest = abs(daysGap(now_year, now_month, now_day) - daysGap(now_year + 1, month, day));
		}
		cout << rest << endl;
	}

	void writeToCopy(istream &mu_in, ostream &copy_mu)
	{
		int delNum = cdnum.delNum;
		int corNum = cdnum.corNum;
		int month, day, rest;
		while (!mu_in.eof())                              //将程序中保存的信息结合原txt输入到副本txt中
		{
			int i = 0;
			mu_in >> name;
			mu_in >> month >> day >> rest;
			if (month > 12 || month < 1 || day > 31 || day < 1 || !strcmp(name, "")) //""得到回车
			{
				break;
			}
			for (i = 0; i < cdnum.delNum; i++)
			{
				if (!strcmp(name, delNo[i].name))
					break;
			}
			if (i < delNum)
				continue;

			for (i = 0; i < corNum; i++)
			{
				if (!strcmp(name, old_name))
				{
					copy_mu << corNo[i].name << "    " << corNo[i].month << "    " << corNo[i].day << "    " << corNo[i].rest << '\n';
					break;
				}
			}
			if (i < corNum)
				continue;
			copy_mu << name << "    " << month << "    " << day << "    " << rest << '\n';
		}
	}

}