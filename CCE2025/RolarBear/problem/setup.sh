#!/bin/sh

DOCKER_GID=$(getent group docker | cut -d: -f3) HOST_ROOT=$(pwd) docker compose up -d --build