from pwn import *
from ctypes import *

port = 8636
rem = remote("host3.dreamhack.games", port)
dll = CDLL("/lib/x86_64-linux-gnu/libc.so.6")

dll.srand(dll.time(0))
for i in range(10) :
  num = dll.rand()
  if num % 3 == 0:
    payload = b"P"
  if num % 3 == 1:
    payload = b"S"
  if num % 3 == 2:
    payload = b"R"
  rem.sendlineafter(b"(R, P, S): ", payload)

rem.recvuntil(b"Flag is ")
print(rem.recvline().rstrip())
    