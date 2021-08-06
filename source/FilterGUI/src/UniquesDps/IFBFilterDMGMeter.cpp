#include "IFBFilterDMGMeter.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>

#define BFILTER_DMGMETER_Num1 14
#define BFILTER_DMGMETER_Num2 15
#define BFILTER_DMGMETER_Num3 16
#define BFILTER_DMGMETER_Num4 17
#define BFILTER_DMGMETER_Num5 18
#define BFILTER_DMGMETER_Num6 19
#define BFILTER_DMGMETER_Num7 20
#define BFILTER_DMGMETER_Num8 21

#define BFILTER_DMGMETER_CharNum1 22
#define BFILTER_DMGMETER_CharNum2 23
#define BFILTER_DMGMETER_CharNum3 24
#define BFILTER_DMGMETER_CharNum4 25
#define BFILTER_DMGMETER_CharNum5 26
#define BFILTER_DMGMETER_CharNum6 27
#define BFILTER_DMGMETER_CharNum7 28
#define BFILTER_DMGMETER_CharNum8 29

#define BFILTER_DMGMETER_DMGNum1 30
#define BFILTER_DMGMETER_DMGNum2 31
#define BFILTER_DMGMETER_DMGNum3 32
#define BFILTER_DMGMETER_DMGNum4 33
#define BFILTER_DMGMETER_DMGNum5 34
#define BFILTER_DMGMETER_DMGNum6 35
#define BFILTER_DMGMETER_DMGNum7 36
#define BFILTER_DMGMETER_DMGNum8 37

#define BFILTER_DMGMETER_DMGText 13
#define BFILTER_DMGMETER_CharText 12

#define BFILTER_DMGMETER_TITLE 11
#define BFILTER_DMGMETER_FRAME 10

#define BFILTER_MENU_FRAME 6
#define BFILTER_MENU_NORMALTITLE 5

GFX_IMPLEMENT_DYNCREATE(CIFDMGMeter, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFDMGMeter, CIFMainFrame)
GFX_END_MESSAGE_MAP()


