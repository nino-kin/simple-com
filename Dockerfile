FROM ubuntu:20.04

ENV TZ=Asia/Tokyo
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get -y install \
    git \
    build-essential \
    cmake \
    libcurl4-openssl-dev \
    libpthread-stubs0-dev \
    python3.8 python3-pip python3-venv \
    jq

# You can be overridden by the command "--build-arg WORK_DIR=$YOUR_WORKDIR".
ARG WORK_DIR=/app
WORKDIR $WORK_DIR

# Add group and user
ARG HOST_UID
ARG HOST_GID
RUN groupadd -g $HOST_GID mygroup && \
    useradd -u $HOST_UID -g $HOST_GID -ms /bin/bash myuser
USER myuser

CMD ["bash"]
