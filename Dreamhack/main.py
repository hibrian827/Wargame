from pwn import *

context.terminal = ['tmux', 'new-window']

success = lambda name, addr: log.success(f"{name}: {hex(addr)}")

env = {"LD_PRELOAD": "/home/hibrian827/Wargame/Dreamhack/Pwnable/iofile_vtable_check/problem/libc.so.6"}
rem = process("./Pwnable/iofile_vtable_check/problem/iofile_vtable_check", env=env)