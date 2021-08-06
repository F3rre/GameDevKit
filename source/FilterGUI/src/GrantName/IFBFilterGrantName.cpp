#include "IFBFilterGrantName.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <ICPlayer.h>
#include "ClientNet/MsgStreamBuffer.h"
#include <BSLib\multiBYTE.h>
#include "ANetwork/CPSMission.h"
#include "MainMenu/IFBFilterMainMenu.h"
#include <memory\hook.h>

#define BFILTERGRANTNAME_APPLY 31
#define BFILTERGRANTNAME_CLOSE_BUTTON 32
#define BFILTERGRANTNAME_NAME_INPUT 36
#define BFILTERGRANTNAME_PIC 11
#define BFILTERGRANTNAME_DESC1 33
#define BFILTERGRANTNAME_DESC2 34
#define BFILTERGRANTNAME_DESC3 35
#define BFILTERGRANTNAME_FRAME 21
#define BFILTERGRANTNAME_BGTITLE 1
#define BFILTERGRANTNAME_FGTITLE 23
#define BFILTERGRANTNAME_STREATCH 22

//LEGEND
//#define BFILTERGRANTNAME_APPLY 17
//#define BFILTERGRANTNAME_NAME_INPUT 16
//#define BFILTERGRANTNAME_NAME_LABEL 15
//#define BFILTERGRANTNAME_TOOLTIP 14
//#define BFILTERGRANTNAME_CLOSE_BUTTON 12
//#define BFILTERGRANTNAME_TITLE 11
//#define BFILTERGRANTNAME_FRAME 10

#define GET_OWN_GAME_ID() \
	MEMUTIL_READ_BY_PTR_OFFSET(g_pCICPlayer, 0xF8, DWORD)

GFX_IMPLEMENT_DYNCREATE(CIFGrantName, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFGrantName, CIFMainFrame)
ONG_COMMAND(BFILTERGRANTNAME_CLOSE_BUTTON, &CIFGrantName::OnClick_Exit)
ONG_COMMAND(BFILTERGRANTNAME_APPLY, &CIFGrantName::On_BtnClick)
GFX_END_MESSAGE_MAP()


CIFGrantName::CIFGrantName(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFGrantName::~CIFGrantName(void)
{
   // printf("> " __FUNCTION__ "\n");
}

bool CIFGrantName::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT buttRect = { 135,199,111,24 };
    RECT butt2Rect = { 216,199,111,24 };

    RECT labRect = { 143,48,194,15 };
    RECT lab2Rect = { 143,70,55,15 };

    RECT NormalRect = { 47,112,342,59 };
    RECT FrameRect = { 35,99,364,82 };
    RECT editRect = { 69,124,298,24 };

    m_mybutton = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), buttRect, BFILTERGRANTNAME_APPLY, 0);
    m_mybutton2 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), butt2Rect, BFILTERGRANTNAME_CLOSE_BUTTON, 0);
    m_edit = (CIFEdit*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEdit), editRect, BFILTERGRANTNAME_NAME_INPUT, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), labRect, BFILTERGRANTNAME_DESC1, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lab2Rect, BFILTERGRANTNAME_DESC2, 0);
    m_custom_label6 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), NormalRect, BFILTERGRANTNAME_FGTITLE, 0);
    Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), FrameRect, BFILTERGRANTNAME_FRAME, 0);

    Frame->SetGWndSize(GetSize().width - 20, GetSize().height - 48);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 38);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
    m_custom_label6->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
    m_custom_label6->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);
    m_custom_label6->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);

    m_mybutton->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton2->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);

    m_title->SetText(L"Change Grant Name");
    m_mybutton->SetText(L"Apply");
    m_mybutton2->SetText(L"Exit");
    m_custom_label2->SetText(L"Enter A valid Grant Name consisting of 12 Letters as max");
    m_custom_label2->MoveGWnd(m_edit->GetBounds().pos.x-30, m_custom_label2->GetBounds().pos.y+15);
    m_custom_label3->MoveGWnd(m_edit->GetBounds().pos.x-30, m_custom_label3->GetBounds().pos.y+15);
    m_custom_label3->SetText(L"");


    std::n_wstring msg(L"Enter your favorite grant name here");

    m_edit->MoveGWnd(m_custom_label3->GetBounds().pos.x, m_custom_label3->GetBounds().pos.y + 20);
    m_edit->SetTooltipText(&msg);
    m_edit->SetToolTipSetting(0x80);
    m_edit->TB_Func_13("interface\\messagebox\\msgbox_gil_title.ddj", 0, 0);
    //m_edit->SetGWndSize(m_edit->GetSize().width, 28);
    m_edit->N00000608 = this;

    m_mybutton->MoveGWnd(m_edit->GetPos().x, m_mybutton->GetBounds().pos.y - 60);
    m_mybutton2->MoveGWnd(m_edit->GetPos().x + m_edit->GetSize().width - m_mybutton2->GetSize().width, m_mybutton2->GetBounds().pos.y - 60);

    m_edit->m_FontTexture.sub_8B4400(1, 0);
    m_edit->m_FontTexture.sub_8B4750(1);
    m_edit->TB_Func_5(1);
    m_edit->TB_Func_6(1);

    m_custom_label2->m_FontTexture.sub_8B4400(0, 0);
    m_custom_label2->m_FontTexture.sub_8B4750(0);
    m_custom_label2->TB_Func_5(0);
    m_custom_label2->TB_Func_6(0);

    m_custom_label3->m_FontTexture.sub_8B4400(0, 0);
    m_custom_label3->m_FontTexture.sub_8B4750(0);
    m_custom_label3->TB_Func_5(0);
    m_custom_label3->TB_Func_6(0);

    Frame->BringToFront();
    m_custom_label6->BringToFront();
    m_title->BringToFront();
    m_custom_label2->BringToFront();
    m_custom_label3->BringToFront();
    m_edit->BringToFront();
    m_mybutton->BringToFront();
    m_mybutton2->BringToFront();
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    this->ShowGWnd(false);
    ResetPosition();
    return true;
}

void CIFGrantName::OnUpdate()
{
}

void CIFGrantName::On_BtnClick()
{
    //no guild?
    if (g_pCICPlayer->GetGuildName().empty() || m_edit->GetNText().length() > 12)
    {
        m_custom_label3->SetText(L"Grant name must be 12 Letters as max");
        return;
    }

    if (m_edit->GetNText().empty())
    {
        m_custom_label3->SetText(L"Set a grant name first");
        return;
    }

    //wchar_t buffer1[45];
    //std::wstring mymsg1;
    //swprintf_s(buffer1, sizeof(buffer1), L"!grant %s", this->m_edit->GetText());
    //mymsg1.assign(buffer1);

    //BYTE type = 0x01;
    //BYTE index = 0x00;

    //CMsgStreamBuffer buf(0x7025);
    //buf << type << index;
    //buf << TO_NSTRING(mymsg1);
    //SendMsg(buf);

    CMsgStreamBuffer buf(0x3501);
    buf << GET_OWN_GAME_ID();
    buf << TO_NSTRING(this->m_edit->GetNText());
    SendMsg(buf);
}

void CIFGrantName::OnClick_Exit()
{
    this->OnCloseWnd();
    m_edit->SetText(L"");
    m_custom_label3->SetText(L"");
    CIFMainMenu::MenuGui->ShowGWnd(true);
    CIFMainMenu::MenuGui->ResetPosition();
}

void CIFGrantName::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 750;
    this->MoveGWnd(PosX, PosY);
}
