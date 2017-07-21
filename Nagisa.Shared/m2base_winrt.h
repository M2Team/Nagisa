/******************************************************************************
Project:M2-Team Common Library
Description: Implemention for base functions for Windows Runtime
File Name: m2base_winrt.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _M2BASE_WINRT_
#define _M2BASE_WINRT_

#include <Windows.h>

/*
The m2_base_winrt_find_sub_string function finds a sub string from a source 
string. 
The ignore_case option can determines whether to ignore case.
If success, it will return true.
*/
static bool m2_base_winrt_find_sub_string(
	Platform::String^ source_string,
	Platform::String^ sub_string,
	bool ignore_case)
{
	return (FindNLSStringEx(
		nullptr,
		(ignore_case ? NORM_IGNORECASE : 0) | FIND_FROMSTART,
		source_string->Data(),
		source_string->Length(),
		sub_string->Data(),
		sub_string->Length(),
		nullptr,
		nullptr,
		nullptr,
		0) >= 0);
}

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#endif