FROM alpine@sha256:0a4eaa0eecf5f8c050e5bba433f58c052be7587ee8af3e8b3910ef9ab5fbe9f5

RUN apk add --no-cache openssh-client openssh-server shadow

RUN adduser -D -u 1001 ctfuser
RUN sed -i 's/ctfuser:!/ctfuser:*/' /etc/shadow

RUN ssh-keygen -A
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin no/' /etc/ssh/sshd_config
RUN sed -i 's/#PubkeyAuthentication yes/PubkeyAuthentication yes/' /etc/ssh/sshd_config
RUN sed -i 's/#PasswordAuthentication yes/PasswordAuthentication no/' /etc/ssh/sshd_config
RUN sed -i 's/AllowTcpForwarding no/AllowTcpForwarding yes/' /etc/ssh/sshd_config
RUN echo "AllowUsers ctfuser" >> /etc/ssh/sshd_config

RUN mkdir -p /home/ctfuser/.ssh
COPY ./src/ssh_keys/id_rsa.pub /home/ctfuser/.ssh/authorized_keys
RUN chmod 700 /home/ctfuser/.ssh
RUN chmod 600 /home/ctfuser/.ssh/authorized_keys
RUN chown -R ctfuser:ctfuser /home/ctfuser/.ssh

RUN echo '#!/bin/sh' > /usr/local/bin/restricted_shell
RUN echo 'echo "This is a restricted shell. You can'"'"'t execute commands."' >> /usr/local/bin/restricted_shell
RUN echo 'while true; do' >> /usr/local/bin/restricted_shell
RUN echo '  read -p "$ " cmd' >> /usr/local/bin/restricted_shell
RUN echo '  echo "Command execution is not allowed."' >> /usr/local/bin/restricted_shell
RUN echo 'done' >> /usr/local/bin/restricted_shell
RUN chmod +x /usr/local/bin/restricted_shell

RUN chsh -s /usr/local/bin/restricted_shell ctfuser

RUN chmod 755 /home/ctfuser

COPY ./src/intserver/dari11.jpg /home/ctfuser/dari11.jpg
COPY ./src/intserver/dari22.jpg /home/ctfuser/dari22.jpg
COPY ./src/intserver/dari33.jpg /home/ctfuser/dari33.jpg
COPY ./src/intserver/flagserver_password.txt /home/ctfuser/flagserver_password.txt

CMD ["/usr/sbin/sshd", "-D", "-e"]