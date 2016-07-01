#include "stdafx.h"
#include <iostream>
using namespace std;

int daysGap(int y, int m, int d)                                                        //计算距离公元元年元月一日的天数
{
	int i = 0, sum = 0;
	for(i = 1;i < y; i++)
	{
		if((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
			sum += 366;
		else
			sum += 365;
	}
	switch(m)
	{
	case 12:
		sum += 30;
	case 11:
		sum += 31;
	case 10:
		sum += 30;
	case 9:
		sum += 31;
	case 8:
		sum += 31;
	case 7:
		sum += 30;
	case 6:
		sum += 31;
	case 5:
		sum += 30;
	case 4:
		sum += 31;
	case 3:
		if((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
			sum += 29;
		else
			sum += 28;
	case 2:
		sum += 31;
	default:
		sum += 0;
	}
	sum += d - 1;
	return sum;
}