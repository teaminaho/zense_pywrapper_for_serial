The python wrapper moduel to get serial number of DCAM710

# Installation

## Without Docker
1. Install SDK(version v3.0.1.0) of DCAM710
https://github.com/Vzense/Vzense_SDK_Linux

2. Install dependencies(--user is optional)
```
pip install --user -r requirements.txt
```

3. Install zense_pywrapper_for_serial (--user is optional)
```
python setup.py install --user
```

## With Docker
1. Run Docker-build
```
make build
```
2. Get into the container
```
make run
```

# Usage(1)
```
In [1]: from zense_pywrapper_for_serial import PyPicoZenseModuleForSerial

In [2]: zns = PyPicoZenseModuleForSerial(0)
Detected 2 devices.
sensor_idx_:0
SERIAL : PD71A1DGD6260045P

In [3]: print(zns.getSerialNumber())
PD71A1DGD6260045P

In [4]: delete zns
    delete zns

In [5]: del zns
```

# Usage(2)
1. Change privilege of print_zense_serial.sh
```
cd ./scripts
chmod +x print_zense_serial.sh
```
2. Connect DCAM710 to PC, and confirm its LED is lightened
3. Run print_zense_serial.sh
```
./print_zense_serial.sh
```
4. Confirm outputs
```
inaho-04@inaho04-NUC7i7DNKE:~/tmp/zense_pywrapper_for_serial/scripts$ ./print_zense_serial.sh 
Detected 1 devices.
sensor_idx_:0
libva info: VA-API version 1.1.0
libva info: va_getDriverName() returns 0
libva info: Trying to open /usr/lib/x86_64-linux-gnu/dri/i965_drv_video.so
libva info: Found init function __vaDriverInit_1_1
libva info: va_openDriver() returns 0
SERIAL : PD71A1EGD8280137P
```
