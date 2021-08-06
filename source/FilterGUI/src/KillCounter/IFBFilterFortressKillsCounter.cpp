//
// Created by kinge on 1/7/2021.
//

#include "IFBFilterFortressKillsCounter.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>
#include <Game.h>

#define BFILTER_FTWCounter_Num1 14
#define BFILTER_FTWCounter_Num2 15
#define BFILTER_FTWCounter_Num3 16
#define BFILTER_FTWCounter_Num4 17
#define BFILTER_FTWCounter_Num5 18
//#define BFILTER_FTWCounter_Num6 19
//#define BFILTER_FTWCounter_Num7 20
//#define BFILTER_FTWCounter_Num8 21

#define BFILTER_FTWCounter_CharNum1 22
#define BFILTER_FTWCounter_CharNum2 23
#define BFILTER_FTWCounter_CharNum3 24
#define BFILTER_FTWCounter_CharNum4 25
#define BFILTER_FTWCounter_CharNum5 26
//#define BFILTER_FTWCounter_CharNum6 27
//#define BFILTER_FTWCounter_CharNum7 28
//#define BFILTER_FTWCounter_CharNum8 29

#define BFILTER_FTWCounter_DMGNum1 30
#define BFILTER_FTWCounter_DMGNum2 31
#define BFILTER_FTWCounter_DMGNum3 32
#define BFILTER_FTWCounter_DMGNum4 33
#define BFILTER_FTWCounter_DMGNum5 34
//#define BFILTER_FTWCounter_DMGNum6 35
//#define BFILTER_FTWCounter_DMGNum7 36
//#define BFILTER_FTWCounter_DMGNum8 37

#define BFILTER_FTWCounter_DMGText 13
#define BFILTER_FTWCounter_CharText 12

#define BFILTER_FTWCounter_TITLE 11
#define BFILTER_FTWCounter_FRAME 10

#define BFILTER_MENU_FRAME 6
#define BFILTER_MENU_NORMALTITLE 5

GFX_IMPLEMENT_DYNCREATE(CIFFTWCounter, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFFTWCounter, CIFMainFrame)
GFX_END_MESSAGE_MAP()


