from pwn import *

context.terminal = ['tmux', 'new-window']

success = lambda name, addr: log.success(f"{name}: {hex(addr)}")

env = {"LD_PRELOAD": "/home/hibrian827/Wargame/Dreamhack/Pwnable/Heap_Basic_1/problem/deploy/libc-2.31.so"}
ld = "/home/hibrian827/Wargame/Dreamhack/Pwnable/Heap_Basic_1/problem/deploy/ld-linux-x86-64.so.2"
rem = process([ld, "./Pwnable/Heap_Basic_1/problem/deploy/prob"], env=env)

gdb.attach(rem)

rem.interactive()