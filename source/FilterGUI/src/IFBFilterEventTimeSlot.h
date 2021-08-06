#pragma once
#include "IFMainFrame.h"

class CIFEentTimeSlot : public CIFWnd
{
    GFX_DECLARE_DYNCREATE(CIFEentTimeSlot)
        GFX_DECLARE_MESSAGE_MAP(CIFEentTimeSlot)

public:
    CIFEentTimeSlot(void);
    ~CIFEentTimeSlot(void);

    bool OnCreate(long ln) override;
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
};

