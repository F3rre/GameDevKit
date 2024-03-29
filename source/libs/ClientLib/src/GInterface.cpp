#include "StdAfx.h"
#include "GInterface.h"
#include "IFflorian0Guide.h"
#include "IFNotify.h"
#include "IFChatViewer.h"
#include "IFNotify.h"
#include "GlobalDataManager.h"

#include <remodel/MemberFunctionHook.h>
#include <MainMenu/IFBFilterMainMenu.h>

void CGInterface::OnNotifyAction(int a1, unsigned short action, int color, int a4, int a5)
{
    reinterpret_cast<void(__thiscall*)(CGInterface*, int, unsigned short, int, int, int)>(0x00778190)(this, a1, action, color, a4, a5);
}

int CGInterface::sub_799970(void)
{
    return reinterpret_cast<int(__thiscall*)(CGInterface*)>(0x00799970)(this);
}

void CGInterface::ShowLogMessage(int color, const wchar_t* msg) {
    GetSystemMessageView()->WriteMessage(0xff, color, msg, 0, 1);
}
CGInterface* CGInterface::GetInterface(void)
{
    return *reinterpret_cast<CGInterface**>(0x0110F80C);
}


HOOK_ORIGINAL_MEMBER(0x0079D5B0, &CGInterface::ToggleActionWnd);
void CGInterface::ToggleActionWnd() {
    // If MainPopup is visible and page 'action' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_ACTION)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    } else {
        m_mainPopup->ShowGWnd(true);
        m_mainPopup->ShowSubPage(GDR_ACTION);
        FUN_0079a7e0(m_mainPopup);
    }
}

HOOK_ORIGINAL_MEMBER(0x0079B0B0, &CGInterface::ToggleApprenticeshipWnd);
void CGInterface::ToggleApprenticeshipWnd() {
    // If MainPopup is visible and page 'apprenticeship' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_APPRENTICESHIP)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
        g_CGlobalDataManager->FUN_008cbac0(GDR_APPRENTICESHIP);
    } else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetApprenticeShip()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_APPRENTICESHIP);
        }
        FUN_0079a7e0(m_mainPopup);
        g_CGlobalDataManager->FUN_008cbac0(GDR_APPRENTICESHIP);
    }
}

HOOK_ORIGINAL_MEMBER(0x0079ACE0, &CGInterface::TogglePlayerInfoWnd);
void CGInterface::TogglePlayerInfoWnd() {
    // If MainPopup is visible and page 'playerinfo' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_PLAYERINFO)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    } else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetPlayerInfo()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_PLAYERINFO);
        }
        FUN_0079a7e0(m_mainPopup);
    }
}

void CGInterface::RenderToggle_GDR_GAMEGUIDE() {
    return reinterpret_cast<void (__thiscall *)(void *)>(0x0079F690)(this);
}

HOOK_ORIGINAL_MEMBER(0x0079B020, &CGInterface::ToggleInventoryWnd);
void CGInterface::ToggleInventoryWnd() {
    // If MainPopup is visible and page 'inventory' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_INVENTORY)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    } else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetInventory()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_INVENTORY);
        }
        FUN_0079a7e0(m_mainPopup);
    }
}

HOOK_ORIGINAL_MEMBER(0x0079ad70, &CGInterface::ToggleEquipmentWnd);
void CGInterface::ToggleEquipmentWnd() {
    // If MainPopup is visible and page 'equipment' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_INVENTORY)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    } else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetEquipment()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_INVENTORY);
        }
        FUN_0079a7e0(m_mainPopup);
    }
}

HOOK_ORIGINAL_MEMBER(0x0079AE90, &CGInterface::TogglePartyWnd);
void CGInterface::TogglePartyWnd() {
    // If MainPopup is visible and page 'party' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_PARTY)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
        g_CGlobalDataManager->FUN_008cbac0(GDR_PARTY);
    } else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetParty()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_PARTY);
        }
        FUN_0079a7e0(m_mainPopup);
        g_CGlobalDataManager->FUN_008cbac0(GDR_PARTY);
    }
}

