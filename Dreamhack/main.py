from pwn import *

# context.terminal = ['tmux', 'new-window']

success = lambda name, addr: log.success(f"{name}: {hex(addr)}")

env = {"LD_PRELOAD": "/home/hibrian827/Wargame/Dreamhack/Holymoly/problem/libc-2.31.so"}
rem = process("./Pwnable/Holymoly/problem/holymoly")