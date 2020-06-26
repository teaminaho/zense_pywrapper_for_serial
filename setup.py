from distutils.core import setup, Extension
from Cython.Build import cythonize
from Cython.Distutils import build_ext
import os
import numpy
import pkgconfig
import glob

zense_cflags = pkgconfig.cflags('libpicozense')
zense_libs = pkgconfig.libs('libpicozense')

zense_install_dir = os.environ["PICOZENSE_INSTALL_DIR"]
cvlibs_folder = os.path.join(
    zense_install_dir,
    'Thirdparty', 'opencv-3.4.1', 'lib'
)

cvinclude = os.path.join(
    zense_install_dir,
    'Thirdparty', 'opencv-3.4.1', 'include'
)

lib_dirs = [cvlibs_folder]

cvlibs = list()
for file in glob.glob(os.path.join(cvlibs_folder, 'libopencv_*.so')):
    cvlibs.append(os.path.basename(file).split('.')[0])
cvlibs = list(set(cvlibs))
cvlibs = ['opencv_{}'.format(
    lib.split(os.path.sep)[-1].split('libopencv_')[-1]) for lib in cvlibs]

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
                      extra_compile_args=[
                          "-std=gnu++11",
                          "-O3",
                          zense_cflags,
                          zense_libs,
                          "-w"
                      ],
                      include_dirs=[numpy.get_include(), cvinclude],
                      library_dirs=lib_dirs,
                      libraries=cvlibs + ["vzense_api", "ImgPreProcess"],
                      language="c++",
                      )
        ]
    ),
    cmdclass={'build_ext': build_ext},
)
