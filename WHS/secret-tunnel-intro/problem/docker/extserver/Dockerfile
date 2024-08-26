FROM alpine@sha256:0a4eaa0eecf5f8c050e5bba433f58c052be7587ee8af3e8b3910ef9ab5fbe9f5

RUN apk add --no-cache python3 py3-pip openssh-client openssh-server shadow

RUN adduser -D -u 1001 appuser
RUN sed -i 's/appuser:!/appuser:*/' /etc/shadow

RUN mkdir -p /home/appuser/.ssh
COPY ./src/ssh_keys/id_rsa /home/appuser/.ssh/id_rsa
COPY ./src/ssh_keys/id_rsa.pub /home/appuser/.ssh/id_rsa.pub
RUN chmod 700 /home/appuser/.ssh
RUN chmod 600 /home/appuser/.ssh/id_rsa
RUN chmod 644 /home/appuser/.ssh/id_rsa.pub

COPY ./src/ssh_keys/id_rsa.pub /home/appuser/.ssh/authorized_keys
RUN chmod 700 /home/appuser/.ssh
RUN chmod 600 /home/appuser/.ssh/authorized_keys
RUN chown -R appuser:appuser /home/appuser/.ssh

COPY ./src/extserver/scp_transfer.sh /home/appuser/scp_transfer.sh
RUN chmod +x /home/appuser/scp_transfer.sh
RUN chown appuser:appuser /home/appuser/scp_transfer.sh

RUN ssh-keygen -A
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin no/' /etc/ssh/sshd_config
RUN sed -i 's/#PubkeyAuthentication yes/PubkeyAuthentication yes/' /etc/ssh/sshd_config
RUN sed -i 's/#PasswordAuthentication yes/PasswordAuthentication no/' /etc/ssh/sshd_config
RUN sed -i 's/AllowTcpForwarding no/AllowTcpForwarding yes/' /etc/ssh/sshd_config
RUN echo "AllowUsers appuser" >> /etc/ssh/sshd_config

ENV VIRTUAL_ENV=/home/appuser/venv
RUN python3 -m venv $VIRTUAL_ENV
ENV PATH="$VIRTUAL_ENV/bin:$PATH"

WORKDIR /home/appuser/app

COPY ./src/extserver/requirements.txt /home/appuser/app/
RUN pip3 install -r requirements.txt

COPY ./src/extserver/app.py /home/appuser/app/

RUN chown -R appuser:appuser /home/appuser/app

echo "flag{dummy_flag_1}" > /home/appuser/flag.txt

EXPOSE 8090 22

COPY ./src/extserver/start.sh /start.sh
RUN chmod +x /start.sh
RUN chown appuser:appuser /start.sh

CMD ["/start.sh"]