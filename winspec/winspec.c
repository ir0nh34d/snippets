#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  HWND hwnd;
  RECT rect;

  if (argc < 2)
    {
      fprintf(stderr, "Usage: %s <Window Class>\n", argv[0]);
      return 1;
    }

  hwnd = FindWindow(argv[1], NULL);
  if (hwnd == NULL)
    {
      fprintf(stderr, "Failed to find window with class: %s\n", argv[1]);
      return 2;
    }

  GetWindowRect(hwnd, &rect);

  fprintf(stdout, "Class: %s\n", argv[1]);
  fprintf(stdout, "Handle: 0x%x\n", (unsigned int)hwnd);
  fprintf(stdout, "Rect: %ld, %ld, %ld, %ld\n", rect.left, rect.top, rect.right, rect.bottom);

  return 0;
}

