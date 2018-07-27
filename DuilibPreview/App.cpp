#include "stdafx.h"
#include "App.h"
#include "PreviewWnd.h"
#include "StringTools.h"

#include <iostream>

//控制台
//#pragma comment(linker, "/subsystem:console /entry:WinMainCRTStartup")

//程序入口及Duilib初始化部分 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR lpCmdLine, int nCmdShow)
{ 
	ShowMainWnd(hInstance);
	
	//CMainWnd mainPtr;
	//mainPtr.previewXmlLayout(lpCmdLine);
    
	return 0; 
} 