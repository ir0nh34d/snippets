#define _WIN32_WINNT 0x0600

#include <windows.h>
#include <shlobj.h>
#include <stdio.h>

typedef HANDLE (WINAPI *lpfnSHAllocShared)(const void*, DWORD, DWORD);
typedef BOOL (WINAPI *lpfnSHFreeShared)(HANDLE, DWORD);

int main(void)
{
  HANDLE sharedMem = NULL;
  DWORD currentProcess = GetCurrentProcessId();
  LPITEMIDLIST pidl = NULL;
  char command[MAX_PATH];
  SHELLEXECUTEINFO sei;
  HMODULE shlwapiDLL = LoadLibrary("shlwapi.dll");
  int ret = 1;
  lpfnSHAllocShared SHAllocShared = (lpfnSHAllocShared)GetProcAddress(shlwapiDLL, "SHAllocShared");
  lpfnSHFreeShared SHFreeShared = (lpfnSHFreeShared)GetProcAddress(shlwapiDLL, "SHFreeShared");

  ZeroMemory(&sei, sizeof(sei));
  sei.cbSize = sizeof(sei);
  sei.fMask = SEE_MASK_UNICODE | SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_DDEWAIT;
  sei.lpFile = "c:\\windows\\explorer.exe";
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
              sprintf(command, "/idlist,:%ld:%ld", (long)sharedMem, (long)currentProcess);
              sei.lpParameters = command;
              if (ShellExecuteEx(&sei))
                {
                  if (!sei.hProcess)
                    fprintf(stdout, "hProcess is NULL\n");
                  WaitForSingleObject(sei.hProcess, INFINITE);
                  ret = 0;
                  fprintf(stdout, "Finished: successful\n");
                }
              else
                fprintf(stdout, "Finished: unsuccessful\n");
              SHFreeShared(sharedMem, currentProcess);
            }
        }
    }

  FreeLibrary(shlwapiDLL);

  return ret;
}
