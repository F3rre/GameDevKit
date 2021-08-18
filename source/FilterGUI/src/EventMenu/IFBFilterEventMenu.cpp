#include "IFBFilterEventMenu.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>
#include "EventMenu/IFBFilterEventMenuList.h"


#define EVENTMENU_FRAME 0
#define EVENTMENU_VSCROLL 1
#define EVENTMENU_TEXT 2

GFX_IMPLEMENT_DYNCREATE(CIFEventMenu, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFEventMenu, CIFMainFrame)
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
    RECT ScrollRect = {188,90,16,115};
    RECT EventTTextRect = {216,51,255,185 };

    Frame = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), MenuFrameRect, EVENTMENU_FRAME, 0);
    Frame->TB_Func_13("interface\\gui\\eventui.ddj", 0, 0);

    m_vericalSroll = (CIFVerticalScroll*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFVerticalScroll), ScrollRect, EVENTMENU_VSCROLL, 0);

    EventText = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), EventTTextRect, EVENTMENU_TEXT, 0);
    //EventText->SetText(L"Test 1\nTest2\nTest 3\nTest 1\nTest2\nTest 3\nTest 1\nTest 1\nTest 1\nTest 1\nTest 1\nTest 1");
    //EventText->TB_Func_13("Blabla",0,0);

    RECT rect = { 0,0,0,0 };
    m_slot1 = (CIFEventMenuList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventMenuList), rect, 40, 0);



    m_slot1->ShowGWnd(true);


    m_slot1->line1->m_custom_label1->SetText(L"Event 1");
    m_slot1->line2->m_custom_label1->SetText(L"Event 2");
    m_slot1->line3->m_custom_label1->SetText(L"Event 3");
    m_slot1->line4->m_custom_label1->SetText(L"Event 4");
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