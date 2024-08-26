FROM alpine@sha256:0a4eaa0eecf5f8c050e5bba433f58c052be7587ee8af3e8b3910ef9ab5fbe9f5

RUN apk add --no-cache openssh-client openssh-server shadow

RUN adduser -D -u 1001 flaguser
RUN echo "flaguser:secretpassword1!" | chpasswd

RUN ssh-keygen -A
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin no/' /etc/ssh/sshd_config
RUN echo "AllowUsers flaguser" >> /etc/ssh/sshd_config
RUN sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config
RUN sed -i 's/AllowTcpForwarding no/AllowTcpForwarding yes/' /etc/ssh/sshd_config
RUN echo "flag{dummy_flag}" > /home/flaguser/flag.txt

WORKDIR /home/flaguser/

CMD ["/usr/sbin/sshd", "-D", "-e"]