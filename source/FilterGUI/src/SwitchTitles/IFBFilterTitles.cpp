#include "IFBFilterTitles.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include "TextStringManager.h"
#include "Game.h"
#include "GInterface.h"
#include "ICPlayer.h"
#include "SRO_MSG_DEF.h"
#include "CharacterDependentData.h"
#include "IFChatViewer.h"
#include "StdAfx.h"
#include "IFTextBox.h"
#include "LinkedScroll.h"
#include "IFListCtrl.h"
#include "IFSystemMessage.h"
#include <MainMenu/IFBFilterMainMenu.h>
#include <BSLib/multiBYTE.h>
#include <sstream>
#include <NetProcessIn.h>
#include <ANetwork/CPSMission.h>

#define BFILTERTITLES_FRAME 10
#define BFILTERTITLES_TITLE 2
#define BFILTERTITLES_VSCROLL 3
#define BFILTERTITLES_APPLY_BUTTON 4
#define BFILTERTITLES_REFRESH_BUTTON 5
#define BFILTERTITLES_TEXTBOX 6
#define BFILTERTITLES_LABLE_1 7
#define BFILTERTITLES_LABLE_2 8

#define BFILTERTITLES_SUBJ 9
#define BFILTERTITLES_STRETCH 10
#define TIMER_UPDATE_PER_SECOND 15

std::map<std::n_wstring, BYTE > CurTitles;
std::map<std::n_wstring, int> TitlesColors;
std::map<std::n_wstring, BYTE>::iterator iter;
std::map<std::n_wstring, int>::iterator Coloriter;

GFX_IMPLEMENT_DYNCREATE(CIFSwitchTitle, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSwitchTitle, CIFMainFrame)
ONG_COMMAND(BFILTERTITLES_REFRESH_BUTTON, &CIFSwitchTitle::On_BtnClick)
ONG_COMMAND(BFILTERTITLES_APPLY_BUTTON, &CIFSwitchTitle::On_BtnClick1)
ONG_BSSig_u38(2, 0x806D, BFILTERTITLES_TEXTBOX, &CIFSwitchTitle::OnListChatThing)
GFX_END_MESSAGE_MAP()

static int RefreshTimes = 0;

CIFSwitchTitle::CIFSwitchTitle(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFSwitchTitle::~CIFSwitchTitle(void)
{
   // printf("> " __FUNCTION__ "\n");
}

bool CIFSwitchTitle::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT RefReshRect = { 266,342,111,24 };    
    RECT TextRect = { 27,28,365,343 };
    RECT labRect = { 220,51,16,23 };
    RECT lab2Rect = { 250,51,16,23 };
    RECT lab3Rect = { 0,0,300,300 };
    RECT scrollRect = { 602,88,16,209 };

    m_mybutton = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), RefReshRect, BFILTERTITLES_REFRESH_BUTTON, 0);
    m_mybutton2 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), RefReshRect, BFILTERTITLES_APPLY_BUTTON, 0);
    m_mybutton->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj",0,0);
    m_mybutton2->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);

    m_textbox = (CIFTextBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFTextBox), TextRect, BFILTERTITLES_TEXTBOX, 0);

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), labRect, BFILTERTITLES_LABLE_1, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lab2Rect, BFILTERTITLES_LABLE_2, 0);
    Frame = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lab3Rect, BFILTERTITLES_FRAME, 0);
    Frame->TB_Func_13("interface\\gui\\titles_frame.ddj", 0, 0);

    m_vericalSroll = (CIFVerticalScroll*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFVerticalScroll), scrollRect, BFILTERTITLES_VSCROLL, 0);

    m_mybutton->MoveGWnd(m_mybutton->GetPos().x - 95, m_mybutton->GetPos().y - 85);
    m_mybutton2->MoveGWnd(m_mybutton->GetPos().x - 150, m_mybutton->GetPos().y);

    m_custom_label2->SetGWndSize(175, 16);
    m_custom_label1->SetGWndSize(70, 20);
    m_custom_label1->MoveGWnd(m_custom_label1->GetPos().x - 200, m_custom_label1->GetPos().y - 5);
    m_custom_label2->MoveGWnd(m_custom_label2->GetPos().x - 152, m_custom_label1->GetPos().y + 3);

    m_textbox->SetGWndSize(235,130);
    m_textbox->MoveGWnd(Frame->GetPos().x + 28, Frame->GetPos().y + 110);

    m_vericalSroll->MoveGWnd(Frame->GetPos().x + Frame->GetSize().width - 32, m_vericalSroll->GetBounds().pos.y + 35);
    m_vericalSroll->sub_65A500(m_vericalSroll->GetSize().height - 120);
    m_vericalSroll->SetGWndSize(m_vericalSroll->GetBounds().size.width, m_vericalSroll->GetSize().height - 120);

    m_mybutton->SetText(L"Apply");
    m_mybutton2->SetText(L"Remove");
    m_custom_label1->SetText(L"Curent Title");
    m_custom_label1->SetTextColor(0xf1dd38);

    m_textbox->N00000608 = this;
    m_textbox->m_HeightInLines = 9;
    m_textbox->SetLineHeight(14);
    m_textbox->sub_638B50(1);
    m_textbox->sub_64E380(1);
    m_textbox->sub_638C70(1);
    m_textbox->SetHightlineLine(true);
    m_textbox->sub_638D50(1);
    m_textbox->SetHighlightColor(0x28ebd4);
    m_textbox->sub_638D40(1);
    m_textbox->LinkScrollbar(m_vericalSroll);
    m_vericalSroll->sub_65A5C0(999);
    //test
    m_textbox->m_FontTexture.sub_8B4400(0,0);
    m_textbox->m_FontTexture.sub_8B4750(0);
    m_textbox->TB_Func_5(0);
    m_textbox->TB_Func_6(0);

    std::n_wstring msg(L"Your current title name");
    m_custom_label2->SetTooltipText(&msg);
    m_custom_label2->SetToolTipSetting(0x80);

    m_title->SetText(L"Title Manager");
    m_title->BringToFront();
    m_close->BringToFront();
    m_textbox->BringToFront();
    m_vericalSroll->BringToFront();
    m_custom_label1->BringToFront();
    m_custom_label2->BringToFront();
    m_mybutton->BringToFront();
    m_mybutton2->BringToFront();
 
    this->ShowGWnd(false);
    ResetPosition();
    CreateThread(NULL, 0, UpdateTitles, NULL, 0, 0);
    return true;
}