HOOK_ORIGINAL_MEMBER(0x0079AE00, &CGInterface::ToggleSkillWnd);
void CGInterface::ToggleSkillWnd() {
    // If MainPopup is visible and page 'skill' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_SKILL)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    } else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetSkill()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_SKILL);
        }
        FUN_0079a7e0(m_mainPopup);
    }
}

HOOK_ORIGINAL_MEMBER(0x0079af20, &CGInterface::ShowInventoryWnd);
void CGInterface::ShowInventoryWnd() {
    m_mainPopup->ShowGWnd(true);
    if (!m_mainPopup->GetInventory()->IsVisible()) {
        m_mainPopup->ShowSubPage(GDR_INVENTORY);
    }
    FUN_0079a7e0(m_mainPopup);
}

HOOK_ORIGINAL_MEMBER(0x0079af70, &CGInterface::ShowApprenticeshipWnd);
void CGInterface::ShowApprenticeshipWnd() {
    m_mainPopup->ShowGWnd(true);
    if (!m_mainPopup->GetApprenticeShip()->IsVisible()) {
        m_mainPopup->ShowSubPage(GDR_APPRENTICESHIP);
    }
    FUN_0079a7e0(m_mainPopup);
}

void CGInterface::ToggleMainPopup() {
    m_mainPopup->ShowGWnd(!m_mainPopup->IsVisible());
    FUN_0079a7e0(m_mainPopup);
}

void CGInterface::RenderToggle_WORLDMAP_GUIDE() {
    return reinterpret_cast<void (__thiscall *)(void *)>(0x0079ABE0)(this);
}

void CGInterface::Render_GDR_AUTO_POTION(bool visible) {
    return reinterpret_cast<void (__thiscall *)(void *, bool)>(0x0079C750)(this, visible);
}

