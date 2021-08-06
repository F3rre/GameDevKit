#include "IFBFilterUniqueList.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include "IFBFilterUniqueLog.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <PSilkroad.h>
#include <IFApprenticeShipSlot.h>

#define GDR_FIRST_BTN 30
#define GDR_SECOND_BTN 31
#define GDR_THIRD_BTN 32
#define GDR_FOUR_BTN 33
#define GDR_FIVE_BTN 34
#define GDR_SIX_BTN 35
#define GDR_SEVEN_BTN 36
#define GDR_EGHIT_BTN 37
#define GDR_NIGHN_BTN 38
#define GDR_TEEN_BTN 39

GFX_IMPLEMENT_DYNCREATE(CIFUniqueList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFUniqueList, CIFWnd)
GFX_END_MESSAGE_MAP()


CIFUniqueList::CIFUniqueList(void)
{
	//printf("> " __FUNCTION__ "\n");
}


CIFUniqueList::~CIFUniqueList(void)
{
	//printf("> " __FUNCTION__ "\n");
}

bool CIFUniqueList::OnCreate(long ln)
{
	//printf("> " __FUNCTION__ "(%d)\n", ln);

	// Populate inherited members
	CIFWnd::OnCreate(ln);


	RECT line1rect = { 18,74,417,24 };
	RECT line2rect = { 18,97,417,24 };
	RECT line3rect = { 18,120,417,24 };
	RECT line4rect = { 18,143,417,24 };
	RECT line5rect = { 18,166,417,24 };
	RECT line6rect = { 18,189,417,24 };
	RECT line7rect = { 18,212,417,24 };
	RECT line8rect = { 18,235,417,24 };
	RECT line9rect = { 18,258,417,24 };
	RECT line10rect = { 18,281,417,24 };

	line1 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line1rect, 30, 0);
	line2 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line2rect, 31, 0);
	line3 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line3rect, 32, 0);
	line4 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line4rect, 33, 0);
	line5 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line5rect, 34, 0);
	line6 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line6rect, 35, 0);
	line7 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line7rect, 36, 0);
	line8 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line8rect, 37, 0);
	line9 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line9rect, 38, 0);
	line10 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line10rect, 39, 0);

	//line1->SetGWndSize(line1->GetSize().width - 58, line1->GetSize().height);
	//line2->SetGWndSize(line2->GetSize().width - 58, line2->GetSize().height);
	//line3->SetGWndSize(line3->GetSize().width - 58, line3->GetSize().height);
	//line4->SetGWndSize(line4->GetSize().width - 58, line4->GetSize().height);
	//line5->SetGWndSize(line5->GetSize().width - 58, line5->GetSize().height);
	//line6->SetGWndSize(line6->GetSize().width - 58, line6->GetSize().height);
	//line7->SetGWndSize(line7->GetSize().width - 58, line7->GetSize().height);
	//line8->SetGWndSize(line8->GetSize().width - 58, line8->GetSize().height);
	//line9->SetGWndSize(line9->GetSize().width - 58, line9->GetSize().height);
	//line10->SetGWndSize(line10->GetSize().width - 58, line10->GetSize().height);

	line1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
	line2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
	line3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
	line4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
	line5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
	line6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
	line7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
	line8->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
	line9->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
	line10->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);

	line1->ShowGWnd(true);
	line2->ShowGWnd(true);
	line3->ShowGWnd(true);
	line4->ShowGWnd(true);
	line5->ShowGWnd(true);
	line6->ShowGWnd(true);
	line7->ShowGWnd(true);
	line8->ShowGWnd(true);
	line9->ShowGWnd(true);
	line10->ShowGWnd(true);

	this->ShowGWnd(false);
	return true;

}

void CIFUniqueList::OnUpdate()
{
}

void CIFUniqueList::WriteLine(BYTE num, const wchar_t* UQName, const wchar_t* State, const wchar_t* Killer, const wchar_t* STme)
{
	CIFUniqueLogSlot* Line;

	switch (num)
	{
	case 30:
	{
		Line = line1;
	}
	break;
	case 31:
	{
		Line = line2;
	}
	break;
	case 32:
	{
		Line = line3;
	}
	break;
	case 33:
	{
		Line = line4;
	}
	break;
	case 34:
	{
		Line = line5;
	}
	break;
	case 35:
	{
		Line = line6;
	}
	break;
	case 36:
	{
		Line = line7;
	}
	break;
	case 37:
	{
		Line = line8;
	}
	break;
	case 38:
	{
		Line = line9;
	}
	break;
	case 39:
	{
		Line = line10;
	}
	break;

	default:
		break;
	}

	Line->m_custom_label2->SetText(UQName);
	Line->m_custom_label3->SetText(State);
	Line->m_custom_label4->SetText(Killer);
	Line->m_custom_label5->SetText(STme);

	if (wcscmp(State, L"Alive") == 0)
	{
		Line->m_custom_label3->SetTextColor(0x5ad3a9);
	}
	else
		Line->m_custom_label3->SetTextColor(0xeb345b);
}