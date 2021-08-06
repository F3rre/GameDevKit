#pragma once
#include "SOItem.h"

class CIFItemComparison
{
	char pad_0000[912]; //0x0000
	CSOItem* _CSOItem; //0x0390

public:
	void AppendAdvancedInfo(class CIFHelperBubbleWindow* window);
	void GlobalItems(class CIFHelperBubbleWindow* window);
};


class ItemUsage
{
public:
	static void Initialize();
	static void OnNameChangeUsage(void);
	static void OnHook(void);
};