#include "IFBFilterCharLock.h"
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
//#define BFILTER_CHARLOCK_NEWLOCK_SET 27
//#define BFILTER_CHARLOCK_NEWLOCK_CONFIRM_PASSWORD_INPUT 26
//#define BFILTER_CHARLOCK_NEWLOCK_PASSWORD_INPUT 25
//#define BFILTER_CHARLOCK_NEWLOCK_CONFIRM_PASSWORD_INPUT 24
//#define BFILTER_CHARLOCK_NEWLOCK_CONFIRM_PASSWORD_LABEL 23
//#define BFILTER_CHARLOCK_NEWLOCK_PASSWORD_LABEL 22
//#define BFILTER_CHARLOCK_NEWLOCK_CONFIRM_PASSWORD_LABEL 21

#define BFILTER_CHARLOCK_NEWLOCKPASSWORD_LABEL 20
//#define BFILTER_CHARLOCK_LOCK 19
#define BFILTER_CHARLOCK_PASSWORD_INPUT 18
#define BFILTER_CHARLOCK_PASSWORD_LABEL 17
#define BFILTER_CHARLOCK_STATUS 16
//#define BFILTER_CHARLOCK_STATUS_ICON 15
//#define BFILTER_CHARLOCK_STATUS_LABEL 14

#define BFILTER_CHARLOCK_UNLOCK 13
//#define BFILTER_CHARLOCK_REMOVELOCK 12
#define BFILTER_CHARLOCK_TITLE 5
#define BFILTER_CHARLOCK_FRAME 6

GFX_IMPLEMENT_DYNCREATE(CIFCharLock, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFCharLock, CIFMainFrame)
//ONG_COMMAND(BFILTER_CHARLOCK_REMOVELOCK, &CIFCharLock::OnClick_RemoveLock)
//ONG_COMMAND(BFILTER_CHARLOCK_LOCK, &CIFCharLock::On_BtnClicklock)
ONG_COMMAND(BFILTER_CHARLOCK_UNLOCK, &CIFCharLock::On_BtnClickUnLock)
//ONG_COMMAND(BFILTER_CHARLOCK_NEWLOCK_SET, &CIFCharLock::OnClick_CreateLock)
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

    RECT lable1rect = {17,45,180,82};
    RECT lable2rect = { 33,82,148,82 };
    RECT lable5rect = { 226,120,90,23 };
    RECT lable7rect = { 103,88,164,23 };
    RECT lable10rect = { 140,41,143,34 };
    RECT lable11rect = { 10,86,91,24 };
    RECT lable12rect = { 10,153,263,29 };

    Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), lable1rect, BFILTER_CHARLOCK_FRAME, 0);
    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable2rect, BFILTER_CHARLOCK_TITLE, 0);
    m_custom_label1->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);


    m_mybutton3 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), lable5rect, BFILTER_CHARLOCK_UNLOCK, 0);

    
    m_edit = (CIFEdit*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEdit), lable7rect, BFILTER_CHARLOCK_PASSWORD_INPUT, 0);


    m_edit->m_FontTexture.sub_8B4400(1, 0);
    m_edit->m_FontTexture.sub_8B4750(1);
    m_edit->TB_Func_5(1);
    m_edit->TB_Func_6(1);


    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable10rect, BFILTER_CHARLOCK_STATUS, 0);
    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable11rect, BFILTER_CHARLOCK_PASSWORD_LABEL, 0);
    m_custom_label6 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable12rect, BFILTER_CHARLOCK_NEWLOCKPASSWORD_LABEL, 0);


    m_custom_label4->MoveGWnd(m_custom_label4->GetPos().x - 45, m_custom_label4->GetPos().y+5);


    m_mybutton3->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);


    m_mybutton3->MoveGWnd(m_mybutton3->GetPos().x - 93, m_mybutton3->GetPos().y);

    m_custom_label4->SetTextColor(0xffffff);

    m_edit->SetTextColor(0xffffff);


    m_edit->MoveGWnd(m_edit->GetBounds().pos.x + 25, m_edit->GetBounds().pos.y);


    m_edit->TB_Func_13("interface\\messagebox\\msgbox_blackbox_02.ddj", 0, 0);


    m_custom_label5->MoveGWnd(m_custom_label5->GetBounds().pos.x + 25, m_custom_label5->GetBounds().pos.y);
    m_custom_label6->MoveGWnd(m_custom_label6->GetBounds().pos.x + 20, m_custom_label6->GetBounds().pos.y);


    m_title->SetText(L"Chacacter Lock");
    m_custom_label4->SetText(L"Unlock Your Character");
    m_custom_label5->SetText(L"Pin");
    m_custom_label6->SetText(L"Click on the blank field, and type in the 6 digit code \nthat was sent to your phone.");
    m_mybutton3->SetText(L"Un-Lock");


    m_custom_label5->SetTextColor(0xffffff);
    m_custom_label6->SetTextColor(0xffd49d);



    Frame->SetGWndSize(this->GetBounds().size.width - 20, this->GetBounds().size.height - 48);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 38);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
    m_custom_label1->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
    m_custom_label1->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);

    std::n_wstring msg(L"Password Here");


    m_edit->SetTooltipText(&msg);
    m_edit->SetToolTipSetting(0x80);
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    this->ShowGWnd(false);
    ResetPosition();
    return true;
}


void CIFCharLock::On_BtnClickUnLock()
{
    if (m_edit->GetNText().empty())
    {
        g_pCGInterface->ShowMessage_Warning(L"Sorry, you have entered an invalid password.");
        return;
    }

    if (m_edit->GetNText().length() > 6)
    {
        g_pCGInterface->ShowMessage_Warning(L"Password must be 6 digits only");
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
void CIFCharLock::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 350;
    this->MoveGWnd(PosX, PosY);
}

void CIFCharLock::Clear()
{
    m_edit->SetText(L"");
}