void CGInterface::CreateFlorian0Event() {
    CIFMainMenu::MenuIcon = GetAlarmManager()->GetGuide(GUIDE_MAINMENU);
    CIFMainMenu::DiscordIcon = GetAlarmManager()->GetGuide(GUIDE_DISCORD);
    CIFMainMenu::FacebookIcon = GetAlarmManager()->GetGuide(GUIDE_FACEBOOK);


    RECT MenuRect = { 0,0,165,420 };
    RECT GrantRect = { 0,0,400,200 };
    RECT SwitchRect = { 0,0,300,300 };
    RECT UniqueRect = { 0,0,470,370 };
    RECT EventRect = { 0,0,395,375 };
    RECT CharlRect = { 0,0,325,205 };
    RECT CustomRankRect = { 0,0,405,415 };
    RECT DmgRect = { 0,0,220,224 };
    RECT FTWRect = { 0,0,187,165 };
    RECT SurvRect = { 0,0,187,165 };
    RECT CustomTitleRect = { 0,0,400,200 };
    RECT NoitfyRect = { 0,0,395,375 };
    RECT EventGuiRect = { 0,0,492,300 };
    RECT EventGuiTRect = {0,0,325,205};
    RECT CharMenuRect = { 0,0,279,237 };

    CIFMainMenu::MenuGui = (CIFMainMenu*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFMainMenu), MenuRect, MainForm, 0);
    CIFMainMenu::GrantNameGUI = (CIFGrantName*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFGrantName), GrantRect, GrantName, 0);
    CIFMainMenu::SwitchTitleGUI = (CIFSwitchTitle*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFSwitchTitle), SwitchRect, SwitchTitles, 0);
    CIFMainMenu::UniqueLogGUI = (CIFUniqueLog*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLog), UniqueRect, UniqueLog, 0);
    CIFMainMenu::EventTimeGUI = (CIFEventTime*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTime), EventRect, EventTime, 0);
    CIFMainMenu::CharLockGUI = (CIFCharLock*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFCharLock), CharlRect, CharLock, 0);
    CIFMainMenu::CustomRankGUI = (CIFCustomRank*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFCustomRank), CustomRankRect, CustomRank, 0);
    CIFMainMenu::DmgMeterGui = (CIFDMGMeter*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFDMGMeter), DmgRect, DMGMeter, 0);
    CIFMainMenu::SurvGuiGUI = (CIFSurvCounter*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFSurvCounter), SurvRect, SurvKillsCounter, 0);
    CIFMainMenu::FtwCunterGUI = (CIFFTWCounter*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFFTWCounter), FTWRect, FtwKillsCounter, 0);
    CIFMainMenu::CustomTitleGUI = (CIFCustomTitle*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFCustomTitle), CustomTitleRect, CustomTitleUD, 0);
    CIFMainMenu::PurbleNoitfy = (CIFNotify*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFNotify), NoitfyRect, PurbleNotify, 0);
    CIFMainMenu::OrangeNoitfy = (CIFNotify*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFNotify), NoitfyRect, OrangeNotify, 0);
    CIFMainMenu::EventMenu = (CIFEventMenu*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventMenu), EventGuiRect, EventMenuGui, 0);
    CIFMainMenu::CharMenu = (CIFCharacterMenu*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFCharacterMenu), CharMenuRect, CharMenuGui,0);
    //CIFMainMenu::EventTeam=(CIFEve)

    CIFMainMenu::OrangeNoitfy->SetEdgeTextures(
        "interface\\ifcommon\\cop_notice_edge2.ddj",
        "interface\\ifcommon\\cop_notice_edge.ddj",
        "interface\\ifcommon\\cop_notice_edge2.ddj",
        "interface\\ifcommon\\cop_notice_edge.ddj");

    CIFMainMenu::OrangeNoitfy->SetCornerTextures("interface\\ifcommon\\cop_notice_corner.ddj");
    CIFMainMenu::OrangeNoitfy->SetYPosition(40);
    CIFMainMenu::OrangeNoitfy->SetColor(255, 99, 71);

    CIFMainMenu::PurbleNoitfy->SetEdgeTextures(
        "interface\\ifcommon\\coq_notice_edge2.ddj",
        "interface\\ifcommon\\coq_notice_edge.ddj",
        "interface\\ifcommon\\coq_notice_edge2.ddj",
        "interface\\ifcommon\\coq_notice_edge.ddj");

    CIFMainMenu::PurbleNoitfy->SetCornerTextures("interface\\ifcommon\\coq_notice_corner.ddj");
    CIFMainMenu::PurbleNoitfy->SetYPosition(70);
    CIFMainMenu::PurbleNoitfy->SetColor(75, 0, 130);



}

CAlramGuideMgrWnd *CGInterface::GetAlarmManager() {
    return m_IRM.GetResObj<CAlramGuideMgrWnd>(GDR_ALRAM_GUIDE_MGR_WND, 1);
}

bool CGInterface::OnCreateIMPL(long ln) {

    BeforeOnCreate();

    bool b = reinterpret_cast<bool (__thiscall *)(CGInterface *, long)>(0x0078c910)(this, ln);

    AfterOnCreate();

    return b;
}

void CGInterface::BeforeOnCreate() {

}

void CGInterface::AfterOnCreate() {
    CreateFlorian0Event();
}

void CGInterface::ShowMessage_Quest(const std::n_wstring &msg) {
    CIFNotify *notify = m_IRM.GetResObj<CIFNotify>(GDR_UPDATE_QUEST_INFO, 1);
    notify->ShowMessage(msg);
}

void CGInterface::ShowMessage_Notice(const std::n_wstring &msg) {
    CIFNotify *notify = m_IRM.GetResObj<CIFNotify>(GDR_NOTICE, 1);
    notify->ShowMessage(msg);
}

void CGInterface::ShowMessage_Warning(const std::n_wstring &msg) {
    CIFNotify *notify = m_IRM.GetResObj<CIFNotify>(GDR_WARNING_WND, 1);
    notify->ShowMessage(msg);
}


