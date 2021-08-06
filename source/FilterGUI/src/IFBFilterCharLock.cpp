#include "IFBFilterCharLock.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include "ClientNet/MsgStreamBuffer.h"
#include "CPSMission.h"
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
#define BFILTER_CHARLOCK_NEWLOCK_SET 27
//#define BFILTER_CHARLOCK_NEWLOCK_CONFIRM_PASSWORD_INPUT 26
#define BFILTER_CHARLOCK_NEWLOCK_PASSWORD_INPUT 25
#define BFILTER_CHARLOCK_NEWLOCK_CONFIRM_PASSWORD_INPUT 24
//#define BFILTER_CHARLOCK_NEWLOCK_CONFIRM_PASSWORD_LABEL 23
#define BFILTER_CHARLOCK_NEWLOCK_PASSWORD_LABEL 22
#define BFILTER_CHARLOCK_NEWLOCK_CONFIRM_PASSWORD_LABEL 21

#define BFILTER_CHARLOCK_NEWLOCKPASSWORD_LABEL 20
#define BFILTER_CHARLOCK_LOCK 19
#define BFILTER_CHARLOCK_PASSWORD_INPUT 18
#define BFILTER_CHARLOCK_PASSWORD_LABEL 17
#define BFILTER_CHARLOCK_STATUS 16
#define BFILTER_CHARLOCK_STATUS_ICON 15
#define BFILTER_CHARLOCK_STATUS_LABEL 14

#define BFILTER_CHARLOCK_UNLOCK 13
#define BFILTER_CHARLOCK_REMOVELOCK 12
#define BFILTER_CHARLOCK_TITLE 5
#define BFILTER_CHARLOCK_FRAME 6

GFX_IMPLEMENT_DYNCREATE(CIFCharLock, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFCharLock, CIFMainFrame)
ONG_COMMAND(BFILTER_CHARLOCK_REMOVELOCK, &CIFCharLock::OnClick_RemoveLock)
ONG_COMMAND(BFILTER_CHARLOCK_LOCK, &CIFCharLock::On_BtnClicklock)
ONG_COMMAND(BFILTER_CHARLOCK_UNLOCK, &CIFCharLock::On_BtnClickUnLock)
ONG_COMMAND(BFILTER_CHARLOCK_NEWLOCK_SET, &CIFCharLock::OnClick_CreateLock)
GFX_END_MESSAGE_MAP()


