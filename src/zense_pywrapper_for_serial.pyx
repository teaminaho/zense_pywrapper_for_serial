# distutils: language = c++
# distutils: sources = src/pico_zense_module_for_serial.cpp

from libc.stdint cimport uint32_t
from libcpp.vector cimport vector
from libcpp.string cimport string
from libcpp cimport bool
import toml

import numpy as np
cimport numpy as np

# For Buffer usage
cdef extern from "Python.h":
    ctypedef struct PyObject
    object PyMemoryView_FromBuffer(Py_buffer *view)
    int PyBuffer_FillInfo(Py_buffer *view, PyObject *obj, void *buf, Py_ssize_t len, int readonly, int infoflags)
    enum:
        PyBUF_FULL_RO

cdef extern from "pico_zense_module_for_serial.hpp" namespace "zense":
    cdef cppclass PicoZenseModuleForSerial:
        PicoZenseModuleForSerial(uint32_t sensor_idx_)except +
        string getSerialNumber()
        string getSerialNumber(string uri_string)
        vector[double] getCameraParameter()
        vector[double] getRGBCameraParameter()
        vector[vector[double]] getExtrinsicParameter()
        uint32_t getDeviceCount()
        void closeDevice()

cdef class PyPicoZenseModuleForSerial:
    cdef PicoZenseModuleForSerial *thisptr

    def __cinit__(self, sensor_idx_):
        self.thisptr = new PicoZenseModuleForSerial(sensor_idx_)

    #def __dealloc__(self):
    #    del self.thisptr

    def close(self):
        self.thisptr.closeDevice()

    def getSerialNumber(self):
        return self.thisptr.getSerialNumber()

    def getSerialNumberWithURI(self, uri_string):
        return self.thisptr.getSerialNumber(uri_string)

    def getDeviceCount(self):
        return self.thisptr.getDeviceCount()

    def getCameraParameter(self):
        return self.thisptr.getCameraParameter()

    def getRGBCameraParameter(self):
        return self.thisptr.getRGBCameraParameter()

    def getExtrinsicParameter(self):
        return self.thisptr.getExtrinsicParameter()
