#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "allInfo.h"
using namespace std;

namespace workLogCorrect
{
	//ʵ�ָù��ܵ�˼·�ǣ���������
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

	//ȫ�ֱ���
	int now_year, now_month, now_day;
	char name[N], old_name[N];
	CDNum cdnum;                                                                     //��delNum��corNum��װ��һ���ṹ���Ŀ����ʲô��������д����ȫ�ֱ������ĸ������һЩ��
	del delNo[N1];
	correct corNo[N1];

	//��������
	void getCurrentTime();
	void writeToPro(ofstream &mu_out, TCHAR muPath[]);       //��һ��  
			//writeToPro�ڲ�ʹ��
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
		mu_out.close();                                                                    //�������recAddLog��һ����ϵ��Ҫɾ��

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
				mu_out.open(muPath, ios::out | ios::app);                   //���ļ�    Ҫɾ��
				recAddLog(mu_out);
				mu_out.close();                                                           //��֤����Ϣ���沢�ҹر����ļ���  Ҫɾ��
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
		cout << "Name(no space)    Month   Day (once a man/womanһ��һ��):" << endl;
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
		while (!mu_in.eof())                              //�������б������Ϣ���ԭtxt���뵽����txt��
		{
			int i = 0;
			mu_in >> name;
			mu_in >> month >> day >> rest;
			if (month > 12 || month < 1 || day > 31 || day < 1 || !strcmp(name, "")) //""�õ��س�
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