FROM ubuntu:24.04@sha256:7c06e91f61fa88c08cc74f7e1b7c69ae24910d745357e0dfe1d2c0322aaf20f9

ENV user myblog
ENV chall_port 8080

RUN apt-get update
RUN apt-get -y install socat adduser

RUN adduser -u 8080 $user

ADD ./deploy/prob /home/$user/prob
ADD ./deploy/run.sh /home/$user/run.sh

RUN chown root:$user /home/$user/

RUN chmod 755 /home/$user/prob
RUN chmod +x /home/$user/run.sh

WORKDIR /home/$user
EXPOSE $chall_port
CMD socat TCP-LISTEN:$chall_port,reuseaddr,fork EXEC:"./run.sh",pty,raw,echo=0,stderr