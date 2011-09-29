#include <windows.h>
#include <stdio.h>

void CreateInstance(const char *application, int index);

int main(void)
{
  int index = 0;
  CreateInstance("cmd.exe", index);
  index++;
  CreateInstance("taskmgr.exe", index);

  return 0;
}

void CreateInstance(const char *application, int index)
{
  char scount[2];
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(si));
  ZeroMemory(&pi, sizeof(pi));

  si.cb = sizeof(si);
  si.dwFlags = STARTF_USESHOWWINDOW;
  si.wShowWindow = SW_SHOW;

  if (SetEnvironmentVariable("AppletCount", _itoa(index, scount, 10)))
    {
      if (CreateProcess(NULL,
                        (char*)application,
                        NULL,
                        NULL,
                        FALSE,
                        NORMAL_PRIORITY_CLASS,
                        NULL,
                        NULL,
                        &si,
                        &pi))
        {
          CloseHandle(pi.hProcess);
          CloseHandle(pi.hThread);
        }
    }
}
