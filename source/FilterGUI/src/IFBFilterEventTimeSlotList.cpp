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

    //m_IRM.LoadFromFile("resinfo\\ifbfiltereventtime.txt");
    //m_IRM.CreateInterfaceSection("List", this);

    //m_custom_label1 = m_IRM.GetResObj<CIFStatic>(BFILTER_STREATCH, 1);
    //m_custom_label2 = m_IRM.GetResObj<CIFStatic>(BFILTER_SUBJ_NAME, 1);
    //m_custom_label3 = m_IRM.GetResObj<CIFStatic>(BFILTER_SUBJ_TIME, 1);

    RECT lable1rect = { 17,195,352,260 };
    RECT lable2rect = { 176,198,175,24 };
    RECT lable3rect = { 60,198,175,24 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable1rect, BFILTER_STREATCH, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable2rect, BFILTER_SUBJ_NAME, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable3rect, BFILTER_SUBJ_TIME, 0);

    RECT line1rect = { 20,220,346,24 };
    RECT line2rect = { 20,243,346,24 };
    RECT line3rect = { 20,266,346,24 };
    RECT line4rect = { 20,289,346,24 };
    RECT line5rect = { 20,312,346,24 };
    RECT line6rect = { 20,335,346,24 };
    RECT line7rect = { 20,358,346,24 };
    RECT line8rect = { 20,381,346,24 };
    RECT line9rect = { 20,404,346,24 };
    RECT line10rect = { 20,427,346,24 };
    RECT line11rect = { 20,427,346,24 };
    RECT line12rect = { 20,427,346,24 };
    RECT line13rect = { 20,427,346,24 };
    RECT line14rect = { 20,427,346,24 };
    RECT line15rect = { 20,427,346,24 };

    Slot1 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line1rect, BFILTER_SLOT_1, 0);
    Slot2 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line2rect, BFILTER_SLOT_2, 0);
    Slot3 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line3rect, BFILTER_SLOT_3, 0);
    Slot4 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line4rect, BFILTER_SLOT_4, 0);
    Slot5 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line5rect, BFILTER_SLOT_5, 0);
    Slot6 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line6rect, BFILTER_SLOT_6, 0);
    Slot7 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line7rect, BFILTER_SLOT_7, 0);
    Slot8 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line8rect, BFILTER_SLOT_8, 0);
    Slot9 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line9rect, BFILTER_SLOT_9, 0);
    Slot10 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line10rect, BFILTER_SLOT_10, 0);
    Slot11 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line11rect, BFILTER_SLOT_11, 0);
    Slot12 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line12rect, BFILTER_SLOT_12, 0);
    Slot13 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line13rect, BFILTER_SLOT_13, 0);
    Slot14 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line14rect, BFILTER_SLOT_14, 0);
    Slot15 = (CIFEentTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEentTimeSlot), line15rect, BFILTER_SLOT_15, 0);

    //Slot1 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_1, 1);
    //Slot2 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_2, 1);
    //Slot3 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_3, 1);
    //Slot4 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_4, 1);
    //Slot5 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_5, 1);
    //Slot6 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_6, 1);
    //Slot7 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_7, 1);
    //Slot8 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_8, 1);
    //Slot9 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_9, 1);
    //Slot10 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_10, 1);
    //Slot11 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_11, 1);
    //Slot12 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_12, 1);
    //Slot13 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_13, 1);
    //Slot14 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_14, 1);
    //Slot15 = m_IRM.GetResObj<CIFEentTimeSlot>(BFILTER_SLOT_15, 1);

    Slot1->ShowGWnd(true);
    Slot2->ShowGWnd(true);
    Slot3->ShowGWnd(true);
    Slot4->ShowGWnd(true);
    Slot5->ShowGWnd(true);
    Slot6->ShowGWnd(true);
    Slot7->ShowGWnd(true);
    Slot8->ShowGWnd(true);
    Slot9->ShowGWnd(true);
    Slot10->ShowGWnd(true);
    Slot11->ShowGWnd(true);
    Slot12->ShowGWnd(true);
    Slot13->ShowGWnd(true);
    Slot14->ShowGWnd(true);
    Slot15->ShowGWnd(true);

    Slot1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot8->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot9->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot10->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot11->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot12->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot13->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot14->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Slot15->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);

    m_custom_label1->MoveGWnd(GetPos().x, GetPos().y);
    m_custom_label1->SetGWndSize(352, 385);

    m_custom_label2->MoveGWnd(m_custom_label1->GetPos().x + 2, m_custom_label1->GetPos().y + 1);
   // m_custom_label2->SetGWndSize(175, 24);
    m_custom_label3->MoveGWnd(m_custom_label2->GetPos().x + m_custom_label2->GetSize().width-2, m_custom_label2->GetPos().y);
   // m_custom_label3->SetGWndSize(175, 24);

    m_custom_label2->TB_Func_13("interface\\guild\\gil_subj_button09.ddj", 0, 0);
    m_custom_label3->TB_Func_13("interface\\guild\\gil_subj_button09.ddj", 0, 0);

    Slot1->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 20);
    Slot2->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 44);
    Slot3->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 68);
    Slot4->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 92);
    Slot5->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 116);
    Slot6->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 140);
    Slot7->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 164);
    Slot8->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 188);
    Slot9->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 212);
    Slot10->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 236);
    Slot11->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 260);
    Slot12->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 284);
    Slot13->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 308);
    Slot14->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 332);
    Slot15->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 356);

    Slot1->SetGWndSize(Slot1->GetSize().width - 2, Slot1->GetSize().height);
    Slot2->SetGWndSize(Slot2->GetSize().width - 2, Slot2->GetSize().height);
    Slot3->SetGWndSize(Slot3->GetSize().width - 2, Slot3->GetSize().height);
    Slot4->SetGWndSize(Slot4->GetSize().width - 2, Slot4->GetSize().height);
    Slot5->SetGWndSize(Slot5->GetSize().width - 2, Slot5->GetSize().height);
    Slot6->SetGWndSize(Slot6->GetSize().width - 2, Slot6->GetSize().height);
    Slot7->SetGWndSize(Slot7->GetSize().width - 2, Slot7->GetSize().height);
    Slot8->SetGWndSize(Slot8->GetSize().width - 2, Slot8->GetSize().height);
    Slot9->SetGWndSize(Slot9->GetSize().width - 2, Slot9->GetSize().height);
    Slot10->SetGWndSize(Slot10->GetSize().width - 2, Slot10->GetSize().height);
    Slot11->SetGWndSize(Slot11->GetSize().width - 2, Slot11->GetSize().height);
    Slot12->SetGWndSize(Slot12->GetSize().width - 2, Slot12->GetSize().height);
    Slot13->SetGWndSize(Slot13->GetSize().width - 2, Slot13->GetSize().height);
    Slot14->SetGWndSize(Slot14->GetSize().width - 2, Slot14->GetSize().height);
    Slot15->SetGWndSize(Slot15->GetSize().width - 2, Slot15->GetSize().height);

    m_custom_label2->SetText(L"Name");
    m_custom_label3->SetText(L"Time");

    this->ShowGWnd(false);
    return true;
}

void CIFEventTimeList::OnUpdate()
{
}
