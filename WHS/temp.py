from pwn import *

print("B"*0x100)

elf = ELF('./WHS/a piece of pie/problem/a_piece_of_pie')
base_to_gadget = elf.symbols["gadget"]
print(base_to_gadget)