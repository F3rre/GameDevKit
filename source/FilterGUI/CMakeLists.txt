set(SOURCE_FILES
        src/ANetwork/CPSMission.cpp src/ANetwork/CPSMission.h
        src/ItemCompare/IFItemComparison.cpp src/ItemCompare/IFItemComparison.h

        src/NotificationHandler.cpp src/NotificationHandler.h
        src/OnGameNotify.cpp src/OnGameNotify.h

        src/CustomTitle/IFBFilterCustomTitle.cpp src/CustomTitle/IFBFilterCustomTitle.h
        src/GrantName/IFBFilterGrantName.cpp src/GrantName/IFBFilterGrantName.h
        src/SwitchTitles/IFBFilterTitles.cpp src/SwitchTitles/IFBFilterTitles.h
        src/UniquesDps/IFBFilterDMGMeter.cpp src/UniquesDps/IFBFilterDMGMeter.h
        src/CharacterLock/IFBFilterCharLock.cpp src/CharacterLock/IFBFilterCharLock.h

        src/KillCounter/IFBFilterSurvivalArena.cpp src/KillCounter/IFBFilterSurvivalArena.h
        src/KillCounter/IFBFilterFortressKillsCounter.cpp src/KillCounter/IFBFilterFortressKillsCounter.h

        src/CustomRank/IFBFilterRank.cpp src/CustomRank/IFBFilterRank.h
        src/CustomRank/IFBFilterRankSlot.cpp src/CustomRank/IFBFilterRankSlot.h
        src/CustomRank/IFBFilterRankList.cpp src/CustomRank/IFBFilterRankList.h


        src/UniqueLog/IFBFilterUniqueLog.cpp src/UniqueLog/IFBFilterUniqueLog.h
        src/UniqueLog/IFBFilterUniqueList.cpp src/UniqueLog/IFBFilterUniqueList.h
        src/UniqueLog/IFBFilterUniqueLogSlot.cpp src/UniqueLog/IFBFilterUniqueLogSlot.h

        src/PlayerChest/IFBFilterChest.cpp src/PlayerChest/IFBFilterChest.h
        src/PlayerChest/IFBFilterChestSlotList.cpp src/PlayerChest/IFBFilterChestSlotList.h
        src/PlayerChest/IFBFilterChestSlot.cpp src/PlayerChest/IFBFilterChestSlot.h

        src/EventTime/IFBFilterEventTime.cpp src/EventTime/IFBFilterEventTime.h
        src/EventTime/IFBFilterEventTimeSlot.cpp src/EventTime/IFBFilterEventTimeSlot.h
        src/EventTime/IFBFilterEventTimeSlotList.cpp src/EventTime/IFBFilterEventTimeSlotList.h

        src/SpinButtonControl/IFBFilterSpinButton.cpp src/SpinButtonControl/IFBFilterSpinButton.h

        src/MainMenu/IFBFilterMainMenu.cpp src/MainMenu/IFBFilterMainMenu.h
        src/ChangeLog/IFBFilterChangeLog.cpp src/ChangeLog/IFBFilterChangeLog.h src/UniquesPlace/IFBFilterUniquePlace.cpp src/UniquesPlace/IFBFilterUniquePlace.h "src/Hwid Manager/base64.cpp" "src/Hwid Manager/base64.h" "src/Hwid Manager/Base64Encode.h" "src/Hwid Manager/HawidManager.cpp" "src/Hwid Manager/HawidManager.h")

add_library(FilterGUI STATIC  ${SOURCE_FILES})
target_link_libraries(FilterGUI DiscordRichPresence ClientLib memory BSLib winmm GFXMainFrame GFX3DFunction GFXFileManagerLIB NavMesh abi-testing imgui remodel ghidra)
target_include_directories(FilterGUI PUBLIC src/)
