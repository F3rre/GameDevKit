#include "IFBFilterUniqueLog.h"
#include "ClientNet/MsgStreamBuffer.h"
#include "IFSpinButtonCtrl.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include <IFBFilterMainMenu.h>
#include <sstream>
#include <CPSMission.h>

#define GDR_1_BTN 20
#define GDR_2_BTN 21
#define GDR_3_BTN 22
#define GDR_4_BTN 24
#define GDR_5_BTN 23
#define GDR_6_BTN 25
#define GDR_7_BTN 3
#define TIMER_CHATBLOCK 230
#define GDR_BFILTER_FRAME 31
#define GDR_BFILTER_TITLE 2
#define GDR_BFILTER_STREACH 1
#define TIMER_UPDATE_PER_SECOND 10

GFX_IMPLEMENT_DYNCREATE(CIFUniqueLog, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFUniqueLog, CIFMainFrame)
ONG_COMMAND(GDR_7_BTN, &On_BtnClick_1)
GFX_END_MESSAGE_MAP()

static int RefreshTimes = 0;

std::vector<CIFUniqueLog::UniqueLogstru> CIFUniqueLog::UQlist;

CIFUniqueLog::CIFUniqueLog(void)
{
	//printf("> " __FUNCTION__ "\n");
}

CIFUniqueLog::~CIFUniqueLog(void)
{
//	printf("> " __FUNCTION__ "\n");
}

bool CIFUniqueLog::OnCreate(long ln)
{
	//printf("> " __FUNCTION__ "(%d)\n", ln);

	// Populate inherited members
	CIFMainFrame::OnCreate(ln);


	RECT Framerect = { 17,45,180,185 };
	RECT Lablerect = { 16,308,480,62 };
	RECT Lable2rect = { 22,54,481,259 };

	RECT Butt1rect = { 25,55,175,24 };
	RECT Butt2rect = { 195,55,60,24 };
	RECT Butt3rect = { 252,55,110,24 };
	RECT Butt4rect = { 356,55,90,24 };

	RECT Spinect = { 197,322,50,16 };

	Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), Framerect, GDR_BFILTER_FRAME, 0);

	m_custom_label = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect, GDR_BFILTER_TITLE, 0);
	m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lable2rect, GDR_BFILTER_STREACH, 0);

	UniqueName = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt1rect, GDR_3_BTN, 0);
	AliveState = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt2rect, GDR_4_BTN, 0);
	KilledBy = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt3rect, GDR_5_BTN, 0);
	SpwanTime = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt4rect, GDR_6_BTN, 0);
	m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), Spinect, 4, 0);

	SpwanTime->TB_Func_13("interface\\guild\\gil_subj_button04.ddj", 0, 0);
	UniqueName->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
	AliveState->TB_Func_13("interface\\guild\\gil_subj_button12.ddj", 0, 0);
	KilledBy->TB_Func_13("interface\\guild\\gil_subj_button12.ddj", 0, 0);
	m_custom_label->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);
	Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
	//m_custom_label2->TB_Func_13("interface\\ifcommon\\com_blacksquare_", 0, 1);


	//m_custom_label = m_IRM.GetResObj<CIFStatic>(GDR_BFILTER_TITLE, 1);
	//m_custom_label2 = m_IRM.GetResObj<CIFStatic>(GDR_BFILTER_STREACH, 1);
	//UniqueName = (CIFButton*)m_IRM.GetResObj<CIFButton>(GDR_3_BTN, 1);
	//AliveState = (CIFButton*)m_IRM.GetResObj<CIFButton>(GDR_4_BTN, 1);
	//KilledBy = (CIFButton*)m_IRM.GetResObj<CIFButton>(GDR_5_BTN, 1);
	//SpwanTime = (CIFWnd*)m_IRM.GetResObj<CIFWnd>(GDR_6_BTN, 1);
	//Conform = m_IRM.GetResObj<CIFButton>(GDR_7_BTN, 1);
	//m_spin = (CIFSpinControl*)m_IRM.GetResObj<CIFSpinControl>(4, 1);

	//m_custom_label2->MoveGWnd(m_custom_label2->GetPos().x + 7, m_custom_label2->GetPos().y + 5);
	m_custom_label2->SetGWndSize(m_custom_label2->GetSize().width-58, m_custom_label2->GetSize().height - 2);

	//Count->MoveGWnd(Count->GetPos().x + 7, Count->GetPos().y + 5);
	//UniqueName->MoveGWnd(m_custom_label2->GetPos().x + 2, UniqueName->GetPos().y + 5);
	//AliveState->MoveGWnd(UniqueName->GetPos().x + UniqueName->GetSize().width-5, AliveState->GetPos().y + 5);
	//KilledBy->MoveGWnd(AliveState->GetPos().x + AliveState->GetSize().width-1, KilledBy->GetPos().y + 5);
	//SpwanTime->MoveGWnd(KilledBy->GetPos().x + KilledBy->GetSize().width-3, SpwanTime->GetPos().y + 5);

	Frame->SetGWndSize(this->GetSize().width - 20, this->GetSize().height - 50);
	Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 40);

	m_custom_label->SetGWndSize(Frame->GetBounds().size.width - 20, Frame->GetBounds().size.height - 20);
	m_custom_label->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);

	RECT rect = { 0,0,0,0 };
	m_slot1 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 40, 0);
	m_slot2 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 41, 0);
	m_slot3 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 42, 0);
	m_slot4 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 43, 0);
	m_slot5 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 44, 0);
	m_slot6 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 45, 0);
	m_slot7 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 46, 0);
	m_slot8 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 47, 0);
	m_slot9 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 48, 0);
	m_slot10 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 49, 0);

	m_slot1->MoveGWnd(m_slot1->GetPos().x + 7, m_slot1->GetPos().y + 5);
	m_slot2->MoveGWnd(m_slot2->GetPos().x + 7, m_slot2->GetPos().y + 5);
	m_slot3->MoveGWnd(m_slot3->GetPos().x + 7, m_slot3->GetPos().y + 5);
	m_slot4->MoveGWnd(m_slot4->GetPos().x + 7, m_slot4->GetPos().y + 5);
	m_slot5->MoveGWnd(m_slot5->GetPos().x + 7, m_slot5->GetPos().y + 5);
	m_slot6->MoveGWnd(m_slot6->GetPos().x + 7, m_slot6->GetPos().y + 5);
	m_slot7->MoveGWnd(m_slot7->GetPos().x + 7, m_slot7->GetPos().y + 5);
	m_slot8->MoveGWnd(m_slot8->GetPos().x + 7, m_slot8->GetPos().y + 5);
	m_slot9->MoveGWnd(m_slot9->GetPos().x + 7, m_slot9->GetPos().y + 5);
	m_slot10->MoveGWnd(m_slot10->GetPos().x + 7, m_slot10->GetPos().y + 5);

	HideLists();
	m_slot1->ShowGWnd(true);
	m_spin->SetMinValue(1);
	m_spin->SetCurrentValue(1);
	m_spin->SetMaxValue(10);
	m_spin->ShowGWnd(true);

	//tests
	this->m_title->SetText(L"Unique History");
	this->UniqueName->SetText(L"Unique Name");
	this->AliveState->SetText(L"State");
	this->KilledBy->SetText(L"Killer");
	this->SpwanTime->SetText(L"Spawn Time");
	TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
	ResetPosition();
	this->ShowGWnd(false);
	return true;
}

