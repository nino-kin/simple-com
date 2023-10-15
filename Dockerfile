FROM ubuntu:20.04

ENV TZ=Asia/Tokyo
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get -y install \
    git \
    build-essential \
    cmake \
    libcurl4-openssl-dev \
    libpthread-stubs0-dev \
    python3.8 python3-pip python3-venv

WORKDIR /app

CMD ["bash"]
