#include "IFBFilterUniqueLogSlot.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <ICPlayer.h>
#include "IFBFilterUniqueLog.h"

#define BFILTER_SLOT_UNIQUELOG_NUM 1
#define BFILTER_SLOT_UNIQUELOG_NAME 2
#define BFILTER_SLOT_UNIQUELOG_STATE 3
#define BFILTER_SLOT_UNIQUELOG_KILLER 4
#define BFILTER_SLOT_UNIQUELOG_TIME 5

GFX_IMPLEMENT_DYNCREATE(CIFUniqueLogSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFUniqueLogSlot, CIFWnd)
GFX_END_MESSAGE_MAP()


CIFUniqueLogSlot::CIFUniqueLogSlot(void)
{
	//printf("> " __FUNCTION__ "\n");
}


CIFUniqueLogSlot::~CIFUniqueLogSlot(void)
{
	//printf("> " __FUNCTION__ "\n");
}

bool CIFUniqueLogSlot::OnCreate(long ln)
{
	//printf("> " __FUNCTION__ "(%d)\n", ln);

	// Populate inherited members
	CIFWnd::OnCreate(ln);

	//m_IRM.LoadFromFile("resinfo\\ifbfilteruniqueslot.txt");
	//m_IRM.CreateInterfaceSection("Create", this);

	RECT rect1 = { 60,7,170,13 };
	RECT rect2 = { 243,7,42,13 };
	RECT rect3 = { 300,7,50,13 };
	RECT rect4 = { 393,7,70,13 };

	m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, BFILTER_SLOT_UNIQUELOG_NAME, 0);
	m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, BFILTER_SLOT_UNIQUELOG_STATE, 0);
	m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect3, BFILTER_SLOT_UNIQUELOG_KILLER, 0);
	m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect4, BFILTER_SLOT_UNIQUELOG_TIME, 0);

	//m_custom_label2 = m_IRM.GetResObj<CIFStatic>(BFILTER_SLOT_UNIQUELOG_NAME, 1);
	//m_custom_label3 = m_IRM.GetResObj<CIFStatic>(BFILTER_SLOT_UNIQUELOG_STATE, 1);
	//m_custom_label4 = m_IRM.GetResObj<CIFStatic>(BFILTER_SLOT_UNIQUELOG_KILLER, 1);
	//m_custom_label5 = m_IRM.GetResObj<CIFStatic>(BFILTER_SLOT_UNIQUELOG_TIME, 1);

	m_custom_label2->MoveGWnd(GetPos().x + 5, m_custom_label2->GetPos().y-2);
	m_custom_label3->MoveGWnd(m_custom_label2->GetPos().x + m_custom_label2->GetSize().width + 15, m_custom_label3->GetPos().y-2);
	m_custom_label4->MoveGWnd(m_custom_label3->GetPos().x + m_custom_label3->GetSize().width + 15, m_custom_label4->GetPos().y-2);
	m_custom_label5->MoveGWnd(m_custom_label4->GetPos().x + m_custom_label4->GetSize().width + 45, m_custom_label5->GetPos().y-2);


	m_custom_label2->SetTextColor(0xffffff);
	m_custom_label3->SetTextColor(0xffffff);
	m_custom_label4->SetTextColor(0xffffff);
	m_custom_label5->SetTextColor(0xffffff);

	this->ShowGWnd(false);
	return true;
}
