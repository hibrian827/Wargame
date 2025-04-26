#!/bin/bash
set -e

IMAGE_NAME=zip
CONTAINER_NAME=zip

docker rm -f ${CONTAINER_NAME} 2>/dev/null || true
docker rmi -f ${IMAGE_NAME} 2>/dev/null || true

echo "Building Docker image..."
docker build --platform linux/amd64 \
    -t ${IMAGE_NAME} --load .
