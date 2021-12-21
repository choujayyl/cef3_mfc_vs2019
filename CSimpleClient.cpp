#include "pch.h"
#include "CSimpleClient.h"

void CSimpleClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    m_cefBrowser = browser;
}
