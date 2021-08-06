#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_RELOAD 13378
#define GUIDE_FACEBOOK 13666
#define GUIDE_MAINMENU 13444
#define GUIDE_DISCORD 13555
#define GUIDE_WEB 135556

class CIFflorian0Guide : public CIFDecoratedStatic {
GFX_DECLARE_DYNCREATE(CIFflorian0Guide)

public:
    bool OnCreate(long ln) override;

    int OnMouseLeftUp(int a1, int x, int y) override;

   /* int OnMouseMove(int a1, int x, int y) override;

    int OnMouseLeftDown(int a1, int x, int y) override;*/

    void OnCIFReady() override;

};
