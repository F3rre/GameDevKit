#include "IFBFilterCharacterMenu.h"
#include <GlobalHelpersThatHaveNoHomeYet.h>
#include <ICPlayer.h>
#include "GlobalDataManager.h"
#include <TextStringManager.h>
#include <sstream>


GFX_IMPLEMENT_DYNCREATE(CIFCharacterMenu, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFCharacterMenu, CIFMainFrame)
GFX_END_MESSAGE_MAP()

CIFCharacterMenu::CIFCharacterMenu(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFCharacterMenu::~CIFCharacterMenu(void)
{
    // printf("> " __FUNCTION__ "\n");
}

bool CIFCharacterMenu::OnCreate(long ln)
{
    // printf("> " __FUNCTION__ "(%d)\n", ln);


     // Populate inherited members

    CIFMainFrame::OnCreate(ln);


    RECT rank_picture = { 13,36,100,100 };
    RECT job_picture = { 200,50,20,20 };
    RECT serverrank_picture = { 127,50,24,24 };
    RECT guild_pricture = { 127,96,20,20 };
    RECT honor_picture = { 200,96,20,20 };
    RECT arealblrect = {35,156,16,16};
    RECT arearect = {80,156,16,16};
    RECT bgtilerect = {20,40,239,173};
    RECT buttonrect = { 13,198,88,24 };


    RECT job_puan = { 228,50,16,16 };
    RECT serverrank_puan = { 159,50,16,16 };
    RECT guild_puan = { 159,96,16,16 };
    RECT honor_puan = { 228,96,16,16 };


    m_bg_tile = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), bgtilerect, 6, 0);
    m_rank_pciture = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rank_picture, 7, 0);
    m_job_picture = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), job_picture, 8, 0);
    m_serverrank_picture = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), serverrank_picture, 9, 0);
    m_guild_pricture = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), guild_pricture, 10, 0);
    m_honor_picture = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), honor_picture, 11, 0);
    m_arealbl = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), arealblrect, 12, 0);
    m_area = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), arearect, 13, 0);
    m_playerrank = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), buttonrect, 14, 0);
    m_guildrank = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), buttonrect, 15, 0);



    m_job_puan = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), job_puan, 16, 0);
    m_serverrank_puan = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), serverrank_puan, 17, 0);
    m_guild_puan = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), guild_puan, 18, 0);
    m_honor_puan = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), honor_puan, 19, 0);


    m_rank_pciture->TB_Func_13("interface\\ifcommon\\player_rank.ddj", 0, 0);
    m_job_picture->TB_Func_13("interface\\ifcommon\\job_points.ddj", 0, 0);
    m_serverrank_picture->TB_Func_13("interface\\ifcommon\\survival_points.ddj", 0, 0);
    m_guild_pricture->TB_Func_13("interface\\ifcommon\\guild_points.ddj", 0, 0);
    m_honor_picture->TB_Func_13("interface\\ifcommon\\honor_points.ddj", 0, 0);
    m_bg_tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_u.ddj", 0, 0);
    m_guildrank->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj",0,0);
    m_playerrank->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);

    m_title->MoveGWnd(m_title->GetPos().x, m_title->GetPos().y - 6);
    m_close->MoveGWnd(m_close->GetPos().x, m_close->GetPos().y - 3);
    m_guildrank->MoveGWnd(m_guildrank->GetPos().x+125,m_guildrank->GetPos().y);


    m_arealbl->SetText(L"Area:");
    m_guildrank->SetText(L"Guild Rank");
    m_playerrank->SetText(L"Player Rank");


    m_job_puan->SetText(L"0");
    m_serverrank_puan->SetText(L"0");
    m_guild_puan->SetText(L"0");
    m_honor_puan->SetText(L"0");




    std::n_wstring rankpicture(L"No Ranked");
    m_rank_pciture->SetTooltipText(&rankpicture);
    m_rank_pciture->SetToolTipSetting(0x80);



    std::n_wstring serverrankpicture(L"Player Rank Points");
    m_serverrank_picture->SetTooltipText(&serverrankpicture);
    m_serverrank_picture->SetToolTipSetting(0x80);

    std::n_wstring jobpicture(L"Job Rank Points");
    m_job_picture->SetTooltipText(&jobpicture);
    m_job_picture->SetToolTipSetting(0x80);

    std::n_wstring guildpricture(L"Guild Points");
    m_guild_pricture->SetTooltipText(&guildpricture);
    m_guild_pricture->SetToolTipSetting(0x80);

    std::n_wstring honorpicture(L"Honor Points");
    m_honor_picture->SetTooltipText(&honorpicture);
    m_honor_picture->SetToolTipSetting(0x80);


    TB_Func_13("interface\\frame\\sframe_job_wnd_", 0, 0);
    this->ShowGWnd(false);
    ResetPosition();
    return true;
}

void CIFCharacterMenu::OnUpdate()
{
    if (!g_pCICPlayer) {
        return;
    }

    m_title->SetText(g_pCICPlayer->GetCharName().c_str());

    std::wstringstream region;
    region << g_pCICPlayer->GetRegion().r;
    const std::n_wstring* nwRegionName = g_CTextStringManager->GetString(region.str().c_str());
    m_area->SetText(nwRegionName->c_str());


    //m_title->SetText(g_pCICPlayer->m_level);
}

void CIFCharacterMenu::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 350;
    this->MoveGWnd(PosX, PosY);
}