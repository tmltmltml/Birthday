// Ե��ľ.cpp : �������̨Ӧ�ó������ڵ㡣
//������:�û�����������Ϣ��������������뵱��ʣ������ӣ�֧����ӣ��޸ģ�ɾ����
#pragma once
#include "stdafx.h"
#include <iostream>
//#include <afx.h>                                                                    //�ж�CString,GetModuleFileName,MAX_PATH,Sleep,lstrcat������
#include "allInfo.h"                                                                 //�ں�afx.h,�����Զ��庯����ͷ�ļ�
using namespace std;
void listAll(TCHAR muPath[]);                                                           //��ʾ������Ϣ

int main()
{
	//�����ʼ�����Ʊ���
	system("color 0C");
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle("Birthday");

	//��ó�������·��
	TCHAR muPath[MAX_PATH], copy_muPath[MAX_PATH];                                   //TCHAR�ֽڹ���
	GetModuleFileName(NULL, muPath, MAX_PATH);
	(_tcsrchr(muPath, _T('\\')))[1] = 0;
	CString mu_url = muPath;                                                         //����CString???

	//���������Ϣ,��Ҫ�Ǽ������ָ���ļ��еĴ������ļ����е�txt��¼�û��������Ϣ
	self_start(muPath);

	//���ļ�·���޸�Ϊ��������Ϣ��·��,��txt·��
	lstrcat(muPath,"workLog");                            
	lstrcat(muPath,"\\birthday.txt");         

	//��������
	lstrcpy(copy_muPath, muPath);
	(_tcsrchr(copy_muPath, _T('\\')))[1] = 0;
	lstrcat(copy_muPath, "\\copy_birthday.txt");

	//ɨ������������еġ�������Ϣ��rest,restָ���Ǿ���ʣ�������
	scanfAd(muPath, copy_muPath);

	//�Ƿ��г�ȫ����Ϣ
	char choice;
	cout << "Would you want to list all infomation?(y/n)" << endl;
	cin >> choice;
	if(choice == 'y')
	{
		listAll(muPath);
	}


	//����workLog�ļ���,����Ϣ��������
	workLogCorrect(muPath, copy_muPath);		

	//30s��رճ���
	cout << "The program will close after 5s ......" << endl;               
	Sleep(5000);   
	return 0;
}

