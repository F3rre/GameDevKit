#include "IFBFilterEventTimeSlot.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <ICPlayer.h>
#include <BSLib\multiBYTE.h>
#include "ICPlayer.h"
#include <BSLib/Debug.h>

#define BFILTER_SLOT_EVENTNAME 11
#define BFILTER_SLOT_EVENTTIME 12

//------------------------------------------------------------------------------
// SLOTS
//------------------------------------------------------------------------------

GFX_IMPLEMENT_DYNCREATE(CIFEentTimeSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFEentTimeSlot, CIFWnd)
GFX_END_MESSAGE_MAP()

CIFEentTimeSlot::CIFEentTimeSlot(void)
{
   // BS_DEBUG("> " __FUNCTION__);
}


CIFEentTimeSlot::~CIFEentTimeSlot(void)
{
   // BS_DEBUG("> " __FUNCTION__);
}

bool CIFEentTimeSlot::OnCreate(long ln)
{
    //BS_DEBUG("> " __FUNCTION__ "(%d)", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    //m_IRM.LoadFromFile("resinfo\\ifbfiltereventtimeslot.txt");
    //m_IRM.CreateInterfaceSection("Create", this);
    TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);

    RECT line1rect = { 2,5,165,13 };
    RECT line2rect = { 173,5,165,13 };
    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), line1rect, BFILTER_SLOT_EVENTNAME, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), line1rect, BFILTER_SLOT_EVENTTIME, 0);

    //m_custom_label1 = m_IRM.GetResObj<CIFStatic>(BFILTER_SLOT_EVENTNAME, 1);
    //m_custom_label2 = m_IRM.GetResObj<CIFStatic>(BFILTER_SLOT_EVENTTIME, 1);

    //m_custom_label1->MoveGWnd(m_custom_label1->GetPos().x - 45, m_custom_label1->GetPos().y - 3);
    //m_custom_label2->MoveGWnd(m_custom_label2->GetPos().x + 10, m_custom_label2->GetPos().y - 3);

    //m_custom_label1->SetGWndSize(165,13);
    //m_custom_label2->SetGWndSize(165, 13);

    m_custom_label1->SetTextColor(0xffffff);
    m_custom_label2->SetTextColor(0xffffff);

    this->ShowGWnd(false);
    return true;
}
