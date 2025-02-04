FROM ubuntu:20.04

RUN apt-get update && apt-get -y upgrade && \
    apt-get install -y cmake && \
    apt-get install -y vim && \
    apt-get install -y g++-10 && \
    apt-get install -y gcc-10 && \
    apt-get install -y libgtest-dev && \
    apt-get install -y libboost-all-dev && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 100 && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 100 

WORKDIR /usr/src/app

COPY . .

RUN mkdir -p /usr/src/app/build && cd /usr/src/app/build && \
    cmake -DCMAKE_BUILD_TYPE=Debug -DNTT=ON -DNTT_DEBUG=OFF .. && \
    make
