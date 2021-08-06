#include "IFBFilterEventTimeSlotList.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>

#define BFILTER_TITLE 3
#define BFILTER_FRAME 5
#define BFILTER_STREATCH 6

#define BFILTER_SUBJ_NUM 25
#define BFILTER_SUBJ_NAME 26
#define BFILTER_SUBJ_DAY 27
#define BFILTER_SUBJ_TIME 28
#define BFILTER_SUBJ_STATE 29

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

GFX_IMPLEMENT_DYNCREATE(CIFEventTimeList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFEventTimeList, CIFWnd)
GFX_END_MESSAGE_MAP()


CIFEventTimeList::CIFEventTimeList(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFEventTimeList::~CIFEventTimeList(void)
{
   // printf("> " __FUNCTION__ "\n");
}

bool CIFEventTimeList::OnCreate(long ln)
{
   // printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT lable1rect = { 17,195,353,260 };

    RECT lable2rect = { 2,199,170,24 };
    RECT lable3rect = { 177,199,50,24 };
    RECT lable4rect = { 227,199,80,24 };
    RECT lable5rect = { 327,199,50,24 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable1rect, BFILTER_STREATCH, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable2rect, BFILTER_SUBJ_NAME, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable3rect, BFILTER_SUBJ_DAY, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable4rect, BFILTER_SUBJ_TIME, 0);
    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable5rect, BFILTER_SUBJ_STATE, 0);

    RECT Line1rect = { 20,220,344,24 };
    RECT Line2rect = { 20,243,344,24 };
    RECT Line3rect = { 20,266,344,24 };
    RECT Line4rect = { 20,289,344,24 };
    RECT Line5rect = { 20,312,344,24 };
    RECT Line6rect = { 20,335,344,24 };
    RECT Line7rect = { 20,358,344,24 };
    RECT Line8rect = { 20,381,344,24 };
    RECT Line9rect = { 20,404,344,24 };
    RECT Line10rect = { 20,427,344,24 };

    Line1 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), Line1rect, BFILTER_SLOT_1, 0);
    Line2 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), Line2rect, BFILTER_SLOT_2, 0);
    Line3 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), Line3rect, BFILTER_SLOT_3, 0);
    Line4 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), Line4rect, BFILTER_SLOT_4, 0);
    Line5 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), Line5rect, BFILTER_SLOT_5, 0);
    Line6 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), Line6rect, BFILTER_SLOT_6, 0);
    Line7 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), Line7rect, BFILTER_SLOT_7, 0);
    Line8 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), Line8rect, BFILTER_SLOT_8, 0);
    Line9 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), Line9rect, BFILTER_SLOT_9, 0);
    Line10 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), Line10rect, BFILTER_SLOT_10, 0);

    Line1->ShowGWnd(true);
    Line2->ShowGWnd(true);
    Line3->ShowGWnd(true);
    Line4->ShowGWnd(true);
    Line5->ShowGWnd(true);
    Line6->ShowGWnd(true);
    Line7->ShowGWnd(true);
    Line8->ShowGWnd(true);
    Line9->ShowGWnd(true);
    Line10->ShowGWnd(true);

    Line1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line8->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line9->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line10->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);

    m_custom_label1->MoveGWnd(GetPos().x, GetPos().y);
    m_custom_label1->SetGWndSize(352, 265);

    m_custom_label2->MoveGWnd(m_custom_label1->GetPos().x + 2, m_custom_label1->GetPos().y);
    m_custom_label3->MoveGWnd(m_custom_label2->GetPos().x + m_custom_label2->GetSize().width-2, m_custom_label2->GetPos().y);
    m_custom_label4->MoveGWnd(m_custom_label3->GetPos().x + m_custom_label3->GetSize().width -1, m_custom_label2->GetPos().y);
    m_custom_label5->MoveGWnd(m_custom_label4->GetPos().x + m_custom_label4->GetSize().width , m_custom_label2->GetPos().y);

    m_custom_label2->TB_Func_13("interface\\guild\\gil_subj_button09.ddj", 0, 0);
    m_custom_label3->TB_Func_13("interface\\guild\\gil_subj_button09.ddj", 0, 0);
    m_custom_label4->TB_Func_13("interface\\guild\\gil_subj_button09.ddj", 0, 0);
    m_custom_label5->TB_Func_13("interface\\guild\\gil_subj_button09.ddj", 0, 0);

    Line1->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 20);
    Line2->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 44);
    Line3->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 68);
    Line4->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 92);
    Line5->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 116);
    Line6->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 140);
    Line7->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 164);
    Line8->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 188);
    Line9->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 212);
    Line10->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 236);

    m_custom_label2->SetText(L"Name");
    m_custom_label3->SetText(L"Day");
    m_custom_label4->SetText(L"Time");
    m_custom_label5->SetText(L"State");

    this->ShowGWnd(false);
    return true;
}

void CIFEventTimeList::OnUpdate()
{
}
