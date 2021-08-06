#include "IFBFilterRankSlot.h"

#define BFILTER_SLOT_UNIQUELOG_NUM 1
#define BFILTER_SLOT_UNIQUELOG_NUM_PIC 2
#define BFILTER_SLOT_UNIQUELOG_NAME 3
#define BFILTER_SLOT_UNIQUELOG_Guild 5
#define BFILTER_SLOT_UNIQUELOG_POINT 6

GFX_IMPLEMENT_DYNCREATE(CIFCustomRankSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFCustomRankSlot, CIFWnd)
GFX_END_MESSAGE_MAP()

CIFCustomRankSlot::CIFCustomRankSlot(void)
{
	//printf("> " __FUNCTION__ "\n");
}


CIFCustomRankSlot::~CIFCustomRankSlot(void)
{
	//printf("> " __FUNCTION__ "\n");
}

bool CIFCustomRankSlot::OnCreate(long ln)
{
	//printf("> " __FUNCTION__ "(%d)\n", ln);

	// Populate inherited members
	CIFWnd::OnCreate(ln);

	//m_IRM.LoadFromFile("resinfo\\ifbfiltercustomrankslot.txt");
	//m_IRM.CreateInterfaceSection("Create", this);

	//m_custom_label1 = m_IRM.GetResObj<CIFStatic>(BFILTER_SLOT_UNIQUELOG_NUM, 1);
	//m_custom_label2 = m_IRM.GetResObj<CIFStatic>(BFILTER_SLOT_UNIQUELOG_NUM_PIC, 1);
	//m_custom_label3 = m_IRM.GetResObj<CIFStatic>(BFILTER_SLOT_UNIQUELOG_NAME, 1);
	//m_custom_label4 = m_IRM.GetResObj<CIFStatic>(BFILTER_SLOT_UNIQUELOG_Guild, 1);
	//m_custom_label5 = m_IRM.GetResObj<CIFStatic>(BFILTER_SLOT_UNIQUELOG_POINT, 1);

	RECT rect0 = { 20,5,25,13 };
	RECT rect1 = { 68,5,20,20 };
	RECT rect2 = { 110,5,115,13 };
	RECT rect3 = { 320,5,80,13 };
	RECT rect4 = { 363,5,40,13 };

	m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect0, BFILTER_SLOT_UNIQUELOG_NUM, 0);
	m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, BFILTER_SLOT_UNIQUELOG_NUM_PIC, 0);
	m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, BFILTER_SLOT_UNIQUELOG_NAME, 0);
	m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect3, BFILTER_SLOT_UNIQUELOG_Guild, 0);
	m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect4, BFILTER_SLOT_UNIQUELOG_POINT, 0);


	//m_custom_label1->MoveGWnd(m_custom_label1->GetPos().x + 10, m_custom_label1->GetPos().y - 2);
	m_custom_label2->MoveGWnd(GetPos().x + 1, m_custom_label1->GetPos().y-3);
	//m_custom_label1->SetGWndSize(25, 13);
	//m_custom_label2->SetGWndSize(20, 20);
	//m_custom_label3->SetGWndSize(115, 13);
	//m_custom_label4->SetGWndSize(80, 13);
	//m_custom_label5->SetGWndSize(40, 13);

	m_custom_label3->MoveGWnd(m_custom_label1->GetPos().x + m_custom_label1->GetSize().width + 5, m_custom_label1->GetPos().y);
	m_custom_label4->MoveGWnd(m_custom_label3->GetPos().x + m_custom_label3->GetSize().width + 30, m_custom_label1->GetPos().y);
	m_custom_label5->MoveGWnd(m_custom_label4->GetPos().x + m_custom_label4->GetSize().width + 30, m_custom_label1->GetPos().y);

	m_custom_label1->SetTextColor(0xffffff);
	m_custom_label2->SetTextColor(0xffffff);
	m_custom_label3->SetTextColor(0xffffff);
	m_custom_label4->SetTextColor(0xffffff);
	m_custom_label5->SetTextColor(0xffffff);
	m_custom_label2->ShowGWnd(false);
	ShowGWnd(true);
	return true;
}

void CIFCustomRankSlot::OnUpdate()
{
}

void CIFCustomRankSlot::WriteLine(const wchar_t* num, const wchar_t* Charname, const wchar_t* Guild, const wchar_t* Points)
{
	m_custom_label1->SetText(num);
	m_custom_label3->SetText(Charname);
	m_custom_label4->SetText(Guild);
	m_custom_label5->SetText(Points);
}

void CIFCustomRankSlot::ShowIcon()
{
	m_custom_label2->ShowGWnd(true);
}