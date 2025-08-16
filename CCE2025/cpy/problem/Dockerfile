FROM ubuntu:24.04

RUN apt-get clean
RUN rm -r /var/lib/apt/lists/*
RUN apt update -o Acquire::CompressionTypes::Order::=gz
RUN apt update -y && apt upgrade -y
RUN apt install -y coreutils binutils

ENV PATH="${PATH}:/home/ctf/prob/bin"
ENV PYTHONPATH="/home/ctf/prob/lib/python3.13/site-packages"
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1
ENV PYTHON_OPT_LEVEL=1

RUN useradd --create-home --shell /bin/bash ctf

WORKDIR /home/ctf

ADD ./prob /home/ctf

RUN chmod +x bridge.py
RUN chmod +x ynetd

WORKDIR /home/ctf
CMD ./ynetd -p 31337 "timeout 60 ./prob/bin/python3 bridge.py"