#!/bin/bash
#
cd /home/find_candy
exec 2>/dev/null
timeout 120 /home/find_candy/find_candy
