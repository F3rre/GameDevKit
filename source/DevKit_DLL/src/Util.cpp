#include "Util.h"

#include <sys/stat.h>

#include <memory/hook.h>

#include "hooks/Hooks.h"
#include "hooks/GFXVideo3d_Hook.h"
#include "hooks/CGame_Hook.h"

#include "hooks/WndProc_Hook.h"

#include <GInterface.h>
#include <IFChatViewer.h>
#include <NetProcessIn.h>
#include <NetProcessSecond.h>
#include <NetProcessThird.h>
#include <BSLib/Debug.h>
#include "QuickStart.h"

#include <OnGameNotify.h>
#include "NotificationHandler.h"
#include <ANetwork/CPSMission.h>
#include <DiscordRichPresence/DiscordManager.h>

std::vector<const CGfxRuntimeClass *> register_objects;
std::vector<overrideFnPtr> override_objects;

QuickStart quickstart;

void Setup() {

#ifdef CONFIG_DEBUG_CONSOLE
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
#endif

    vftableHook(0x00E0963C, 17, addr_from_this(&CGFXVideo3D_Hook::CreateThingsHook));
    vftableHook(0x00E0963C, 26, addr_from_this(&CGFXVideo3D_Hook::EndSceneHook));
    vftableHook(0x00E0963C, 20, addr_from_this(&CGFXVideo3D_Hook::SetSizeHook));

    vftableHook(0x00db95a4, 10, addr_from_this(&CGInterface::OnCreateIMPL));

    replaceAddr(0x00831337 + 4, (int) &WndProcHook);

    placeHook(0x0065c6f0, addr_from_this(&CAlramGuideMgrWnd::GetGuide));

    replaceOffset(0x008491d1, addr_from_this(&CGame_Hook::LoadGameOption));

    replaceOffset(0x00832a11, addr_from_this(&CGame_Hook::InitGameAssets_Impl));

   //replaceOffset(0x0084c9bf, addr_from_this(&CNetProcessIn::RegisterPacketHandlers));
   //replaceOffset(0x00898656, addr_from_this(&CNetProcessSecond::RegisterPacketHandlers));
   //replaceOffset(0x008a4876, addr_from_this(&CNetProcessThird::RegisterPacketHandlers));

   // placeHook(0x0049d620, Put);

  //  quickstart.Setup();

#ifdef CONFIG_DEBUG_REDIRECT_PUTDUMP
    replaceAddr(0x00832927 + 1, (int) &DebugPrintCallback);
#endif // CONFIG_DEBUG_REDIRECT_PUTDUMP

#ifdef CONFIG_TRANSLATIONS_DEBUG
    placeHook(0x008C9C30, addr_from_this(&CTextStringManager::GetString));
#endif // CONFIG_TRANSLATIONS_DEBUG

//#ifdef CONFIG_CHATVIEWER
    replaceOffset(0x008774f4, (int)&WriteToChatWindow);
    replaceOffset(0x00877b5c, (int)&WriteToChatWindow);

    //placeHook(0x007a9bd0, addr_from_this(&CIFChatViewer::ShowHideControls));
//#endif // CONFIG_CHATVIEWER

    //BFILTER
        //old main pop
    //RenderNop((void*)0x006A290A, 1);
    //RenderNop((void*)0x006A290B, 2);
    //RenderNop((void*)0x006A2918, 1);
    //RenderNop((void*)0x006A2919, 2);
    //RenderNop((void*)0x006A2926, 1);
    //RenderNop((void*)0x006A2927, 2);
    //RenderNop((void*)0x006A2934, 1);
    //RenderNop((void*)0x006A2935, 2);
    //RenderNop((void*)0x006A2942, 1);
    //RenderNop((void*)0x006A2943, 2);
    //RenderNop((void*)0x006A2950, 1);
    //RenderNop((void*)0x006A2951, 2);
    //RenderNop((void*)0x006A295E, 1);
    //RenderNop((void*)0x006A295F, 2);
    //RenderNop((void*)0x006A2973, 1);
    //RenderNop((void*)0x006A2974, 2);

   //CALLFunction(0x006A2540, 0x007990E0);
   //RenderNop((void*)0x006A2545, 2);
   //JMPFunction(0x006A2275, 0x006A2357);
   //JMPFunction(0x006A232A, 0x006A2357);

    //COLORING?
    replaceAddr(0x00DE2C4C, addr_from_this(&CICPlayer::Render));
    //replaceAddr(0x00DE2C50, addr_from_this(&CICPlayer::Render));

    replaceAddr(0x00dd92d4, addr_from_this(&CPSTitle::OnServerPacketRecv));
    //vftableHook(0x00dd92bc, 10, addr_from_this(&CPSTitle::OnCreateTMEP));
    replaceAddr(0x00dd8134, addr_from_this(&CPSCharacterSelect::OnServerPacketRecv));
    replaceAddr(0x00DD440C, addr_from_this(&CPSMission::OnServerPacketRecv));
    replaceOffset(0x0070BCF2, addr_from_this(&CInterfaceNetSender::DonateGuildPoints));

    //price comma
    replaceOffset(0x00679836, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x0067984d, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x006798ba, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x00679999, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x00679a6b, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x00679d3e, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x006789ac, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x00678ced, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x00678e1f, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x00678ee8, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x00678fb1, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x0067907a, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x00679143, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x0067920c, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x006792d5, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x0067939d, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x00679469, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x00679535, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x00679601, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x006796b5, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    replaceOffset(0x00678a33, addr_from_this(&CIFHelperBubbleWindow::WriteLine));

    //guild in job mode
    RenderNop((void*)0x009DF09D, 6);
    GuildJobMode();

    // replaceAddr(0x00dbd4fc, addr_from_this(&CIFPlayerMiniInfo::Render));

    //old tooltip
    CALLFunction(0x0068286A, 0x0066FD60);
    CALLFunction(0x00682E9A, 0x0066FD60);
    CALLFunction(0x00682C4A, 0x0066FD60);
    CALLFunction(0x006830E4, 0x0066FD60);
    PatchAdvColor();

    // w/o Item Comparison
    //CALLFunction(0x00682AFC, 0x0066FA60);
    //CALLFunction(0x00682FBE, 0x0066FA60);
    //CALLFunction(0x0068320E, 0x0066FA60);
    //CALLFunction(0x00682D6E, 0x0066FA60);

    //isro sys Comparison with old tool tip



    //g_notificationhandler.Initialize();
   //replaceAddr(0x0086FCDD, addr_from_this(&Notify::OnGameNotify));

    //show char icon
    RenderNop((void*)0x009DED3D, 6);

    PatchWrongPassword();
    PatchWatermark();
    PatchChatLamps();
    DiscordManager::Instance().Start(870781023661719622);
}

void PatchWatermark()
{

#pragma pack(push, 1)
    struct
    {
        byte opcode;
        int color;
    } colorPatch;
#pragma pack(pop)
    colorPatch.opcode = 0x68; // push (constant)
    colorPatch.color = 0x49f5d7;
    CopyBytes(0x0086BC33, &colorPatch, sizeof(colorPatch));

    static std::wstring versionFormat;
    if (versionFormat.length() == 0)
    {
        versionFormat.append(L"  Version %d.%03d\n");
    }
#pragma pack(push, 1)
    struct
    {
        byte opcode;
        const wchar_t* address;
    } textPatch;
#pragma pack(pop)
    textPatch.opcode = 0x68;
    textPatch.address = versionFormat.c_str();
    CopyBytes(0x0086BC6F, &textPatch, sizeof(textPatch));
}

void PatchChatLamps()
{

#pragma pack(push, 1)
    struct
    {
        byte opcode;
        byte opcode2;
    } FirstLamp;
#pragma pack(pop)
    FirstLamp.opcode = 0x80; // push (constant)
    FirstLamp.opcode2 = 0x04;
    CopyBytes(0x007A9B18, &FirstLamp, sizeof(FirstLamp));

#pragma pack(push, 1)
    struct
    {
        byte opcode;
        byte opcode2;
    } SecondLamp;
#pragma pack(pop)
    SecondLamp.opcode = 0x7C;
    SecondLamp.opcode2 = 0x04;
    CopyBytes(0x007A9B20, &SecondLamp, sizeof(SecondLamp));
}

void PatchAdvColor()
{
#pragma pack(push, 1)
    struct
    {
        byte opcode;
        int color;
    } colorPatch;
#pragma pack(pop)
    colorPatch.opcode = 0x68; // push (constant)
    colorPatch.color = 0xFFF5CC32;
    CopyBytes(0x0066FE61, &colorPatch, sizeof(colorPatch));

#pragma pack(push, 1)
    struct
    {
        byte opcode;
        byte size;
    } colorwide;
#pragma pack(pop)
    colorwide.opcode = 0x6A; // push (constant)
    colorwide.size = 0x6;
    CopyBytes(0x0066FE5D, &colorwide, sizeof(colorwide));

#pragma pack(push, 1)
    struct
    {
        byte opcode;
        byte size;
    } colorwide1;
#pragma pack(pop)
    colorwide1.opcode = 0x6A; // push (constant)
    colorwide1.size = 0x6;
    CopyBytes(0x0066FE21, &colorwide1, sizeof(colorwide1));
}

void GuildJobMode()
{
#pragma pack(push, 1)
    struct
    {
        byte opcode;
        byte code;
    } Guild;
#pragma pack(pop)
    Guild.opcode = 0x00;
    Guild.code = 0x00;
    CopyBytes(0x00D92240, &Guild, sizeof(Guild));
}

void PatchWrongPassword()
{
#pragma pack(push, 1)
    struct
    {
        byte opcode;
    } First;
#pragma pack(pop)
    First.opcode = 0x52; // push (constant)
    CopyBytes(0x0086C0EF, &First, sizeof(First));

#pragma pack(push, 1)
    struct
    {
        byte opcode;
    } Second;
#pragma pack(pop)
    Second.opcode = 0x51; // push (constant)
    CopyBytes(0x0086C0F0, &Second, sizeof(Second));
}

bool DoesFileExists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void RegisterObject(const CGfxRuntimeClass *obj) {
    register_objects.push_back(obj);
}

void OverrideObject(overrideFnPtr fn) {
    override_objects.push_back(fn);
}

void InstallRuntimeClasses(CGame *) {
    // Replace Create & Delete for existing classes
    // Note: We can't just inject existing objects like we would do with new objects.
    //       Joymax uses == on GFX_RUNTIME_CLASS(), so we would end up breaking this comparison

    for (std::vector<const CGfxRuntimeClass *>::const_iterator it = register_objects.begin();
         it != register_objects.end(); ++it) {
        reinterpret_cast<void (__thiscall *)(const CGfxRuntimeClass *, const char *, void *, void *,const CGfxRuntimeClass *, size_t, int)>(0x00B9C9C0)(*it,(*it)->m_lpszClassName, (*it)->m_pfnCreateObject, (*it)->m_pfnDeleteObject, (*it)->m_pBaseClass, (*it)->m_nObjectSize, 0);
    }

    for (std::vector<overrideFnPtr>::const_iterator it = override_objects.begin(); it != override_objects.end(); ++it) {
        (*it)();
    }
}
