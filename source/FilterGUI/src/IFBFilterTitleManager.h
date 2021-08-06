#pragma once
#include "IFMainFrame.h"
#include "IFChatViewer.h"
#include "IFBFilterTitles.h"
#include "IFBFilterCustomTitle.h"


class CIFTitleManager : public CIFMainFrame
{
    GFX_DECLARE_DYNCREATE(CIFTitleManager)
        GFX_DECLARE_MESSAGE_MAP(CIFTitleManager)

public:
    CIFTitleManager(void);
    ~CIFTitleManager(void);

    bool OnCreate(long ln) override;
    void OnUnknownStuff();
    void ActivateTabPage(BYTE page);
    void OnUpdate() override;
    void ResetPosition();
public:
    /// Internal constants
    static const int numberOfTabs = 2;
    static const int tabWidth = 90;
    static const int tabHeight = 24;
    static const int tabMarginLeft = 55;
    static const int tabFirstId = 100;

    CIFFrame* Frame;
    CIFWnd* NormalTitle;
    CIFSwitchTitle* Switch;
    CIFCustomTitle* Custom;
    CIFSelectableArea** m_pTabs;
};
