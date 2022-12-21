//
// Created by 赵润朔 on 2022/12/20.
//
#include<iostream>
#include"RbfNetWork.h"

bool RbfNetWork::Initialize() {
    //导入当前路径
    PyRun_SimpleString("import sys\n"
                       "sys.argv = ['']");
   
    PyObject *module_name = PyUnicode_DecodeFSDefault("rbf_nn");
    py_module = PyImport_Import(module_name);
    Py_DECREF(module_name);
    if(!py_module) {
        std::cout << "Failed to load Python module 'rbf_nn'" << "\n";
        PyErr_Print();
        return false;
    }
    py_func_train = PyObject_GetAttrString(py_module, "train");
    if(!py_func_train || !PyCallable_Check(py_func_train)) {
        std::cout << "Failed to load Python function 'train'" << "\n";
        PyErr_Print();
        Py_DECREF(py_module);
        return false;
    }
    return true;
}

void RbfNetWork::Finalize() {
    Py_DECREF(py_func_train);
    Py_DECREF(py_module);
}

std::vector<Eigen::Vector2f>
RbfNetWork::Train(const std::vector<Eigen::Vector2f> &in_pos, int num_middle, int epochs, float l, float r,
                  float step) {
    PyObject *func_args = PyTuple_New(5);
    int n = in_pos.size();
    PyObject *x_list = PyList_New(n);
    PyObject *y_list = PyList_New(n);
    for(int i = 0; i < n; i ++) {
        PyList_SetItem(x_list, i, PyFloat_FromDouble(in_pos[i].x()));
        PyList_SetItem(y_list, i, PyFloat_FromDouble(in_pos[i].y()));
    }
    
    std::vector<float> x_pre;
    for(float x = l; x <= r; x += step) {
        x_pre.push_back(x);
    }
    PyObject *xp_list = PyList_New(x_pre.size());
    for(int i = 0; i < x_pre.size(); i ++) {
        PyList_SetItem(xp_list, i, PyFloat_FromDouble(x_pre[i]));
    }
    PyTuple_SetItem(func_args, 0, x_list);
    PyTuple_SetItem(func_args, 1, y_list);
    PyTuple_SetItem(func_args, 2, PyLong_FromLong(num_middle));
    PyTuple_SetItem(func_args, 3, PyLong_FromLong(epochs));
    PyTuple_SetItem(func_args, 4, xp_list);
    
    PyObject *fn_net = PyObject_CallObject(py_func_train, func_args);
    if(!fn_net) {
        std::cout << "Failed to call Python function train" << "\n";
        PyErr_Print();
        Py_DECREF(x_list);
        Py_DECREF(y_list);
        Py_DECREF(xp_list);
        Py_DECREF(func_args);
        return std::vector<Eigen::Vector2f>();
    }
    std::vector<Eigen::Vector2f> y_pre(x_pre.size());
    for(int i = 0; i < x_pre.size(); i ++) {
        y_pre[i] = {x_pre[i], PyFloat_AsDouble(PyList_GetItem(fn_net, i))};
    } 
    return y_pre;
}
