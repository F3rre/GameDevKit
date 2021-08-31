#pragma once
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include <IFEdit.h>
#include "EventMenu/IFBFilterEventMenuList.h"


class CIFEventMenu : public CIFMainFrame
{
    GFX_DECLARE_DYNCREATE(CIFEventMenu)
        GFX_DECLARE_MESSAGE_MAP(CIFEventMenu)

public:
    CIFEventMenu(void);
    ~CIFEventMenu(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void ResetPosition();
    void ClearDDJ();
private:
    void On_Register();
    void On_UnRegister();
public:
    CIFStatic* Frame;
    CIFVerticalScroll* m_vericalSroll;
    CIFButton* EventRegister;
    CIFButton* EventUnRegister;
    CIFStatic* EventText;
    CIFEventMenuList* m_slot1;
    std::n_wstring SelectedEventName;
    std::n_wstring SelectedTeam;
};