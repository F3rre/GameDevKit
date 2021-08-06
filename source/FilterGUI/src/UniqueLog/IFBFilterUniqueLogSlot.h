#pragma once
#include "IFMainFrame.h"

class CIFUniqueLogSlot : public CIFWnd
{
	GFX_DECLARE_DYNCREATE(CIFUniqueLogSlot)
	GFX_DECLARE_MESSAGE_MAP(CIFUniqueLogSlot)

public:
	CIFUniqueLogSlot(void);
	~CIFUniqueLogSlot(void);

	bool OnCreate(long ln) override;
public:
	CIFStatic* m_custom_label1;
	CIFStatic* m_custom_label2;
	CIFStatic* m_custom_label3;
	CIFStatic* m_custom_label4;
	CIFStatic* m_custom_label5;
};
