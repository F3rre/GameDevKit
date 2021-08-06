#include "IFBFilterGMPassword.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include "ClientNet/MsgStreamBuffer.h"
#include <ICPlayer.h>
#include <BSLib\multiBYTE.h>

#define ELECTUSGRANTNAME_APPLY 17
#define ELECTUSGRANTNAME_NAME_INPUT 16
#define ELECTUSGRANTNAME_NAME_LABEL 15
#define ELECTUSGRANTNAME_TOOLTIP 14
#define ELECTUSGRANTNAME_CLOSE_BUTTON 12
#define ELECTUSGRANTNAME_TITLE 11
#define ELECTUSGRANTNAME_FRAME 10

GFX_IMPLEMENT_DYNCREATE(CIFGMPassword, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFGMPassword, CIFMainFrame)
ONG_COMMAND(ELECTUSGRANTNAME_CLOSE_BUTTON, &OnClick_Exit)
ONG_COMMAND(ELECTUSGRANTNAME_APPLY, &On_BtnClick)
GFX_END_MESSAGE_MAP()


CIFGMPassword::CIFGMPassword(void)
{
	printf("> " __FUNCTION__ "\n");
}


CIFGMPassword::~CIFGMPassword(void)
{
	printf("> " __FUNCTION__ "\n");
}

bool CIFGMPassword::OnCreate(long ln)
{
	printf("> " __FUNCTION__ "(%d)\n", ln);

	// Populate inherited members
	CIFMainFrame::OnCreate(ln);

	//m_IRM.LoadFromFile("resinfo\\ifelectusgrantname.txt");
	//m_IRM.CreateInterfaceSection("Create", this);

	//m_mybutton = m_IRM.GetResObj<CIFButton>(ELECTUSGRANTNAME_APPLY, 1);

	//m_edit = m_IRM.GetResObj<CIFEdit>(ELECTUSGRANTNAME_NAME_INPUT, 1);

	//m_custom_label = m_IRM.GetResObj<CIFStatic>(ELECTUSGRANTNAME_NAME_LABEL, 1);
	//m_custom_label1 = m_IRM.GetResObj<CIFStatic>(ELECTUSGRANTNAME_TOOLTIP, 1);
	//m_custom_label2 = m_IRM.GetResObj<CIFStatic>(ELECTUSGRANTNAME_TITLE, 1);
	//m_custom_label3 = m_IRM.GetResObj<CIFStatic>(ELECTUSGRANTNAME_FRAME, 1);

	//m_custom_label->SetText(L"Password:");
	//m_custom_label1->SetText(L"This will allow you to use GM's Commands");
	//m_custom_label2->SetText(L"GM Second Password");

	//m_mybutton->SetText(L"Apply");

	//this->ShowGWnd(false);
	//ResetPosition();
	return true;
}

void CIFGMPassword::OnUpdate()
{
	//time_t rawtime;
	//struct tm * timeinfo;
	//wchar_t buffer[80];

	//time (&rawtime);
	//timeinfo = localtime(&rawtime);

	//wcsftime(buffer,sizeof(buffer),L"%d-%m-%Y %H:%M:%S",timeinfo);

	//m_IRM.GetResObj<CIFStatic>(GDR_FLORIAN0_LABEL_TIME, 1)->SetText(buffer);
}

void CIFGMPassword::ResetPosition()
{
	USHORT PosX = 0, PosY = 165;
	PosX = CLIENT_SCREEN_WIDTH - 750;
	this->MoveGWnd(PosX, PosY);
}

void CIFGMPassword::On_BtnClick()
{
	printf("> " __FUNCTION__ "\n");

	CMsgStreamBuffer buf(0x3265);
	buf << std::n_string(TO_NSTRING(g_pCICPlayer->GetCharName())); // Character Name
	buf << std::n_string(TO_NSTRING(this->m_edit->GetNText()));
	SendMsg(buf);
}

void CIFGMPassword::OnClick_Exit()
{
	this->OnCloseWnd();
}
