//≤È’“”⁄Õ¯…œhttp://www.docin.com/p-494724719.html
#include "stdafx.h"
#include <iostream>
#include <Windows.h>                                                              //Beep
using namespace std;
/*
	MessageBeep(MB_ICONASTERISK);
	MessageBeep(MB_ICONEXCLAMATION);
	MessageBeep(MB_ICONHAND);
	MessageBeep(MB_ICONQUESTION);
	MessageBeep(MB_OK);
	*/

void beepHB()                                                                    //Happy Birthday
{
	unsigned FREQUENCY[] = {392, 392, 440, 392, 523, 494,
		392, 392, 440, 392, 587, 523,
		392, 392, 784, 659, 523, 494, 440,
		689, 689, 523, 587, 523};
	unsigned DELAY[] = {375, 125, 500, 500, 500, 1000,
		372, 125, 500, 500, 500, 1000,
		372, 125, 500, 500, 500, 500, 1000,
		372, 125, 500, 500, 500, 1000,
	};

	int i = 0;
	for(; i < 25; i++)
	{
		Beep(FREQUENCY[i], DELAY[i]);
	}
}
