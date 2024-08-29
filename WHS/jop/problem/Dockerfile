FROM ubuntu:22.04@sha256:b6b83d3c331794420340093eb706a6f152d9c1fa51b262d9bf34594887c2c7ac

RUN apt-get update && apt-get install -y socat

RUN adduser pwn

WORKDIR /home/pwn

COPY ./flag ./flag
COPY ./deploy/prob ./prob
COPY ./deploy/run.sh ./run.sh

RUN chmod 644 ./flag 
RUN chmod 755 ./prob
RUN chmod 755 ./run.sh

USER pwn

EXPOSE 8080
CMD socat TCP-LISTEN:8080,reuseaddr,fork EXEC:./run.sh,stderr
