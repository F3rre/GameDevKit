#include "IFBFilterCustomTitle.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <IFEdit.h>
#include <ICPlayer.h>
#include <BSLib\multiBYTE.h>
#include <IFBFilterMainMenu.h>
#include <GInterface.h>

#define BFILTERGRANTNAME_APPLY 31
#define BFILTERGRANTNAME_CLOSE_BUTTON 32
#define BFILTERGRANTNAME_NAME_INPUT 36
#define BFILTERGRANTNAME_PIC 11
#define BFILTERGRANTNAME_DESC1 33
#define BFILTERGRANTNAME_DESC2 34
#define BFILTERGRANTNAME_DESC3 35
#define BFILTERGRANTNAME_TITLE_1 1
#define BFILTERGRANTNAME_TITLE_2 23
#define BFILTERGRANTNAME_FRAME 21
#define BFILTERGRANTNAME_STREATCH 22

//LEGEND
//#define BFILTERGRANTNAME_APPLY 17
//#define BFILTERGRANTNAME_NAME_INPUT 16
//#define BFILTERGRANTNAME_NAME_LABEL 15
//#define BFILTERGRANTNAME_TOOLTIP 14
//#define BFILTERGRANTNAME_CLOSE_BUTTON 12
//#define BFILTERGRANTNAME_TITLE 11
//#define BFILTERGRANTNAME_FRAME 10


GFX_IMPLEMENT_DYNCREATE(CIFCustomTitle, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFCustomTitle, CIFMainFrame)
ONG_COMMAND(BFILTERGRANTNAME_CLOSE_BUTTON, &CIFCustomTitle::OnClick_Exit)
ONG_COMMAND(BFILTERGRANTNAME_APPLY, &CIFCustomTitle::On_BtnClick)
GFX_END_MESSAGE_MAP()


CIFCustomTitle::CIFCustomTitle(void)
{
}

CIFCustomTitle::~CIFCustomTitle(void)
{
}

bool CIFCustomTitle::OnCreate(long ln)
{

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
    m_custom_label6 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), NormalRect, BFILTERGRANTNAME_TITLE_2, 0);
    Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), FrameRect, BFILTERGRANTNAME_FRAME, 0);

    Frame->SetGWndSize(GetSize().width - 20, GetSize().height - 48);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 38);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
    m_custom_label6->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
    m_custom_label6->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);
    m_custom_label6->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);

    m_mybutton->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton2->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);

    m_title->SetText(L"Custom Title");
    m_mybutton->SetText(L"Apply");
    m_mybutton2->SetText(L"Exit");
    m_custom_label2->SetText(L"Enter A valid custom title consisting of 20 Letters as max");
    m_custom_label2->MoveGWnd(m_edit->GetBounds().pos.x - 30, m_custom_label2->GetBounds().pos.y + 15);
    m_custom_label3->MoveGWnd(m_edit->GetBounds().pos.x - 30, m_custom_label3->GetBounds().pos.y + 15);
    m_custom_label3->SetText(L"");


    std::n_wstring msg(L"Enter your favorite custom title here");

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

void CIFCustomTitle::On_BtnClick()
{
    if (m_edit->GetNText().empty())
    {
        m_custom_label3->SetText(L"Set a Custom title first");
        return;
    }
    if (m_edit->GetNText().length() > 20)
    {
        m_custom_label3->SetText(L"Title cant be more than 20 characters");
        return;
    }

    CMsgStreamBuffer buf(0x1202);
    buf << std::n_string(TO_NSTRING(g_pCICPlayer->GetCharName()));
    buf << std::n_string(TO_NSTRING(this->m_edit->GetNText()));
    SendMsg(buf);
}

void CIFCustomTitle::OnClick_Exit()
{
    this->OnCloseWnd();
    m_edit->SetText(L"");
    m_custom_label3->SetText(L"");
    CIFMainMenu::MenuGui->ShowGWnd(true);
    CIFMainMenu::MenuGui->ResetPosition();
}

void CIFCustomTitle::ResetPosition()
{
    m_edit->SetText(L"");
    m_custom_label3->SetText(L"");

    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 450;
    this->MoveGWnd(PosX, PosY);
}
