#include "IFBFilterChangeLog.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>

#define BFILTER_TITLE 10
#define BFILTER_FRAME 11
#define BFILTER_TEXTBOX 12
#define BFILTERTITLES_VSCROLL 13

GFX_IMPLEMENT_DYNCREATE(CIFChangeLog, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFChangeLog, CIFMainFrame)
GFX_END_MESSAGE_MAP()


CIFChangeLog::CIFChangeLog(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFChangeLog::~CIFChangeLog(void)
{
    //  printf("> " __FUNCTION__ "\n");
}

bool CIFChangeLog::OnCreate(long ln)
{
    // printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT lable1rect = { 19,47,349,113 };
    RECT lable2rect = { 30,60,340,290 };
    RECT lable3rect = { 25,55,340,290 };
    RECT scrollRect = { 355,70,16,209 };

    Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), lable1rect, BFILTER_FRAME, 0);
    m_custom_label = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable2rect, BFILTER_TITLE, 0);
    m_textbox = (CIFTextBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFTextBox), lable3rect, BFILTER_TEXTBOX, 0);
    m_vericalSroll = (CIFVerticalScroll*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFVerticalScroll), scrollRect, BFILTERTITLES_VSCROLL, 0);

    //m_textbox->N00000608 = this;
    //m_textbox->m_HeightInLines = 9;
    m_textbox->SetLineHeight(14);
    //m_textbox->sub_638B50(1);
    //m_textbox->sub_64E380(1);
    //m_textbox->sub_638C70(1);
    //m_textbox->SetHightlineLine(true);
    //m_textbox->sub_638D50(1);
    m_textbox->SetHighlightColor(0x8594b4);
    //m_textbox->sub_638D40(1);
    m_textbox->m_FontTexture.sub_8B4400(0,0);
    m_textbox->m_FontTexture.sub_8B4750(0);
    m_textbox->TB_Func_5(0);
    m_textbox->TB_Func_6(0);
    m_textbox->LinkScrollbar(m_vericalSroll);
    m_vericalSroll->sub_65A5C0(999);

    Frame->SetGWndSize(this->GetBounds().size.width - 20, this->GetBounds().size.height - 48);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 38);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);

    m_custom_label->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
    m_custom_label->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);
    m_custom_label->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);

   int TitleColor = 0x8594b4;
   int MsgColor = 0x53b7d2;

    std::n_wstring Title(L"ChangeLog v1.0.0");
    std::n_wstring Line(L"--------------------------------------");
    std::n_wstring Empty2(L"");
    std::n_wstring Msg(L"Fixed GUi");

    m_textbox->sub_64F8A0( Title, 0, TitleColor, TitleColor, -1, 0, 0);
    m_textbox->sub_64F8A0( Line, 0, TitleColor, TitleColor, -1, 0, 0);
    m_textbox->sub_64F8A0( Empty2, 0, TitleColor, TitleColor, -1, 0, 0);
    m_textbox->sub_64F8A0(Msg, 0, MsgColor, MsgColor, -1, 0, 0);


    this->m_title->SetText(L"Change Log");
    std::n_wstring msg(L"Refresh Log");
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    ResetPosition();
    this->ShowGWnd(false);
    return true;
}

void CIFChangeLog::OnUpdate()
{
}

void CIFChangeLog::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 750;
    this->MoveGWnd(PosX, PosY);
}