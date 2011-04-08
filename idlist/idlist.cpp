#define UNICODE

#include <windows.h>
#include <shlobj.h>
#include <stdio.h>
#include <Shlwapi.h>

#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

typedef HANDLE (WINAPI *lpfnSHAllocShared)(const void*, DWORD, DWORD);
typedef BOOL (WINAPI *lpfnSHFreeShared)(HANDLE, DWORD);

int WINAPI WinMain (HINSTANCE hInstance UNUSED,
                    HINSTANCE hPrevInstance UNUSED,
                    LPSTR lpCmdLine UNUSED,
                    int nCmdShow UNUSED)
{
  HANDLE sharedMem = NULL;
  DWORD currentProcess = GetCurrentProcessId();
  LPITEMIDLIST pidl = NULL;
  WCHAR command[MAX_PATH];
  SHELLEXECUTEINFO sei;
  HMODULE shlwapiDLL = LoadLibrary(L"shlwapi.dll");
  int ret = 1;
  lpfnSHAllocShared SHAllocShared = (lpfnSHAllocShared)GetProcAddress(shlwapiDLL, "SHAllocShared");
  lpfnSHFreeShared SHFreeShared = (lpfnSHFreeShared)GetProcAddress(shlwapiDLL, "SHFreeShared");

  ZeroMemory(&sei, sizeof(sei));
  sei.cbSize = sizeof(sei);
  sei.fMask = SEE_MASK_UNICODE | SEE_MASK_NOCLOSEPROCESS;
  sei.lpFile = L"c:\\windows\\explorer.exe";
  sei.nShow = SW_SHOW;
  sei.hwnd = GetDesktopWindow();

  if (SHAllocShared && SHFreeShared)
    {
      if (SUCCEEDED(SHGetFolderLocation(NULL, CSIDL_DRIVES, NULL, 0, &pidl)))
        {
          sharedMem = SHAllocShared(pidl, ILGetSize(pidl), currentProcess);
          ILFree(pidl);

          if (sharedMem)
            {
              swprintf(command, L"/idlist,:%d:%d", sharedMem, currentProcess);
              sei.lpParameters = command;
              ShellExecuteEx(&sei);
              WaitForSingleObject(sei.hProcess, INFINITE);
              SHFreeShared(sharedMem, currentProcess);
              ret = 0;
            }
        }
    }

  FreeLibrary(shlwapiDLL);

  return ret;
}
