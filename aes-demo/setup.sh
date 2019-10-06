#!/bin/bash
sudo apt-get update && sudo apt-get upgrade -y && \
sudo apt-get install -y \
    python3 \
    python3-pip \
    libusb-dev \
    make \
    avr-libc \
    gcc-avr

wget https://mirrors.kernel.org/ubuntu/pool/universe/n/newlib/libnewlib-dev_3.0.0.20180802-2_all.deb
wget https://mirrors.kernel.org/ubuntu/pool/universe/n/newlib/libnewlib-arm-none-eabi_3.0.0.20180802-2_all.deb
sudo dpkg -i libnewlib-arm-none-eabi_3.0.0.20180802-2_all.deb libnewlib-dev_3.0.0.20180802-2_all.deb