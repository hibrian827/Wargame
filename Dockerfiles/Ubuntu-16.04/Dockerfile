FROM ubuntu:16.04
 
ENV DEBIAN_FRONTEND=noninteractive
 
RUN dpkg --add-architecture i386
RUN apt-get -y update --fix-missing && apt-get -y upgrade
RUN apt-get -y install libc6:i386 libncurses5:i386 libstdc++6:i386
RUN apt-get -y install socat gdb git gcc vim
RUN apt-get -y install gcc-multilib
 
WORKDIR /root
RUN git clone https://github.com/pwndbg/pwndbg.git
WORKDIR /root/pwndbg
RUN ./setup.sh
WORKDIR /root
RUN git clone https://github.com/longld/peda.git ~/peda
RUN git clone https://github.com/scwuaptx/Pwngdb.git
RUN cp ./Pwngdb/.gdbinit ~/
 
RUN apt install -y netcat
RUN apt-get -y install tmux
RUN apt-get install -y python2.7-dev python-pip libssl-dev libffi-dev build-essential
RUN pip install pwntools
RUN apt-get -y install
