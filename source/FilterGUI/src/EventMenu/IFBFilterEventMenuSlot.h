#pragma once
#include "IFMainFrame.h"

class CIFEventMenuSlot : public CIFWnd
{
	GFX_DECLARE_DYNCREATE(CIFEventMenuSlot)
		GFX_DECLARE_MESSAGE_MAP(CIFEventMenuSlot)

public:
	CIFEventMenuSlot(void);
	~CIFEventMenuSlot(void);
	int OnMouseLeftUp(int a1, int x, int y) override;
	void WriteLine(const wchar_t* ItemName);
	bool OnCreate(long ln) override;
public:
	CIFStatic* m_custom_label1;
};