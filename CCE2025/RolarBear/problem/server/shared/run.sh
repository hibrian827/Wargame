#!/bin/sh

MAX_PROCS=64

if [ -f /etc/environment ]; then
    . /etc/environment
fi

timeout --foreground 10m \
    docker run \
    --volume $HOST_ROOT/server/shared/flag:/home/rolarbear/flag:ro \
    --memory=2g \
    -it \
    --rm \
    app:latest
