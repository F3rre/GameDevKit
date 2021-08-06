#pragma once
#include "SOItem.h"
#include "GInterface.h"

class CIFItemComparison
{
	char pad_0000[912]; //0x0000
	CSOItem* _CSOItem; //0x0390

public:
	void AppendAdvancedInfo(class CIFHelperBubbleWindow* window);
};
