#include "IFBFilterChestSlot.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <ICPlayer.h>
#include "MainMenu/IFBFilterMainMenu.h"

#define BFILTER_SLOT_UNIQUELOG_NUM 1
#define BFILTER_SLOT_UNIQUELOG_NAME 2
#define BFILTER_SLOT_UNIQUELOG_STATE 3
#define BFILTER_SLOT_UNIQUELOG_KILLER 4
#define BFILTER_SLOT_UNIQUELOG_TIME 5

GFX_IMPLEMENT_DYNCREATE(CIFPlayerChestSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFPlayerChestSlot, CIFWnd)
GFX_END_MESSAGE_MAP()

CIFPlayerChestSlot::CIFPlayerChestSlot(void)
{
	//printf("> " __FUNCTION__ "\n");
}

CIFPlayerChestSlot::~CIFPlayerChestSlot(void)
{
	//printf("> " __FUNCTION__ "\n");
}

bool CIFPlayerChestSlot::OnCreate(long ln)
{
	//printf("> " __FUNCTION__ "(%d)\n", ln);

	// Populate inherited members
	CIFWnd::OnCreate(ln);

	RECT rect1 = { 18,5,210,13 };
	RECT rect2 = { 285,5,50,13 };
	RECT rect3 = { 350,5,150,13 };
	RECT rect4 = { 500,5,80,13 };

	m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, BFILTER_SLOT_UNIQUELOG_NAME, 0);
	m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, BFILTER_SLOT_UNIQUELOG_STATE, 0);
	m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect3, BFILTER_SLOT_UNIQUELOG_KILLER, 0);
	m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect4, BFILTER_SLOT_UNIQUELOG_TIME, 0);

	m_custom_label2->MoveGWnd(GetPos().x + 5, m_custom_label2->GetPos().y);
	m_custom_label3->MoveGWnd(m_custom_label2->GetPos().x + m_custom_label2->GetSize().width + 10, m_custom_label3->GetPos().y);
	m_custom_label4->MoveGWnd(m_custom_label3->GetPos().x + m_custom_label3->GetSize().width + 15, m_custom_label4->GetPos().y);
	m_custom_label5->MoveGWnd(m_custom_label4->GetPos().x + m_custom_label4->GetSize().width + 10, m_custom_label5->GetPos().y);


	m_custom_label2->SetTextColor(0xffffff);
	m_custom_label3->SetTextColor(0xffffff);
	m_custom_label4->SetTextColor(0xffffff);
	m_custom_label5->SetTextColor(0xffffff);

	m_custom_label2->BringToFront();
	m_custom_label3->BringToFront();
	m_custom_label4->BringToFront();
	m_custom_label5->BringToFront();

	this->ShowGWnd(false);
	return true;
}

void CIFPlayerChestSlot::WriteLine(const wchar_t* ItemName, const wchar_t* Count, const wchar_t* From, const wchar_t* Date)
{
    m_custom_label2->SetText(ItemName);
    m_custom_label3->SetText(Count);
    m_custom_label4->SetText(From);
    m_custom_label5->SetText(Date);
}

int CIFPlayerChestSlot::OnMouseLeftUp(int a1, int x, int y)
{
    CIFMainMenu::ChestGUI->ClearDDJ();
    CIFMainMenu::ChestGUI->SelectedItemName = m_custom_label2->GetNText();
    TB_Func_13("interface\\ifcommon\\com_bar01select_mid.ddj", 0, 0);
    return 0;
}
