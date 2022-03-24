// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

#include "include/cef_app.h"
#include "include/cef_v8.h"
// Implement application-level callbacks for the browser process.
class SimpleApp : public CefApp, public CefBrowserProcessHandler,
public CefRenderProcessHandler, public CefV8Handler
{
 public:
  SimpleApp();

  // CefApp methods:

  void OnBeforeCommandLineProcessing(const CefString& process_type,
      CefRefPtr<CefCommandLine> command_line) override
  {
      command_line->AppendSwitch("--disable-web-security");
      command_line->AppendSwitch("--disable-site-isolation-trials");
  }

  // CefBrowserProcessHandler methods:
  //void OnContextInitialized() override;
  //CefRefPtr<CefClient> GetDefaultClient() override;
  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;
  virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;

  virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;

	virtual bool Execute(const CefString& name,
      CefRefPtr<CefV8Value> object,
      const CefV8ValueList& arguments,
      CefRefPtr<CefV8Value>& retval,
      CefString& exception) override;

 private:
  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(SimpleApp);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
