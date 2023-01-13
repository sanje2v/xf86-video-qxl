FROM ubuntu:22.04
ARG HOST_UID=1000
ARG HOST_NAME=dev
ARG DEBIAN_FRONTEND=noninteractive

USER root
WORKDIR /root

RUN apt update && apt upgrade -y
RUN apt install -y build-essential make cmake autoconf
RUN apt install -y xutils-dev pkg-config libtool xorg-dev libspice-protocol-dev libspice-server-dev git
RUN apt install -y nano sudo
RUN apt autoremove -y

# Create dev user and disable asking for its password when trying to use 'sudo ...'
RUN useradd --create-home --uid ${HOST_UID} --groups cdrom,audio,video,plugdev,users,dialout,dip,sudo --user-group ${HOST_NAME}
RUN echo "${HOST_NAME} ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

USER ${HOST_NAME}
WORKDIR /home/${HOST_NAME}
