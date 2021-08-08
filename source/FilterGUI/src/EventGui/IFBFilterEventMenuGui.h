#pragma once
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include "IFEdit.h"



class CIFEventMenuGui : public CIFMainFrame
{
    GFX_DECLARE_DYNCREATE(CIFEventMenuGui)
        GFX_DECLARE_MESSAGE_MAP(CIFEventMenuGui)

public:
    CIFEventMenuGui(void);
    ~CIFEventMenuGui(void);

    bool OnCreate(long ln) override;
    void ResetPosition();
private:

    CIFStatic* m_custom_label1;
    CIFStatic* Frame;

public:


};