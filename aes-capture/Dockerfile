FROM ubuntu:bionic

RUN apt-get update && \
    apt-get install -y debconf-utils && \
    echo 'libssl1.1 libssl1.1/restart-services string' | debconf-set-selections && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
        python3 \
        python3-pip \
        libusb-dev \
        make \
        avr-libc \
        wget \
        gcc-avr && \
    wget https://mirrors.kernel.org/ubuntu/pool/universe/n/newlib/libnewlib-dev_3.0.0.20180802-2_all.deb && \
    wget https://mirrors.kernel.org/ubuntu/pool/universe/n/newlib/libnewlib-arm-none-eabi_3.0.0.20180802-2_all.deb && \
    dpkg -i libnewlib-arm-none-eabi_3.0.0.20180802-2_all.deb libnewlib-dev_3.0.0.20180802-2_all.deb