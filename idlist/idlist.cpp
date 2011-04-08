#include <windows.h>
#include <shlobj.h>
#include <stdio.h>
#include <Shlwapi.h>

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int nCmdShow)
{
	HANDLE sharedMem = NULL;
	DWORD currentProcess = GetCurrentProcessId();
	LPITEMIDLIST pidl = NULL;
	WCHAR command[MAX_PATH];
	SHELLEXECUTEINFO sei;

	ZeroMemory(&sei, sizeof(sei));
	sei.cbSize = sizeof(sei);
	sei.fMask = SEE_MASK_NOASYNC | SEE_MASK_UNICODE;
	sei.lpFile = L"C:\\Windows\\Explorer.exe";
	sei.nShow = SW_SHOW;
	sei.hwnd = GetDesktopWindow();

	if (SUCCEEDED(SHGetFolderLocation(NULL, CSIDL_DRIVES, NULL, 0, &pidl)))
	{
		sharedMem = SHAllocShared(pidl, ILGetSize(pidl), currentProcess);
		ILFree(pidl);

		if (sharedMem)
		{
			swprintf_s(command, L"/idlist,:%d:%d", sharedMem, currentProcess);
			sei.lpParameters = command;
			ShellExecuteEx(&sei);
			Sleep(100);
			return 0;
		}
	}

	return 1;
}
