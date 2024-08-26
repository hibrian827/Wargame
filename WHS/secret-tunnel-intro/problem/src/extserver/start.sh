#!/bin/sh

/usr/sbin/sshd
su - appuser -c "source /home/appuser/venv/bin/activate && python3 /home/appuser/app/app.py"