FROM ubuntu:22.04@sha256:aabed3296a3d45cede1dc866a24476c4d7e093aa806263c27ddaadbdce3c1054

ENV user=printer
ENV chall_port=31337

RUN apt-get update
RUN apt-get -y install socat

RUN adduser $user -u 1337

ADD ./deploy/flag /home/$user/flag
ADD ./deploy/art /home/$user/art
ADD ./deploy/flag-printer /home/$user/flag-printer

RUN chown root:$user /home/$user/flag
RUN chown root:$user /home/$user/art
RUN chown root:$user /home/$user/flag-printer

RUN chmod 755 /home/$user/flag-printer
RUN chmod 440 /home/$user/flag
RUN chmod 440 /home/$user/art

WORKDIR /home/$user
USER $user
EXPOSE $chall_port
CMD socat -T 25 TCP-LISTEN:$chall_port,reuseaddr,fork EXEC:/home/$user/flag-printer