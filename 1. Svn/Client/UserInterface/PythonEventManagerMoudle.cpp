// Arriba de
PyObject * eventSetVisibleStartLine(PyObject * poSelf, PyObject * poArgs)
{
	...
	...
	...
}

// Agregar
PyObject * eventGetTotalLineCount(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	return Py_BuildValue("i", CPythonEventManager::Instance().GetTotalLineCount(iIndex));
}

// Arriba de
									  {"GetLineCount", eventGetLineCount, METH_VARARGS},
// Agregar
									  {"GetTotalLineCount", eventGetTotalLineCount, METH_VARARGS},
