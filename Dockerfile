FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive

RUN sed -i -r 's|(archive\|security)\.ubuntu\.com/|ftp.jaist.ac.jp/pub/Linux/|' /etc/apt/sources.list && \
    apt-get update && apt-get upgrade -y && \
    apt-get install -y build-essential apt-utils ca-certificates \
    cmake git pkg-config software-properties-common \
    libswscale-dev wget autoconf automake unzip curl \
    python-dev python-pip libavcodec-dev libavformat-dev libgtk2.0-dev libv4l-dev &&\
    # SDK dependency
    add-apt-repository ppa:nilarimogard/webupd8 && \
    apt-get update && apt-get install -y libvdpau-va-gl1 i965-va-driver vdpauinfo && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

ENV PICOZENSE_INSTALL_DIR=/usr/local/PicoZenseSDK
ENV PICOZENSE_LIB="Vzense_SDK_linux/Ubuntu18.04"

#RUN echo "--- installing zense sdk ---"
COPY . /app
RUN mkdir -p /etc/udev/rules.d
RUN git clone https://github.com/Vzense/Vzense_SDK_linux.git
RUN ./install_zense_sdk.sh

RUN apt-get update && \
    apt -y install emacs \
    wget \
    git \
    libssl-dev \
    libbz2-dev \
    libsqlite3-dev \
    libreadline-dev \
    zlib1g-dev \
    libasound2-dev \
    libxss1 \
    libxtst6 \
    gdebi
RUN wget -O vscode-amd64.deb https://go.microsoft.com/fwlink/?LinkID=760868
RUN yes | gdebi vscode-amd64.deb
RUN rm vscode-amd64.deb

CMD [ /bin/bash ]