CIFDMGMeter::CIFDMGMeter(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFDMGMeter::~CIFDMGMeter(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFDMGMeter::OnCreate(long ln)
{
   // printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT FrameRect = { 0,0,220,224 };
    RECT normal2Rect = { 33,82,148,110 };

    RECT lable1Rect = { 24,33,82,14 };
    RECT lable2Rect = { 129,33,49,14 };

    RECT lable3Rect = { 15,12,13,13 };
    RECT lable4Rect = { 15,35,13,13 };
    RECT lable5Rect = { 15,58,13,13 };
    RECT lable6Rect = { 15,81,13,13 };
    RECT lable7Rect = { 15,104,13,13 };
    RECT lable8Rect = { 15,127,13,13 };
    RECT lable9Rect = { 15,150,13,13 };
    RECT lable10Rect = { 15,173,13,13 };

    RECT lable11Rect = { 31,12,110,14 };
    RECT lable12Rect = { 31,35,110,14 };
    RECT lable13Rect = { 31,58,110,14 };
    RECT lable14Rect = { 31,81,110,14 };
    RECT lable15Rect = { 31,104,110,14 };
    RECT lable16Rect = { 31,127,110,14 };
    RECT lable17Rect = { 31,150,110,14 };
    RECT lable18Rect = { 31,173,110,14 };

    RECT lable19Rect = { 138,12,44,14 };
    RECT lable20Rect = { 138,35,44,14 };
    RECT lable21Rect = { 138,58,44,14 };
    RECT lable22Rect = { 138,81,44,14 };
    RECT lable23Rect = { 138,104,44,14 };
    RECT lable24Rect = { 138,127,44,14 };
    RECT lable25Rect = { 138,150,44,14 };
    RECT lable26Rect = { 138,173,44,14 };

    Frame = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), FrameRect, BFILTER_MENU_FRAME, 0);
    //NormalTitle = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), normal2Rect, BFILTER_MENU_NORMALTITLE, 0);
   
    //Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
    //NormalTitle->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);

    ///m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable1Rect, BFILTER_DMGMETER_CharText, 0);
    //m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable2Rect, BFILTER_DMGMETER_DMGText, 0);

    //m_custom_label3->MoveGWnd(m_custom_label3->GetBounds().pos.x + 15, m_custom_label3->GetBounds().pos.y + 15);
    //m_custom_label4->MoveGWnd(m_custom_label4->GetBounds().pos.x + 10, m_custom_label4->GetBounds().pos.y + 15);
    
    //m_custom_label3->SetTextColor(0xffffff);
    //m_custom_label4->SetTextColor(0xffffff);

    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable3Rect, BFILTER_DMGMETER_Num1, 0);
    m_custom_label6 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable4Rect, BFILTER_DMGMETER_Num2, 0);
    m_custom_label7 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable5Rect, BFILTER_DMGMETER_Num3, 0);
    m_custom_label8 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable6Rect, BFILTER_DMGMETER_Num4, 0);
    m_custom_label9 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable7Rect, BFILTER_DMGMETER_Num5, 0);
    m_custom_label10 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable8Rect, BFILTER_DMGMETER_Num6, 0);
    m_custom_label11 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable9Rect, BFILTER_DMGMETER_Num7, 0);
    m_custom_label12 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable10Rect, BFILTER_DMGMETER_Num8, 0);


    m_custom_label13 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable11Rect, BFILTER_DMGMETER_CharNum1, 0);
    m_custom_label14 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable12Rect, BFILTER_DMGMETER_CharNum2, 0);
    m_custom_label15 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable13Rect, BFILTER_DMGMETER_CharNum3, 0);
    m_custom_label16 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable14Rect, BFILTER_DMGMETER_CharNum4, 0);
    m_custom_label17 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable15Rect, BFILTER_DMGMETER_CharNum5, 0);
    m_custom_label18 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable16Rect, BFILTER_DMGMETER_CharNum6, 0);
    m_custom_label19 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable17Rect, BFILTER_DMGMETER_CharNum7, 0);
    m_custom_label20 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable18Rect, BFILTER_DMGMETER_CharNum8, 0);


    m_custom_label21 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable19Rect, BFILTER_DMGMETER_DMGNum1, 0);
    m_custom_label22 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable20Rect, BFILTER_DMGMETER_DMGNum2, 0);
    m_custom_label23 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable21Rect, BFILTER_DMGMETER_DMGNum3, 0);
    m_custom_label24 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable22Rect, BFILTER_DMGMETER_DMGNum4, 0);
    m_custom_label25 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable23Rect, BFILTER_DMGMETER_DMGNum5, 0);
    m_custom_label26 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable24Rect, BFILTER_DMGMETER_DMGNum6, 0);
    m_custom_label27 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable25Rect, BFILTER_DMGMETER_DMGNum7, 0);
    m_custom_label28 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable26Rect, BFILTER_DMGMETER_DMGNum8, 0);


   // m_custom_label5->SetTextColor(0xffffff);
    //m_custom_label6->SetTextColor(0xffffff);
    //m_custom_label7->SetTextColor(0xffffff);
    //m_custom_label8->SetTextColor(0xffffff);
    //m_custom_label9->SetTextColor(0xffffff);
    //m_custom_label10->SetTextColor(0xffffff);
    //m_custom_label11->SetTextColor(0xffffff);
    //m_custom_label12->SetTextColor(0xffffff);
    ///;/m_custom_label16->SetTextColor(0xffffff);
    //m_custom_label17->SetTextColor(0xffffff);
    //m_custom_label18->SetTextColor(0xffffff);
    //m_custom_label19->SetTextColor(0xffffff);
    //m_custom_label20->SetTextColor(0xffffff);
    //m_custom_label24->SetTextColor(0xffffff);
    //m_custom_label25->SetTextColor(0xffffff);
    //m_custom_label26->SetTextColor(0xffffff);
    //m_custom_label27->SetTextColor(0xffffff);
    //m_custom_label28->SetTextColor(0xffffff);

    //Frame->SetGWndSize(this->GetBounds().size.width - 20, this->GetBounds().size.height - 48);
    //Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 38);

   // NormalTitle->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
   // NormalTitle->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);

    m_title->SetText(L"Damage Meter");
    m_close->ShowGWnd(false);
    m_handleBar->ShowGWnd(false);

    //m_custom_label3->SetText(L"Character");
    //m_custom_label4->SetText(L"Damage");

    m_custom_label5->SetText(L"1");
    m_custom_label5->SetTextColor(0xeb345b);
    m_custom_label6->SetText(L"2");
    m_custom_label6->SetTextColor(0xfef29d);
    m_custom_label7->SetText(L"3");
    m_custom_label7->SetTextColor(0x5ad3a9);
    m_custom_label8->SetText(L"4");
    m_custom_label9->SetText(L"5");
    m_custom_label10->SetText(L"6");
    m_custom_label11->SetText(L"7");
    m_custom_label12->SetText(L"8");

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

    m_custom_label18->SetText(L"<NONE>");
    m_custom_label26->SetText(L"0");

    m_custom_label19->SetText(L"<NONE>");
    m_custom_label27->SetText(L"0");

    m_custom_label20->SetText(L"<NONE>");
    m_custom_label28->SetText(L"0");

    Frame->TB_Func_13("interface\\gui\\bfilterdmgmeter.ddj", 0, 0);

    this->ShowGWnd(false);
    m_title->MoveGWnd(m_title->GetPos().x,Frame->GetPos().x+Frame->GetSize().height-25);
    m_title->BringToFront();
    //ResetPosition();
    return true;
}

void CIFDMGMeter::OnUpdate()
{
}


void CIFDMGMeter::ResetPosition()
{
    USHORT PosX, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 650;
    this->MoveGWnd(PosX, PosY);

}

void CIFDMGMeter::WriteLine(BYTE Num, const wchar_t* Charname, const wchar_t* DMG) const
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
    case 6:
        m_custom_label18->SetText(Charname);
        m_custom_label26->SetText(DMG);
        break;
    case 7:
        m_custom_label19->SetText(Charname);
        m_custom_label27->SetText(DMG);
        break;
    case 8:
        m_custom_label20->SetText(Charname);
        m_custom_label28->SetText(DMG);
        break;

    default:
        break;
    }
}

void CIFDMGMeter::Clear() const
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

    m_custom_label18->SetText(L"<NONE>");
    m_custom_label26->SetText(L"0");

    m_custom_label19->SetText(L"<NONE>");
    m_custom_label27->SetText(L"0");

    m_custom_label20->SetText(L"<NONE>");
    m_custom_label28->SetText(L"0");
}