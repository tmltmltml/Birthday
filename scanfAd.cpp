#include "stdafx.h"
#include <iostream>
//#include <Windows.h>                                                                   //Beep, Sleep,GetLocalTime(afx.hҲ����)
#include <fstream>
#include "allInfo.h"
using namespace std;

                                                                                       //abs��˭����������
void scanfAd(TCHAR muPath[],TCHAR copy_muPath[])
{
	ifstream mu_in(muPath);
	ofstream copy_mu(copy_muPath);
	if((!mu_in) || (!copy_mu))                                                         //�򿪳ɹ�����ֵΪ1
	{
		cout << "??? Fail to open!!!" << endl;
		return;
	}
	
	char name[N];                                   
	int month, day, rest;                                     
	int now_year, now_month, now_day;
	
	SYSTEMTIME t;                                                                      //ger current time
	GetLocalTime(&t);
	now_year = t.wYear;
	now_month = t.wMonth;
	now_day = t.wDay;

	while(!mu_in.eof())
	{
		mu_in >> name;
		                                                                               //cout << name << '1 ' << strlen(name) <<endl;??          strlen ������
		mu_in >> month >> day >> rest;		
		if( month > 12 || month < 1 || day > 31 || day < 1 || !strcmp(name, ""))       //""�õ��س�
		{
			break;
		}
		if(now_month < month || (now_month == month && now_day <= day))
		{
			rest = abs(daysGap(now_year, now_month, now_day) - daysGap(now_year, month, day));
		}
		else
		{
			rest = abs(daysGap(now_year, now_month, now_day) - daysGap(now_year + 1, month, day));
		}
		copy_mu << name << '\t' << month << '\t' << day << '\t' << rest << '\n';
		if(rest <= 7)
			cout << name << '\t' << month << '\t' << day << '\t' << rest << endl;
		if(rest <= 3)
		{
			if(!strcmp(name, "tml"))
				beepXJW();            //С����
			beepHB();                 //���տ��ָ�
			Sleep(10);
		}
	}

	mu_in.close();
	copy_mu.close();
	remove(muPath);
	rename(copy_muPath, muPath);
	return ;
}