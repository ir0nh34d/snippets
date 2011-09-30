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
  WCHAR docs[MAX_PATH], fullpath[MAX_PATH];

  wcscpy(docs, L".\\docs\\the_basics.html");
  GetFullPathName(docs, MAX_PATH, fullpath, NULL);

  if ((hinstMSHTML == NULL) || (hinstURLMON == NULL))
    {
      // Error loading module -- fail as securely as possible
      return 1;
    }

  SHOWHTMLDIALOGFN* pfnShowHTMLDialog;
  pfnShowHTMLDialog = (SHOWHTMLDIALOGFN*)GetProcAddress(hinstMSHTML,
                                                        "ShowHTMLDialog");
  CreateURLMoniker* pfnCreateURLMoniker;
  pfnCreateURLMoniker = (CreateURLMoniker*)GetProcAddress(hinstURLMON,
                                                        "CreateURLMoniker");
  if (pfnShowHTMLDialog && pfnCreateURLMoniker)
    {
      IMoniker *pURLMoniker;
      BSTR bstrURL = SysAllocString(fullpath);
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

  return 0;
}
