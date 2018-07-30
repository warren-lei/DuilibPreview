#include "MainWnd.h"
#include "PreviewWnd.h"
#include "StringTools.h"
#include "PreviewXml.h"

#include <iostream>

CMainWnd::CMainWnd()
{
}

CMainWnd::~CMainWnd()
{
}

void CMainWnd::InitWindow()
{
	m_closeBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("close_btn")));
	m_maxBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("max_btn")));
	m_restoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("restore_btn")));
	m_minBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("min_btn")));
	m_previewBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("preview_btn")));
	m_xmlPathEdit = static_cast<CRichEditUI*>(m_pm.FindControl(_T("xml_path_edit")));
}

void CMainWnd::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_closeBtn)
		{
			PostQuitMessage(0L);
		}
		else if (msg.pSender == m_minBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			return;
		}
		else if (msg.pSender == m_maxBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			m_maxBtn->SetVisible(false);
			m_restoreBtn->SetVisible(true);
			return;
		}
		else if (msg.pSender == m_restoreBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_maxBtn->SetVisible(true);
			m_restoreBtn->SetVisible(false);
			return;
		}
		else if (msg.pSender == m_previewBtn)
		{
			previewXmlLayout();
		}
	}
}

LRESULT CMainWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	PostQuitMessage(0L);
	return 0;
}

LRESULT CMainWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT lRes = 0;
	BOOL hHandled = TRUE;

	switch (uMsg)
	{
	case WM_DESTROY:
		lRes = OnDestroy(uMsg, wParam, lParam, hHandled);
		break;
	default:
		break;
	}
	
	if (bHandled) return lRes;
	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LPCTSTR CMainWnd::GetWindowClassName() const
{
	return _T("Duilib Preview");
}

CDuiString CMainWnd::GetSkinFile()
{
	return _T("MainDlg.xml");
}

LPCTSTR CMainWnd::getXmlPath() const
{
	if (m_xmlPathEdit->GetTextLength() == 0)
		return _T("");
	else
		return m_xmlPathEdit->GetText();
}

void CMainWnd::tcharToChar(const TCHAR* sourTchar, char* destChar)
{
	int iLength;
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, sourTchar, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char    
	WideCharToMultiByte(CP_ACP, 0, sourTchar, -1, destChar, iLength, NULL, NULL);
}

void CMainWnd::previewXmlLayout(/*LPSTR lpCmdLine*/)
{
	char cXmlPathStr[1024] = "";
	tcharToChar(m_xmlPathEdit->GetText(), cXmlPathStr);

#ifdef UNICODE
	CDuiString* filepath = new CDuiString(m_xmlPathEdit->GetText());
#else
	CDuiString* filepath = new CDuiString(cXmlPathStr);
#endif

	//CDuiString* filepath = new CDuiString(_W(lpCmdLine));
	std::wcout << "filepath: " << filepath->GetData() << std::endl;

	if (filepath->IsEmpty())
	{
		MessageBox(NULL, _T("温馨提示：请输入正确的xml文件的路径（包含xml文件本身）！"), _T("加载xml文件失败"), MB_OK);
		return;
	}

	int n = filepath->ReverseFind('\\') + 1;
	if (filepath->Right(4) != _T(".xml"))
	{
		MessageBox(NULL, _T("文件扩展名不是xml格式"), _T("扩展名错误"), MB_OK);
		return;
	}
		

	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr))
	{
		MessageBox(NULL, _T("温馨提示：初始化失败！"), _T("初始化错误"), MB_OK);
		return;
	}

	//CPreviewWnd* pPreviewForm = new CPreviewWnd();
	//if (pPreviewForm == NULL) return ;
	//pPreviewForm->SetSkinFile(filepath->Right(filepath->GetLength() - n).GetData());
	//pPreviewForm->SetSkinFolder(filepath->Left(n).GetData());
	//pPreviewForm->Create(NULL, _T("预览窗口"), UI_WNDSTYLE_EX_FRAME, WS_EX_WINDOWEDGE);
	//pPreviewForm->CenterWindow();
	//pPreviewForm->ShowWindow(true);

	//CPaintManagerUI::MessageLoop();
	//CPaintManagerUI::MessageLoopChild();
    //::CoUninitialize();
	
	CPreviewXml *pSettingDlg2 = new CPreviewXml(filepath->Right(filepath->GetLength() - n).GetData());
	pSettingDlg2->SetSkinFolder(filepath->Left(n).GetData());
	pSettingDlg2->Create(m_hWnd, _T(""), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	pSettingDlg2->CenterWindow();
	pSettingDlg2->ShowWindow(SW_NORMAL);
}
