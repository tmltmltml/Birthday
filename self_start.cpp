#include "stdafx.h"
#include <iostream>  
#include "allInfo.h"
//#include <afx.h>                                                            //CString
#include <fstream>   
#include <io.h>																//����_access

using namespace std;
//�ж������������ϲο������ġ�����
int self_start(CString mu_url)                                            //Ϊʲô��������Ϊint������
{
	char pathDocu[MAX_PATH] = {0};
	lstrcat(pathDocu, mu_url);
	lstrcat(pathDocu, "workLog");
	char path_copy[MAX_PATH] ;
	lstrcpy(path_copy, pathDocu);
	if(_access(pathDocu, NULL) == 0)                                       //�ж��ļ����Ƿ���ڣ�������
		return 0;
	CreateDirectory(pathDocu, NULL);

	//�״�ʹ��.exe��ʾ�������ܺ�ʹ�÷���
	cout << "/***************************************************************/" << endl;
	cout << "/*****************�����򽫼�¼�����ṩ��************************/" << endl;
	cout << "/*******************�й����յ�һЩ��Ϣ**************************/" << endl;
	cout << "/*****************����Ϊ:�����������£���***********************/" << endl;
	cout << "/****************�ҽ�Ϊ����ʾ������������*********************/" << endl;
	cout << "/**********�뾡��ʹ��Ӣ�Ķ��Ǻ��֣���������������!**************/" << endl;
	system("pause");
	system("cls");
	//����������Ϣ
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
	
	char pathtofile[MAX_PATH];                     //��ǰ�ļ�·��
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

