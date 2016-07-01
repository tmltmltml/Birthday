#include "stdafx.h"
#include <iostream>
#include  "shlobj.h"
#include "atlconv.h"
using namespace std;
bool CreatLinkToStartMenu(char * pszPeFileName)
{
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		IShellLink *pisl;
		hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pisl);
		if (SUCCEEDED(hr))
		{
			IPersistFile* pIPF;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//这里是我们要创建快捷方式的原始文件地址
			pisl->SetPath(pszPeFileName);
			hr = pisl->QueryInterface(IID_IPersistFile, (void**)&pIPF);
			if (SUCCEEDED(hr))
			{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//这里是我们要创建快捷方式的目标地址
				char szStartPath[MAX_PATH] = {0};
				SHGetSpecialFolderPath(NULL,szStartPath, CSIDL_STARTUP, 0);
				lstrcat(szStartPath,"\\mumu.lnk");

				USES_CONVERSION;
				LPCOLESTR lpOleStr = A2COLE(szStartPath);
				pIPF->Save(lpOleStr, FALSE);
				pIPF->Release();
			}
			else
				return false;
			pisl->Release();
		}
		else
			return false;
		CoUninitialize();
		return true;
	}
	return false;
}