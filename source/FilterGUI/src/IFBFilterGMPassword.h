#pragma once
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include "IFEdit.h"

class CIFGMPassword : public CIFMainFrame
{
	GFX_DECLARE_DYNCREATE(CIFGMPassword)
		GFX_DECLARE_MESSAGE_MAP(CIFGMPassword)

public:
	CIFGMPassword(void);
	~CIFGMPassword(void);

	bool OnCreate(long ln) override;
	void OnUpdate() override;
	void ResetPosition();

private:
    void On_BtnClick();

private:
    void OnClick_Exit();
public:
    CIFEdit *m_edit;
    CIFButton* m_mybutton;
    CIFStatic* m_custom_label;
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
};