int CGInterface::Get_SelectedObjectId() {
    return this->m_selectedObjectId;
}

CIFTimerWnd *CGInterface::Get_TimerWindow() {
    return this->m_timerWindow;
}

CIFQuickStateHalfWnd *CGInterface::Get_QuickStateHalfWnd() {
    return this->N00002637;
}

CIF_NPCWindow *CGInterface::Get_GDR_NPCWINDOW() {
    return (CIF_NPCWindow *) this->m_IRM.GetResObj(GDR_NPCWINDOW, 1);
}

HOOK_ORIGINAL_MEMBER(0x00798D00, &CGInterface::GetMainPopup);
CIFMainPopup *CGInterface::GetMainPopup() {
    return (CIFMainPopup *) this->m_IRM.GetResObj(GDR_MAINPOPUP, 1);
}

CIFStorageRoom *CGInterface::Get_GDR_STORAGEROOM() {
    return (CIFStorageRoom *) this->m_IRM.GetResObj(GDR_STORAGEROOM, 1);
}

CIFStorageRoom *CGInterface::Get_GDR_GUILDSTORAGEROOM() {
    return (CIFStorageRoom *) this->m_IRM.GetResObj(GDR_GUILDSTORAGEROOM, 1);
}

void CGInterface::WriteErrorMessage(byte errorType, unsigned __int16 errorCode, int colorARGB, int a5, int a6) {
    return reinterpret_cast<
            void (__thiscall *)(void *, byte, unsigned __int16, int, int, int)
            >(0x00778190)(this, errorType, errorCode, colorARGB, a5, a6);
}

void CGInterface::WriteSystemMessage(eLogType level, const wchar_t *str) {
    reinterpret_cast<void (__thiscall *)(CGInterface *, eLogType, const wchar_t *)>(0x007781B0)(this, level, str);
}

void CGInterface::sub_787C10(SChatMetaData &meta) {
    reinterpret_cast<void (__thiscall *)(CGInterface *, SChatMetaData *)>(0x787C10)(this, &meta);
}

int CGInterface::TryParseChatCommands(const wchar_t *text, RECT &r, std::vector<void *> &v) {
    return reinterpret_cast<
            int (__thiscall *)(CGInterface *, const wchar_t *, RECT *, std::vector<void *> *)
            >(0x0078BEA0)(this, text, &r, &v);
}

void CGInterface::ToggleQuestNew() {
    reinterpret_cast<void (__thiscall *)(CGInterface *)>(0x007990e0)(this);
}

CNIFCommunityWnd *CGInterface::GetCommunityWnd() {
    return reinterpret_cast<CNIFCommunityWnd *(__thiscall *)(CGInterface *)>(0x007994f0)(this);
}

void CGInterface::FUN_00777c30(ChatType type, const wchar_t *message, D3DCOLOR color, int a5) {
    CIFChatViewer *chatViewer = m_IRM.GetResObj<CIFChatViewer>(GDR_CHATVIEWER, 1);
    chatViewer->FUN_007aca30(type, color, message, 0, a5);
}

void CGInterface::FUN_00778a10(int a2, const wchar_t *message, D3DCOLOR color) {
    reinterpret_cast<
            void (__thiscall *)(CGInterface *, int, const wchar_t *, D3DCOLOR)
            >(0x00778a10)(this, a2, message, color);
}

void CGInterface::FUN_00777cf0(const std::n_wstring &recipient) {
    reinterpret_cast<void (__thiscall *)(CGInterface *, const std::n_wstring *)>(0x00777cf0)(this, &recipient);
}

CIFSystemMessage *CGInterface::GetSystemMessageView() {
    return m_IRM.GetResObj<CIFSystemMessage>(GDR_SYSTEM_MESSAGE_VIEW, 1);
}

void CGInterface::FUN_0079a7e0(CGWndBase *pGWnd) const {
    reinterpret_cast<void (__thiscall *)(const CGInterface *, CGWndBase *)>(0x0079a7e0)(this, pGWnd);
}