void CIFUniqueLog::OnUpdate()
{
}


void CIFUniqueLog::ResetPosition()
{
	USHORT PosX = 0, PosY = 165;
	PosX = CLIENT_SCREEN_WIDTH - 780;
	this->MoveGWnd(PosX, PosY);
}

void CIFUniqueLog::On_BtnClick_1()
{
//	printf("> " __FUNCTION__ "\n");
}

void CIFUniqueLog::OnClick_Exit()
{
	this->OnCloseWnd();
}

//but show the sent id
void CIFUniqueLog::HideLists()
{
	m_slot1->ShowGWnd(false);
	m_slot2->ShowGWnd(false);
	m_slot3->ShowGWnd(false);
	m_slot4->ShowGWnd(false);
	m_slot5->ShowGWnd(false);
	m_slot6->ShowGWnd(false);
	m_slot7->ShowGWnd(false);
	m_slot8->ShowGWnd(false);
	m_slot9->ShowGWnd(false);
	m_slot10->ShowGWnd(false);
}

void CIFUniqueLog::ShowList(BYTE listid)
{
	switch (listid)
	{
	case 1:
		HideLists();
		m_slot1->ShowGWnd(true);
		break;
	case 2:
		HideLists();
		m_slot2->ShowGWnd(true);
		break;
	case 3:
		HideLists();
		m_slot3->ShowGWnd(true);
		break;
	case 4:
		HideLists();
		m_slot4->ShowGWnd(true);
		break;
	case 5:
		HideLists();
		m_slot5->ShowGWnd(true);
		break;
	case 6:
		HideLists();
		m_slot6->ShowGWnd(true);
		break;
	case 7:
		HideLists();
		m_slot7->ShowGWnd(true);
		break;
	case 8:
		HideLists();
		m_slot8->ShowGWnd(true);
		break;
	case 9:
		HideLists();
		m_slot9->ShowGWnd(true);
		break;
	case 10:
		HideLists();
		m_slot10->ShowGWnd(true);
		break;
	}
}

