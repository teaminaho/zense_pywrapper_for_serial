from distutils.core import setup, Extension
from Cython.Build import cythonize
from Cython.Distutils import build_ext
import numpy
import sys
import os
import glob
import pdb

ZENSE_LIB_DIR = "/home/{}/Libraries/PicoZenseSDK/Lib/x64".format(os.environ.get('USER'))
ZENSE_INCLUDE_DIR = "/home/{}/Libraries/PicoZenseSDK/Include".format(os.environ.get('USER'))

cvlib_folder = os.path.join(sys.prefix,'local', 'lib')
lib_dirs = [cvlib_folder, ZENSE_LIB_DIR]

cvlibs = list()
for file in glob.glob(os.path.join(cvlib_folder, 'libopencv_*')):
    cvlibs.append(file.split('.')[0])
cvlibs = list(set(cvlibs))
cvlibs = ['opencv_{}'.format(lib.split(os.path.sep)[-1].split('libopencv_')[-1]) for lib in cvlibs]

setup(
    name = "zense_pywrapper_for_serial",

    version='1.0.0',
    description='serial number getter for zense',
    author='yuki yoshikawa',

    ext_modules = cythonize(
                 [
                    Extension("zense_pywrapper_for_serial",
                        sources=["src/zense_pywrapper_for_serial.pyx", "src/pico_zense_module_for_serial.cpp"],
                        extra_compile_args=["-std=gnu++11", "-O3"],
                        include_dirs=[numpy.get_include(), ZENSE_INCLUDE_DIR],
                        library_dirs=lib_dirs,
                        libraries= cvlibs + ["picozense_api"],
                        language="c++",
                    )
                 ]
    ),
    cmdclass = {'build_ext': build_ext},
)