void CIFSwitchTitle::OnUpdate()
{
}

DWORD WINAPI CIFSwitchTitle::UpdateTitles(LPVOID lpParam) {
    while (true) {
        CMsgStreamBuffer buf(0x1200);
        SendMsg(buf);
        CIFMainMenu::SwitchTitleGUI->m_custom_label2->SetText(L"");
        Sleep(5 * 60000);
    }
}
void CIFSwitchTitle::OnListChatThing(int a1, int a2) {
    printf("%s(%d, %d)\n", __FUNCTION__, a1, a2);

    CIFListCtrl* pList;
    pList = m_textbox;

    CIFListCtrl::SLineOfText* line = pList->sub_63A940();

    std::n_wstring str;
    line->m_font->GetText(&str);

    if (str.empty())
        return;

    m_custom_label2->SetText(str.c_str());

    unsigned char ID = 0;

    Coloriter = TitlesColors.find(m_custom_label2->GetText());
    if (Coloriter != TitlesColors.end())
    {
        m_custom_label2->SetTextColor(Coloriter->second);
    }
}

void CIFSwitchTitle::On_BtnClick()
{
    if (m_custom_label2->GetNText().length() <= 0)
    {
        g_pCGInterface->ShowMessage_Warning(L"Cannot set null title");
        return;
    }

    iter = CurTitles.find(m_custom_label2->GetText());
    if (iter != CurTitles.end())
    {
        if (iter->second != CPSMission::CurHawn)
        {
            CMsgStreamBuffer buf(0x1201);
            buf << iter->second;
            SendMsg(buf);
        }
        else
        {
            g_pCGInterface->ShowMessage_Warning(L"Your already using this title");
            return;
        }
    }
   // m_custom_label1->SetText(TO_WSTRING(GetGuildName()).c_str());
}

std::string CIFSwitchTitle::GetGuildName() {
   int Hunter = MEMUTIL_READ_BY_PTR_OFFSET(g_pCICPlayer, 0x7F8, DWORD);
    std::string Res;
   if (Hunter < 8) {
       Res = MEMUTIL_READ_BY_PTR_OFFSET(g_pCICPlayer, 0x7F8, std::string);
    } else {
        Res = MEMUTIL_READ_BY_PTR_OFFSET(g_pCICPlayer, 0x7E8, std::string);
    }
    return Res;
}
void CIFSwitchTitle::On_BtnClick1() {

    if (0 != CPSMission::CurHawn) {
        BYTE REMOVE = 0;
        CMsgStreamBuffer buf(0x1201);
        buf << REMOVE;
        SendMsg(buf);
    } else {
        g_pCGInterface->ShowMessage_Warning(L"Your already removed your title");
        return;
    }
}

void CIFSwitchTitle::OnClick_Exit()
{
    this->OnCloseWnd();
    m_custom_label2->SetText(L"");
    m_textbox->m_LinesOfHistory = 0;
}

void CIFSwitchTitle::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 750;
    this->MoveGWnd(PosX, PosY);
}

bool CIFSwitchTitle::TitExists(BYTE ID)
{
    for (std::map<std::n_wstring, BYTE>::iterator iter = CurTitles.begin(); iter != CurTitles.end(); iter++)
    {
        if (iter->second == ID)
            return true;
    }
    return false;
}

bool CIFSwitchTitle::TitColorExists(const wchar_t* title)
{
    for (std::map<std::n_wstring,int>::iterator iter = TitlesColors.begin(); iter != TitlesColors.end(); iter++)
    {
        if (iter->first == title)
            return true;
    }
    return false;
}

void CIFSwitchTitle::AddTitle(const wchar_t* title, BYTE ID, int Color)
{

    if (!CIFSwitchTitle::TitColorExists(title))
    {
        TitlesColors.insert(std::pair<std::n_wstring,int>(title, Color));
    }
    else
    {
        for (std::map<std::n_wstring, int>::iterator iter = TitlesColors.begin(); iter != TitlesColors.end(); iter++)
        {
            if (iter->first == title)
            {
                TitlesColors.erase(iter->first);
                TitlesColors.insert(std::pair<std::n_wstring, int>(title, Color));
                return;
            }
        }
    }

    if (!CIFSwitchTitle::TitExists(ID))
    {
        CurTitles.insert(std::pair<std::n_wstring, BYTE>(title, ID));
    }
    else
    {
        for (std::map<std::n_wstring, BYTE>::iterator iter = CurTitles.begin(); iter != CurTitles.end(); iter++)
        {
            if (iter->second == ID)
            {
                CurTitles.erase(iter->first);
                CurTitles.insert(std::pair<std::n_wstring, BYTE>(title, ID));
                return;
            }
        }
    }
}
