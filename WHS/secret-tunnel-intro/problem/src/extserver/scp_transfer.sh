#!/bin/sh
SRC_FILE=$1
DEST_FILE=$2

scp -v -i /home/appuser/.ssh/id_rsa -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null ctfuser@intserver:$SRC_FILE $DEST_FILE