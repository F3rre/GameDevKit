#pragma once

#include <cstdlib>

#define STRING(s) #s

#define ENSURE_SIZE(class_name, sz) \
	int size_check ## class_name [ sizeof(class_name) == sz ? 1 : -1 ];


#define check_size(class_name, sz) \
	check_size_tpl<class_name, sz>(STRING(class_name))

template<typename T, std::size_t expected_size>
bool check_size_tpl(const char *class_name)
{
	bool size_ok = sizeof(T) == expected_size;
	printf("[%s] sizeof(%s) 0x%X %s 0x%X\n", size_ok ? "OK" : "FAIL", class_name, sizeof(T), size_ok ? "==" : "!=", expected_size);
	return size_ok;
}