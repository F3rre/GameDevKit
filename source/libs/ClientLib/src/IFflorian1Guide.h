#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_FLORIAN1 13398

class CIFflorian1Guide : public CIFDecoratedStatic
{
	GFX_DECLARE_DYNCREATE(CIFflorian1Guide)

public:
	bool OnCreate(long ln) override;
	int OnMouseLeftUp(int a1, int x, int y) override;
	void OnCIFReady() override;
};
