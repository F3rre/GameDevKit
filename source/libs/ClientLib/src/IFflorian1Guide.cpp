#include "IFflorian1Guide.h"
#include <BSLib/Debug.h>
#include "GEffSoundBody.h"
#include "GInterface.h"
#include "ICPlayer.h"
GFX_IMPLEMENT_DYNCREATE(CIFflorian1Guide, CIFDecoratedStatic)


bool CIFflorian1Guide::OnCreate(long ln)
{
	BS_DEBUG_LOW("> " __FUNCTION__ "(%d)", ln);
	CIFDecoratedStatic::OnCreate(ln);

	TB_Func_13("icon\\etc\\facebook_x.ddj", 0, 0);
	set_N00009BD4(2);
	set_N00009BD3(500);
	CGEffSoundBody::get()->PlaySound(L"snd_quest");
	this->MoveGWnd(1235, 222);
	return true;

}	


int CIFflorian1Guide::OnMouseLeftUp(int a1, int x, int y)
{
	BS_DEBUG_LOW("> " __FUNCTION__ "(%d, %d, %d)", a1, x, y);

	CGEffSoundBody::get()->PlaySound(L"snd_quest");
	ShellExecute(NULL, "open", "https://facebook.com/groups/696053461092334/", NULL, NULL, SW_SHOWNORMAL);

	return 0;
}

void CIFflorian1Guide::OnCIFReady()
{
	BS_DEBUG_LOW("> " __FUNCTION__);

	CIFDecoratedStatic::OnCIFReady();
	sub_633990();

}
