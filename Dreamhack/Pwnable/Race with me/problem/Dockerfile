FROM ubuntu:22.04@sha256:2b7412e6465c3c7fc5bb21d3e6f1917c167358449fecac8176c6e496e5c1f05f

# 환경 변수 설정
ENV user race
ENV chall_port 5000

RUN apt-get update && apt-get -y install socat
RUN adduser $user

ADD ./deploy/flag /home/$user/flag
ADD ./deploy/chall /home/$user/chall

RUN chown root:$user /home/$user/flag
RUN chown root:$user /home/$user/chall

RUN chmod 755 /home/$user/chall
RUN chmod 440 /home/$user/flag

WORKDIR /home/$user
USER $user
EXPOSE $chall_port
CMD socat -T 90 TCP-LISTEN:$chall_port,reuseaddr,fork EXEC:/home/$user/chall
