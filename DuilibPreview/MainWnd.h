#pragma once
#include "stdafx.h"

class CMainWnd : public WindowImplBase
{
public:
	CMainWnd();
	~CMainWnd();

	void Notify(TNotifyUI& msg);
	void InitWindow();

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LPCTSTR GetWindowClassName() const;
	CDuiString GetSkinFile();

	LPCTSTR getXmlPath() const;
	void previewXmlLayout(/*LPSTR lpCmdLine*/);
	void tcharToChar(const TCHAR* sourTchar, char* destChar);

private:
	CButtonUI* m_closeBtn;
	CButtonUI* m_minBtn;
	CButtonUI* m_maxBtn;
	CButtonUI* m_restoreBtn;
	CButtonUI* m_previewBtn;
	CRichEditUI* m_xmlPathEdit;
};
