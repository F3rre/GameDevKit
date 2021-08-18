#include "EventMenu/IFBFilterEventMenuList.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>



#define BFILTER_STREATCH 6

GFX_IMPLEMENT_DYNCREATE(CIFEventMenuList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFEventMenuList, CIFWnd)
GFX_END_MESSAGE_MAP()


CIFEventMenuList::CIFEventMenuList(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFEventMenuList::~CIFEventMenuList(void)
{
    // printf("> " __FUNCTION__ "\n");
}

bool CIFEventMenuList::OnCreate(long ln)
{
    // printf("> " __FUNCTION__ "(%d)\n", ln);

     // Populate inherited members
    CIFWnd::OnCreate(ln);
    RECT line1rect = { 19,75,167,24 };
    RECT line2rect = { 19,98,167,24 };
    RECT line3rect = { 19,121,167,24 };
    RECT line4rect = { 19,144,167,24 };
    RECT line5rect = { 19,167,167,24 };
    RECT line6rect = { 19,190,167,24 };
    RECT line7rect = { 19,213,167,24 };


    line1 = (CIFEventMenuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventMenuSlot), line1rect, 30, 0);
    line2 = (CIFEventMenuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventMenuSlot), line2rect, 31, 0);
    line3 = (CIFEventMenuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventMenuSlot), line3rect, 32, 0);
    line4 = (CIFEventMenuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventMenuSlot), line4rect, 33, 0);
    line5 = (CIFEventMenuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventMenuSlot), line5rect, 34, 0);
    line6 = (CIFEventMenuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventMenuSlot), line6rect, 35, 0);
    line7 = (CIFEventMenuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventMenuSlot), line7rect, 36, 0);

    line1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);


    line1->ShowGWnd(true);
    line2->ShowGWnd(true);
    line3->ShowGWnd(true);
    line4->ShowGWnd(true);
    line5->ShowGWnd(true);
    line6->ShowGWnd(true);
    line7->ShowGWnd(true);


    this->ShowGWnd(false);
    return true;
}
void CIFEventMenuList::OnUpdate()
{

}

void CIFEventMenuList::ClearDDJ()
{
    line1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
}