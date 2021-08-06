#pragma once
#include "ClientNet/MsgStreamBuffer.h"
#include <memory\hook.h>
class Notify
{
public:
	void OnGameNotify(class CMsgStreamBuffer* msg);
};