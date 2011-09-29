#define UNICODE 1

#include <windows.h>
#include <mshtmhst.h>

int main(void)
{
  HINSTANCE hinstMSHTML = LoadLibrary(TEXT("MSHTML.DLL"));

  if (hinstMSHTML == NULL)
    {
      // Error loading module -- fail as securely as possible
      return 1;
    }

  SHOWHTMLDIALOGFN* pfnShowHTMLDialog;
  pfnShowHTMLDialog = (SHOWHTMLDIALOGFN*)GetProcAddress(hinstMSHTML,
                                                        "ShowHTMLDialog");
  if (pfnShowHTMLDialog)
    {
      IMoniker *pURLMoniker;
      BSTR bstrURL = SysAllocString(L"http://sites.google.com/site/emergedesktop/Home");
      CreateURLMoniker(NULL, bstrURL, &pURLMoniker);

      if (pURLMoniker)
        {
          (*pfnShowHTMLDialog)(NULL, pURLMoniker, NULL, (WCHAR*)L"dialogWidth:900px", NULL);
          pURLMoniker->Release();
        }

      SysFreeString(bstrURL);
    }

  FreeLibrary(hinstMSHTML);

  return 0;
}
