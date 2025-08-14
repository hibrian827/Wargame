from pwn import *

context.terminal = ['tmux', 'new-window']

success = lambda name, addr: log.success(f"{name}: {hex(addr)}")

env = {"LD_PRELOAD": "/home/hibrian827/Wargame/Dreamhack/Pwnable/iofile_vtable_check/problem/libc.so.6"}
rem = process("./Pwnable/iofile_vtable_check/problem/iofile_vtable_check", env=env)

# elf = ELF("./Pwnable/iofile_vtable_check/problem/iofile_vtable_check")
# lib = ELF("./Pwnable/iofile_vtable_check/problem/libc.so.6")

# rem.recvuntil(b"stdout: ")
# stdout_addr = int(rem.recvn(14).decode(), 16)
# lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']

# success("lib base", lib_base)

rem.interactive()