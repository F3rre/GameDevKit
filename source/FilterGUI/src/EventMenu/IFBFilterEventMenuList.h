#pragma once
#include "IFMainFrame.h"
#include "EventMenu/IFBFilterEventMenuSlot.h"

class CIFEventMenuList : public CIFWnd
{
    GFX_DECLARE_DYNCREATE(CIFEventMenuList)
        GFX_DECLARE_MESSAGE_MAP(CIFEventMenuList)

public:
    CIFEventMenuList(void);
    ~CIFEventMenuList(void);
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void ClearDDJ();
public:
    CIFEventMenuSlot* line1;
    CIFEventMenuSlot* line2;
    CIFEventMenuSlot* line3;
    CIFEventMenuSlot* line4;
    CIFEventMenuSlot* line5;
    CIFEventMenuSlot* line6;
    CIFEventMenuSlot* line7;
};