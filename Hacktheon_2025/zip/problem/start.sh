#!/bin/bash

nsjail -Ml --port 9999 --user 99999 --group 99999 --time_limit 30 --chroot /jail -- zip
