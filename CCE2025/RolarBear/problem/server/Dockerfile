FROM debian:bookworm-slim

ARG DOCKER_GID
ARG HOST_ROOT

RUN apt-get update && apt-get install -y openssh-server ca-certificates curl

RUN install -m 0755 -d /etc/apt/keyrings
RUN curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
RUN chmod a+r /etc/apt/keyrings/docker.asc

RUN echo \
"deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian \
$(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
tee /etc/apt/sources.list.d/docker.list > /dev/null

RUN apt-get update && apt-get install -y docker-ce-cli

RUN mkdir /run/sshd

COPY ./shared/sshd_config /etc/ssh/sshd_config
COPY ./shared/authorized_keys /etc/ssh/authorized_keys
COPY ./shared/motd /etc/motd

RUN chmod 600 /etc/ssh/authorized_keys

WORKDIR /chall

COPY ./shared/run.sh /chall/run.sh

RUN echo "HOST_ROOT=${HOST_ROOT}" >> /etc/environment
RUN chmod +x run.sh

RUN useradd -u 1000 -d / -s /chall/run.sh user
RUN usermod -p '*' user
RUN chown -R user:user /chall
RUN chown user:user /etc/ssh/authorized_keys
RUN groupadd -g $DOCKER_GID docker
RUN usermod -aG docker user

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config"]