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
    Refresh = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), lable3rect, GDR_REFRESH_BUTTON, 0);
    m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), lable4rect, GDR_SPIN_BUTTON, 0);


    //Frame = m_IRM.GetResObj<CIFFrame>(BFILTER_FRAME, 1);
    //m_custom_label = m_IRM.GetResObj<CIFStatic>(BFILTER_TITLE, 1);
    //Refresh = m_IRM.GetResObj<CIFButton>(GDR_REFRESH_BUTTON, 1);
    //m_spin = (CIFSpinControl*)m_IRM.GetResObj<CIFSpinControl>(GDR_SPIN_BUTTON, 1);

    Frame->SetGWndSize(this->GetBounds().size.width - 20, this->GetBounds().size.height - 48);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 38);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
  
    m_custom_label->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
    m_custom_label->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);
    //m_custom_label->ShowGWnd(true);
    m_custom_label->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);
    RECT rect = { 0,0,0,0 };
    Slot1 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 40, 0);
    Slot2 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 41, 0);
    Slot3 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 42, 0);
    Slot4 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 43, 0);
    Slot5 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 44, 0);
    Slot6 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 45, 0);
    Slot7 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 46, 0);

    Slot1->MoveGWnd(m_custom_label->GetPos().x+1, m_custom_label->GetPos().y);
    Slot1->ShowGWnd(true);
    Slot2->ShowGWnd(false);
    Slot3->ShowGWnd(false);
    Slot4->ShowGWnd(false);
    Slot5->ShowGWnd(false);
    Slot6->ShowGWnd(false);
    Slot7->ShowGWnd(false);

    m_spin->MoveGWnd(m_spin->GetPos().x - 60, m_custom_label->GetPos().y + m_custom_label->GetSize().height - 35);
    m_spin->SetMinValue(1);
    m_spin->SetCurrentValue(1);
    m_spin->SetMaxValue(7);
    m_spin->ShowGWnd(true);

    Refresh->MoveGWnd(m_custom_label->GetPos().x + m_custom_label->GetSize().width - 40, m_custom_label->GetPos().y + m_custom_label->GetSize().height - 37);
    this->m_title->SetText(L"Event Timer");
    Refresh->TB_Func_13("interface\\ifcommon\\bfilter\\refresh.ddj", 0, 0);
    //Refresh->MoveGWnd(Refresh->GetPos().x, Refresh->GetPos().y + 100);
    //Refresh->SetGWndSize(36, 36);
    std::n_wstring msg(L"Refresh Log");
    Refresh->SetTooltipText(&msg);
    Refresh->SetToolTipSetting(0x80);
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

void CIFEventTime::WriteLine(BYTE num, const wchar_t* EventName, const wchar_t* Time)
{
    switch (num)
    {
    case 30:
    {
        Slot1->Slot1->m_custom_label1->SetText(EventName);
        Slot1->Slot1->m_custom_label2->SetText(Time);
    }
    break;
    }
}
