#!/bin/bash

docker rm -f contract
docker run -d -p 12455:12455 --name contract --restart unless-stopped --privileged contract