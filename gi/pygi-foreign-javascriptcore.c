/* -*- mode: C; c-basic-offset: 4; indent-tabs-mode: nil; -*- */
/*
 * Copyright (c) 2016  Adrian Freund <freundadrian@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <JavaScriptCore/JSBase.h>
#include <JavaScriptCore/JSContextRef.h>
#include <Python.h>

#if PY_VERSION_HEX < 0x03000000
#include <pyjavascriptcore.h>
#else
#include <py3javascriptcore.h>
#endif
#include <pygi-foreign-api.h>
#include <pyglib-python-compat.h>
#include <stdio.h>

/*
 * JSContext marshaling
 */

static PyObject *
javascriptcore_jscontext_to_arg (PyObject        *value,
                      GIInterfaceInfo *interface_info,
                      GITransfer       transfer,
                      GIArgument      *arg)
{
    JSGlobalContextRef ctx;

    g_assert (transfer == GI_TRANSFER_NOTHING);

    ctx = (JSGlobalContextRef) PyJSContext_GetContext (value);
    if (!ctx) {
        return NULL;
    }

    arg->v_pointer = ctx;
    Py_RETURN_NONE;
}

static PyObject *
javascriptcore_jscontext_from_arg (GIInterfaceInfo *interface_info,
                        GITransfer       transfer,
                        gpointer         data)
{
    JSGlobalContextRef context = (JSGlobalContextRef) data;

	JSGlobalContextRetain(context);

	return PyJSContext_New (context);
}


static PyObject *
javascriptcore_jscontext_release (GIBaseInfo *base_info,
                       gpointer    struct_)
{
	//No need to release. This is already done by pyjavascriptcore
    Py_RETURN_NONE;
}


static PyMethodDef _gi_javascriptcore_functions[] = { {0,} };
PYGLIB_MODULE_START(_gi_javascriptcore, "_gi_javascriptcore")
{
	import_javascriptcore();
    pygobject_init (3, 13, 2);

    pygi_register_foreign_struct ("JavaScriptCore",
                                  "GlobalContext",
                                  javascriptcore_jscontext_to_arg,
                                  javascriptcore_jscontext_from_arg,
                                  javascriptcore_jscontext_release);
}
PYGLIB_MODULE_END
