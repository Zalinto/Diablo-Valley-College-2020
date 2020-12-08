// finalProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "finalProject.h"
#include "finalProjectDlg.h"
#include "afxdialogex.h"

#include <sstream>
#include <vector>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "pFinalProject.h"
vector<Bank> accounts;


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CfinalProjectDlg dialog



CfinalProjectDlg::CfinalProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FINALPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfinalProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CfinalProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CfinalProjectDlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, &CfinalProjectDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CfinalProjectDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT4, &CfinalProjectDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT3, &CfinalProjectDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON2, &CfinalProjectDlg::OnBnClickedButton2)
END_MESSAGE_MAP()



BOOL CfinalProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			

	/******************************COMBO BOX TEXT MENU******************************/
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);

	pCombo->InsertString(0, _T("Open an Account"));
	pCombo->InsertString(1, _T("Withdraw"));
	pCombo->InsertString(2, _T("Deposit"));
	pCombo->InsertString(3, _T("Transfer"));
	pCombo->InsertString(4, _T("Show Account"));
	pCombo->InsertString(5, _T("Show All Accounts"));

	pCombo->SetCurSel(0);														// Drop down menu starts with "Open an Account"
	 
	CEdit* userInput = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT1));			// User input text box
	userInput->SetWindowText(CString(_T("")));									// Set default text

	CStatic* pPicture = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC6));	// home picture
	pPicture->ModifyStyle(0xF, SS_BITMAP, SWP_NOSIZE);
	HBITMAP hb = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	pPicture->SetBitmap(hb);

	return TRUE;  
}

void CfinalProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CfinalProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CfinalProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CfinalProjectDlg::OnCbnSelchangeCombo1()
{
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int n = pCombo->GetCurSel();

	CEdit* userInput1 = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT1));				// User input text box
	CEdit* userInput2 = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT3));				// User transfer account box
	CEdit* userInput3 = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT4));				// Amount of desired money to transfer
	
	CEdit* results = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT2));

	ostringstream sout;

	switch (n)
	{
		case 0:																				// Open an Account
		{
			userInput2->ShowWindow(SW_SHOW);
			userInput3->ShowWindow(SW_SHOW);

			CStatic* pPicture = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC6));		// picture
			pPicture->ModifyStyle(0xF, SS_BITMAP, SWP_NOSIZE);
			HBITMAP hb = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
				MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
			pPicture->SetBitmap(hb);

			// change account number
			CStatic* textBox1 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC3));
			textBox1->SetWindowText(CString("Enter your account number:"));
			// change name
			CStatic* textBox2 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC4));
			textBox2->SetWindowText(CString("Enter your name:"));
			// change balance 
			CStatic* textBox3 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC5));
			textBox3->SetWindowText(CString("Enter your balance:"));

			results->SetWindowText(CString(""));											// reset text each iteration

			break;
		}

		case 1:																				// Withdraw
		{
			userInput2->ShowWindow(SW_SHOW);
			userInput3->ShowWindow(SW_HIDE);

			CStatic* pPicture = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC6));		// picture
			pPicture->ModifyStyle(0xF, SS_BITMAP, SWP_NOSIZE);
			HBITMAP hb = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
				MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
			pPicture->SetBitmap(hb);

			// change account number
			CStatic* textBox1 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC3));
			textBox1->SetWindowText(CString("Enter your account number:"));
			// change balance
			CStatic* textBox2 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC4));
			textBox2->SetWindowText(CString("Enter your balance:"));
			// disappear 
			CStatic* textBox3 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC5));
			textBox3->SetWindowText(CString(""));

			results->SetWindowText(CString(""));											// reset text each iteration

			break;
		}

		case 2:																				// Deposit
		{
			userInput2->ShowWindow(SW_SHOW);
			userInput3->ShowWindow(SW_HIDE);

			CStatic* pPicture = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC6));		// picture
			pPicture->ModifyStyle(0xF, SS_BITMAP, SWP_NOSIZE);
			HBITMAP hb = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
				MAKEINTRESOURCE(IDB_BITMAP3), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
			pPicture->SetBitmap(hb);

			// change account number
			CStatic* textBox1 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC3));
			textBox1->SetWindowText(CString("Enter your account number:"));
			// change balance
			CStatic* textBox2 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC4));
			textBox2->SetWindowText(CString("Enter your balance:"));
			// disappear 
			CStatic* textBox3 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC5));
			textBox3->SetWindowText(CString(""));

			results->SetWindowText(CString(""));											// reset text each iteration

			break;
		}

		case 3:																				// Transfer 
		{
			userInput2->ShowWindow(SW_SHOW);
			userInput3->ShowWindow(SW_SHOW);

			CStatic* pPicture = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC6));		// picture
			pPicture->ModifyStyle(0xF, SS_BITMAP, SWP_NOSIZE);
			HBITMAP hb = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
				MAKEINTRESOURCE(IDB_BITMAP4), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
			pPicture->SetBitmap(hb);

			// change acc1
			CStatic* textBox1 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC3));
			textBox1->SetWindowText(CString("Enter your account number:"));
			// change acc2
			CStatic* textBox2 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC4));
			textBox2->SetWindowText(CString("Enter the other you are transferring to:"));
			// change balance 
			CStatic* textBox3 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC5));
			textBox3->SetWindowText(CString("Enter the balance you wish to transfer:"));

			results->SetWindowText(CString(""));											// reset text each iteration

			break;
		}

		case 4:																				// Show Account
		{
			userInput2->ShowWindow(SW_HIDE);
			userInput3->ShowWindow(SW_HIDE);

			CStatic* pPicture = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC6));		// picture
			pPicture->ModifyStyle(0xF, SS_BITMAP, SWP_NOSIZE);
			HBITMAP hb = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
				MAKEINTRESOURCE(IDB_BITMAP5), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
			pPicture->SetBitmap(hb);

			// change account number
			CStatic* textBox1 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC3));
			textBox1->SetWindowText(CString("Enter your account number:"));
			// disappear
			CStatic* textBox2 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC4));
			textBox2->SetWindowText(CString(""));
			// disappear 
			CStatic* textBox3 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC5));
			textBox3->SetWindowText(CString(""));

			results->SetWindowText(CString(""));											// reset text each iteration

			break;
		}

		case 5:																				// TEST FUNCTION
		{
			// password
			CStatic* textBox1 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC3));
			textBox1->SetWindowText(CString("Enter the password (ADMIN):"));
			// disappear
			CStatic* textBox2 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC4));
			textBox2->SetWindowText(CString(""));
			// disappear 
			CStatic* textBox3 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC5));
			textBox3->SetWindowText(CString(""));

			userInput2->ShowWindow(SW_HIDE);
			userInput3->ShowWindow(SW_HIDE);
		}
	}
}


