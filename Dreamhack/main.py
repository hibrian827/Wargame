from pwn import *

rem = process("./Pwnable/__environ/problem/environ")

rem.recvuntil(b'stdout: ')

stdout_addr = int(rem.recvn(14), 16)