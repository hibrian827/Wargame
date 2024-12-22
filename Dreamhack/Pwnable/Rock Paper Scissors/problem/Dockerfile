FROM ubuntu:24.04@sha256:d4f6f70979d0758d7a6f81e34a61195677f4f4fa576eaf808b79f17499fd93d1

RUN apt update
RUN apt-get install -y socat

WORKDIR /root

COPY ./flag ./flag
COPY ./deploy/chall ./chall

RUN chmod 644 ./flag
RUN chmod 755 ./chall

USER root

EXPOSE 8080
CMD socat TCP-LISTEN:8080,reuseaddr,fork EXEC:./chall,stderr
