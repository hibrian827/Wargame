from pwn import *

rem = process("./Pwnable/pizza/problem/pizza")
gdb.attach(rem)

elf = ELF("./Pwnable/pizza/problem/pizza")

rem.sendlineafter(b"name > ", b"test")

rem.interactive()

# print(elf.symbols)