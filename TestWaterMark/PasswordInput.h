#pragma once
#include "afxwin.h"
#include "ImageDigitalMarkingDlg.h"


// PasswordInput dialog

class PasswordInput : public CDialogEx
{
	DECLARE_DYNAMIC(PasswordInput)

public:
	PasswordInput(CWnd* pParent = NULL);   // standard constructor
	virtual ~PasswordInput();

// Dialog Data
	enum { IDD = IDD_DIALOGPasswordInput };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CEdit passwordInputText;
	CImageDigitalMarkingDlg* pDialog;
public:
	afx_msg void OnBnClickedOk();
	void setMainDialog(CImageDigitalMarkingDlg*);
};
