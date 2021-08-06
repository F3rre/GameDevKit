#include "IFBFilterEventTime.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>

#define BFILTER_TITLE 3
#define BFILTER_FRAME 5
#define BFILTER_STREATCH 6

#define BFILTER_SUBJ_NUM 25
#define BFILTER_SUBJ_NAME 26
#define BFILTER_SUBJ_TIME 27

#define BFILTER_SLOT_1 30
#define BFILTER_SLOT_2 31
#define BFILTER_SLOT_3 32
#define BFILTER_SLOT_4 33
#define BFILTER_SLOT_5 34
#define BFILTER_SLOT_6 35
#define BFILTER_SLOT_7 36
#define BFILTER_SLOT_8 37
#define BFILTER_SLOT_9 38
#define BFILTER_SLOT_10 39
#define BFILTER_SLOT_11 40
#define BFILTER_SLOT_12 41
#define BFILTER_SLOT_13 42
#define BFILTER_SLOT_14 43
#define BFILTER_SLOT_15 44
#define BFILTER_SLOT_16 45
#define BFILTER_SLOT_17 46
#define GDR_REFRESH_BUTTON 6
#define GDR_SPIN_BUTTON 4


//------------------------------------------------------------------------------
// Main Wind
//------------------------------------------------------------------------------
std::vector<CIFEventTime::EventSetting> CIFEventTime::EventList;

GFX_IMPLEMENT_DYNCREATE(CIFEventTime, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFEventTime, CIFMainFrame)
GFX_END_MESSAGE_MAP()


CIFEventTime::CIFEventTime(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFEventTime::~CIFEventTime(void)
{
  //  printf("> " __FUNCTION__ "\n");
}

bool CIFEventTime::OnCreate(long ln)
{
   // printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT lable1rect = { 19,47,349,113 };
    RECT lable2rect = { 16,40,356,445 };
    RECT lable3rect = { 217,350,36,36 };
    RECT lable4rect = { 227,314,50,16 };

    Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), lable1rect, BFILTER_FRAME, 0);
    m_custom_label = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable2rect, BFILTER_TITLE, 0);
    //Refresh = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), lable3rect, GDR_REFRESH_BUTTON, 0);
    m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), lable4rect, GDR_SPIN_BUTTON, 0);

    Frame->SetGWndSize(this->GetBounds().size.width - 20, this->GetBounds().size.height - 48);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 38);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
  
    m_custom_label->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
    m_custom_label->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);
    m_custom_label->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);
    RECT rect = { 0,0,0,0 };
   Slot1 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 40, 0);
   Slot2 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 41, 0);
   Slot3 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 42, 0);
   Slot4 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 43, 0);

   Slot1->MoveGWnd(m_custom_label->GetPos().x+1, m_custom_label->GetPos().y);
   Slot2->MoveGWnd(m_custom_label->GetPos().x+1, m_custom_label->GetPos().y);
   Slot3->MoveGWnd(m_custom_label->GetPos().x+1, m_custom_label->GetPos().y);
   Slot4->MoveGWnd(m_custom_label->GetPos().x+1, m_custom_label->GetPos().y);

   Slot1->ShowGWnd(true);
   Slot2->ShowGWnd(false);
   Slot3->ShowGWnd(false);
   Slot4->ShowGWnd(false);

    m_spin->MoveGWnd(m_spin->GetPos().x - 60, m_custom_label->GetPos().y + m_custom_label->GetSize().height - 35);
    m_spin->SetMinValue(1);
    m_spin->SetCurrentValue(1);
    m_spin->SetMaxValue(4);
    m_spin->ShowGWnd(true);

    //Refresh->MoveGWnd(m_custom_label->GetPos().x + m_custom_label->GetSize().width - 40, m_custom_label->GetPos().y + m_custom_label->GetSize().height - 37);
    this->m_title->SetText(L"Event Timer");
    //Refresh->TB_Func_13("interface\\ifcommon\\bfilter\\refresh.ddj", 0, 0);

   // std::n_wstring msg(L"Refresh Log");
    //Refresh->SetTooltipText(&msg);
    //Refresh->SetToolTipSetting(0x80);
    this->ShowGWnd(false);
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    ResetPosition();
    return true;
}

void CIFEventTime::OnUpdate()
{
}

void CIFEventTime::On_BtnClick()
{

}

void CIFEventTime::On_BtnClick1()
{
}

