#include <MainMenu/IFBFilterMainMenu.h>
#include "IFflorian0Guide.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include "ClientNet/MsgStreamBuffer.h"
#include "ANetwork/CPSMission.h"

GFX_IMPLEMENT_DYNCREATE(CIFflorian0Guide, CIFDecoratedStatic)

bool CIFflorian0Guide::OnCreate(long ln)
{
    CIFDecoratedStatic::OnCreate(ln);

    switch (this->UniqueID())
    {
        case GUIDE_WEB:
        {
            this->TB_Func_13("icon\\soci\\webguide_focus.ddj", 0, 0);
            this->sub_634470("icon\\soci\\webguide_focus.ddj");
            this->set_N00009BD4(2);
            this->set_N00009BD3(500);
        }
            break;
        case GUIDE_MAINMENU:
        {
            this->TB_Func_13("icon\\social\\webgacha2_1.ddj", 0, 0);
            this->sub_634470("icon\\social\\webgacha2_2.ddj");
            this->set_N00009BD4(2);
            this->set_N00009BD3(500);
        }
            break;
        case GUIDE_FACEBOOK:
        {
            this->TB_Func_13("icon\\social\\facebook1_1.ddj", 0, 0);
            this->sub_634470("icon\\social\\facebook1_2.ddj");
            this->set_N00009BD4(2);
            this->set_N00009BD3(500);
        }
            break;
        case GUIDE_DISCORD:
        {
            this->TB_Func_13("icon\\social\\discord1_1.ddj", 0, 0);
            this->sub_634470("icon\\social\\discord1_2.ddj");
            this->set_N00009BD4(2);
            this->set_N00009BD3(500);
        }
            break;
        case GUIDE_RELOAD:
        {
            this->TB_Func_13("icon\\soci\\discordguide_focus.ddj", 0, 0);
            this->sub_634470("icon\\soci\\discordguide_focus.ddj");
            this->set_N00009BD4(2);
            this->set_N00009BD3(500);
        }
            break;
    }

    return true;
}
void CIFflorian0Guide::OnCIFReady()
{
    CIFDecoratedStatic::OnCIFReady();
    sub_633990();
}
int CIFflorian0Guide::OnMouseLeftUp(int a1, int x, int y)
{
    switch (this->UniqueID())
    {
        case GUIDE_MAINMENU:
        {
            if (CIFMainMenu::CustomRankGUI->IsVisible()) {
                CIFMainMenu::CustomRankGUI->ShowGWnd(false);
            }

            if (CIFMainMenu::CharLockGUI->IsVisible()) {
                CIFMainMenu::CharLockGUI->ShowGWnd(false);
            }

            if (CIFMainMenu::UniqueLogGUI->IsVisible()) {
                CIFMainMenu::UniqueLogGUI->ShowGWnd(false);
            }

            if (CIFMainMenu::EventTimeGUI->IsVisible()) {
                CIFMainMenu::EventTimeGUI->ShowGWnd(false);
            }

            if (CIFMainMenu::CharLockGUI->IsVisible()) {
                CIFMainMenu::CharLockGUI->ShowGWnd(false);
            }

            if (CIFMainMenu::SwitchTitleGUI->IsVisible()) {
                CIFMainMenu::SwitchTitleGUI->ShowGWnd(false);
            }

            if (CIFMainMenu::MenuGui->IsVisible()) {
                CIFMainMenu::MenuGui->ResetPosition();
                CIFMainMenu::MenuGui->BringToFront();
                return 0;
            }

            CIFMainMenu::MenuGui->ShowGWnd(true);
            CIFMainMenu::MenuGui->ResetPosition();
            CIFMainMenu::MenuGui->BringToFront();

        }
            break;
        case GUIDE_FACEBOOK:
        {
            ShellExecute(NULL, "open", "https://facelink.com", NULL, NULL, SW_SHOWNORMAL);

        }
            break;
        case GUIDE_DISCORD:
        {
            ShellExecute(NULL, "open", "https://discordlink.com", NULL, NULL, SW_SHOWNORMAL);
        }
            break;
        case GUIDE_WEB:
        {
            ShellExecute(NULL, "open", "http://www.serveradi.com", NULL, NULL, SW_SHOWNORMAL);
        }
            break;
        case GUIDE_RELOAD: {
            CMsgStreamBuffer buf(0x3502);
            buf << GET_OWN_GAME_ID();
            SendMsg(buf);

            //int invs = 4;
            //CMsgStreamBuffer buf1(0x3503);
            //buf1 << GET_OWN_GAME_ID();
            //buf1 << invs;
            //SendMsg(buf1);
        }
    }
    return 0;
}