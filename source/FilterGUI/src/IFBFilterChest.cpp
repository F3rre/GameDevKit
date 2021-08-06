#include "IFBFilterChest.h"
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

GFX_IMPLEMENT_DYNCREATE(CIFPlayerChest, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFPlayerChest, CIFMainFrame)
ONG_COMMAND(GDR_7_BTN, &CIFPlayerChest::On_BtnClick_1)
GFX_END_MESSAGE_MAP()

static int RefreshTimes = 0;

std::vector<CIFPlayerChest::Chest> CIFPlayerChest::ChestList;

CIFPlayerChest::CIFPlayerChest(void)
{
	//printf("> " __FUNCTION__ "\n");
}

CIFPlayerChest::~CIFPlayerChest(void)
{
	//printf("> " __FUNCTION__ "\n");
}

bool CIFPlayerChest::OnCreate(long ln)
{
//	printf("> " __FUNCTION__ "(%d)\n", ln);

	// Populate inherited members
	CIFMainFrame::OnCreate(ln);


	RECT Framerect = { 17,45,180,185 };
	RECT Lablerect = { 16,308,480,62 };
	RECT Lable2rect = { 15,49,481,259 };

	RECT Butt1rect = { 68,51,225,24 };
	RECT Butt2rect = { 243,51,75,24 };
	RECT Butt3rect = { 319,51,170,24 };
	RECT Butt4rect = { 373,51,95,24 };

	RECT Spinect = { 200,322,50,16 };
	RECT Takerect = { 217,350,70,24 };

	Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), Framerect, GDR_BFILTER_FRAME, 0);

	m_custom_label = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect, GDR_BFILTER_TITLE, 0);
	m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lable2rect, GDR_BFILTER_STREACH, 0);

	UniqueName = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt1rect, GDR_3_BTN, 0);
	AliveState = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt2rect, GDR_4_BTN, 0);
	KilledBy = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt3rect, GDR_5_BTN, 0);
	SpwanTime = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt4rect, GDR_6_BTN, 0);
	m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), Spinect, 4, 0);
	Conform = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Takerect, GDR_7_BTN, 0);

	SpwanTime->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
	UniqueName->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
	AliveState->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
	KilledBy->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
	m_custom_label->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);
	Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
	Conform->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);

	m_custom_label2->MoveGWnd(m_custom_label2->GetPos().x + 7, m_custom_label2->GetPos().y + 5);
	m_custom_label2->SetGWndSize(m_custom_label2->GetSize().width, m_custom_label2->GetSize().height - 2);

	UniqueName->MoveGWnd(m_custom_label2->GetPos().x + 2, UniqueName->GetPos().y + 5);
	AliveState->MoveGWnd(UniqueName->GetPos().x + UniqueName->GetSize().width-9, AliveState->GetPos().y + 5);
	KilledBy->MoveGWnd(AliveState->GetPos().x + AliveState->GetSize().width-4, KilledBy->GetPos().y + 5);
	SpwanTime->MoveGWnd(KilledBy->GetPos().x + KilledBy->GetSize().width-7, SpwanTime->GetPos().y + 5);

	Frame->SetGWndSize(this->GetSize().width - 20, this->GetSize().height - 50);
	Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 40);

	m_custom_label->SetGWndSize(Frame->GetBounds().size.width - 20, Frame->GetBounds().size.height - 20);
	m_custom_label->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);

	RECT rect = { 0,0,0,0 };
	m_slot1 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 40, 0);
	m_slot2 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 41, 0);
	m_slot3 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 42, 0);
	m_slot4 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 43, 0);
	m_slot5 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 44, 0);
	m_slot6 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 45, 0);
	m_slot7 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 46, 0);
	m_slot8 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 47, 0);
	m_slot9 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 48, 0);
	m_slot10 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 49, 0);

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
	//m_spin->MoveGWnd(m_spin->GetPos().x-30, m_spin->GetPos().y + 8);
	m_spin->ShowGWnd(true);

	//tests
	this->m_title->SetText(L"Chest");
	this->UniqueName->SetText(L"Item Name");
	this->AliveState->SetText(L"Quantity");
	this->KilledBy->SetText(L"From");
	this->SpwanTime->SetText(L"Date");
	this->Conform->SetText(L"Take");
	Conform->MoveGWnd(Conform->GetPos().x + 250, Conform->GetPos().y - 30);
	TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
	ResetPosition();
	this->ShowGWnd(false);
	return true;
}

void CIFPlayerChest::OnUpdate()
{
}

void CIFPlayerChest::ResetPosition()
{
	USHORT PosX = 0, PosY = 165;
	PosX = CLIENT_SCREEN_WIDTH - 750;
	this->MoveGWnd(PosX, PosY);
}

void CIFPlayerChest::On_BtnClick_1()
{
	printf("> " __FUNCTION__ "\n");

	//RefreshTimes++;

	//if (RefreshTimes > 2)
	//{
	//	g_pCGInterface->ShowMessage_Warning(L"Unique History automatically refresh every 5 minute");
	//	return;
	//}

	//CMsgStreamBuffer buf(0x1203);
	//SendMsg(buf);
}

void CIFPlayerChest::OnClick_Exit()
{
	this->OnCloseWnd();
}

//but show the sent id
void CIFPlayerChest::HideLists()
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

void CIFPlayerChest::ShowList(BYTE listid)
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

bool CIFPlayerChest::UqListContains(const wchar_t* UqName)
{
	for (std::vector<CIFPlayerChest::Chest>::iterator it = CIFPlayerChest::ChestList.begin(); it != CIFPlayerChest::ChestList.end(); ++it)
		if (wcscmp((*it).ItemName.c_str(), UqName) == 0)
			return true;
	return false;
}



bool CIFPlayerChest::IsPageFull(BYTE PageID, BYTE LineID)
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