FROM ubuntu:24.04@sha256:440dcf6a5640b2ae5c77724e68787a906afb8ddee98bf86db94eea8528c2c076

RUN apt update && apt install -y adduser python3 libpixman-1-dev libglib2.0-0t64
RUN adduser rolarbear

ADD deploy/ /home/rolarbear/
RUN chmod +x /home/rolarbear/run.sh
RUN chmod +x /home/rolarbear/exec-qemu.sh

WORKDIR /home/rolarbear
CMD ["/home/rolarbear/run.sh"]