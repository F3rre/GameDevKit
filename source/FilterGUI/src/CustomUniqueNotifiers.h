#pragma once
#include <iostream>
#include <vector>

class CustomUniqueNotifiers
{
public:
	void NewMsg(std::wstring* NameStrID);
	void OnUniqueNameRetrieve(std::wstring* NameStrID);
};