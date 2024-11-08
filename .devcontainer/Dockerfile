FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update

# install cmake version 3.28.1
RUN apt-get install -y build-essential
RUN apt-get install -y libtool
RUN apt-get install -y autoconf
RUN apt-get install -y unzip
RUN apt-get install -y wget
RUN apt-get install -y openssl
RUN apt-get install -y libssl-dev

COPY ./docker/scripts/install-cmake-3.28.1.sh /root/scripts/
RUN bash /root/scripts/install-cmake-3.28.1.sh
RUN ln -s /usr/local/bin/cmake /usr/bin/cmake
RUN apt-get install -y gdb

# GStreamer Project dependencies
RUN apt-get install -y libboost-all-dev

# Install git
RUN apt-get install -y git

# Run the installation script
RUN bash scripts/install.sh
