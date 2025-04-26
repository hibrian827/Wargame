#!/bin/bash
set -e

IMAGE_NAME=zip
CONTAINER_NAME=zip

docker rm -f ${CONTAINER_NAME} || true
docker run --platform linux/amd64 -d -p 9999:9999 --name ${CONTAINER_NAME} --restart unless-stopped --privileged ${IMAGE_NAME}