void CfinalProjectDlg::OnEnChangeEdit1()
{

}


void CfinalProjectDlg::OnBnClickedButton1()
{
	vector<string> tokens;
	const string password = "123";

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int n = pCombo->GetCurSel();

	CEdit* userInput1 = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT1));				// User input text box
	CEdit* userInput2 = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT3));				// User transfer account box
	CEdit* userInput3 = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT4));				// Amount of desired money to transfer


	CEdit* results = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT2));

	CEdit* testResults = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT5));

	ostringstream sout;

	switch (n)
	{
		case 0:																				// Open an Account
		{
			CString mEdit0;
			tokens.push_back("Open");

			userInput1->GetWindowText(mEdit0);
			string temp((CT2CA)mEdit0);														// I got CT2CA from StackedOverflow when converting CString to string
			tokens.push_back(temp);

			userInput2->GetWindowText(mEdit0);
			string temp1((CT2CA)mEdit0);
			tokens.push_back(temp1);

			userInput3->GetWindowText(mEdit0);
			string temp2((CT2CA)mEdit0);
			tokens.push_back(temp2);

			Bank account(tokens);
			account.showAccount(sout);
			results->SetWindowText(CString(sout.str().c_str()));

			accounts.push_back(account);													// store the account in a global vector 
			break;
		}

		case 1:																				// Withdraw
		{
			CString mEdit1;

			userInput1->GetWindowText(mEdit1);												// user enters account number
			string temp((CT2CA)mEdit1);

			userInput2->GetWindowText(mEdit1);												// user enter amount they want to withdraw
			string temp1((CT2CA)mEdit1);

			
			for (int i = 0; i < accounts.size(); i++)
			{
				if (accounts[i].accountNumber == temp)
				{
					accounts[i].withdraw(_wtof(mEdit1));
					accounts[i].showAccount(sout);
					results->SetWindowText(CString(sout.str().c_str()));
					break;
				}
				if(i == accounts.size() && accounts[i].accountNumber != temp)
				{
					results->SetWindowText(CString("No accounts found."));
					break;
				}
			}
			if (accounts.size() == 0)
			{
				results->SetWindowText(CString("No accounts found.\r\n(This is a handler showing that there were no accounts made)"));
			}
			break;
		}

		case 2:																				// Deposit
		{
			CString mEdit2;

			userInput1->GetWindowText(mEdit2);												// user enters account number
			string temp((CT2CA)mEdit2);

			userInput2->GetWindowText(mEdit2);												// user enter amount they want to withdraw
			string temp1((CT2CA)mEdit2);


			for (int i = 0; i < accounts.size(); i++)
			{
				if (accounts[i].accountNumber == temp)
				{
					accounts[i].deposit(_wtof(mEdit2));
					accounts[i].showAccount(sout);
					results->SetWindowText(CString(sout.str().c_str()));
					break;
				}
				if (i == accounts.size() && accounts[i].accountNumber != temp)
				{
					results->SetWindowText(CString("No accounts found."));
					break;
				}

			}
			if (accounts.size() == 0)
			{
				results->SetWindowText(CString("No accounts found.\r\n(This is a handler showing that there were no accounts made)"));
			}
			break;
		}

		case 3:																				// Transfer 
		{
			CString mEdit3;

			userInput1->GetWindowText(mEdit3);												// user enters account number
			string temp((CT2CA)mEdit3);

			userInput2->GetWindowText(mEdit3);												// user enters the account they desire
			string temp1((CT2CA)mEdit3);

			userInput3->GetWindowText(mEdit3);												// user enters the account they desire
			string temp2((CT2CA)mEdit3);

			bool account1 = false;
			int a1;
			bool account2 = false;
			int a2;
			for (int i = 0; i < accounts.size(); i++)
			{
				if (accounts[i].accountNumber == temp)
				{
					account1 = true;														// mark that account 1 exists
					a1 = i;																	// save the index of the first account
				}
				if (accounts[i].accountNumber == temp1)
				{
					account2 = true;														// mark that account 2 exists
					a2 = i;																	// save the index of the second account
				}
			}
			if (account1 == true && account2 == true)										// both accounts exist
			{
				accounts[a1].withdraw(atof(temp2.c_str()));
				accounts[a2].deposit(atof(temp2.c_str()));

				accounts[a1].showAccount(sout);
				results->SetWindowText(CString(sout.str().c_str()));
				accounts[a2].showAccount(sout);
				results->SetWindowText(CString(sout.str().c_str()));
			}
			else if (account1 == false && account2 == true)
			{
				results->SetWindowText(CString("The first account specified does not exist, but the second one does exist"));

			}
			else if (account1 == true && account2 == false)
			{
				results->SetWindowText(CString("The first account specified exists, but the second one does not exist"));
			}
			if (accounts.size() == 0)
			{
				results->SetWindowText(CString("No accounts found.\r\n(This is a handler showing that there were no accounts made)"));
			}
			break;
		}

		case 4:																				// Show account
		{
			CString mEdit4;

			userInput1->GetWindowText(mEdit4);												// user enters account number
			string temp((CT2CA)mEdit4);

			userInput2->GetWindowText(mEdit4);												// user enter amount they want to withdraw
			string temp1((CT2CA)mEdit4);


			for (int i = 0; i < accounts.size(); i++)
			{
				if (accounts[i].accountNumber == temp)
				{
					accounts[i].showAccount(sout);
					results->SetWindowText(CString(sout.str().c_str()));
					break;
				}
				if (i == accounts.size() && accounts[i].accountNumber != temp)
				{
					results->SetWindowText(CString("No accounts found."));
					break;
				}
			}
			if (accounts.size() == 0)
			{
				results->SetWindowText(CString("No accounts found.\r\n(This is a handler showing that there were no accounts made)"));
			}
			break;
		}

		case 5:																					// Show all Accounts
		{
			CString mEdit5;

			userInput1->GetWindowText(mEdit5);													// user enters account number
			string temp((CT2CA)mEdit5);

			if (temp == password)																// security
			{
				CStatic* hiddenBox = reinterpret_cast<CStatic*>(GetDlgItem(IDC_EDIT5));
				hiddenBox->ShowWindow(SW_SHOW);													// reveal hidden box

				CStatic* hiddenText4 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC10));
				hiddenText4->ShowWindow(SW_SHOW);												// reveal hidden text

				CStatic* userMODE = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC112));		// changes user mode text
				userMODE->SetWindowText(CString("ADMIN MODE"));

				CStatic* buttonCancel = reinterpret_cast<CStatic*>(GetDlgItem(IDC_BUTTON2));	// makes button visible
				buttonCancel->ShowWindow(SW_SHOW);

				testResults->SetWindowText(CString(""));
				if (accounts.size() == 0)
				{
					testResults->SetWindowText(CString("No accounts found.\r\n(This is a handler showing that there were no accounts made)"));
				}
				for (int i = 0; i < accounts.size(); i++)
				{
					accounts[i].showAccount(sout);
					testResults->SetWindowText(CString(sout.str().c_str()));
				}
			}
			break;
		}
	}
}


void CfinalProjectDlg::OnEnChangeEdit4()
{
}


void CfinalProjectDlg::OnEnChangeEdit3()
{
}


void CfinalProjectDlg::OnBnClickedButton2()
{
	CStatic* buttonCancel = reinterpret_cast<CStatic*>(GetDlgItem(IDC_BUTTON2));			// makes button invisible
	buttonCancel->ShowWindow(SW_HIDE);

	CStatic* userMODE = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC112));				// changes user mode text
	userMODE->SetWindowText(CString("USER MODE"));

	CStatic* hiddenBox = reinterpret_cast<CStatic*>(GetDlgItem(IDC_EDIT5));
	hiddenBox->ShowWindow(SW_HIDE);															// hide box

	CStatic* hiddenText4 = reinterpret_cast<CStatic*>(GetDlgItem(IDC_STATIC10));
	hiddenText4->ShowWindow(SW_HIDE);														// hide text
}
