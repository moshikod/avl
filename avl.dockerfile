ARG TARGET=demo
FROM ubuntu:latest

RUN export DEBIAN_FRONTEND=noninteractive && apt-get -y update && apt-get -y install \
    cmake \
    g++ \
    locales \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

RUN locale-gen en_US.UTF-8 && update-locale
ENV LC_ALL='en_US.UTF-8'
ENV LANG='en_US.UTF-8'
ENV LANGUAGE='en_US.UTF-8'

ARG TARGET
COPY . /usr/src/avl
WORKDIR /usr/src/avl
RUN make TARGET=${TARGET}
ENV TARGET_APP=./${TARGET}
CMD ${TARGET_APP}
