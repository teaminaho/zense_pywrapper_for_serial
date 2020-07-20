# distutils: language = c++
# distutils: sources = src/pico_zense_module_for_serial.cpp

from libc.stdint cimport int32_t, uint32_t
from libcpp.vector cimport vector
from libcpp.string cimport string
from libcpp cimport bool
import toml
import faulthandler
import numpy as np
cimport numpy as np


cdef public api void call_a_cy_func(char* method, bint *error):
    if (method in globals()):
        error[0] = 0
        globals()[method]()
    else:
        error[0] = 1

# For Buffer usage
cdef extern from "Python.h":
    ctypedef struct PyObject
    object PyMemoryView_FromBuffer(Py_buffer *view)
    int PyBuffer_FillInfo(Py_buffer *view, PyObject *obj, void *buf, Py_ssize_t len, int readonly, int infoflags)
    enum:
        PyBUF_FULL_RO

cdef extern from "pico_zense_module_for_serial.hpp" namespace "zense":
    void ShutdownWithSEGVHandling()
    void Shutdown()
    cdef cppclass PicoZenseModuleForSerial:
        PicoZenseModuleForSerial(int32_t sensor_idx_)except +
        string getSerialNumber()
        vector[double] getCameraParameter()
        vector[double] getRGBCameraParameter()
        vector[vector[double]] getExtrinsicParameter()
        uint32_t getDeviceCount()
        void closeDevice()
        void shutdown()

def shutdown_():
    ShutdownWithSEGVHandling()

cdef class PyPicoZenseModuleForSerial:
    cdef PicoZenseModuleForSerial *thisptr

    def __cinit__(self, sensor_idx_):
        self.thisptr = new PicoZenseModuleForSerial(sensor_idx_)

    def shutdown(self):
        shutdown_()

    def close(self):
        self.thisptr.closeDevice()

    def getSerialNumber(self):
        return self.thisptr.getSerialNumber()

    def getDeviceCount(self):
        return self.thisptr.getDeviceCount()

    def getCameraParameter(self):
        return self.thisptr.getCameraParameter()

    def getRGBCameraParameter(self):
        return self.thisptr.getRGBCameraParameter()

    def getExtrinsicParameter(self):
        return self.thisptr.getExtrinsicParameter()

