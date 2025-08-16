FROM ubuntu@sha256:4f1db91d9560cf107b5832c0761364ec64f46777aa4ec637cca3008f287c975e

ENV user book
ENV chall_port 12345

RUN apt-get update
RUN apt-get -y install socat adduser

RUN adduser -u 1234 $user

ADD ./deploy/prob /home/$user/prob
ADD ./deploy/run.sh /home/$user/run.sh
ADD ./deploy/flag /home/$user/flag

RUN chown root:$user /home/$user/

RUN chmod 755 /home/$user/prob
RUN chmod +x /home/$user/run.sh
RUN chmod 444 /home/$user/flag

WORKDIR /home/$user
EXPOSE $chall_port
CMD socat TCP-LISTEN:$chall_port,reuseaddr,fork EXEC:./run.sh,stderr