bool CIFUniqueLog::UqListContains(const wchar_t* UqName)
{
	for (std::vector<CIFUniqueLog::UniqueLogstru>::iterator it = CIFUniqueLog::UQlist.begin(); it != CIFUniqueLog::UQlist.end(); ++it)
		if (wcscmp((*it).UqName.c_str(), UqName) == 0)
			return true;
	return false;
}

void CIFUniqueLog::UpdateLog()
{
	for (std::vector<CIFUniqueLog::UniqueLogstru>::iterator it = CIFUniqueLog::UQlist.begin(); it != CIFUniqueLog::UQlist.end(); ++it)
	{

		//std::wcout << L"Page " << (*it).Pagenum << L" LineNum " << (*it).LineNum << L" Uq " << (*it).UqName.c_str() << L" life " << (*it).LifeState.c_str() << L" Killer " << (*it).Killer.c_str() << L" Time " << (*it).Time.c_str() << std::endl;

		switch ((*it).Pagenum)
		{
		case 1:
		{
			m_slot1->WriteLine((*it).LineNum, (*it).UqName.c_str(), (*it).LifeState.c_str(), (*it).Killer.c_str(), (*it).Time.c_str());
		}
		break;
		case 2:
		{
			m_slot2->WriteLine((*it).LineNum, (*it).UqName.c_str(), (*it).LifeState.c_str(), (*it).Killer.c_str(), (*it).Time.c_str());
		}
		break;
		case 3:
		{
			m_slot3->WriteLine((*it).LineNum, (*it).UqName.c_str(), (*it).LifeState.c_str(), (*it).Killer.c_str(), (*it).Time.c_str());
		}
		break;
		case 4:
		{
			m_slot4->WriteLine((*it).LineNum, (*it).UqName.c_str(), (*it).LifeState.c_str(), (*it).Killer.c_str(), (*it).Time.c_str());
		}
		break;
		case 5:
		{
			m_slot5->WriteLine((*it).LineNum, (*it).UqName.c_str(), (*it).LifeState.c_str(), (*it).Killer.c_str(), (*it).Time.c_str());
		}
		break;
		case 6:
		{
			m_slot6->WriteLine((*it).LineNum, (*it).UqName.c_str(), (*it).LifeState.c_str(), (*it).Killer.c_str(), (*it).Time.c_str());
		}
		break;
		case 7:
		{
			m_slot7->WriteLine((*it).LineNum, (*it).UqName.c_str(), (*it).LifeState.c_str(), (*it).Killer.c_str(), (*it).Time.c_str());
		}
		break;
		case 8:
		{
			m_slot8->WriteLine((*it).LineNum, (*it).UqName.c_str(), (*it).LifeState.c_str(), (*it).Killer.c_str(), (*it).Time.c_str());
		}
		break;
		case 9:
		{
			m_slot9->WriteLine((*it).LineNum, (*it).UqName.c_str(), (*it).LifeState.c_str(), (*it).Killer.c_str(), (*it).Time.c_str());
		}
		break;
		case 10:
		{
			m_slot10->WriteLine((*it).LineNum, (*it).UqName.c_str(), (*it).LifeState.c_str(), (*it).Killer.c_str(), (*it).Time.c_str());
		}
		break;
		}
	}
}

bool CIFUniqueLog::IsPageFull(BYTE PageID, BYTE LineID)
{
	bool full = false;
	if (PageID == 1)
	{
		if (LineID == 30)
		{
			if (m_slot1->line1->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (m_slot1->line10->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}
	if (PageID == 2)
	{
		if (LineID == 30)
		{
			if (m_slot2->line1->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (m_slot2->line10->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}
	if (PageID == 3)
	{
		if (LineID == 30)
		{
			if (m_slot3->line1->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (m_slot3->line10->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}
	if (PageID == 4)
	{
		if (LineID == 30)
		{
			if (m_slot4->line1->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (m_slot4->line10->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}
	if (PageID == 5)
	{
		if (LineID == 30)
		{
			if (m_slot5->line1->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (m_slot5->line10->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}
	if (PageID == 6)
	{
		if (LineID == 30)
		{
			if (m_slot6->line1->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (m_slot6->line10->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}
	if (PageID == 7)
	{
		if (LineID == 30)
		{
			if (m_slot7->line1->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (m_slot7->line10->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}
	if (PageID == 8)
	{
		if (LineID == 30)
		{
			if (m_slot8->line1->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (m_slot8->line10->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}
	if (PageID == 9)
	{
		if (LineID == 30)
		{
			if (m_slot9->line1->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (m_slot9->line10->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}
	if (PageID == 10)
	{
		if (LineID == 30)
		{
			if (m_slot10->line1->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (m_slot10->line10->m_custom_label2->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}

	return full;
}