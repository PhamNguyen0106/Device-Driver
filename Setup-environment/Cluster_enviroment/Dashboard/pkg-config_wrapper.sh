#!/bin/sh
PKG_CONFIG_SYSROOT_DIR=/home/tma/raspi3/sysroot
export PKG_CONFIG_SYSROOT_DIR
PKG_CONFIG_LIBDIR=/home/tma/raspi3/sysroot/usr/lib/pkgconfig:/home/tma/raspi3/sysroot/usr/share/pkgconfig:/home/tma/raspi3/sysroot/usr/lib/arm-linux-gnueabihf/pkgconfig
export PKG_CONFIG_LIBDIR
exec pkg-config "$@"
