from pwn import *

port =  9817
rem = remote("srv1.kitriwhs.kr", port)

elf = ELF('./WHS/a piece of pie/problem/a_piece_of_pie')
print(elf.address)
print(elf.symbols["gadget"])

elf.address = 5000

print(elf.address)
print(elf.symbols["gadget"])

# rem.sendlineafter(b"name: ", b"A" * 0xa0)
# print(rem.recvline())

# rem.sendlineafter(b"1: ", b"A")
# print(rem.recvline())
# rem.sendlineafter(b"2: ", b"A")
# print(rem.recvline())
# rem.sendlineafter(b"3: ", b"A")
