#include "IFBFilterEventMenuGui.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include "ClientNet/MsgStreamBuffer.h"
#include "ANetwork/CPSMission.h"
#include "PSQuickStart.h"
#include "GInterface.h"

#include "unsorted.h"
#include "GlobalHelpersThatHaveNoHomeYet.h"
#include "ClientNet/ClientNet.h"
#include "Game.h"
#include "ICPlayer.h"
#include "IFWnd.h"
#include <IFSystemMessage.h>
#include <BSLib\multiBYTE.h>
//#include "Images/EventUI.bmp";


#define BFILTER_EVENTGUI_FRAME 5

GFX_IMPLEMENT_DYNCREATE(CIFEventMenuGui, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFEventMenuGui, CIFMainFrame)

GFX_END_MESSAGE_MAP()

CIFEventMenuGui::CIFEventMenuGui(void)
{

}


CIFEventMenuGui::~CIFEventMenuGui(void)
{

}


bool CIFEventMenuGui::OnCreate(long ln)
{
    CIFMainFrame::OnCreate(ln);


    RECT frame = { 0,0,492,300 };
    Frame = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), frame, BFILTER_EVENTGUI_FRAME, 0);
    Frame->TB_Func_13("interface\\gui\\eventui.ddj", 0, 0);




    m_title->SetText(L"Events");
    m_title->BringToFront();
    m_close->BringToFront();
this->ShowGWnd(false);
ResetPosition();
return true;
}

void CIFEventMenuGui::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 350;
    this->MoveGWnd(PosX, PosY);
}