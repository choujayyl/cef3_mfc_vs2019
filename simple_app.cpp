// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_app.h"

#include <string>

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
//#include "tests/cefsimple/simple_handler.h"

//namespace {
//
//// When using the Views framework this object provides the delegate
//// implementation for the CefWindow that hosts the Views-based browser.
//class SimpleWindowDelegate : public CefWindowDelegate {
// public:
//  explicit SimpleWindowDelegate(CefRefPtr<CefBrowserView> browser_view)
//      : browser_view_(browser_view) {}
//
//  void OnWindowCreated(CefRefPtr<CefWindow> window) override {
//    // Add the browser view and show the window.
//    window->AddChildView(browser_view_);
//    window->Show();
//
//    // Give keyboard focus to the browser view.
//    browser_view_->RequestFocus();
//  }
//
//  void OnWindowDestroyed(CefRefPtr<CefWindow> window) override {
//    browser_view_ = nullptr;
//  }
//
//  bool CanClose(CefRefPtr<CefWindow> window) override {
//    // Allow the window to close if the browser says it's OK.
//    CefRefPtr<CefBrowser> browser = browser_view_->GetBrowser();
//    if (browser)
//      return browser->GetHost()->TryCloseBrowser();
//    return true;
//  }
//
//  CefSize GetPreferredSize(CefRefPtr<CefView> view) override {
//    return CefSize(800, 600);
//  }
//
// private:
//  CefRefPtr<CefBrowserView> browser_view_;
//
//  IMPLEMENT_REFCOUNTING(SimpleWindowDelegate);
//  DISALLOW_COPY_AND_ASSIGN(SimpleWindowDelegate);
//};
//
//class SimpleBrowserViewDelegate : public CefBrowserViewDelegate {
// public:
//  SimpleBrowserViewDelegate() {}
//
//  bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view,
//                                 CefRefPtr<CefBrowserView> popup_browser_view,
//                                 bool is_devtools) override {
//    // Create a new top-level Window for the popup. It will show itself after
//    // creation.
//    CefWindow::CreateTopLevelWindow(
//        new SimpleWindowDelegate(popup_browser_view));
//
//    // We created the Window.
//    return true;
//  }
//
// private:
//  IMPLEMENT_REFCOUNTING(SimpleBrowserViewDelegate);
//  DISALLOW_COPY_AND_ASSIGN(SimpleBrowserViewDelegate);
//};
//
//}  // namespace

SimpleApp::SimpleApp() {}

void SimpleApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context)
{
    // The var type can accept all object or variable
    CefRefPtr<CefV8Value> window = context->GetGlobal();

    // bind value into window[or you can bind value into window sub node]
    CefRefPtr<CefV8Value> strValue = CefV8Value::CreateString("say yes");
    window->SetValue("say_yes", strValue, V8_PROPERTY_ATTRIBUTE_NONE);

    CefRefPtr<CefV8Handler> handler = new SimpleApp();
    window->SetValue("register",
        CefV8Value::CreateFunction("register", handler),
        V8_PROPERTY_ATTRIBUTE_NONE);
}

bool SimpleApp::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if (name == "register")
    {
        if (arguments.size() == 1 && arguments[0]->IsFunction())
        {
            CefRefPtr<CefV8Value> callbackFunc = arguments[0];
            CefRefPtr<CefV8Context> callbackContext = CefV8Context::GetCurrentContext();

            CefV8ValueList args;
            args.push_back(CefV8Value::CreateInt(3));
            args.push_back(CefV8Value::CreateInt(4));

            CefRefPtr<CefV8Value> ret = callbackFunc->ExecuteFunctionWithContext(callbackContext, object, args);

            if (ret == nullptr)
            {
                MessageBox(NULL, L"Hello, Windows!", L"hello", MB_OK);
            }
            else
            {
                //QMessageBox::information(nullptr, "title", QString("%1").arg(ret->GetIntValue()));
                std::string tmp = std::to_string(ret->GetIntValue());
                std::wstring stemp = std::wstring(tmp.begin(), tmp.end());
                LPCWSTR sw = stemp.c_str();
                MessageBox(NULL, sw,L"title", MB_OK);
            }
            return true;
        }
    }

    return false;

}

CefRefPtr<CefBrowserProcessHandler> SimpleApp::GetBrowserProcessHandler()
{
    return this;
}

CefRefPtr<CefRenderProcessHandler> SimpleApp::GetRenderProcessHandler()
{
    return this;
}

//
//void SimpleApp::OnContextInitialized() {
//  CEF_REQUIRE_UI_THREAD();
//
//  CefRefPtr<CefCommandLine> command_line =
//      CefCommandLine::GetGlobalCommandLine();
//
//  // Create the browser using the Views framework if "--use-views" is specified
//  // via the command-line. Otherwise, create the browser using the native
//  // platform framework.
//  const bool use_views = command_line->HasSwitch("use-views");
//
//  // SimpleHandler implements browser-level callbacks.
//  CefRefPtr<SimpleHandler> handler(new SimpleHandler(use_views));
//
//  // Specify CEF browser settings here.
//  CefBrowserSettings browser_settings;
//
//  std::string url;
//
//  // Check if a "--url=" value was provided via the command-line. If so, use
//  // that instead of the default URL.
//  url = command_line->GetSwitchValue("url");
//  if (url.empty())
//    url = "http://www.google.com";
//
//  if (use_views) {
//    // Create the BrowserView.
//    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(
//        handler, url, browser_settings, nullptr, nullptr,
//        new SimpleBrowserViewDelegate());
//
//    // Create the Window. It will show itself after creation.
//    CefWindow::CreateTopLevelWindow(new SimpleWindowDelegate(browser_view));
//  } else {
//    // Information used when creating the native window.
//    CefWindowInfo window_info;
//
//#if defined(OS_WIN)
//    // On Windows we need to specify certain flags that will be passed to
//    // CreateWindowEx().
//    window_info.SetAsPopup(nullptr, "cefsimple");
//#endif
//
//    // Create the first browser window.
//    CefBrowserHost::CreateBrowser(window_info, handler, url, browser_settings,
//                                  nullptr, nullptr);
//  }
//}

//CefRefPtr<CefClient> SimpleApp::GetDefaultClient() {
//  // Called when a new browser window is created via the Chrome runtime UI.
//  return SimpleHandler::GetInstance();
//}
