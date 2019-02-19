#include "pch.h"

#define EC_W32(fnx) \
	[&]() -> LSTATUS { \
	const auto _lresult = (fnx); \
	if (_lresult != ERROR_SUCCESS) wprintf(L"lResult = 0x%08X from %hs\r\n", _lresult, #fnx); \
	return _lresult; \
	}()

int main()
{
	wprintf(L"Broadcasting WM_SETTINGCHANGE\r\n");
	auto lresult = EC_W32(::SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE, NULL, NULL, SMTO_ABORTIFHUNG, 1000, NULL));
	if (lresult != ERROR_SUCCESS)
	{
		auto err = GetLastError();
		if (err == ERROR_TIMEOUT)
		{
			wprintf(L"Got ERROR_TIMEOUT (0x%08X) from WM_SETTINGCHANGE\r\n", err);
		}
		else
		{
			wprintf(L"Got 0x%08X from WM_SETTINGCHANGE\r\n", err);
		}
	}
}