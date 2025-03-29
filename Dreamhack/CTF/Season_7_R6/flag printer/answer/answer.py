from pwn import *

port = 21647
rem = remote("host3.dreamhack.games", port)

payload = b""
ans = b"&-17"
for b in ans:
  payload += bytes([int(b) ^ 0x42])

payload += b" print"
print(payload)
rem.sendlineafter(b"> ", payload)
print(rem.recvline())