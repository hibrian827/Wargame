FROM ubuntu:22.04@sha256:34fea4f31bf187bc915536831fd0afc9d214755bf700b5cdb1336c82516d154e

ARG DEBIAN_FRONTEND=noninteractive

ENV user cat_jump
ENV chall_port 31337
ENV TZ=Asia/Seoul

RUN apt-get update
RUN apt-get install -y \
    xinetd \
    tzdata

RUN ln -sf /usr/share/zoneinfo/Asia/Seoul /etc/localtime
RUN dpkg-reconfigure tzdata

RUN adduser $user

ADD ./deploy/xinetd /etc/xinetd.d/chall
ADD ./deploy/flag /home/$user/flag
ADD ./deploy/$user /home/$user/$user
ADD ./deploy/run.sh /home/$user/run.sh

RUN chown -R root:root /home/$user
RUN chown root:$user /home/$user/flag
RUN chown root:$user /home/$user/$user
RUN chown root:$user /home/$user/run.sh

RUN chmod 755 /home/$user
RUN chmod 755 /home/$user/$user
RUN chmod 440 /home/$user/flag
RUN chmod 755 /home/$user/run.sh

RUN service xinetd restart

WORKDIR /home/$user
USER $user
EXPOSE $chall_port
CMD ["/usr/sbin/xinetd", "-dontfork"]