CIFCharLock::CIFCharLock(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFCharLock::~CIFCharLock(void)
{
   // printf("> " __FUNCTION__ "\n");
}

bool CIFCharLock::OnCreate(long ln)
{
   // printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT lable1rect = { 17,45,180,185 };
    RECT lable2rect = { 33,82,148,110 };

    RECT lable3rect = { 257,15,14,14 };
    RECT lable4rect = { 177,120,90,23 };
    RECT lable5rect = { 226,9,24,24 };
    RECT lable6rect = { 177,269,90,23 };

    RECT lable7rect = { 103,88,164,23 };
    RECT lable8rect = { 103,190,164,23 };
    RECT lable9rect = { 103,216,164,23 };

    RECT lable10rect = { 140,41,143,34 };
    RECT lable11rect = { 10,86,91,24 };
    RECT lable12rect = { 10,153,263,29 };
    RECT lable13rect = { 10,188,91,24 };
    RECT lable14rect = { 10,214,91,24 };

    Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), lable1rect, BFILTER_CHARLOCK_FRAME, 0);
    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable2rect, BFILTER_CHARLOCK_TITLE, 0);
    m_custom_label1->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);

    m_mybutton = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), lable3rect, BFILTER_CHARLOCK_REMOVELOCK, 0);
    m_mybutton2 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), lable4rect, BFILTER_CHARLOCK_LOCK, 0);
    m_mybutton3 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), lable5rect, BFILTER_CHARLOCK_UNLOCK, 0);
    m_mybutton4 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), lable6rect, BFILTER_CHARLOCK_NEWLOCK_SET, 0);
    
    m_edit = (CIFEdit*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEdit), lable7rect, BFILTER_CHARLOCK_PASSWORD_INPUT, 0);
    m_edit2 = (CIFEdit*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEdit), lable8rect, BFILTER_CHARLOCK_NEWLOCK_CONFIRM_PASSWORD_INPUT, 0);
    m_edit3 = (CIFEdit*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEdit), lable9rect, BFILTER_CHARLOCK_NEWLOCK_PASSWORD_INPUT, 0);

    m_edit->m_FontTexture.sub_8B4400(1, 0);
    m_edit->m_FontTexture.sub_8B4750(1);
    m_edit->TB_Func_5(1);
    m_edit->TB_Func_6(1);

    m_edit2->m_FontTexture.sub_8B4400(1, 0);
    m_edit2->m_FontTexture.sub_8B4750(1);
    m_edit2->TB_Func_5(1);
    m_edit2->TB_Func_6(1);

    m_edit3->m_FontTexture.sub_8B4400(1, 0);
    m_edit3->m_FontTexture.sub_8B4750(1);
    m_edit3->TB_Func_5(1);
    m_edit3->TB_Func_6(1);

    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable10rect, BFILTER_CHARLOCK_STATUS, 0);
    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable11rect, BFILTER_CHARLOCK_PASSWORD_LABEL, 0);
    m_custom_label6 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable12rect, BFILTER_CHARLOCK_NEWLOCKPASSWORD_LABEL, 0);
    m_custom_label7 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable13rect, BFILTER_CHARLOCK_NEWLOCK_CONFIRM_PASSWORD_LABEL, 0);
    m_custom_label8 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable14rect, BFILTER_CHARLOCK_NEWLOCK_PASSWORD_LABEL, 0);

    m_custom_label4->MoveGWnd(m_custom_label4->GetPos().x - 45, m_custom_label4->GetPos().y+5);

    m_mybutton2->MoveGWnd(m_mybutton2->GetPos().x + 32, m_mybutton2->GetPos().y);

    m_mybutton->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton2->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton3->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton4->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);

    m_mybutton3->MoveGWnd(m_mybutton2->GetPos().x - 93, m_mybutton2->GetPos().y);
    m_mybutton3->SetGWndSize(m_mybutton2->GetSize().width, m_mybutton2->GetSize().height);

    m_mybutton->MoveGWnd(m_mybutton2->GetPos().x - 185, m_mybutton2->GetPos().y);
    m_mybutton->SetGWndSize(m_mybutton2->GetSize().width, m_mybutton2->GetSize().height);

    m_mybutton4->MoveGWnd(m_mybutton4->GetPos().x, m_mybutton4->GetPos().y - 23);

    m_mybutton4->SetTextColor(0xffffff);
    m_mybutton2->SetTextColor(0xffffff);
    m_custom_label4->SetTextColor(0xffffff);

    m_edit->SetTextColor(0xffffff);
    m_edit2->SetTextColor(0xffffff);
    m_edit3->SetTextColor(0xffffff);

    m_edit->MoveGWnd(m_edit->GetBounds().pos.x + 35, m_edit->GetBounds().pos.y);
    m_edit2->MoveGWnd(m_edit2->GetBounds().pos.x + 35, m_edit2->GetBounds().pos.y);
    m_edit3->MoveGWnd(m_edit3->GetBounds().pos.x + 35, m_edit3->GetBounds().pos.y);

    m_edit->TB_Func_13("interface\\messagebox\\msgbox_blackbox_02.ddj", 0, 0);
    m_edit2->TB_Func_13("interface\\messagebox\\msgbox_blackbox_02.ddj", 0, 0);
    m_edit3->TB_Func_13("interface\\messagebox\\msgbox_blackbox_02.ddj", 0, 0);

    m_custom_label5->MoveGWnd(m_custom_label5->GetBounds().pos.x + 25, m_custom_label5->GetBounds().pos.y);
    m_custom_label6->MoveGWnd(m_custom_label6->GetBounds().pos.x + 20, m_custom_label6->GetBounds().pos.y);
    m_custom_label7->MoveGWnd(m_custom_label7->GetBounds().pos.x + 25, m_custom_label7->GetBounds().pos.y);
    m_custom_label8->MoveGWnd(m_custom_label8->GetBounds().pos.x + 25, m_custom_label8->GetBounds().pos.y);

    m_title->SetText(L"Chacacter Lock");
    m_custom_label4->SetText(L"Unlock Your Character");
    m_custom_label5->SetText(L"Password");
    m_custom_label6->SetText(L"Create A new Lock");
    m_custom_label7->SetText(L"Password");
    m_custom_label8->SetText(L"Confirm Password");
    m_mybutton->SetText(L"Remove Lock");
    m_mybutton2->SetText(L"Lock");
    m_mybutton3->SetText(L"Un-Lock");
    m_mybutton4->SetText(L"Create");

    m_custom_label5->SetTextColor(0xffffff);
    m_custom_label6->SetTextColor(0xffffff);
    m_custom_label7->SetTextColor(0xffffff);
    m_custom_label8->SetTextColor(0xffffff);

    //m_custom_label->SetGWndSize(this->GetBounds().size.width - 18, this->GetBounds().size.height - 48);
    //m_custom_label->MoveGWnd(m_custom_label->GetBounds().pos.x - 6, m_custom_label->GetBounds().pos.y-6);
    //m_custom_label1->SetGWndSize(m_custom_label->GetBounds().size.width - 5, m_custom_label->GetBounds().size.height - 5);
    //m_custom_label1->MoveGWnd(m_custom_label->GetBounds().pos.x, m_custom_label->GetBounds().pos.y);

    Frame->SetGWndSize(this->GetBounds().size.width - 20, this->GetBounds().size.height - 48);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 38);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
    m_custom_label1->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
    m_custom_label1->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);

    std::n_wstring msg(L"Password Here");
    std::n_wstring msg1(L"New Password");
    std::n_wstring msg2(L"Repeat Password");

    m_edit->SetTooltipText(&msg);
    m_edit->SetToolTipSetting(0x80);
    m_edit2->SetTooltipText(&msg1);
    m_edit2->SetToolTipSetting(0x80);
    m_edit3->SetTooltipText(&msg2);
    m_edit3->SetToolTipSetting(0x80);
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    this->ShowGWnd(false);
    ResetPosition();
    return true;
}

