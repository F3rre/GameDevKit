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
public:
    CIFStatic* Frame;
    CIFVerticalScroll* m_vericalSroll;

    CIFStatic* EventText;
    CIFEventMenuList* m_slot1;
};