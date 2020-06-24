from distutils.core import setup, Extension
from Cython.Build import cythonize
from Cython.Distutils import build_ext
import numpy
import sys
import os
import glob
import pdb
import pkgconfig

zense_cflags = pkgconfig.cflags('libpicozense')
zense_libs = pkgconfig.libs('libpicozense')

opencv_cflags = pkgconfig.cflags('opencv').split()
cvlibs_string = pkgconfig.libs('opencv')
cvinclude = [str('{}'.format(elem.split('-I')[-1])) for elem in opencv_cflags]

lib_dirs = []
cvlibs = list()
cvlibs_pkgcfg_list = cvlibs_string.split()
for elem in cvlibs_pkgcfg_list:
    # like u'-L/usr/local/lib'
    if elem.startswith("-L"):
        lib_dirs.append(str('{}'.format(elem.split('-L')[-1])))
    # like u'-lopencv_stitching'
    elif elem.startswith("-l"):
        _cvlib = 'opencv_{}'.format(elem.split('-lopencv_')[-1])
        cvlibs.append(_cvlib)
    else:
        pass

setup(
    name="zense_pywrapper_for_serial",

    version='1.0.0',
    description='serial number getter for zense',
    author='yuki yoshikawa',

    ext_modules=cythonize(
        [
            Extension("zense_pywrapper_for_serial",
                      sources=["src/zense_pywrapper_for_serial.pyx",
                               "src/pico_zense_module_for_serial.cpp"],
                      extra_compile_args=["-std=gnu++11",
                                          "-O3", zense_cflags, zense_libs],
                      include_dirs=[numpy.get_include()] + cvinclude,
                      library_dirs=lib_dirs,
                      libraries=cvlibs + ["picozense_api"],
                      language="c++",
                      )
        ]
    ),
    cmdclass={'build_ext': build_ext},
)
