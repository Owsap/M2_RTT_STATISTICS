/// 1.
// Search
PyObject* appGetRenderFPS(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonApplication::Instance().GetRenderFPS());
}

// Add below
#if defined(ENABLE_RTT_STATISTICS)
PyObject* appGetRTT(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonApplication::Instance().GetRTT());
}

PyObject* appGetPacketLossPct(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("f", CPythonApplication::Instance().GetPacketLossPct());
}
#endif

/// 2.
// Search
		{ "GetRenderFPS", appGetRenderFPS, METH_VARARGS },

// Add below
#if defined(ENABLE_RTT_STATISTICS)
		{ "GetRTT", appGetRTT, METH_VARARGS },
		{ "GetPacketLossPct", appGetPacketLossPct, METH_VARARGS },
#endif

/// 2.
// Search
	PyModule_AddIntConstant(poModule, "CAMERA_STOP", CPythonApplication::CAMERA_STOP);

// Add below
#if defined(ENABLE_RTT_STATISTICS)
	PyModule_AddIntConstant(poModule, "ENABLE_RTT_STATISTICS", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_RTT_STATISTICS", 0);
#endif