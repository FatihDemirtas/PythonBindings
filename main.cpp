//#define PY_SSIZE_T_CLEAN
#include <stdio.h>
#include <iostream>
#include <Python.h>
#include <filesystem>
#include <opencv2\highgui\highgui.hpp>
#include <chrono>
#include <string>  

using namespace std;
namespace fs = std::experimental::filesystem;

int main() 
{

    std::cout << "Current path is " << fs::current_path() << '\n';
    Py_Initialize();
    
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("."));

    PyObject * ModuleString = PyUnicode_FromString((char*) "multiply");
    if (ModuleString == NULL)
        printf("file not found");
    else
        printf("%s\n", PyUnicode_AsUTF8(ModuleString));

    PyObject * Module = PyImport_Import(ModuleString);
    if (Module == nullptr)
        printf("no Module\n");

    PyObject * Dict = PyModule_GetDict(Module);
    PyObject * multiply = PyDict_GetItemString(Dict, "multiply");
    PyObject * add = PyDict_GetItemString(Dict, "add");
    PyObject * callFromAnotherScript = PyDict_GetItemString(Dict, "callFromAnotherScript");
    PyObject * pArgs = PyTuple_New(2);
    PyObject * pValue1 = PyLong_FromLong(3);
    PyObject * pValue2 = PyLong_FromLong(7);
    PyTuple_SetItem(pArgs, 0, pValue1);
    PyTuple_SetItem(pArgs, 1, pValue2);

    PyObject * Result_m = PyObject_CallObject(multiply, pArgs);
    PyObject * Result_a = PyObject_CallObject(add, pArgs);
    PyObject * imshow = PyDict_GetItemString(Dict, "imshow");

    auto start = std::chrono::high_resolution_clock::now();
    PyObject * Result_i = PyObject_CallObject(imshow, NULL);
    auto finish = std::chrono::high_resolution_clock::now();
    auto elapsed = finish - start;
    std::cout << "(C++) Adaptive threshold elapsed = " << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << std::endl;
    //PyObject * RETURN = PyObject_CallObject(callFromAnotherScript, NULL);

    int rows = 0, cols = 0; 
    PyObject * result_i = NULL;
    PyArg_ParseTuple(Result_i, "iiO", &rows, &cols, &result_i);
    uchar *data = (uchar *)PyByteArray_AsString(result_i);
    cv::Mat img(rows, cols, CV_8UC1, data);
    //cv::imshow("c++ image", img);
    //cv::waitKey(0);

    int result_1 = 0, result_2 = 0, result_3 = 0, result_4 = 0;
    //PyArg_ParseTuple(RETURN, "iiii", &result_1, &result_2, &result_3, &result_4);

    long result_m = PyLong_AsLong(Result_m);
    long result_a = PyLong_AsLong(Result_a);

    printf("Multiplication Result from C++ is : %d \n", result_m);
    printf("Addition Result from C++ is : %d \n", result_a);
    printf("Roi Result from C++ is : %d , %d , %d , %d \n", result_1, result_2, result_3, result_4);

    Py_Finalize();

    return 0;
}