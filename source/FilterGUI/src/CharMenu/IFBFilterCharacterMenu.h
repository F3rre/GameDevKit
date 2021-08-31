#pragma once
#include "IFMainFrame.h"


class CIFCharacterMenu : public CIFMainFrame
{
    GFX_DECLARE_DYNCREATE(CIFCharacterMenu)
        GFX_DECLARE_MESSAGE_MAP(CIFCharacterMenu)

public:
    CIFCharacterMenu(void);
    ~CIFCharacterMenu(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void ResetPosition();
public:
    CIFStatic* m_rank_pciture;
    CIFStatic* m_job_picture;
    CIFStatic* m_serverrank_picture;
    CIFStatic* m_guild_pricture;
    CIFStatic* m_honor_picture;





    CIFStatic* m_rank_puan;
    CIFStatic* m_job_puan;
    CIFStatic* m_serverrank_puan;
    CIFStatic* m_guild_puan;
    CIFStatic* m_honor_puan;


    CIFStatic* m_arealbl;
    CIFStatic* m_area;


    CIFButton* m_playerrank;
    CIFButton* m_guildrank;
    CIFFrame* Frame;
    CIFStatic* m_bg_tile;
};