from pwn import *

elf = ELF("./Pwnable/pizza/problem/pizza")

print(elf.symbols['main'])