# -*- Mode: Python; py-indent-offset: 4 -*-
# coding=utf-8
# vim: tabstop=4 shiftwidth=4 expandtab

import unittest

import gi

try:
    gi.require_foreign("javascriptcore")
    import javascriptcore
    has_javascriptcore = True
except ImportError:
    has_Javascriptcore = False

try:
    from gi.repository import WebKit2
    has_webkit2 = True
except:
    has_webkit2 = None


@unittest.skipUnless(has_javascriptcore, 'build without javascriptcore support')
@unittest.skipUnless(has_webkit2, 'WebKit2 not available')
class testWebKitJSContext(unittest.TestCase):
    def test_global_context(self):
        webView = WebKit2.WebView()
        ctx = webView.get_javascript_global_context()
        self.assertIsInstance(ctx, javascriptcore.JSContext)
        self.assertIsInstance(ctx.globalObject, javascriptcore.JSObject)
        self.assertTrue(ctx.evaluateScript("true"))

if __name__ == '__main__':
    unittest.main()
