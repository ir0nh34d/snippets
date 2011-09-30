#define UNICODE 1

#include <windows.h>

typedef HRESULT STDAPICALLTYPE SHOWHTMLDIALOGFN (
    HWND hwndParent,
    IMoniker *pMk,
    VARIANT *pvarArgIn,
    WCHAR *pchOptions,
    VARIANT *pvarArgOut
);

typedef HRESULT STDAPICALLTYPE CreateURLMoniker(
    IMoniker *pMkCtx,
    LPCWSTR szURL,
    IMoniker **ppmk
);

int main(void)
{
  HINSTANCE hinstMSHTML = LoadLibrary(TEXT("MSHTML.DLL"));
  HINSTANCE hinstURLMON = LoadLibrary(TEXT("URLMON.DLL"));

  if ((hinstMSHTML == NULL) || (hinstURLMON == NULL))
    {
      // Error loading module -- fail as securely as possible
      return 1;
    }

  OleInitialize(NULL);

  SHOWHTMLDIALOGFN* pfnShowHTMLDialog;
  pfnShowHTMLDialog = (SHOWHTMLDIALOGFN*)GetProcAddress(hinstMSHTML,
                                                        "ShowHTMLDialog");
  CreateURLMoniker* pfnCreateURLMoniker;
  pfnCreateURLMoniker = (CreateURLMoniker*)GetProcAddress(hinstURLMON,
                                                        "CreateURLMoniker");
  if (pfnShowHTMLDialog && pfnCreateURLMoniker)
    {
      IMoniker *pURLMoniker;
      BSTR bstrURL = SysAllocString(L"http://sites.google.com/site/emergedesktop/Home");
      (*pfnCreateURLMoniker)(NULL, bstrURL, &pURLMoniker);

      if (pURLMoniker)
        {
          (*pfnShowHTMLDialog)(NULL, pURLMoniker, NULL, (WCHAR*)L"dialogWidth:900px", NULL);
          pURLMoniker->Release();
        }

      SysFreeString(bstrURL);
    }

  FreeLibrary(hinstMSHTML);
  FreeLibrary(hinstURLMON);

  OleUninitialize();

  return 0;
}
