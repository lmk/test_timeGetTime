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

TCHAR* getAgo(ULONGLONG ms, TCHAR* out)
{
	TCHAR buf[256] = { 0, };

	ULONGLONG day=0, hour=0, min=0, sec=0;
	day = ms / 24 / 60 / 60 / 1000;
	ms -= (day * 24 * 60 * 60 * 1000);

	hour = ms / 60 / 60 / 1000;
	ms -= (hour *60 * 60 * 1000);

	min = ms / 60 / 1000;
	ms -= (min * 60 * 1000);

	sec = ms / 1000;
	ms -= (sec * 1000);

	if (day) _stprintf(buf, L" %llu days", day);
	_tcscat(out, buf);

	if (hour) _stprintf(buf, L" %llu hours", hour);
	_tcscat(out, buf);

	if (min) _stprintf(buf, L" %llu minutes", min);
	_tcscat(out, buf);

	_stprintf(buf, L" %llu secounds ago", sec);
	_tcscat(out, buf);

	return out;
}

//#define MAXMONTH 120
#define MAXMONTH (12 * 250)

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR ago[1024] = { 0, };

	_tprintf(L"\ntimeGetTime %s -----------------------------\n", getAgo(timeGetTime(), ago));
	for(DWORD i=1; i<=MAXMONTH; i++)
	{
		TCHAR buf[1024] = {0, };
		_stprintf(buf, L"current + %u month ago", i);

		DWORD v = timeGetTime();
		report(buf, v < v + (i*30*24*60*60*1000));
	}

	memset(ago, 0, sizeof(ago));
	_tprintf(L"\nGetTickCount %s -----------------------------\n", getAgo(GetTickCount(), ago));
	for(DWORD i=1; i<=MAXMONTH; i++)
	{
		TCHAR buf[1024] = {0, };
		_stprintf(buf, L"current + %u month ago", i);

		DWORD v = GetTickCount();
		report(buf, v < v + (i*30*24*60*60*1000));
	}

	memset(ago, 0, sizeof(ago));
	_tprintf(L"\ntimeGetTime64_xp %s -----------------------------\n", getAgo(timeGetTime64_xp(), ago));
	for(ULONGLONG i=1; i<=MAXMONTH; i++)
	{
		TCHAR buf[1024] = {0, };
		_stprintf(buf, L"current + %llu month ago", i);

		ULONGLONG v = timeGetTime64_xp();
		report(buf, v < v + (i*30*24*60*60*1000));
	}

	memset(ago, 0, sizeof(ago));
	_tprintf(L"\ntimeGetTime64 %s -----------------------------\n", getAgo(timeGetTime64(), ago));
	for(ULONGLONG i=1; i<=MAXMONTH; i++)
	{
		TCHAR buf[1024] = {0, };
		_stprintf(buf, L"current + %llu month ago", i);

		ULONGLONG v = timeGetTime64();
		report(buf, v < v + (i*30*24*60*60*1000));
	}

	_tprintf(L"\n");

	return 0;
}

