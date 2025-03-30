FROM amd64/ubuntu:22.04

RUN dpkg --add-architecture i386
RUN apt-get update && apt-get install -y socat libc6:i386

RUN adduser --no-create-home --disabled-login --gecos '' -- "gaia" && mkdir -p "/home/gaia"

COPY --chown=gaia:gaia chall /home/gaia/
COPY --chown=gaia:gaia flag.txt /home/gaia/

RUN chmod 750 "/home/gaia/chall" && chmod 750 "/home/gaia/flag.txt"

ENV LANG C.UTF-8
ENV TERM linux

WORKDIR /home/gaia
EXPOSE 28966/tcp
CMD ["socat", "TCP-LISTEN:28966,reuseaddr,fork", "EXEC:/home/gaia/chall,nofork,stderr,setsid,su=gaia"]
