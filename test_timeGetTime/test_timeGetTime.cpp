// test_timeGetTime.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 

// for timeGetTime()
#pragma comment(lib, "winmm.lib")

//ULONGLONG timeGetTime64()
//{
//	ULONGLONG ret = 0;
//
//	//Server 2003 나 xp 이상부터 지원
//#if (_WIN32_WINNT >= 0x0600)
//	ret = GetTickCount64();
//#else
//	FILETIME ft;
//	GetSystemTimeAsFileTime(&ft);
//	ret |= ft.dwHighDateTime;
//	ret <<= 32;
//	ret |= ft.dwLowDateTime;
//	ret /= 10000; // 100ns -> 1ms로 변환
//#endif
//
//	return ret;
//}


ULONGLONG timeGetTime64_xp() 
{
	ULONGLONG ret = 0;

	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	ret |= ft.dwHighDateTime;
	ret <<= 32;
	ret |= ft.dwLowDateTime;
	ret /= 10000; // 100ns -> 1ms로 변환

	return ret;
}

ULONGLONG timeGetTime64() 
{
	ULONGLONG ret = 0;

	ret = GetTickCount64();

	return ret;
}

void report(LPCTSTR msg, BOOL expression)
{
	//_tprintf(L"%5s\t%s\n", (expression)?L"OK":L"NOK", msg);
	_tprintf(L"%c", (expression) ? '.' : 'X');
}

//#define MAXMONTH 120
#define MAXMONTH (12 * 250)

int _tmain(int argc, _TCHAR* argv[])
{
	_tprintf(L"\ntimeGetTime -----------------------------\n");
	for(DWORD i=1; i<=MAXMONTH; i++)
	{
		TCHAR buf[1024] = {0, };
		_stprintf(buf, L"current + %u month ago", i);

		DWORD v = timeGetTime();
		report(buf, v < v + (i*30*24*60*60*1000));
	}

	_tprintf(L"\nGetTickCount -----------------------------\n");
	for(DWORD i=1; i<=MAXMONTH; i++)
	{
		TCHAR buf[1024] = {0, };
		_stprintf(buf, L"current + %u month ago", i);

		DWORD v = GetTickCount();
		report(buf, v < v + (i*30*24*60*60*1000));
	}

	_tprintf(L"\ntimeGetTime64_xp -----------------------------\n");
	for(ULONGLONG i=1; i<=MAXMONTH; i++)
	{
		TCHAR buf[1024] = {0, };
		_stprintf(buf, L"current + %llu month ago", i);

		ULONGLONG v = timeGetTime64_xp();
		report(buf, v < v + (i*30*24*60*60*1000));
	}

	_tprintf(L"\ntimeGetTime64 -----------------------------\n");
	for(ULONGLONG i=1; i<=MAXMONTH; i++)
	{
		TCHAR buf[1024] = {0, };
		_stprintf(buf, L"current + %llu month ago", i);

		ULONGLONG v = timeGetTime64_xp();
		report(buf, v < v + (i*30*24*60*60*1000));
	}

	_tprintf(L"\n");

	return 0;
}

