#!/bin/sh

if [ `whoami` != root ]; then
    echo Please run this script with sudo
    exit
fi

ORIG_PATH=`pwd`
USER_LOCAL=`echo $ORIG_PATH | sed -r "s/^\/home\/?([^\/]*).*$/\1/"`

ln -s `find /home/${USER_LOCAL}/Libraries -name PicoZenseSDK` /usr/local/PicoZenseSDK
ln -sf $(pkg-config --libs-only-L libpicozense | sed 's/^-L//')/* /usr/local/lib/
