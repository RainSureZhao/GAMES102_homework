//
// Created by 赵润朔 on 2022/12/16.
//
#include <vector>

#ifdef MINGW
// MinGW will complain that there is no 'hypot', including "math.h" can fix it (but including "cmath" cannot)
#include <math.h>
#endif

#include <math.h>
#define PY_SSIZE_T_CLEAN
#ifdef _DEBUG
#undef _DEBUG
#include "Python/include/Python.h"
#define _DEBUG
#else
#include "Python/include/Python.h"
#endif
int main()
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;

    Py_Initialize();
    PyRun_SimpleString("import sys\n"
                       "sys.argv = ['']");
//    PyRun_SimpleString("import  sys");
//    PyRun_SimpleString("sys.path.append('./')");
    pName = PyUnicode_DecodeFSDefault("multiply");
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "multiply");
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);
            for (i = 0; i < 2; ++i) {
                pValue = PyLong_FromLong(atoi("40"));
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", "multiply");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", "multiply");
        return 1;
    }
    if (Py_FinalizeEx() < 0) {
        return 120;
    }
}