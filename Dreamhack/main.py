from pwn import *

env = {"LD_PRELOAD": "/home/hibrian827/Wargame/Dreamhack/Pwnable/xrop/problem/deploy/libc.so.6"}
rem = process("./Pwnable/xrop/problem/deploy/prob", env=env)