void CIFCharLock::On_BtnClicklock()
{
    if (m_edit->GetNText().empty())
    {
        g_pCGInterface->ShowMessage_Warning(L"Sorry, you have entered an invalid password.");
        return;
    }

    if (m_edit->GetNText().length() > 4)
    {
        g_pCGInterface->ShowMessage_Warning(L"Password must be 4 digits only");
        return;
    }

    for (int i = 0; i < strlen(TO_NSTRING(m_edit->GetNText()).c_str()); i++)
    {
        if (isdigit(TO_NSTRING(m_edit->GetNText()).c_str()[i]) == 0)
        {
            g_pCGInterface->ShowMessage_Warning(L"Please insert only digits");
            return;
        }
    }

    BYTE type = 2;
    CMsgStreamBuffer buf(0x1204);
    buf << type;
    buf << std::n_string(TO_NSTRING(this->m_edit->GetNText()));
    SendMsg(buf);
    Clear();
}
void CIFCharLock::On_BtnClickUnLock()
{
    if (m_edit->GetNText().empty())
    {
        g_pCGInterface->ShowMessage_Warning(L"Sorry, you have entered an invalid password.");
        return;
    }

    if (m_edit->GetNText().length() > 4)
    {
        g_pCGInterface->ShowMessage_Warning(L"Password must be 4 digits only");
        return;
    }

    for (int i = 0; i <strlen(TO_NSTRING(m_edit->GetNText()).c_str()); i++)
    {
        if (isdigit(TO_NSTRING(m_edit->GetNText()).c_str()[i]) == 0)
        {
            g_pCGInterface->ShowMessage_Warning(L"Please insert only digits");
            return;
        }
    }

    BYTE type = 1;
    CMsgStreamBuffer buf(0x1204);
    buf << type;
    buf << std::n_string(TO_NSTRING(this->m_edit->GetNText()));
    SendMsg(buf);
    Clear();
}

void CIFCharLock::OnClick_RemoveLock()
{
    if (m_edit->GetNText().empty())
    {
        g_pCGInterface->ShowMessage_Warning(L"Sorry, you have entered an invalid password.");
        return;
    }

    if (m_edit->GetNText().length() > 4)
    {
        g_pCGInterface->ShowMessage_Warning(L"Password must be 4 digits only");
        return;
    }

    for (int i = 0; i < strlen(TO_NSTRING(m_edit->GetNText()).c_str()); i++)
    {
        if (isdigit(TO_NSTRING(m_edit->GetNText()).c_str()[i]) == 0)
        {
            g_pCGInterface->ShowMessage_Warning(L"Please insert only digits");
            return;
        }
    }

    BYTE type = 3;
    CMsgStreamBuffer buf(0x1204);
    buf << type;
    buf << std::n_string(TO_NSTRING(this->m_edit->GetNText()));
    SendMsg(buf);
    Clear();
}

void CIFCharLock::OnClick_CreateLock()
{
    if (m_edit2->GetNText().empty()|| m_edit3->GetNText().empty())
    {
        g_pCGInterface->ShowMessage_Warning(L"Sorry, you have entered an invalid password.");
        return;
    }

    if (m_edit2->GetNText().length() > 4 || m_edit3->GetNText().length() > 4)
    {
        g_pCGInterface->ShowMessage_Warning(L"Password must be 4 digits only");
        return;
    }

    for (int i = 0; i < strlen(TO_NSTRING(m_edit2->GetNText()).c_str()); i++)
    {
        if (isdigit(TO_NSTRING(m_edit2->GetNText()).c_str()[i]) == 0)
        {
            g_pCGInterface->ShowMessage_Warning(L"Please insert only digits");
            return;
        }
    }

    for (int i = 0; i < strlen(TO_NSTRING(m_edit3->GetNText()).c_str()); i++)
    {
        if (isdigit(TO_NSTRING(m_edit3->GetNText()).c_str()[i]) == 0)
        {
            g_pCGInterface->ShowMessage_Warning(L"Please insert only digits");
            return;
        }
    }

    if (strcmp(TO_NSTRING(m_edit2->GetNText()).c_str(), TO_NSTRING(m_edit3->GetNText()).c_str()) != 0)
    {
        g_pCGInterface->ShowMessage_Warning(L"Please make sure your passwords match");
        return;
    }

    BYTE type = 4;
    CMsgStreamBuffer buf(0x1204);
    buf << type;
    buf << std::n_string(TO_NSTRING(this->m_edit2->GetNText()));
    SendMsg(buf);
    Clear();
}
void CIFCharLock::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 750;
    this->MoveGWnd(PosX, PosY);
}

void CIFCharLock::Clear()
{
    m_edit->SetText(L"");
    m_edit2->SetText(L"");
    m_edit3->SetText(L"");
}
