#pragma once
#include <include/cef_command_line.h>
//#include "include/cef_app.h"
#include "include/cef_client.h"

class CSimpleClient : public CefClient, public CefLifeSpanHandler,public CefKeyboardHandler
{
public:
    CSimpleClient() {};
    ~CSimpleClient() {};

    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override
    {
        return this;
    }

    // CefLifeSpanHandler methods:
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

    CefRefPtr<CefBrowser> GetBrowser() { return m_cefBrowser; }

    ////重新这里用来在代码里执行command-line
    //virtual void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) override
    //{
    //    //flash插件
    //    command_line->AppendSwitch("--disable-web-security");
    //    command_line->AppendSwitch("--disable-site-isolation-trials");
    //}
    virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override
    {
        return this;
    }
    virtual bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event, bool* is_keyboard_shortcut) ;
    virtual  bool OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event) ;

    void ShowDevTools(CefRefPtr<CefBrowser> browser, const CefPoint& inspect_element_at);

private:
    CefRefPtr<CefBrowser> m_cefBrowser;

    IMPLEMENT_REFCOUNTING(CSimpleClient);
};
