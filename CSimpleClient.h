#pragma once
#include <include/cef_command_line.h>
//#include "include/cef_app.h"
#include "include/cef_client.h"

class CSimpleClient : public CefClient, public CefLifeSpanHandler
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

    ////�������������ڴ�����ִ��command-line
    //virtual void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) override
    //{
    //    //flash���
    //    command_line->AppendSwitch("--disable-web-security");
    //    command_line->AppendSwitch("--disable-site-isolation-trials");
    //}

private:
    CefRefPtr<CefBrowser> m_cefBrowser;

    IMPLEMENT_REFCOUNTING(CSimpleClient);
};
