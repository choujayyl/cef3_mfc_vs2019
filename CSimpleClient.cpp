#include "pch.h"
#include "CSimpleClient.h"

void CSimpleClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    m_cefBrowser = browser;
}

bool CSimpleClient::OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event,
	bool* is_keyboard_shortcut)
{
	if(event.type == KEYEVENT_RAWKEYDOWN)
	{
		if(event.windows_key_code == VK_F5)
		{
			browser->Reload();
			return true;
		}
		else if(event.windows_key_code == VK_F12)
		{
			ShowDevTools(browser, CefPoint());
			return true;
		}
	}

	return false;
}

bool CSimpleClient::OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event)
{
	return false;
}

void CSimpleClient::ShowDevTools(CefRefPtr<CefBrowser> browser, const CefPoint& inspect_element_at)
{
	CefWindowInfo windowInfo;
	CefBrowserSettings settings;

#if defined(OS_WIN)

	//CRect rect;
	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	//RECT rc = {rect.right / 2, 0, rect.right, rect.bottom };
	//windowInfo.SetAsWindowless(browser->GetHost()->GetWindowHandle());

	//windowInfo.SetAsPopup(browser->GetHost()->GetWindowHandle(), "DevTools");
	windowInfo.SetAsPopup(NULL, "DevTools");

	//windowInfo.SetAsChild(m_hParent->m_hWnd, rc);
	//windowInfo.SetAsChild(*theApp.m_pMainWnd, rc);
#endif

	browser->GetHost()->ShowDevTools(windowInfo, this, settings, CefPoint());

}