CIFFTWCounter::CIFFTWCounter(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFFTWCounter::~CIFFTWCounter(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFFTWCounter::OnCreate(long ln)
{
   // printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT FrameRect = { 0,0,187,165 };
    RECT normal2Rect = { 33,82,148,110 };

    RECT lable1Rect = { 24,31,82,14 };
    RECT lable2Rect = { 133,31,49,14 };

    RECT lable3Rect = { 9,39,13,13 };
    RECT lable4Rect = { 9,61,13,13 };
    RECT lable5Rect = { 9,82,13,13 };
    RECT lable6Rect = { 9,104,13,13 };
    RECT lable7Rect = { 9,125,13,13 };

    RECT lable11Rect = { 26,39,110,14 };
    RECT lable12Rect = { 26,61,110,14 };
    RECT lable13Rect = { 26,82,110,14 };
    RECT lable14Rect = { 26,104,110,14 };
    RECT lable15Rect = { 26,125,110,14 };

    RECT lable19Rect = { 132,39,44,14 };
    RECT lable20Rect = { 132,61,44,14 };
    RECT lable21Rect = { 132,82,44,14 };
    RECT lable22Rect = { 132,104,44,14 };
    RECT lable23Rect = { 132,125,44,14 };

    Frame = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), FrameRect, BFILTER_MENU_FRAME, 0);

    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable1Rect, BFILTER_FTWCounter_CharText, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable2Rect, BFILTER_FTWCounter_DMGText, 0);

    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable3Rect, BFILTER_FTWCounter_Num1, 0);
    m_custom_label6 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable4Rect, BFILTER_FTWCounter_Num2, 0);
    m_custom_label7 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable5Rect, BFILTER_FTWCounter_Num3, 0);
    m_custom_label8 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable6Rect, BFILTER_FTWCounter_Num4, 0);
    m_custom_label9 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable7Rect, BFILTER_FTWCounter_Num5, 0);

    m_custom_label13 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable11Rect, BFILTER_FTWCounter_CharNum1, 0);
    m_custom_label14 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable12Rect, BFILTER_FTWCounter_CharNum2, 0);
    m_custom_label15 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable13Rect, BFILTER_FTWCounter_CharNum3, 0);
    m_custom_label16 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable14Rect, BFILTER_FTWCounter_CharNum4, 0);
    m_custom_label17 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable15Rect, BFILTER_FTWCounter_CharNum5, 0);

    m_custom_label21 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable19Rect, BFILTER_FTWCounter_DMGNum1, 0);
    m_custom_label22 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable20Rect, BFILTER_FTWCounter_DMGNum2, 0);
    m_custom_label23 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable21Rect, BFILTER_FTWCounter_DMGNum3, 0);
    m_custom_label24 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable22Rect, BFILTER_FTWCounter_DMGNum4, 0);
    m_custom_label25 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable23Rect, BFILTER_FTWCounter_DMGNum5, 0);

    m_custom_label5->MoveGWnd(m_custom_label5->GetBounds().pos.x + 15, m_custom_label5->GetBounds().pos.y + 15);
    m_custom_label6->MoveGWnd(m_custom_label6->GetBounds().pos.x + 15, m_custom_label6->GetBounds().pos.y + 15);
    m_custom_label7->MoveGWnd(m_custom_label7->GetBounds().pos.x + 15, m_custom_label7->GetBounds().pos.y + 15);
    m_custom_label8->MoveGWnd(m_custom_label8->GetBounds().pos.x + 15, m_custom_label8->GetBounds().pos.y + 15);
    m_custom_label9->MoveGWnd(m_custom_label9->GetBounds().pos.x + 15, m_custom_label9->GetBounds().pos.y + 15);

    m_custom_label13->MoveGWnd(m_custom_label13->GetBounds().pos.x + 15, m_custom_label13->GetBounds().pos.y + 15);
    m_custom_label14->MoveGWnd(m_custom_label14->GetBounds().pos.x + 15, m_custom_label14->GetBounds().pos.y + 15);
    m_custom_label15->MoveGWnd(m_custom_label15->GetBounds().pos.x + 15, m_custom_label15->GetBounds().pos.y + 15);
    m_custom_label16->MoveGWnd(m_custom_label16->GetBounds().pos.x + 15, m_custom_label16->GetBounds().pos.y + 15);
    m_custom_label17->MoveGWnd(m_custom_label17->GetBounds().pos.x + 15, m_custom_label17->GetBounds().pos.y + 15);

    m_custom_label21->MoveGWnd(m_custom_label21->GetBounds().pos.x + 10, m_custom_label21->GetBounds().pos.y + 15);
    m_custom_label22->MoveGWnd(m_custom_label22->GetBounds().pos.x + 10, m_custom_label22->GetBounds().pos.y + 15);
    m_custom_label23->MoveGWnd(m_custom_label23->GetBounds().pos.x + 10, m_custom_label23->GetBounds().pos.y + 15);
    m_custom_label24->MoveGWnd(m_custom_label24->GetBounds().pos.x + 10, m_custom_label24->GetBounds().pos.y + 15);
    m_custom_label25->MoveGWnd(m_custom_label25->GetBounds().pos.x + 10, m_custom_label25->GetBounds().pos.y + 15);

    m_title->SetText(L"Fortress Kills");
    m_close->ShowGWnd(false);

    m_custom_label3->SetText(L"Guild");
    m_custom_label4->SetText(L"Kills");

    m_custom_label5->SetText(L"1");
    m_custom_label5->SetTextColor(0xeb345b);
    m_custom_label6->SetText(L"2");
    m_custom_label6->SetTextColor(0xfef29d);
    m_custom_label7->SetText(L"3");
    m_custom_label7->SetTextColor(0x5ad3a9);
    m_custom_label8->SetText(L"4");
    m_custom_label9->SetText(L"5");

    m_custom_label13->SetTextColor(0xeb345b);
    m_custom_label14->SetTextColor(0xfef29d);
    m_custom_label15->SetTextColor(0x5ad3a9);

    m_custom_label21->SetTextColor(0xeb345b);
    m_custom_label22->SetTextColor(0xfef29d);
    m_custom_label23->SetTextColor(0x5ad3a9);

    m_custom_label13->SetText(L"<NONE>");
    m_custom_label21->SetText(L"0");

    m_custom_label14->SetText(L"<NONE>");
    m_custom_label22->SetText(L"0");

    m_custom_label15->SetText(L"<NONE>");
    m_custom_label23->SetText(L"0");

    m_custom_label16->SetText(L"<NONE>");
    m_custom_label24->SetText(L"0");

    m_custom_label17->SetText(L"<NONE>");
    m_custom_label25->SetText(L"0");

    Frame->TB_Func_13("interface\\gui\\bfiltersurvivalarenaframe.ddj", 0, 0);
    m_title->BringToFront();
    m_title->MoveGWnd(m_title->GetPos().x,m_title->GetPos().y-4);
    this->ShowGWnd(false);
    ResetPosition();
    return true;
}

void CIFFTWCounter::OnUpdate()
{
}


void CIFFTWCounter::ResetPosition()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();
    this->MoveGWnd(res.width-230, res.height-400);
}
void CIFFTWCounter::WriteLine(BYTE Num, const wchar_t* Charname, const wchar_t* DMG) const
{
    switch (Num)
    {
        case 1:
            m_custom_label13->SetText(Charname);
            m_custom_label21->SetText(DMG);
            break;
        case 2:
            m_custom_label14->SetText(Charname);
            m_custom_label22->SetText(DMG);
            break;
        case 3:
            m_custom_label15->SetText(Charname);
            m_custom_label23->SetText(DMG);
            break;
        case 4:
            m_custom_label16->SetText(Charname);
            m_custom_label24->SetText(DMG);
            break;
        case 5:
            m_custom_label17->SetText(Charname);
            m_custom_label25->SetText(DMG);
            break;
        default:
            break;
    }
}

void CIFFTWCounter::Clear() const
{
    m_custom_label13->SetText(L"<NONE>");
    m_custom_label21->SetText(L"0");

    m_custom_label14->SetText(L"<NONE>");
    m_custom_label22->SetText(L"0");

    m_custom_label15->SetText(L"<NONE>");
    m_custom_label23->SetText(L"0");

    m_custom_label16->SetText(L"<NONE>");
    m_custom_label24->SetText(L"0");

    m_custom_label17->SetText(L"<NONE>");
    m_custom_label25->SetText(L"0");

}