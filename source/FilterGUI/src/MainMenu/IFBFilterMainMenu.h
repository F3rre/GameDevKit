#pragma once
#include "IFMainFrame.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include "UniqueLog/IFBFilterUniqueLog.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <ICPlayer.h>
#include "GrantName/IFBFilterGrantName.h"
#include "CharacterLock/IFBFilterCharLock.h"
#include "EventTime/IFBFilterEventTime.h"
#include "ANetwork/CPSMission.h"
#include "CustomRank/IFBFilterRank.h"

#include "SwitchTitles/IFBFilterTitles.h"
#include "PlayerChest/IFBFilterChest.h"
#include "UniquesDps/IFBFilterDMGMeter.h"
#include "CustomTitle/IFBFilterCustomTitle.h"
#include "KillCounter/IFBFilterSurvivalArena.h"
#include "KillCounter/IFBFilterFortressKillsCounter.h"
#include <IFflorian0Guide.h>
#include <ChangeLog/IFBFilterChangeLog.h>
#include <IFNotify.h>

class CIFMainMenu : public CIFMainFrame
{
    GFX_DECLARE_DYNCREATE(CIFMainMenu)
        GFX_DECLARE_MESSAGE_MAP(CIFMainMenu)

public:
    CIFMainMenu(void);
    ~CIFMainMenu(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void ResetPosition();
private:
    void On_BtnClick_1();
    void On_BtnClick_2();
    void On_BtnClick_3();
    void On_BtnClick_4();
    void On_BtnClick_5();
    void On_BtnClick_6();
    int OnChar(UINT, UINT, UINT);
    void On_Btn_turkishLang();
    void On_Btn_EnglishLang();
    void OnChangeLogButton();

public:
    CIFStatic* LAB_TITLES;
    CIFStatic* LAB_TITLES1;
    CIFStatic* LAB_TITLES2;
    CIFStatic* LAB_TITLES3;
    CIFStatic* LAB_TITLES4;
    CIFStatic* LAB_TITLES5;
    CIFStatic* LAB_TITLES6;

    CIFTextBox* m_textbox;
    CIFButton* m_mybutton;
    CIFButton* m_mybutton2;
    CIFButton* m_mybutton3;
    CIFButton* m_mybutton4;
    CIFButton* m_mybutton5;
    CIFButton* m_mybutton6;
    CIFButton* m_mybutton7;
    CIFButton* m_mybutton8;
    CIFButton* m_mybutton9;
    CIFButton* m_mybutton10;
    CIFButton* m_mybutton11;
    CIFButton* m_mybutton12;
    CIFButton* m_mybutton13;
    CIFButton* m_mybutton14;
    CIFButton* m_mybutton15;
    CIFButton* m_mybutton16;
    CIFButton* m_mybutton17;
    CIFButton* m_mybutton18;
    CIFButton* m_mybutton19;
    CIFButton* m_mybutton20;
    CIFStatic* m_custom_label;
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;
    CIFStatic* m_custom_label6;
    CIFStatic* m_custom_label7;
    CIFStatic* m_custom_label8;
    CIFStatic* m_custom_label9;
    CIFStatic* m_custom_label10;
    CIFStatic* m_custom_label11;
    CIFStatic* m_custom_label12;
    CIFStatic* m_custom_label13;
    CIFStatic* m_custom_label14;
    CIFStatic* m_custom_label15;
    CIFStatic* m_custom_label16;
    CIFStatic* m_custom_label17;
    CIFStatic* m_custom_label18;
    CIFStatic* m_custom_label19;
    CIFStatic* m_custom_label20;
    CIFStatic* m_custom_label21;
    CIFStatic* m_custom_label22;
    CIFStatic* m_custom_label23;
    CIFStatic* m_custom_label24;
    CIFStatic* m_custom_label25;
    CIFStatic* Frame;
    CIFDragableArea* HandleBar; //0x07B4

public:
    static CIFMainMenu* MenuGui;
    static CIFGrantName* GrantNameGUI;
    static CIFSwitchTitle* SwitchTitleGUI;
    static CIFUniqueLog* UniqueLogGUI;
    static CIFEventTime* EventTimeGUI;
    static CIFCharLock* CharLockGUI;
    static CIFCustomRank* CustomRankGUI;
    static CIFPlayerChest* ChestGUI;
    static CIFDMGMeter* DmgMeterGui;
    static CIFCustomTitle* CustomTitleGUI;
    static CIFSurvCounter* SurvGuiGUI;
    static CIFFTWCounter* FtwCunterGUI;
    static CGWnd* ReloadIcon;
    static CGWnd* MenuIcon;
    static CGWnd* DiscordIcon;
    static CGWnd* FacebookIcon;
    static CIFChangeLog* ChangeLogGui;
    static CIFNotify* PurbleNoitfy;
    static CIFNotify* OrangeNoitfy;

};
