// Despues de
PyObject * wndButtonDown(PyObject * poSelf, PyObject * poArgs)
{
	...
	...
	...
}

// Agregar
PyObject * wndButtonOver(PyObject * poSelf, PyObject * poArgs)
{
	UI::CWindow * pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	((UI::CButton*)pWindow)->Over();

	return Py_BuildNone();
}

// Despues de
									  {"Down", wndButtonDown, METH_VARARGS},

// Agregar
									  {"Over", wndButtonOver, METH_VARARGS},
