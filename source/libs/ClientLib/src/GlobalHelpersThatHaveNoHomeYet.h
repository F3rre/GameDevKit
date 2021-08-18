#pragma once

union uregion {
	struct {
		char y;
		char x;
	} single;
	short r;
};

#define g_CurrentIfUnderCursor (*(CGWndBase**)0x0110F608)
#define g_Controler (*(CControler**)0x0110F7D4)

#define g_Region (*(uregion*)0xEEF68C)

#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)
#define CLIENT_SCREEN_HEIGHT (*(int*)0x00ED7CBC)

#define MainForm 11440
#define UniqueLog 11441
#define GMPassword 11442
#define CharLock 11443
#define GrantName 11444
#define TitleManager 11445
#define DMGMeter 11446
#define EventTime 11447
#define FtwKillsCounter 11448
#define SurvKillsCounter 11449
#define CustomRank 11450
#define SwitchTitles 11452
#define CustomTitleUD 11453
#define PurbleNotify 11455
#define OrangeNotify 11456
#define EventMenuGui 11457

#define SendMsg(x) reinterpret_cast<void (__cdecl *)(CMsgStreamBuffer&)>(0x008418D0)(x)

