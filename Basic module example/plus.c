#include <Python.h>

static PyObject *py_plus(PyObject *self, PyObject *args) {
    double x, y, result;

    if (!PyArg_ParseTuple(args,"dd", &x, &y)) {
        return NULL;
    }
    result = x + y;
    return Py_BuildValue("d", result);
}

static PyMethodDef ownmod_methods[] = {
        {
                "plus", // название функции внутри python
                py_plus, // функция C
                      METH_VARARGS, // макрос, поясняющий, что функция у нас с аргументами
                         "plus function" // документация для функции внутри python
        },
        { NULL, NULL, 0, NULL } // так называемый sentiel. Сколько бы элементов структуры у вас не было, этот нулевой элемент должен быть всегда, и при этом быть последним
};

static PyModuleDef simple_module = {
        /* Описываем наш модуль */
        PyModuleDef_HEAD_INIT, // обязательный макрос
        "my_plus", // my_plus.__name__
        "amazing documentation", // my_plus.__doc__
        -1,
        ownmod_methods // сюда передаем методы модуля
};

// в названии функции обязательно должен быть префикс PyInit
PyMODINIT_FUNC PyInit_my_plus(void) {
    PyObject* m;
// создаем модуль
    m = PyModule_Create(&simple_module);
// если все корректно, то эта проверка не проходит
    if (m == NULL)
        return NULL;
    return m;
}