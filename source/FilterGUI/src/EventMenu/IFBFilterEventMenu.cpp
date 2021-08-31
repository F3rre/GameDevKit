#include "IFBFilterEventMenu.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>
#include "EventMenu/IFBFilterEventMenuList.h"


#define EVENTMENU_FRAME 0
#define EVENTMENU_VSCROLL 1
#define EVENTMENU_TEXT 6
#define EVENTMENU_BUTTON_REGISTER 4
#define EVENTMENU_BUTTON_UNREGÝSTER 5

GFX_IMPLEMENT_DYNCREATE(CIFEventMenu, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFEventMenu, CIFMainFrame)
ONG_COMMAND(EVENTMENU_BUTTON_REGISTER,&On_Register)
ONG_COMMAND(EVENTMENU_BUTTON_UNREGÝSTER,&On_UnRegister)
GFX_END_MESSAGE_MAP()


CIFEventMenu::CIFEventMenu(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFEventMenu::~CIFEventMenu(void)
{
    //  printf("> " __FUNCTION__ "\n");
}

bool CIFEventMenu::OnCreate(long ln)
{
    // printf("> " __FUNCTION__ "(%d)\n", ln);

     // Populate inherited members
    CIFMainFrame::OnCreate(ln);


    RECT MenuFrameRect = {0,0,492,300};
    Frame = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), MenuFrameRect, EVENTMENU_FRAME, 0);
    Frame->TB_Func_13("interface\\gui\\eventui.ddj", 0, 0);

    
    RECT ScrollRect = {188,90,16,115};
    m_vericalSroll = (CIFVerticalScroll*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFVerticalScroll), ScrollRect, EVENTMENU_VSCROLL, 0);

    
    
    RECT EventTextRect = {216,51,255,185 };
    //m_IRM.GetResObj<CIFStatic>(EVENTMENU_TEXT, 1);
    EventText = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), EventTextRect, EVENTMENU_TEXT, 0);

    RECT SlotRect = { 0,0,0,0 };
    m_slot1 = (CIFEventMenuList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventMenuList), SlotRect, 40, 0);

    RECT RegRect = {19,257,88,24};
    EventRegister = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), RegRect, EVENTMENU_BUTTON_REGISTER, 1);
    EventRegister->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    EventRegister->SetText(L"Register");

    RECT UnRegRect = { 120,257,88,24 };
    EventUnRegister = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), UnRegRect, EVENTMENU_BUTTON_UNREGÝSTER, 1);
    EventUnRegister->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    EventUnRegister->SetText(L"UnRegister");


    m_slot1->ShowGWnd(true);


    m_slot1->line1->m_custom_label1->SetText(L"Random PVP Event");
    m_slot1->line2->m_custom_label1->SetText(L"Random Guild PVP Event");
    m_slot1->line3->m_custom_label1->SetText(L"PVP Event");
    m_slot1->line4->m_custom_label1->SetText(L"Guild Pvp Event");
    m_slot1->line5->m_custom_label1->SetText(L"Event 5");
    m_slot1->line6->m_custom_label1->SetText(L"Event 6");
    m_slot1->line7->m_custom_label1->SetText(L"Event 7");

    m_title->SetText(L"Event Manager");
    m_title->BringToFront();
    m_close->BringToFront();
    this->ShowGWnd(false);
    ResetPosition();
    return true;
}
void CIFEventMenu::OnUpdate()
{
}
void CIFEventMenu::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 750;
    this->MoveGWnd(PosX, PosY);
}

void CIFEventMenu::ClearDDJ() {
    m_slot1->ClearDDJ();
}

void CIFEventMenu::On_Register()
{

}

void CIFEventMenu::On_UnRegister()
{

}