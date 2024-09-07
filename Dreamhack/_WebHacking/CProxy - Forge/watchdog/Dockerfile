FROM python:3.10-alpine@sha256:3bfac1caa31cc6c0e796b65ba936f320d1e549d80f5ac02c2e4f83a0f04af3aa

ENV USER watchdog

# Change tmp permissions
RUN chmod 1733 /tmp /var/tmp /dev/shm

# Install requirements
RUN pip install --no-cache-dir requests

# Add user
RUN adduser -D -g "" $USER \
 && chown -R root:root /home/$USER

# Add files
COPY --chown=root:$USER . /home/$USER/

# chown & chmod files
WORKDIR /home/$USER
RUN chmod 550 check.py \
 && chmod 440 pw flag_poison

# Run server
WORKDIR /home/$USER/
CMD while :; do sleep 7; ./check.py; done
USER $USER
