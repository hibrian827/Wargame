from pwn import *

context.terminal = ['tmux', 'new-window']

success = lambda name, addr: log.success(f"{name}: {hex(addr)}")

ld = "/home/hibrian827/Wargame/Dreamhack/Pwnable/toxic_malloc/problem/deploy/ld-linux-x86-64.so.2"
env = {"LD_PRELOAD": "/home/hibrian827/Wargame/Dreamhack/Pwnable/toxic_malloc/problem/deploy/libc.so.6"}
rem = process([ld, "./Pwnable/toxic_malloc/problem/deploy/chall"], env=env)