void CIFEventTime::OnClick_Exit()
{
    this->OnCloseWnd();
}

void CIFEventTime::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 750;
    this->MoveGWnd(PosX, PosY);
}

//but show the sent id
void CIFEventTime::HideLists()
{
	Slot1->ShowGWnd(false);
	Slot2->ShowGWnd(false);
	Slot3->ShowGWnd(false);
	Slot4->ShowGWnd(false);
}

void CIFEventTime::ShowList(BYTE listid)
{
	switch (listid)
	{
	case 1:
		HideLists();
		Slot1->ShowGWnd(true);
		break;
	case 2:
		HideLists();
		Slot2->ShowGWnd(true);
		break;
	case 3:
		HideLists();
		Slot3->ShowGWnd(true);
		break;
	case 4:
		HideLists();
		Slot4->ShowGWnd(true);
		break;
	}
}

bool CIFEventTime::EventListContains(const wchar_t* UqName)
{
	for (std::vector<CIFEventTime::EventSetting>::iterator it = CIFEventTime::EventList.begin(); it != CIFEventTime::EventList.end(); ++it)
		if (wcscmp((*it).EventName.c_str(), UqName) == 0)
			return true;
	return false;
}

void CIFEventTime::UpdateLog()
{
    for (std::vector<CIFEventTime::EventSetting>::iterator it = CIFEventTime::EventList.begin(); it != CIFEventTime::EventList.end(); ++it)
    {
        switch ((*it).LineNum)
        {
        case 1:
        {
            Slot1->Line1->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 2:
        {
           Slot1->Line2->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 3:
        {
           Slot1->Line3->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 4:
        {
           Slot1->Line4->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 5:
        {
           Slot1->Line5->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 6:
        {
           Slot1->Line6->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 7:
        {
           Slot1->Line7->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 8:
        {
           Slot1->Line8->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 9:
        {
           Slot1->Line9->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 10:
        {
           Slot1->Line10->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 11:
        {
           Slot2->Line1->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 12:
        {
           Slot2->Line2->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 13:
        {
           Slot2->Line3->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 14:
        {
           Slot2->Line4->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 15:
        {
           Slot2->Line5->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 16:
        {
           Slot2->Line6->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 17:
        {
           Slot2->Line7->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 18:
        {
           Slot2->Line8->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 19:
        {
           Slot2->Line9->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 20:
        {
           Slot2->Line10->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 21:
        {
           Slot3->Line1->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 22:
        {
           Slot3->Line2->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 23:
        {
           Slot3->Line3->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 24:
        {
           Slot3->Line4->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 25:
        {
           Slot3->Line5->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 26:
        {
           Slot3->Line6->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 27:
        {
           Slot3->Line7->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 28:
        {
           Slot3->Line8->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 29:
        {
           Slot3->Line9->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 30:
        {
           Slot3->Line10->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 31:
        {
           Slot4->Line1->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 32:
        {
           Slot4->Line2->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 33:
        {
           Slot4->Line3->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 34:
        {
           Slot4->Line4->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 35:
        {
           Slot4->Line5->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 36:
        {
           Slot4->Line6->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 37:
        {
           Slot4->Line7->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 38:
        {
           Slot4->Line8->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 39:
        {
           Slot4->Line9->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        case 40:
        {
           Slot4->Line10->WriteLine((*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str(), (*it).State.c_str());
        }
        break;
        }
    }
}

bool CIFEventTime::IsPageFull(BYTE PageID, BYTE LineID)
{
	bool full = false;
	if (PageID == 1)
	{
		if (LineID == 30)
		{
			if (Slot1->Line1->m_custom_label1->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (Slot1->Line10->m_custom_label1->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}
	if (PageID == 2)
	{
		if (LineID == 30)
		{
			if (Slot2->Line1->m_custom_label1->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (Slot2->Line10->m_custom_label1->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}
	if (PageID == 3)
	{
		if (LineID == 30)
		{
			if (Slot3->Line1->m_custom_label1->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (Slot3->Line10->m_custom_label1->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}
	if (PageID == 4)
	{
		if (LineID == 30)
		{
			if (Slot4->Line1->m_custom_label1->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
		if (LineID == 39)
		{
			if (Slot4->Line10->m_custom_label1->GetNText().length() > 0)
				full = true;
			else
				full = false;
		}
	}


	return full;
}