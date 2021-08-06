#pragma once
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include <IFEdit.h>

class CIFChangeLog : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFChangeLog)
GFX_DECLARE_MESSAGE_MAP(CIFChangeLog)

public:
    CIFChangeLog(void);
    ~CIFChangeLog(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void ResetPosition();
public:
    CIFVerticalScroll* m_vericalSroll;
    CIFTextBox* m_textbox;
    CIFStatic* m_custom_label;
    CIFFrame* Frame;
};

