#!/bin/sh

docker rm -f contract
docker rmi -f contract

docker build -t contract .
docker run -d --name contract contract tail -f /dev/null

docker rm -f contract